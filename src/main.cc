#include "DecisionTree.h"

int main(int argc, char* argv[]) {
  // TODO: handling error
  string trainfile_path(argv[1]);
  string testfile_path(argv[2]);
  Data testfile(testfile_path);
  Data trainfile(trainfile_path);

  DecisionTree tree(trainfile_path, stod(argv[3]));
  tree.buildTree();

  tree.TestTree(trainfile, false);
  tree.TestTree(testfile, true);
  cout << tree.summaryTostring();

  tree.prune_tree();

  tree.TestTree(trainfile, false);
  tree.TestTree(testfile, true);
  cout << tree.summaryTostring();
  return 0;
}
