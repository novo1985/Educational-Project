#ifndef DECISION_TREE_DECISIONTREE_H
#define DECISION_TREE_DECISIONTREE_H

#include "TreeNode.h"

class DecisionTree {
 public:
  // constructor using initialization list
  DecisionTree(const string& TrainData_path, double pf)
      : root_node(new TreeNode(0, TrainData_path)),
        P_Factor(pf),
        count_of_nodes(1),
        num_of_leafnodes(0),
        accurary(0.0f){};

  // create Decision tree
  void buildTree() { SplitTree(root_node); }

  // print Decision Tree
  string PrintTree() {
    string output;
    int count = -1;
    TreeToString(output, root_node, count);
    output += "\n";
    return output;
  }
  void TestTree(const Data& Test_Data);

  string summaryTostring();

 private:
  void SplitTree(TreeNode* cur_parent);
  void TreeToString(string& str, TreeNode* current_parent, int count);

 private:
  double P_Factor;
  int count_of_nodes;
  int num_of_leafnodes;
  TreeNode* root_node;
  vector<TreeNode*> leaf_nodes;
  double accurary;

  int num_of_instance_test;
  int num_of_attri_test;
};

#endif  // DECISION_TREE_DECISIONTREE_H
