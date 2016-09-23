#include "DecisionTree.h"

int main(int argc, char* argv[]) {
  string file_path(argv[1]);
  DecisionTree tree(file_path, " ", 0.1f);
  tree.buildTree();
  return 0;
}
