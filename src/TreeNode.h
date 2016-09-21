#ifndef DECISION_TREE_TREENODE_H
#define DECISION_TREE_TREENODE_H

#include <iostream>
#include <string>
#include <vector>
#include "Data.h"

class TreeNode {
 public:
  // constructor using initialization list
  TreeNode(Data& train, Data& test) : Train_Dset(train), Test_Dset(test){};
  TreeNode(string& trainfile, string& testfile)
      : Train_Dset(trainfile), Test_Dset(testfile){};

  // choosing best IG attribute
  void pick_splitting_attri();

 private:
  Data Train_Dset;
  Data Test_Dset;
  TreeNode* RightChild;
  TreeNode* LeftChild;
  string Best_Attri;
};

#endif  // DECISION_TREE_TREENODE_H
