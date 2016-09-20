//
// Created by Lei Gao on 9/20/16.
//

#include "Data.h"

string Data::DataToString() {
  string output;
  for (auto iter = att_names.cbegin(); iter != att_names.cend(); ++iter) {
    output += *iter;
    output += " ";
  }
  output += "\n";
  for (auto row : rows) {
    for (auto num : row) {
      output += to_string(num);
      output += " ";
    }
    output += "\n";
  }

  return output;
}