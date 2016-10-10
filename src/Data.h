#ifndef DECISION_TREE_DATA_H
#define DECISION_TREE_DATA_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

class Data {
 public:
  Data(void) {}

  // constructor 1, and how to use initialization list here?
  Data(const string& file_name) : filename(file_name) {
    readData();
    Calc();
  }

  // constructor 2, using for create new child nodes after splitting.
  Data(const Data& previous_data, int index, int value);

  /* obtain the names of Xi and y of instances, and also get values of
  each instances */
  void readData();

  const vector<vector<int>>& get_rows() const { return rows; }
  const vector<string>& get_att_names() const { return att_names; }

  string DataToString();

  // get the entropy of data set
  double get_Entropy(const int& index);

  // For each attribute, we can get the IG
  void Calc_Info_Gain();

  vector<double> att_InfoGain;

  // double get_Info_Gain(const int& index) { return att_InfoGain.at(index); }

  bool pure_labels() const;

  int get_majority_of_data() const;

  int get_majority() const { return majority; }

  string print_att_InfoGain() const {
    string str;
    if (att_InfoGain.size()) {
      for (auto iter : att_InfoGain) {
        str += to_string(iter);
        str += " ";
      }
    } else {
      str += "none";
    }

    str += "\n";
    return str;
  }

  double Log(const double& value) const { return value ? log2(value) : 0.0f; }

 private:
  void Calc(void) {
    Calc_Info_Gain();
    majority = get_majority_of_data();
  }

 private:
  int majority;
  string filename;
  vector<vector<int>> rows;
  vector<string> att_names;
};

#endif  // DECISION_TREE_DATA_H
