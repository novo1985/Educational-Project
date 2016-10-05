#include "TreeNode.h"
#include <algorithm>
#include <random>

int TreeNode::pick_splitting_attri() {
  // get the index of the attribute

  vector<double>::iterator iter;
  iter = max_element(Train_Dset.att_InfoGain.begin(),
                     Train_Dset.att_InfoGain.end());
  index_splitter = distance(Train_Dset.att_InfoGain.begin(), iter);

  return index_splitter;
}

Children TreeNode::splitting_update() {
  int index = pick_splitting_attri();
  down_splitter = get_name_splitter(index);

#ifdef DEBUG
  cout << "the index of splitter is " << index << endl;
#endif

  // new two child nodes
  TreeNode* Left_Node =
      new TreeNode(node_index_ * 2 + 1, Train_Dset, index, 0, down_splitter);
  Left_Node->set_parent(this);
#ifdef DEBUG
  cout << "left child: " << Left_Node->InfoGainToString();
#endif
  TreeNode* Right_Node =
      new TreeNode(node_index_ * 2 + 2, Train_Dset, index, 1, down_splitter);
  Right_Node->set_parent(this);
#ifdef DEBUG
  cout << "right child: " << Right_Node->InfoGainToString();
#endif

  LeftChild = Left_Node;
  RightChild = Right_Node;

  return make_pair(make_pair(node_index_ * 2 + 1, LeftChild),
                   make_pair(node_index_ * 2 + 2, RightChild));
}

unsigned int TreeNode::random_index_of_splitter() {
  return distribution_(random_eng_) % (Train_Dset.get_att_names().size() - 1);
}

Children TreeNode::random_splitting_and_update() {
  int index = random_index_of_splitter();
  down_splitter = get_name_splitter(index);

  // new two child nodes
  TreeNode* Left_Node =
      new TreeNode(node_index_ * 2 + 1, Train_Dset, index, 0, down_splitter);
  Left_Node->set_parent(this);
#ifdef DEBUG
  cout << "left child: " << Left_Node->InfoGainToString();
#endif
  TreeNode* Right_Node =
      new TreeNode(node_index_ * 2 + 2, Train_Dset, index, 1, down_splitter);
  Right_Node->set_parent(this);
#ifdef DEBUG
  cout << "right child: " << Right_Node->InfoGainToString();
#endif

  LeftChild = Left_Node;
  RightChild = Right_Node;

  return make_pair(make_pair(node_index_ * 2 + 1, LeftChild),
                   make_pair(node_index_ * 2 + 2, RightChild));
}

void TreeNode::print_TreeNode(string& str) {
  if (splitter_value == -1) {
    return;
  }

  str += up_splitter;
  str += " = ";
  str += to_string(splitter_value);
  str += " : ";
  if (leaflabel != -1) {
    str += to_string(Train_Dset.get_majority());
  }
  str += "\n";
}
