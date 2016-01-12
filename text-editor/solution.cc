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



int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N, K;
    fin >> N >> K;

    vector<string> words;
    // build words, O(nlogn).
    for (int i = 0; i < N; ++i) {
      string word;
      fin >> word;
      words.push_back(word);
    }
    sort(words.begin(), words.end());

    vector<vector<int>> common_prefix_length(N, vector<int>(N));
    // build common_prefix_length, O(n^2)
    for (int end = 0; end < N; ++end) {
      for (int begin = 0; begin < end; ++begin) {
        int index = 0;
        const auto &left = words[begin];
        const auto &right = words[end];
        while (index < left.size() && index < right.size() &&
               left[index] == right[index]) {
          ++index;
        }
        common_prefix_length[begin][end] = index;
      }
    }

    // dp.
    vector<int> pre_count(N, 0);
    vector<int> cur_count(N);
    // init pre_count.
    for (int i = 0; i < N; ++i) {
      pre_count[i] = words[i].size();
    }

    for (int k = 2; k <= K; ++k) {
      // promise:
      // * pre_count: dp[k - 1][i], minimum operations to print (k - 1) words,
      //   ending with the ith word.
      // * cur_count: dp[k][i].

      // dp[k][i] = min({dp[k - i][j] + cost(j, i), j < i})
      for (int end = 0; end < N; ++end) {
        int min_cost = INT_MAX;
        for (int begin = k - 2; begin < end; ++begin) {
          int prefix = common_prefix_length[begin][end];
          int transform_cost =
              static_cast<int>(words[begin].size() + words[end].size()) -
              2 * prefix;
          min_cost = min(min_cost, pre_count[begin] + transform_cost);
        }
        cur_count[end] = min_cost;
      }
      
      swap(pre_count, cur_count);
    }

    int min_cost = INT_MAX;
    for (int i = K - 1; i < N; ++i) {
      min_cost = min(min_cost,
                     pre_count[i] + static_cast<int>(words[i].size()));
    }

    fout << "Case #" << case_idx << ": " << min_cost + K << endl;
  }

  fout.close();
}
