// Copyright 2013 Jike Inc. All Rights Reserved.
// Author: Liqiang Guo(guoliqiang@jike.com)
// I just want to GH to hss~
// Date  : 2013-09-26 15:17:48
// File  : code.cc
// Brief :

/*
 * Run Status: Accepted!
 * Program Runtime: 8 milli secs
 * Progress: 6/6 test cases passed.
 * Run Status: Accepted!
 * Program Runtime: 28 milli secs
 * Progress: 21/21 test cases passed.
 *
 * */

#include <vector>
#include "base/public/logging.h"
#include "base/public/string_util.h"

namespace algorithm {

void Fill(std::vector<std::vector<int> > & v, int b, int n, int & num) {
  // 注意处理两个边界
  if (n <= 0) return;
  if (n == 1) {
    v[b][b] = num++;
  } else {
    int size = n - 1;
    for (int i = 0; i < n - 1; i++) v[b][b + i] = num++;
    for (int i = 0; i < n - 1; i++) v[b + i][b + size] = num++;
    for (int i = 0; i < n - 1; i++) v[b + size][b + size - i] = num++;
    for (int i = 0; i < n - 1; i++) v[b + size - i][b] = num++;
  }
}

std::vector<std::vector<int> > GenerateMatrix(int n) {
  std::vector<std::vector<int> > rs(n, std::vector<int>(n, 0));
  int k = n;
  int num = 1;
  for (int i = 0; i <= rs.size() / 2; i++) {
    Fill(rs, i, k, num);
    k -= 2;
  }
  return rs;
}

}  // namespace algorithm

using namespace algorithm;


int main(int argc, char** argv) {
  std::vector<std::vector<int> > rs = GenerateMatrix(0);
  LOG(INFO) << JoinMatrix(&rs);
  return 0;
}