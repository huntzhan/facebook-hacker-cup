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

inline
int CountBits(unsigned int x) {
  // int c = 0;
  // for (; x; ++c) {
  //   x = x & (x - 1);
  // }
  // return c;
  return __builtin_popcount(x);
}

// promise: x is power of 2.
inline
int Log2(unsigned int x) {
  // static const int MultiplyDeBruijnBitPosition2[32] = {
  //   0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
  //   31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
  // };
  // return MultiplyDeBruijnBitPosition2[(uint32_t)(x * 0x077CB531U) >> 27];
  return __builtin_ctz(x);
}

inline
int TourmentSizeToRank(const int size, const int round_offset, const int N) {
  int round;
  if (size == INT_MAX) {
    round = round_offset;
  } else {
    round = Log2(N) - Log2(size) + 1 + round_offset;
  }
  return round == 1? 1 : 1 + (1 << (round - 2));
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

        for (int wi = b1; wi != 0; wi = wi & (wi - 1)) {
          int i = Log2(wi & -wi);
          for (int wj = b2; wj != 0; wj = wj & (wj - 1)) {
            int j = Log2(wj & -wj);

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

    fout << "Case #" << case_idx << ":" << endl;
    for (int i = 0; i < N; ++i) {
      fout << TourmentSizeToRank(max_tourments[i], 0, N)
           << " "
           << TourmentSizeToRank(min_tourments[i], 1, N)
           << endl;
    }
  }

  fout.close();
}
