#include "DecisionTree.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Wrong parameters!\n";
    return -1;
  }

  try {
    Data testfile(argv[2]);

    DecisionTree tree(argv[1]);
    tree.buildTree();

    tree.TestTrain();
    tree.TestTree(testfile, true);
    cout << tree.summaryTostring();

    cout << "\n--------- Now Randomly Picks Attributes ---------\n";
    DecisionTree random_tree(argv[1]);
    random_tree.random_buildTree();
    random_tree.TestTrain();
    random_tree.TestTree(testfile, true);
    cout << random_tree.summaryTostring();
  } catch (runtime_error& err) {
    cerr << err.what();
  } catch (...) {
    cerr << "Some error happened, aborted!\n";
  }

  return 0;
}
