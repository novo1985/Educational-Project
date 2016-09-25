#ifndef DECISION_TREE_TREENODE_H
#define DECISION_TREE_TREENODE_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Data.h"

class TreeNode;

typedef pair<pair<int, TreeNode*>, pair<int, TreeNode*>> Children;

class TreeNode {
 public:
  // constructor using initialization list
  TreeNode(const int& node_index, Data& train, int index, int value,
           const string& splitter_name)
      : splitter_value(value),
        node_index_(node_index),
        Train_Dset(train, index, value),
        leaflabel(-1),
        up_splitter(splitter_name),
        LeftChild(nullptr),
        RightChild(nullptr),
        Parent(nullptr),
        Prune_Flag(false){};

  TreeNode(const int& node_index, const string& trainfile)
      : splitter_value(-1),
        node_index_(node_index),
        Train_Dset(trainfile),
        leaflabel(-1),
        LeftChild(nullptr),
        RightChild(nullptr),
        Parent(nullptr),
        Prune_Flag(false){};

  // choosing best IG attribute
  int pick_splitting_attri();

  int get_splitter_index() { return index_splitter; }

  string get_name_splitter(int index) {
    return Train_Dset.get_att_names().at(index);
  }

  void InfoGainToString() {
    cout << "Node[" << node_index_
         << "] Information Gain: " << Train_Dset.print_att_InfoGain();
  }

  const bool IsLeaf(void) const { return (leaflabel != -1); }

  void make_node_label() { leaflabel = Train_Dset.get_majority_of_data(); }

  int get_size_of_attribute() const { return Train_Dset.att_InfoGain.size(); }

  // splitting node and create two new child TreeNodes
  Children splitting_update();

  bool node_pure() const { return Train_Dset.pure_labels(); }

  const int GetNodeIndex() const { return node_index_; }

  void print_TreeNode(string& str);
  const int get_majority() const { return Train_Dset.get_majority(); }

  TreeNode* get_Left_child() { return LeftChild; }
  TreeNode* get_Right_child() { return RightChild; }

  const string get_splitter_name() const { return down_splitter; }
  const long query_original_index(const string& name) const {
    auto res = find(Train_Dset.get_att_names().cbegin(),
                    Train_Dset.get_att_names().cend(), name);
    return distance(Train_Dset.get_att_names().cbegin(), res);
  }
  const Data& get_train_data() const { return Train_Dset; }

  void set_parent(TreeNode* Parent_pointer) { Parent = Parent_pointer; }
  TreeNode* get_parent() const { return Parent; }

  void set_pruneflag(bool flag) { Prune_Flag = flag; }

  const bool get_pruneflag() const { return Prune_Flag; }

 private:
  int node_index_;
  Data Train_Dset;
  int splitter_value;
  int leaflabel;
  int index_splitter;
  string up_splitter;
  string down_splitter;
  TreeNode* RightChild;
  TreeNode* LeftChild;
  TreeNode* Parent;
  bool Prune_Flag;
};

#endif  // DECISION_TREE_TREENODE_H
