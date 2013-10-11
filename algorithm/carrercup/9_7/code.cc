// Copyright 2013 Jike Inc. All Rights Reserved.
// Author: Liqiang Guo(guoliqiang@jike.com)
// I just want to GH to hss~
// Date  : 2013-10-06 00:20:42
// File  : code.cc
// Brief :

#include "base/public/common_head.h"

namespace algorithm {

/*
 * BSearch1 BSearch2
 * 循环结束时，如果发现k，则b为k的下标，如果没发现k
 * 则b为比k稍大元素的下标或n
 *
 * */
int BSearch1(std::vector<int> & v, int k) {
  int b = 0;
  int e = v.size();
  if (b == e) return -1;
  while (b < e) {
    int mid = b + (e - b) / 2;
    if (v[mid] < k) b = mid + 1;
    else e = mid;
  }
  return b;
}

int BSearch2(std::vector<int> & v, int k) {
  int b = 0;
  int e = v.size() - 1;
  if (b > e) return -1;
  while (b <= e) {
    int mid = b + (e - b) / 2;
    if (v[mid] < k) b = mid + 1;
    else e = mid - 1;
  }
  return b;
}

/*
 * BSearch3 BSearch4
 * 循环结束时如果发现k，返回k下一个元素的下标
 * 如果未发现k，返回比k稍大元素的下标或n
 *
 * 这种方式不要用,因为发现k，返回的不是k的下标比较奇怪
 * */
int BSearch3(std::vector<int> & v, int k) {
  int b = 0;
  int e = v.size();
  if (b == e) return -1;
  while (b < e) {
    int mid = b + (e - b) / 2;
    if (v[mid] > k) e = mid;
    else b = mid + 1;
  }
  return b;
}

int BSearch4(std::vector<int> & v, int k) {
  int b = 0;
  int e = v.size() - 1;
  if (b > e) return -1;
  while (b <= e) {
    int mid = b + (e - b) / 2;
    if (v[mid] > k) e = mid - 1;
    else b = mid + 1;
  }
  return b;
}
}  // namespace algorithm


/*
 * 通用LSI问题
 * http://blog.csdn.net/acm_xmzhou/article/details/8778909
 *
 * */

namespace algorithm {

/*
 * dp[i]保存的是递增序列长度是i的序类中，末尾元素最小的
 * 那个序列的末尾元素值
 * 
 * 可以证明dp是连续的
 * path 保存递增子序列
 * 
 * 时间复杂度 n * log(n)
 * 
 * 大众的dp写法是n^2
 *
 * 此问题也可以转换为最长公共子序列问题
 *
 * */

int LSI(std::vector<int> & v) {
  std::vector<int> dp(v.size() + 1);
  std::vector<int> path;
  dp[1] = v[0];
  int len = 1;
  for (int i = 1; i < v.size(); i++) {
    int b = 1;
    int e = len;
    while (b <= e) {
      int mid = b + (e - b) / 2;
      if (dp[mid] < v[i]) b = mid + 1;
      else e = mid - 1;
    }
    /* 如果dp中含有v[i]则b指向那个元素的下标
     * 否则b指向比b稍大元素的下表或len +１
     * 由dp的定义可知道，此位置应该赋值为v[i]
     * */
    dp[b] = v[i];
    if (b > len) {
      len = b;
      path = dp;
    }
  }
  /*
  for (int i = 1; i <= len; i++) {
    std::cout << path[i] << " ";
  }
  std::cout << std::endl;
  */
  return len;
}

/*
 * 最长不减子序列
 *
 * 输出所有最长的递增(不减)子序列用大众dp + 回溯　更实在
 *
 * */
int LSI2(std::vector<int> & v) {
  std::vector<std::vector<int> > dp(v.size() + 1, std::vector<int>());
  std::vector<std::vector<int> > path;
  dp[1].push_back(v[0]);
  int len = 1;
  int max = 0;
  int sum = 1;
  for (int i = 1; i < v.size(); i++) {
    int b = 1;
    int e = len;
    while (b <= e) {
      int mid = b + (e - b) / 2;
      if (dp[mid].front() < v[i]) b = mid + 1;
      else e = mid - 1;
    }
    if (dp[b].size() != 0 && dp[b].front() != v[i]) {
      sum -= dp[b].size();
      dp[b].clear();
    }
    dp[b].push_back(v[i]);
    sum++;
    if (b > len) {
      len = b;
    }
    if (sum > max) {
      max = sum;
      path = dp;
    }
  }
  /*
  for (int i = 1; i <= len; i++) {
    LOG(INFO) << JoinVector(path[i]);
  }
  */
  return max;
}
}  // namespace algorithm



namespace algorithm {
bool Cmp(const std::pair<int, int> & a1, const std::pair<int, int> & a2) {
  if (a1.first == a2.first) return a1.second < a2.second;
  return a1.first < a2.first;
}

int Tower(std::vector<std::pair<int, int> > & v, std::vector<std::pair<int, int> >  & rs) {
  std::sort(v.begin(), v.end(),Cmp);
  std::vector<std::pair<int, int> > dp(v.size() + 1);
  dp[1] = v[0];
  int len = 1;
  for (int i = 1; i < v.size(); i++) {
    int b = 1;
    int e = len;
    while (b <= e) {
      int mid = b + (e - b) / 2;
      if (dp[mid].second < v[i].second) b = mid + 1;
      else e = mid - 1;
    }
    dp[b] = v[i];
    if (b > len) {
     len = b;
     rs = dp;
    }
  }
  return len;
}

}  // namespace algorithm


using namespace algorithm;


int main(int argc, char** argv) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.push_back(5);
  v.push_back(8);
  v.push_back(9);
  v.push_back(10);
  v.push_back(12);
  /*
  LOG(INFO) << BSearch1(v, 14);
  LOG(INFO) << BSearch2(v, 14);
  LOG(INFO) << BSearch3(v, 14);
  LOG(INFO) << BSearch4(v, 14);
  
  LOG(INFO) << BSearch1(v, 8);
  LOG(INFO) << BSearch2(v, 8);
  LOG(INFO) << BSearch3(v, 8);
  LOG(INFO) << BSearch4(v, 8);
  */
  v.clear();
  v.push_back(2);
  v.push_back(1);
  v.push_back(4);
  v.push_back(8);
  v.push_back(7);
  v.push_back(7);
  v.push_back(12);
  v.push_back(20);
  v.push_back(20);
  v.push_back(3);
  LOG(INFO) << LSI(v);
  LOG(INFO) << LSI2(v);
  /*
  std::vector<std::pair<int, int> > persons;
  persons.push_back(std::make_pair(65, 100));
  persons.push_back(std::make_pair(70, 150));
  persons.push_back(std::make_pair(56, 90));
  persons.push_back(std::make_pair(75, 190));
  persons.push_back(std::make_pair(60, 95));
  persons.push_back(std::make_pair(68, 110));
  std::vector<std::pair<int, int> > rs;
  LOG(INFO) << Tower(persons, rs);
  for (int i = 1; i < rs.size(); i++) {
    LOG(INFO) << rs[i].first << " " << rs[i].second;
  }
  */
  return 0;
}