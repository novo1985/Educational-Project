#include "Data.h"

int main(int argc, char* argv[]) {
  string file_path(argv[1]);
  Data file(file_path);
  file.readData();
  cout << file.DataToString();
  return 0;
}
