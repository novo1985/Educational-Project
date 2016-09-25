#include "Data.h"
#include <cmath>
#include <vector>
#include <stdexcept>

Data::Data(const Data& previous_data, int index, int value)
    : att_names(previous_data.get_att_names()) {
  // constructor, it will create Data class depends on the Three parameters
  // it is used to create Data of new child nodes
  // Within Data class, it will automatically initialize rows and att_names to
  // empty
  vector<int> temp;
  for (auto iter = previous_data.get_rows().cbegin();
       iter != previous_data.get_rows().cend(); ++iter) {
    if (iter->at(index) == value) {
      temp = *iter;
      temp.erase(temp.begin() + index);
      rows.push_back(move(temp));  // Need check
    }
  }
  // att_names is already assigned in the initialization list, just remove the
  // splitter
  att_names.erase(att_names.begin() + index);

  Calc();
}

void Data::readData() {
  fstream input;
  string str;
  input.open(filename);

  if (!input.is_open()) {
    throw runtime_error("Wrong file path: " + filename + "\n");
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

double Data::get_Entropy(const int& index) {
  double posCount =
      0.0f;  // the number of "1" in the whole set AND be initialized to zero
  double negCount =
      0.0f;  // the number of "0" in the whole set AND be initialized to zero
  // the total number of instances in the whole set = posCount + negCount

  double pp = 0.0f;  // p(+)
  double np = 0.0f;  // p(-)
  // storing the value of entropy
  double S = 0.0f;

  if (index == -1) {
    // calculate the original set entropy
    for (auto iter = rows.cbegin(); iter != rows.cend(); ++iter) {
      if (iter->back() == 1) {
        posCount++;
      } else {
        negCount++;
      }
    }

    pp = posCount / (posCount + negCount);
    np = negCount / (posCount + negCount);
    S = -pp * Log(pp) - np * Log(np);
    return S;
  }

  double P_posCount =
      0.0f;  // when attribute = 1, the number of positive labels
  double P_negCount =
      0.0f;  // when attribute = 1, the number of negative labels
  double N_posCount =
      0.0f;  // when attribute = 0, the number of positive labels
  double N_negCount =
      0.0f;          // when attribute = 0, the number of negative labels
  double P_pp;       // when attribute = 1, p(+)
  double P_np;       // when attribute = 1, p(-)
  double N_pp;       // when attribute = 0, p(+)
  double N_np;       // when attribute = 0, p(-)
  double Sp = 0.0f;  // entropy of subset which attribute = 1
  double Sn = 0.0f;  // entropy of subset which attribute = 0
  for (auto iter = rows.cbegin(); iter != rows.cend(); ++iter) {
    // splitting by index(attribute)
    if (iter->at(index) == 1 && iter->back() == 1) {
      P_posCount++;
    }
    if (iter->at(index) == 1 && iter->back() == 0) {
      P_negCount++;
    }

    if (iter->at(index) == 0 && iter->back() == 1) {
      N_posCount++;
    }
    if (iter->at(index) == 0 && iter->back() == 0) {
      N_negCount++;
    }
  }

  if (P_posCount + P_negCount) {
    P_pp = P_posCount / (P_posCount + P_negCount);
    P_np = 1 - P_pp;
    Sp = -P_pp * Log(P_pp) - P_np * Log(P_np);
  }

  if (N_posCount + N_negCount) {
    N_pp = N_posCount / (N_posCount + N_negCount);
    N_np = 1 - N_pp;
    Sn = -N_pp * Log(N_pp) - N_np * Log(N_np);
  }

  double i = P_posCount + P_negCount;
  double j = N_posCount + N_negCount;
  if (i + j) {
    S = (i / (i + j)) * Sp + (j / (i + j)) * Sn;
  }

  return S;
}

void Data::Calc_Info_Gain() {
  double TotalEn = get_Entropy(-1);
  for (unsigned int i = 0; i < att_names.size() - 1; i++) {
    att_InfoGain.push_back(TotalEn - get_Entropy(i));
  }
}

bool Data::pure_labels() const {
  if (rows.empty()) {
    return true;
  }

  auto iter = rows.cbegin();
  int temp = iter->back();

  ++iter;
  while (iter != rows.cend() && iter->back() == temp) {
    ++iter;
  }

  return (iter == rows.cend());
}

int Data::get_majority_of_data() const {
  int one_nums = 0;
  int zero_nums = 0;
  for (auto iter = rows.cbegin(); iter != rows.cend(); iter++) {
    if (iter->back() == 1) {
      one_nums++;
    }
    if (iter->back() == 0) {
      zero_nums++;
    }
  }

  return (one_nums >= zero_nums) ? 1 : 0;
}
