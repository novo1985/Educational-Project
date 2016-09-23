#include "DecisionTree.h"

void DecisionTree::SplitTree(TreeNode* current_parent) {
  static int count = 0;

  /* checkpoint 1, if only one attribute left we do not need splitter anymore
   because it will stop erasing and stop splitting */
  /* checkpoint 2, if class is pure, node does not need split anymore */
  if (current_parent->get_size_of_attribute() == 0 ||
      current_parent->node_pure()) {
    current_parent->make_node_label();
    leaf_nodes.push_back(current_parent);
    cout << "Level " << count << " leaf: " << current_parent->GetNodeIndex()
         << endl;
    return;
  }

  Children res = current_parent->splitting_update();
  SplitTree(res.first);
  SplitTree(res.second);
  cout << "Level " << ++count << endl;
};

void DecisionTree::TreeToString(string& str, TreeNode* current_parent,
                                int count) {
  current_parent->print_TreeNode(str);
  if (current_parent->get_Left_child()) {
    int temp = count;
    temp++;
    for (int i = 0; i < temp; i++) {
      str += "| ";
    }
    TreeToString(str, current_parent->get_Left_child(), temp);
  }

  if (current_parent->get_Right_child()) {
    int temp = count;
    temp++;
    for (int i = 0; i < temp; i++) {
      str += "| ";
    }
    TreeToString(str, current_parent->get_Right_child(), temp);
  }
}
