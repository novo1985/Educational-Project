#include "Data.h"

int main(int argc, char* argv[]) {
  string file_path(argv[1]);
  Data file(file_path);
  cout << file.DataToString();
  file.Calc_Info_Gain();
  cout << file.print_att_InfoGain() << endl;
  return 0;
}
