#ifndef DECISION_TREE_DECISIONTREE_H
#define DECISION_TREE_DECISIONTREE_H

#include "TreeNode.h"

class DecisionTree {
 public:
  // constructor using initialization list
  DecisionTree(string& TrainData_path, string& TestData_path, double pf)
      : root_node(new TreeNode(TrainData_path, TestData_path)), P_Factor(pf){};

  // splitting node and create two new child TreeNodes
  void Node_splitting();

  // print Decision Tree
  void TreeToString();

 private:
  double P_Factor;
  TreeNode* root_node;
};

#endif  // DECISION_TREE_DECISIONTREE_H
