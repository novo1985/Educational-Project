#ifndef DECISION_TREE_DATA_H
#define DECISION_TREE_DATA_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Data {
 public:
  // constructor, and how to use initialization list here?
  Data(const string& file_name) : filename(file_name) { readData(); };

  /* obtain the names of Xi and y of instances, and also get values of
  each instances */
  void readData();
  vector<vector<int>>& get_rows() { return rows; }
  vector<string>& get_att_names() { return att_names; }
  string DataToString();

  // get the entropy of data set
  double get_Entropy(const int& index);

  // For each attribute, we can get the IG
  void Calc_Info_Gain();
  double get_Info_Gain(const int& index) { return att_InfoGain.at(index); }
  string print_att_InfoGain() const {
    string str;
    for (auto iter : att_InfoGain) {
      str += to_string(iter);
      str += " ";
    }
    return str;
  };

  double Log(const double& value) const { return value ? log2(value) : 0.0f; }

 private:
  string filename;
  vector<vector<int>> rows;
  vector<string> att_names;
  vector<double> att_InfoGain;
};

#endif  // DECISION_TREE_DATA_H
