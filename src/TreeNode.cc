#include "TreeNode.h"
#include <algorithm>

int TreeNode::pick_splitting_attri() {
  // get the index of the attribute
  int index_splitter;

  vector<double>::iterator iter;
  iter = max_element(Train_Dset.att_InfoGain.begin(),
                     Train_Dset.att_InfoGain.end());
  index_splitter = distance(Train_Dset.att_InfoGain.begin(), iter);

  return index_splitter;
}

pair<TreeNode*, TreeNode*> TreeNode::splitting_update() {
  int index = pick_splitting_attri();
  string str = get_name_splitter(index);

  cout << "the index of splitter is " << index << endl;

  // new two child nodes
  TreeNode* Left_Node =
      new TreeNode(node_index_ * 2 + 1, Train_Dset, index, 0, Test_Dset, str);
  cout << "left child: ";
  Left_Node->InfoGainToString();
  TreeNode* Right_Node =
      new TreeNode(node_index_ * 2 + 2, Train_Dset, index, 1, Test_Dset, str);
  cout << "right child: ";
  Right_Node->InfoGainToString();

  LeftChild = Left_Node;
  RightChild = Right_Node;

  return make_pair(LeftChild, RightChild);
}

void TreeNode::print_TreeNode(string& str) {
  // first, we need get splitter name each time

  if (Train_Dset.att_InfoGain.empty() && splitter_value == -1) {
    str += "root has no attribute";
    return;
  }
  if (splitter_value == -1) {
    return;
  }
  str += splitter;
  str += " = ";
  str += to_string(splitter_value);
  str += " : ";
  if (leaflabel != -1) {
    str += to_string(Train_Dset.get_majority());
  }
  str += "\n";
}
