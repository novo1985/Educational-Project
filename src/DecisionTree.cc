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
