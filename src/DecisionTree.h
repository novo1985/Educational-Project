#ifndef DECISION_TREE_DECISIONTREE_H
#define DECISION_TREE_DECISIONTREE_H

#include "TreeNode.h"

class DecisionTree {
 public:
  // constructor using initialization list
  DecisionTree(const string& TrainData_path, const string& TestData_path,
               double pf)
      : root_node(new TreeNode(0, TrainData_path, TestData_path)),
        P_Factor(pf){};

  // create Decision tree
  void buildTree() { SplitTree(root_node); }

  // print Decision Tree
  string PrintTree() {
    string output;
    int count = -1;
    TreeToString(output, root_node, count);
    return output;
  }

 private:
  void SplitTree(TreeNode* cur_parent);
  void TreeToString(string& str, TreeNode* current_parent, int count);

 private:
  double P_Factor;
  TreeNode* root_node;
  vector<TreeNode*> leaf_nodes;
};

#endif  // DECISION_TREE_DECISIONTREE_H
