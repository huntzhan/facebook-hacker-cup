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

double CalculateIntervalExpected(
    // accumulate interval.
    const int a, const int b,
    // gloabl interval.
    const int A, const int B) {
  int l = max(a, A);
  int r = min(b, B);
  int ldiff = l - a;
  int rdiff = r - a;
  return 1.0 *
         (ldiff + rdiff) / 2 *
         (r - l) / (B - A);
}

void MoveForwardInterval(
    const vector<int> &C,
    int &interval_begin, int &interval_end, int &step) {
  const int N = C.size();

  step = (step + 1) % N;
  interval_begin = interval_end;
  interval_end = interval_begin + C[step];
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

    double expected = 0.0;

    int step = 0;
    // locate first interleave interval.
    int interval_begin = yacht_price * (A / yacht_price);
    int interval_end = interval_begin + C[step];
    while (interval_end < A) {
      MoveForwardInterval(C, interval_begin, interval_end, step);
    }
    
    // first interval.
    expected += CalculateIntervalExpected(
        interval_begin, interval_end,
        A, B);

    // move to the next step.
    MoveForwardInterval(C, interval_begin, interval_end, step);

    // skip intermediate intervals.
    if (interval_end <= B) {
      int intermediate_size = (B - interval_begin) / yacht_price;
      for (int i = 0; i < N; ++i) {
        expected += 1.0 *
                    C[i] / 2 *
                    (intermediate_size * C[i]) / (B - A);
      }
      // move interval forward.
      interval_begin += intermediate_size * yacht_price;
      interval_end = interval_begin + C[step];
    }

    while (interval_begin < B) {
      expected += CalculateIntervalExpected(
          interval_begin, interval_end,
          A, B);
      // move to next step.
      MoveForwardInterval(C, interval_begin, interval_end, step);
    }

    fout << fixed << setprecision(9)
         << "Case #" << case_idx << ": " << expected << endl;
  }

  fout.close();
}
