#ifndef DECISION_TREE_TREENODE_H
#define DECISION_TREE_TREENODE_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Data.h"

class TreeNode;

typedef pair<TreeNode*, TreeNode*> Children;

class TreeNode {
 public:
  // constructor using initialization list
  TreeNode(const int& node_index, Data& train, int index, int value, Data& test)
      : node_index_(node_index),
        Train_Dset(train, index, value),
        leaflabel(-1){};

  TreeNode(const int& node_index, const string& trainfile,
           const string& testfile)
      : node_index_(node_index), Train_Dset(trainfile), leaflabel(-1){};

  // choosing best IG attribute
  int pick_splitting_attri();

  void InfoGainToString() {
    cout << "Node[" << node_index_
         << "] Information Gain: " << Train_Dset.print_att_InfoGain();
  }

  void make_node_label() { leaflabel = Train_Dset.get_majority_of_data(); }

  int get_size_of_attribute() const { return Train_Dset.att_InfoGain.size(); }

  // splitting node and create two new child TreeNodes
  Children splitting_update();
  bool node_pure() const { return Train_Dset.pure_labels(); }

  const int GetNodeIndex() const { return node_index_; }

 private:
  int node_index_;
  Data Train_Dset;
  Data Test_Dset;
  int leaflabel;
  TreeNode* RightChild;
  TreeNode* LeftChild;
};

#endif  // DECISION_TREE_TREENODE_H
