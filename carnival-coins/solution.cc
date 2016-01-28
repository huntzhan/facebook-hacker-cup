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
    double p;
    fin >> N >> K >> p;

    vector<vector<double>> choose_dp(N + 1, vector<double>(N + 1, 0.0));
    // init.
    choose_dp[0][0] = 1.0;
    for (int i = 1; i <= N; ++i) {
      choose_dp[i][0] = (1 - p) * choose_dp[i - 1][0];
    }
    // choose_dp[i][j]: i choose j.
    // choose_dp[i][j] = p * choose_dp[i - 1][j - 1] +
    //                   (1 - p) * choose_dp[i - 1][j]
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= i; ++j) {
        choose_dp[i][j] = p * choose_dp[i - 1][j - 1] +
                          (1 - p) * choose_dp[i - 1][j];
      }
    }

    // choose_k[i]: sigma(i choose j, K <= j <= i).
    vector<double> choose_k(N + 1, 0.0);
    for (int i = K; i <= N; ++i) {
      for (int j = K; j <= i; ++j) {
        choose_k[i] += choose_dp[i][j];
      }
    }

    vector<double> prize_dp(N + 1);
    // init.
    for (int i = 0; i < K; ++i) {
      prize_dp[i] = 0.0;
    }
    // prize_dp[i] = max(prize_dp[j] + choose_k[i - j], 0 <= j < i).
    for (int i = K; i <= N; ++i) {
      prize_dp[i] = choose_k[i];
      for (int j = K; j < i; ++j) {
        prize_dp[i] = max(prize_dp[i], prize_dp[j] + choose_k[i - j]);
      }
    }

    fout << fixed << setprecision(9)
         << "Case #" << case_idx << ": " << prize_dp[N] << endl;
  }

  fout.close();
}
