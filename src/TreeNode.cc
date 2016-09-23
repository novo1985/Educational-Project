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

  cout << "the index of splitter is " << index << endl;

  // new two child nodes
  TreeNode* Left_Node =
      new TreeNode(node_index_ * 2 + 1, Train_Dset, index, 0, Test_Dset);
  cout << "left child: ";
  Left_Node->InfoGainToString();
  TreeNode* Right_Node =
      new TreeNode(node_index_ * 2 + 2, Train_Dset, index, 1, Test_Dset);
  cout << "right child: ";
  Right_Node->InfoGainToString();

  LeftChild = Left_Node;
  RightChild = Right_Node;

  return make_pair(LeftChild, RightChild);
}
