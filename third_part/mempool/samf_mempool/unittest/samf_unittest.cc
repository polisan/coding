// Copyright 2010 Yunrang Inc. All Rights Reserved.
// Author: yanliangcui@yunrang.com (Yanliang Cui)

#include <string>
#include "third_part/testing/gtest/include/gtest/gtest.h"
#include "third_part/mempool/samf_mempool/public/samf_mempool.h"
#include "base/public/logging.h"

using namespace util::mempool;  // NOLINT

namespace util {
namespace mempool {
namespace samf_mempool_test {

class SamfUnittest: public testing::Test {
  public:
  protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

static const int kNumIter = 10;
static const int kAllocTimes = 10000;
static const int kItemSize = 16;
static const int kItemPerBlock = 1024;

uint64 tmdiff(const timeval& t1, const timeval& t2) {
  return (static_cast<uint64>(t2.tv_sec) * 1000000 + t2.tv_usec -
         (static_cast<uint64>(t1.tv_sec) * 1000000 + t1.tv_usec));
}

TEST_F(SamfUnittest, RawMallocAndFree) {
  timeval t1, t2;
  vector<void*> blocks;
  blocks.reserve(kAllocTimes * kItemPerBlock);
  uint64 total_alloc_tm = 0;
  uint64 total_free_tm = 0;
  for (int iter = 0; iter < kNumIter; ++iter) {
    gettimeofday(&t1, NULL);
    for (int i = 0; i < kAllocTimes * kItemPerBlock; ++i) {
      blocks.push_back(malloc(kItemSize));
    }
    gettimeofday(&t2, NULL);
    total_alloc_tm += tmdiff(t1, t2);
    gettimeofday(&t1, NULL);
    size_t size = blocks.size();
    for (int i = 0; i< size; ++i) {
      free(blocks[i]);
    }
    gettimeofday(&t2, NULL);
    total_free_tm += tmdiff(t1, t2);
    blocks.clear();
  }
  LOG(INFO) << "alloc time cost:" << total_alloc_tm;
  LOG(INFO) << "free time cost:" << total_free_tm;
}


TEST_F(SamfUnittest, MallocAndFreeWithMempool) {
  timeval t1, t2;
  SamfMempool mempool(kItemSize, kItemPerBlock, true);
  vector<void*> blocks;
  uint64 total_alloc_tm = 0;
  uint64 total_free_tm = 0;
  blocks.reserve(kAllocTimes);
  for (int iter = 0; iter < kNumIter; ++iter) {
    gettimeofday(&t1, NULL);
    for (int i = 0; i< kAllocTimes; ++i) {
      blocks.push_back(mempool.FetchBlock());
    }
    gettimeofday(&t2, NULL);
    total_alloc_tm += tmdiff(t1, t2);
    gettimeofday(&t1, NULL);
    for (int i = 0; i< blocks.size(); ++i) {
      mempool.FreeBlock(blocks[i]);
    }
    gettimeofday(&t2, NULL);
    total_free_tm += tmdiff(t1, t2);
    blocks.clear();
  }
  LOG(INFO) << "alloc time cost:" << total_alloc_tm;
  LOG(INFO) << "free time cost:" << total_free_tm;
}

TEST_F(SamfUnittest, MasfMallocAndFree) {
  LOG(INFO) << "start Test MasfMallocAndFree";
  timeval t1, t2;
  SamfMempool mempool(kItemSize, kItemPerBlock, true);
  vector<void*> blocks;
  blocks.reserve(kAllocTimes);
  uint64 total_alloc_tm = 0;
  uint64 total_free_tm = 0;
  for (int iter = 0; iter < kNumIter; ++iter) {
    // LOG(INFO) << iter << " " << kNumIter;
    gettimeofday(&t1, NULL);
    for (int i = 0; i< kAllocTimes; ++i) {
      // LOG(INFO) << i << " " << kAllocTimes;
      blocks.push_back(mempool.FetchBlock());
    }
    gettimeofday(&t2, NULL);
    total_alloc_tm += tmdiff(t1, t2);
    gettimeofday(&t1, NULL);
    size_t size = blocks.size();
    for (int i = 0; i < size; ++i) {
      // LOG(INFO) << i << " " << size;
      char *p = reinterpret_cast<char*>(blocks[i]);
      for (int item_idx = 0; item_idx < kItemPerBlock; ++item_idx) {
        mempool.FreeItem(p);
        p += kItemSize;
      }
    }
    gettimeofday(&t2, NULL);
    total_free_tm += tmdiff(t1, t2);
    blocks.clear();
  }
  LOG(INFO) << "alloc time cost:" << total_alloc_tm;
  LOG(INFO) << "free time cost:" << total_free_tm;
}

}  // namespace samf_mempool_test
}  // namespace ymempool
}  // namespace util