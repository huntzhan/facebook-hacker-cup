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

int CountBits(unsigned int x) {
  int c = 0;
  for (; x; ++c) {
    x = x & (x - 1);
  }
  return c;
}

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N;
    fin >> N;

    vector<vector<bool>> W(N, vector<bool>(N, false));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int flag;
        fin >> flag;
        W[i][j] = flag;
      }
    }

    const int upper_bound = 1 << N;
    // dp[subset][i]: True if ith competitor could win the subset tourment in
    // some permutation.
    vector<vector<bool>> dp(upper_bound, vector<bool>(N, false));
    // initial states.
    for (int i = 0; i < N; ++i) {
      dp[1 << i][i] = true;
    }

    // maximum tourment that ith competitor can win.
    vector<int> max_tourments(N, 1);
    // minimum tourment that ith competitor can lose.
    vector<int> min_tourments(N, INT_MAX);

    for (int b = 1; b < upper_bound; ++b) {
      int b_cnt = CountBits(b);
      if (b_cnt == 1 || b_cnt & (b_cnt - 1)) {
        continue;
      }
      for (int b1 = (b - 1) & b; b1; b1 = (b1 - 1) & b) {
        int b1_cnt = CountBits(b1);
        if (b1_cnt != b_cnt / 2) {
          continue;
        }
        int b2 = b ^ b1;
        // now, b1, b2 are valid subsets.

        // i: winner of b1.
        // j: winner of b2.
        for (int i = 0; i < N; ++i) {
          for (int j = 0; j < N; ++j) {
            if (!dp[b1][i] || !dp[b2][j]) {
              continue;
            }
            if (W[i][j]) {
              dp[b][i] = true;
              max_tourments[i] = max(max_tourments[i], b_cnt);
              min_tourments[j] = min(min_tourments[j], b_cnt);
            } else {
              dp[b][j] = true;
              max_tourments[j] = max(max_tourments[j], b_cnt);
              min_tourments[i] = min(min_tourments[i], b_cnt);
            }
          }
        }
      }
    }

    unordered_map<int, int> size_round_mapping;
    size_round_mapping[INT_MAX] = 0;
    for (int k = log2(N), round = 1; k >= 0; --k, ++round) {
      size_round_mapping[1 << k] = round;
    }
    vector<int> round_rank_mapping(static_cast<int>(log2(N) + 2));
    round_rank_mapping[1] = 1;
    for (int i = 0; i < log2(N); ++i) {
      round_rank_mapping[i + 2] = 1 + (1 << i);
    }

    fout << "Case #" << case_idx << ":" << endl;
    for (int i = 0; i < N; ++i) {
      int r1 = size_round_mapping[max_tourments[i]];
      int r2 = size_round_mapping[min_tourments[i]] + 1;
      fout << round_rank_mapping[r1] << " " << round_rank_mapping[r2] << endl;
    }
  }

  fout.close();
}
