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
    return;
  }

  Children res = current_parent->splitting_update();
  SplitTree(res.first.second);
  pointer_array.push_back(res.first);
  SplitTree(res.second.second);
  pointer_array.push_back(res.second);
};

void DecisionTree::TreeToString(string& str, TreeNode* current_parent,
                                int count) {
  if (current_parent->get_pruneflag()) {
    return;
  }

  current_parent->print_TreeNode(str);
  if (current_parent->get_Left_child() &&
      !current_parent->get_Left_child()->get_pruneflag()) {
    int temp = count;
    temp++;
    for (int i = 0; i < temp; i++) {
      str += "| ";
    }
    TreeToString(str, current_parent->get_Left_child(), temp);
  }

  if (current_parent->get_Right_child() &&
      !current_parent->get_Right_child()->get_pruneflag()) {
    int temp = count;
    temp++;
    for (int i = 0; i < temp; i++) {
      str += "| ";
    }
    TreeToString(str, current_parent->get_Right_child(), temp);
  }
}

void DecisionTree::TestTree(const Data& Test_Data, bool test) {
  double correct(0.0f);
  double total(Test_Data.get_rows().size());
  TreeNode* current_parent(nullptr);
  int index;
  int result;
  num_of_instance_test = Test_Data.get_rows().size();
  num_of_attri_test = Test_Data.get_att_names().size() - 1;

  for (auto iter = Test_Data.get_rows().cbegin();
       iter != Test_Data.get_rows().cend(); iter++) {
    current_parent = root_node;

    while (!current_parent->IsLeaf()) {
      index =
          root_node->query_original_index(current_parent->get_splitter_name());
      if (iter->at(index) == 0) {
        if (current_parent->get_Left_child()) {
          if (current_parent->get_Left_child()->get_pruneflag()) {
            result = current_parent->get_majority();
            break;
          }
          current_parent = current_parent->get_Left_child();
        }
      } else if (iter->at(index) == 1) {
        if (current_parent->get_Right_child()) {
          if (current_parent->get_Right_child()->get_pruneflag()) {
            result = current_parent->get_majority();
            break;
          }
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

  if (test) {
    test_accuracy = correct / total;
  } else {
    train_accuracy = correct / total;
  }
}

string DecisionTree::summaryTostring() {
  stringstream sstr;
  count_of_nodes = 0;
  num_of_leafnodes = 0;
  statistic_nodes(root_node);
  statistic_leafnodes(root_node);

  sstr << PrintTree();
  sstr << (pruned ? "Post" : "Pre");
  sstr << "-Pruned Accuracy\n"
          "-------------------------------------\n"
          "Number of training instances = "
       << root_node->get_train_data().get_rows().size()
       << "\n"
          "Number of training attributes = "
       << root_node->get_train_data().get_att_names().size() - 1
       << "\n"
          "Total number of nodes in the tree = "
       << count_of_nodes << "\n"
                            "Number of leaf nodes in the tree = "
       << num_of_leafnodes << "\n"
                              "Accuracy of the model on the training dataset = "
       << train_accuracy * 100 << "%\n"
                                  "Number of testing instances = "
       << num_of_instance_test << "\n"
                                  "Number of testing attributes = "
       << num_of_attri_test << "\n"
                               "Accuracy of the model on the testing dataset = "
       << test_accuracy * 100 << "%\n";
  return sstr.str();
}

void DecisionTree::prune_tree() {
  pruned = true;
  unsigned int index_del;
  int prune_num = static_cast<int>(ceil(P_Factor * count_of_nodes));
  vector<pair<int, TreeNode*>> prune_array(pointer_array);

  if (prune_num > prune_array.size()) {
    throw runtime_error(
        "Pruning nodes exceed total number of nodes. Aborted!\n");
  }

  for (int i = 0; i < prune_num; i++) {
    index_del = distribution(random_eng) % prune_array.size();
#if DEBUG
    cout << "p index = " << temp.at(index_del).first << endl;
#endif
    prune_array.at(index_del).second->set_pruneflag(true);
    prune_array.erase(prune_array.begin() + index_del);
  }
}

void DecisionTree::statistic_nodes(TreeNode* current_parent) {
  if (!current_parent->get_pruneflag()) {
    count_of_nodes++;
    if (current_parent->get_Left_child() &&
        !current_parent->get_Left_child()->get_pruneflag()) {
      statistic_nodes(current_parent->get_Left_child());
    }
    if (current_parent->get_Right_child() &&
        !current_parent->get_Right_child()->get_pruneflag()) {
      statistic_nodes(current_parent->get_Right_child());
    }
  }
}

void DecisionTree::statistic_leafnodes(TreeNode* current_parent) {
  if (!current_parent->get_pruneflag()) {
    TreeNode* temp = current_parent;

    if (temp->get_Left_child() && !temp->get_Left_child()->get_pruneflag()) {
      temp = temp->get_Left_child();

      if (temp->IsLeaf()) {
        num_of_leafnodes++;
      } else {
        statistic_leafnodes(temp);
      }
    }

    temp = current_parent;

    if (temp->get_Right_child() && !temp->get_Right_child()->get_pruneflag()) {
      temp = temp->get_Right_child();

      if (temp->IsLeaf()) {
        num_of_leafnodes++;
      } else {
        statistic_leafnodes(temp);
      }
    }
  }
}
