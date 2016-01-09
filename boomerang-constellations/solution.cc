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


int Pow2(const int num) {
  return num * num;
}

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx){
    int N;
    fin >> N;

    vector<int> x(N, 0);
    vector<int> y(N, 0);

    // read points.
    for (int i = 0; i < N; ++i) {
      fin >> x[i] >> y[i];
    }

    int count = 0;

    for (int i = 0; i < N; ++i) {
      unordered_map<int, int> distance_count;
      for (int j = 0; j < N; ++j) {
        if (i == j) {
          continue;
        }
        // -10,000 ≤ Xi, Yi ≤ 10,000.
        // hence Pow2(x[i] - x[j]) in the range of [0, 4 * 10^8]
        // power_of_distance would not overflow.
        int distance = Pow2(x[i] - x[j]) + Pow2(y[i] - y[j]);
        ++distance_count[distance];
      }

      for (const auto &e : distance_count) {
        int num = e.second;
        count += num * (num - 1) / 2;
      }
    }

    fout << "Case #" << case_idx << ": " << count << endl;
  }

  fout.close();
}
