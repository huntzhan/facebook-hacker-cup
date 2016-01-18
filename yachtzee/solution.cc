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

double CalExpect(const int begin, const int end, const long long total) {
  return static_cast<double>(1LL * end * end - 1LL * begin * begin) / (2 * total);
}

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N, A, B;
    fin >> N >> A >> B;

    long long yacht_price = 0;
    vector<int> C(N);
    for (int i = 0; i < N; ++i) {
      fin >> C[i];
      yacht_price += C[i];
    }

    // [begin, end) pairs.
    vector<pair<int, int>> non_full_intervals;

    // ignore the amount of money spent on yachts.
    int shift_money = A - (A % yacht_price);
    A -= shift_money;
    B -= shift_money;

    int money = A;

    int step = 0;
    while (money >= C[step]) {
      money -= C[step];
      ++step;
    }
    if (money > 0) {
      // be careful with the corner case.
      int interval_end = min(C[step], B - (A - money));
      auto interval = make_pair(money, interval_end);
      non_full_intervals.push_back(interval);
      // money points to the next step.
      money = A + (interval.second - interval.first);
      step = (step + 1) % N;
    }

    // skip intermedia full steps.
    long long intermediate_size = (B - money) / yacht_price;
    if (intermediate_size > 0) {
      money += intermediate_size * yacht_price;
    }

    // count tailing steps.
    vector<int> tailing_step_indices;
    while (money < B) {
      if (money + C[step] <= B) {
        tailing_step_indices.push_back(step);
        money += C[step];
      } else {
        auto interval = make_pair(0, B - money);
        non_full_intervals.push_back(interval);
        // exit while loop.
        money = B;
      }
      step = (step + 1) % N;
    }

    // create PDF.
    long long total = 0;
    for (const auto &interval : non_full_intervals) {
      total += interval.second - interval.first;
    }
    for (int i = 0; i < N; ++i) {
      total += intermediate_size * C[i];
    }
    for (const int step : tailing_step_indices) {
      total += C[step];
    }

    double expected_amount = 0.0;
    for (const auto &interval : non_full_intervals) {
      expected_amount += CalExpect(interval.first, interval.second, total);
    }
    for (int i = 0; i < N; ++i) {
      expected_amount += intermediate_size * CalExpect(0, C[i], total);
    }
    for (const int step : tailing_step_indices) {
      expected_amount += CalExpect(0, C[step], total);
    }

    fout << "Case #" << case_idx << ": " << fixed << setprecision(9) << expected_amount << endl;
  }

  fout.close();
}
