//
// Created by Lei Gao on 9/20/16.
//

#ifndef DECISION_TREE_DATA_H
#define DECISION_TREE_DATA_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Data {
 public:
  // constructor, and how to use initialization list here?
  Data(const string& file_name) : filename(file_name){};

 private:
  string filename;
  vector<vector<int>> rows;
  vector<string> att_names;

 public:
  /* obtain the names of Xi and y of instances, and also get values of
   each instances */
  void readData();
  string DataToString();
};

inline void Data::readData() {
  fstream input;
  string str;
  input.open(filename);

  if (!input.is_open()) {
    input.clear();
    input.open(filename, std::ios::out);  // Create file.
    input.close();
    input.open(filename);
  }

  // iteratively get each line and store it into string str.
  int count = 0;
  while (getline(input, str)) {
    count++;
    int pos;
    string element;
    string search_str = "\t";
    vector<int> num_row;

    while (!str.empty()) {
      pos = str.find_first_of(search_str);
      if (pos == -1) {
        element = str;
      } else {
        element = str.substr(0, pos);
      }

      if (!element.empty()) {
        if (count == 1) {
          att_names.push_back(element);
        } else {
          num_row.push_back(stoi(element));
        }
      }
      if (pos == -1) {
        str.erase(0);
      } else {
        str.erase(0, pos + 1);
      }
    }

    if (!num_row.empty()) {
      rows.push_back(num_row);
    }
  }
}

#endif  // DECISION_TREE_DATA_H
