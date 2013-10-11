// Copyright 2013 Jike Inc. All Rights Reserved.
// Author: Liqiang Guo(guoliqiang@jike.com)
// I just want to GH to hss~
// Date  : 2013-09-26 21:49:20
// File  : code.cc
// Brief :

/*
 * Run Status: Accepted!
 * Program Runtime: 8 milli secs
 * Progress: 10/10 test cases passed.
 * Run Status: Accepted!
 * Program Runtime: 12 milli secs
 * Progress: 45/45 test cases passed.
 *
 * fobonaci 数列
 *
 * */

#include "base/public/common_head.h"

namespace algorithm {

std::vector<int> Multiply(std::vector<int> & a, std::vector<int> & b) {
  std::vector<int> rs(4, 0);
  rs[0] = a[0] * b[0] + a[1] * b[2];
  rs[1] = a[0] * b[1] + a[1] * b[3];
  rs[2] = a[2] * b[0] + a[3] * b[2];
  rs[3] = a[2] * b[1] + a[3] * b[3];
  return rs;
}



std::vector<int> Multiply(int n) {
  std::vector<int> rs (4, 0);
  rs[0] = 1;
  rs[2] = 1;
  
  std::vector<int> tmp(4, 1);
  tmp[3] = 0;

  while (n) {
    if (n & 0x1) {
      rs = Multiply(rs, tmp);
    }
    tmp = Multiply(tmp, tmp);
    n >>= 1;
  }
  return rs;
}

int ClimbStairs(int n ) {
  if (n <= 0) return 0;
  if (n == 1) return 1;
  if (n == 2) return 2;
  std::vector<int> foo = Multiply(n - 2);
  return foo[0] * 2 + foo[1];
}


}  // namespace algorithm

using namespace algorithm;


int main(int argc, char** argv) {
  LOG(INFO) << ClimbStairs(3);
  LOG(INFO) << ClimbStairs(5);
  LOG(INFO) << ClimbStairs(7);
  LOG(INFO) << ClimbStairs(20);

  return 0;
}