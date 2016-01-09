// {{{ $VIMCODER$ <-----------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// }}}

const string kInputFilename = "input.txt";
const string kOutputFilename = "output.txt";

ifstream fin(kInputFilename);
ofstream fout(kOutputFilename);


int ToNum(const vector<int> &digits, const int pos) {
  int ret = 0;
  for (int i = pos - 1; i >= 0; --i) {
    ret = 10 * ret + digits[i];
  }
  return ret;
}


int main() {
  int n;
  fin >> n;

  int case_index = 1;
  while (n > 0) {
    int num;
    fin >> num;

    vector<int> digits(15, 0);

    fout << "Case #" << case_index << ": ";

    if (num == 0) {
      fout << 0 << " " << 0 << endl;
    } else {
      int pos = 0;
      while (num > 0) {
        digits[pos++] = num % 10;
        num /= 10;
      }
      
      // min.
      int min_pos = pos - 1;
      for (int i = 0; i < pos; ++i) {
        if (digits[i] != 0 && digits[i] < digits[min_pos]) {
          min_pos = i;
        }
      }
      swap(digits[pos - 1], digits[min_pos]);
      fout << ToNum(digits, pos) << " ";
      swap(digits[pos - 1], digits[min_pos]);

      // max.
      int max_pos = pos - 1;
      for (int i = 0; i < pos; ++i) {
        if (digits[i] != 0 && digits[i] > digits[max_pos]) {
          max_pos = i;
        }
      }
      swap(digits[pos - 1], digits[max_pos]);
      fout << ToNum(digits, pos) << endl;
      swap(digits[pos - 1], digits[max_pos]);
    }
    --n;
    ++case_index;
  }
  fout.close();
}
