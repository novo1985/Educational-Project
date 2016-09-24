#include "DecisionTree.h"
#include <sstream>

void DecisionTree::SplitTree(TreeNode* current_parent) {
  /* checkpoint 1, if only one attribute left we do not need splitter anymore
   because it will stop erasing and stop splitting */
  /* checkpoint 2, if class is pure, node does not need split anymore */
  if (current_parent->get_size_of_attribute() == 0 ||
      current_parent->node_pure()) {
    current_parent->make_node_label();
    leaf_nodes.push_back(current_parent);
    num_of_leafnodes++;
    return;
  }

  Children res = current_parent->splitting_update();
  SplitTree(res.first);
  SplitTree(res.second);
  count_of_nodes += 2;
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

void DecisionTree::TestTree(const Data& Test_Data) {
  double correct(0.0f);
  double total(Test_Data.get_rows().size());
  TreeNode* current_parent(nullptr);
  int index;
  int result;
  num_of_instance_test = Test_Data.get_rows().size();
  num_of_attri_test = Test_Data.get_att_names().size();

  for (auto iter = Test_Data.get_rows().cbegin();
       iter != Test_Data.get_rows().cend(); iter++) {
    current_parent = root_node;

    while (!current_parent->IsLeaf()) {
      index =
          root_node->query_original_index(current_parent->get_splitter_name());

      if (iter->at(index) == 0) {
        if (current_parent->get_Left_child()) {
          current_parent = current_parent->get_Left_child();
        }
      } else if (iter->at(index) == 1) {
        if (current_parent->get_Right_child()) {
          current_parent = current_parent->get_Right_child();
        }
      }
    }
    result = current_parent->get_majority();

    if (result == iter->back()) {
      correct++;
    } else {
#ifdef DEBUG
      cout << "error = " << distance(Test_Data.get_rows().cbegin(), iter)
           << endl;
#endif
    }
  }

  accurary = correct / total;
}

string DecisionTree::summaryTostring() {
  stringstream sstr;
  sstr << PrintTree();
  sstr << "Pre-Pruned Accuracy\n"
          "-------------------------------------\n"
          "Number of training instances = "
       << root_node->get_train_data().get_rows().size()
       << "\n"
          "Number of training attributes = "
       << root_node->get_train_data().get_att_names().size()
       << "\n"
          "Total number of nodes in the tree = "
       << count_of_nodes << "\n"
                            "Number of leaf nodes in the tree = "
       << num_of_leafnodes << "\n"
                              "Accuracy of the model on the training dataset = "
       << accurary * 100 << "%\n"
                            "Number of testing instances = "
       << num_of_instance_test << "\n"
                                  "Number of testing attributes = "
       << num_of_attri_test << "\n"
                               "Accuracy of the model on the testing dataset = "
       << accurary * 100 << "%\n";
  return sstr.str();
}
