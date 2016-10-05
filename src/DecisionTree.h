#ifndef DECISION_TREE_DECISIONTREE_H
#define DECISION_TREE_DECISIONTREE_H

#include <random>
#include "TreeNode.h"

class DecisionTree {
 public:
  // constructor using initialization list
  DecisionTree(const string& TrainData_path, double pf = 1.0f)
      : root_node(new TreeNode(0, TrainData_path)),
        P_Factor(pf),
        count_of_nodes(0),
        num_of_leafnodes(0),
        sum_depth_(0),
        train_accuracy(0.0f),
        test_accuracy(0.0f),
        pruned(false),
        distribution(1, 1000) {
    random_eng.seed(random_device()());
  }

  ~DecisionTree() {
    for (auto item : pointer_array) {
      delete item.second;
    }
    delete root_node;
  }

  // create Decision tree
  void buildTree() { SplitTree(root_node); }

  // build random tree
  void random_buildTree() { random_SplitTree(root_node); }

  // print Decision Tree
  string PrintTree() {
    string output("\n");
    output += (pruned ? "Post" : "Pre");
    output += "-Pruned Decision Tree Model\n";
    output += "-------------------------------------\n";
    int count = -1;
    TreeToString(output, root_node, count);
    output += "\n";
    return output;
  }

  void TestTrain() { TestTree(root_node->get_train_data(), false); }
  void TestTree(const Data& Test_Data, bool test);

  string summaryTostring();

  void prune_tree();

  void statistic_nodes(TreeNode* current_parent);
  void statistic_leafnodes(TreeNode* current_parent, int sum_depth);

 private:
  void SplitTree(TreeNode* cur_parent);
  void random_SplitTree(TreeNode* cur_parent);
  void TreeToString(string& str, TreeNode* current_parent, int count);

 private:
  TreeNode* root_node;
  double P_Factor;
  int count_of_nodes;
  int num_of_leafnodes;
  int sum_depth_;
  vector<TreeNode*> leaf_nodes;
  double train_accuracy;
  double test_accuracy;
  int num_of_instance_test;
  int num_of_attri_test;
  vector<pair<int, TreeNode*>> pointer_array;
  bool pruned;

  mt19937 random_eng;
  uniform_int_distribution<mt19937::result_type> distribution;
};

#endif  // DECISION_TREE_DECISIONTREE_H
