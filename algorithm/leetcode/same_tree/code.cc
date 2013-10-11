// Copyright 2013 Jike Inc. All Rights Reserved.
// Author: Liqiang Guo(guoliqiang@jike.com)
// I just want to GH to hss~
// Date  : 2013-09-29 17:24:54
// File  : code.cc
// Brief :

#include "../ojbst/ojbst.h"

/*
 * Run Status: Accepted!
 * Program Runtime: 0 milli secs
 * Progress: 12/12 test cases passed.
 * Run Status: Accepted!
 * Program Runtime: 12 milli secs
 * Progress: 52/52 test cases passed.
 *
 * */

namespace algorithm {

bool SameTree(TreeNode * root1, TreeNode * root2) {
  if (root1 == NULL && root2 == NULL) return true;
  if (root1 == NULL || root2 == NULL) return false;

  if (root1->val != root2->val) return false;
  if (SameTree(root1->left, root2->left) &&
      SameTree(root1->right, root2->right)) return true;
  return false;
}

}  // namespace algorithm

using namespace algorithm;


int main(int argc, char** argv) {

  return 0;
}