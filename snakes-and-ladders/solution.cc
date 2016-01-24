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

int AddCost(const long long cost, long long length) {
  const int kBase = 1000000007;
  return (cost + (length * length) % kBase) % kBase;
}

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N;
    fin >> N;
    vector<pair<int, int>> xh_pairs(N);
    for (int i = 0; i < N; ++i) {
      fin >> xh_pairs[i].first >> xh_pairs[i].second;
    }
    sort(xh_pairs.begin(), xh_pairs.end());

    int cost = 0;
    for (int i = 0; i < N - 1; ++i) {
      int j = i + 1;
      while (true) {
        while (j < N && xh_pairs[j].second < xh_pairs[i].second) {
          ++j;
        }
        if (j == N || xh_pairs[j].second > xh_pairs[i].second) {
          break;
        }
        // xh_pairs[j].second == xh_pairs[i].second.
        cost = AddCost(cost, xh_pairs[j].first - xh_pairs[i].first);
        ++j;
      }
    }

    fout << "Case #" << case_idx << ": " << cost << endl;
  }

  fout.close();
}
