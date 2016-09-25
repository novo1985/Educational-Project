#include "DecisionTree.h"

int main(int argc, char* argv[]) {
  double pruning_factor(0.0f);
  if (argc != 4) {
    cerr << "Wrong parameters!\n";
    return -1;
  } else {
    pruning_factor = stod(argv[3]);
  }

  if (pruning_factor < 0.0f || pruning_factor >= 1.0f) {
    cerr << "pruning factor: " << pruning_factor << " is out of range!\n";
    return -1;
  }

  try {
    Data trainfile(argv[1]);
    Data testfile(argv[2]);

    DecisionTree tree(argv[1], pruning_factor);
    tree.buildTree();

    tree.TestTree(trainfile, false);
    tree.TestTree(testfile, true);
    cout << tree.summaryTostring();

    tree.prune_tree();

    tree.TestTree(trainfile, false);
    tree.TestTree(testfile, true);
    cout << tree.summaryTostring();
  } catch (runtime_error& err) {
    cerr << err.what();
  } catch (...) {
    cerr << "Some error happened, aborted!\n";
  }

  return 0;
}
