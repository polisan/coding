// Copyright 2010 Yunrang Inc. All Rights Reserved.
// Author: yanliangcui@yunrang.com (Yanliang Cui)
// 单线程多次分配一次释放的内存池

#ifndef UTIL_YMEMPOOL_MASF_MEMPOOL_MASF_MEMPOOL_H_
#define UTIL_YMEMPOOL_MASF_MEMPOOL_MASF_MEMPOOL_H_

#include <vector>
#include "base/public/logging.h"

namespace util {
namespace mempool {

class MasfMemUnittest;

const int kDftItemPerBlock = 64;
const float kDftBalanceFactor = 0.5;
const int kDftBalancePeriod = 100;

// 单线程固定大小内存池
// 功能：多次申请,集中释放,不提供单次释放功能
class SolidMempool {
 public:
  SolidMempool(size_t item_size,
               int item_per_block = kDftItemPerBlock,
               float balance_factor = kDftBalanceFactor,
               int balance_period = kDftBalancePeriod);
  virtual ~SolidMempool();

  void  Destroy();
  void *Malloc();
  virtual void Recycle();

  // for unittest
  size_t GetTotalSize() {
    return blocks_.size() * item_per_block_ * item_size_;
  }
  size_t GetUsedSize() {
    size_t block_size = item_per_block_ * item_size_;
    return block_idx_ * block_size + item_idx_ * item_size_;
  }

 protected:
  void AllocNewBlock();
  void BalancePool();

  std::vector<char *> blocks_;
  // param
  size_t item_size_;
  int item_per_block_;
  float inv_balance_factor_;
  int balance_period_;

  // runtime variables
  int item_idx_;
  int block_idx_;
  // for recycle
  uint32 next_balance_time_;
  uint64 max_used_per_period_;
};

// 单线程变长内存池,
// 功能：多次申请,集中释放,不提供单次释放功能
class MasfMempool {
 public:
  MasfMempool(int item_per_block = kDftItemPerBlock,
              float balance_factor = kDftBalanceFactor,
              int balance_period = kDftBalancePeriod);
  ~MasfMempool();
  void *Malloc(size_t size);
  void Recycle();

  void Create();
  void Destroy();

 private:
  friend class MasfMemUnittest;
  static const size_t kInitMaxSize = 1024*1024;
  std::vector<SolidMempool*> smp_;
  int max_size_;
  // param
  int item_per_block_;
  float balance_factor_;
  int balance_period_;
};

// 单线程对象内存池
// 功能：多次申请,集中释放,
// 可以单次delete,Delete只执行析构函数,不释放内存
// 申请的内存仍要等到Recycle()被调用时才会被释放：
template <class Type>
class MasfObjPool : public SolidMempool {
 public:
  MasfObjPool(int item_per_block = kDftItemPerBlock,
              float balance_factor = kDftBalanceFactor,
              int balance_period = kDftBalancePeriod)
              : SolidMempool(sizeof(Type),
                             item_per_block,
                             balance_factor,
                             balance_period) {
    debug_mem_count_ = 0;
  }
  virtual ~MasfObjPool() {}

  virtual void Recycle() {
    DCHECK_EQ(debug_mem_count_, 0);
    SolidMempool::Recycle();
  }

  Type *New() {
    ++debug_mem_count_;
    void *buf = Malloc();
    return new (buf) Type();
  }

  template <class Arg1>
  Type *New(Arg1 arg1) {
    ++debug_mem_count_;
    void *buf = Malloc();
    return new (buf) Type(arg1);
  }

  template <class Arg1, class Arg2>
  Type *New(Arg1 arg1, Arg2 arg2) {
    ++debug_mem_count_;
    void *buf = Malloc();
    return new (buf) Type(arg1, arg2);
  }

  template <class Arg1, class Arg2, class Arg3>
  Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3) {
    ++debug_mem_count_;
    void *buf = Malloc();
    return new (buf) Type(arg1, arg2, arg3);
  }

  template <class Arg1, class Arg2, class Arg3, class Arg4>
  Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) {
    ++debug_mem_count_;
    void *buf = Malloc();
    return new (buf) Type(arg1, arg2, arg3, arg4);
  }

  template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
  Type *New(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) {
    ++debug_mem_count_;
    void *buf = Malloc();
    return new (buf) Type(arg1, arg2, arg3, arg4, arg5);
  }

  void Delete(Type *obj) {
    --debug_mem_count_;
    obj->~Type();
  }
 private:
  int debug_mem_count_;
};

}  // namespace mempool
}  // namespace util

#endif  // UTIL_YMEMPOOL_MASF_MEMPOOL_MASF_MEMPOOL_H_