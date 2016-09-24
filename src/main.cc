#include "DecisionTree.h"

int main(int argc, char* argv[]) {
  string trainfile_path(argv[1]);
  string testfile_path(argv[2]);
  DecisionTree tree(trainfile_path, 0.1f);
  tree.buildTree();
  Data testfile(testfile_path);
  tree.TestTree(testfile);
  cout << tree.summaryTostring();
  return 0;
}
