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

double Choose(int n, int k) {
  if (k > n) {
    return 0;
  }
  if (k * 2 > n) {
    k = n - k;
  }
  if (k == 0) {
    return 1;
  }

  double ret = n;
  for (int i = k; i >= 2; --i) {
    ret = ret * (n - i + 1) / i;
  }
  return ret;
}

double Possibility(const int n, const int k, const double p) {
  long double ret = 0.0;
  for (int i = k; i <= n; ++i) {
    ret += Choose(n, i) * pow(p, i) * pow(1 - p, n - i);
  }
  return ret;
}

int main() {
  int T;
  fin >> T;

  cout << Possibility(3000, 50, 0.987) << endl;
  cout << Possibility(2000, 50, 0.987) << endl;
  cout << Possibility(1000, 50, 0.987) << endl;
  cout << Possibility(300, 50, 0.987) << endl;
  cout << Possibility(200, 50, 0.987) << endl;
  cout << Possibility(100, 50, 0.987) << endl;
  cout << Possibility(50, 50, 0.987) << endl;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N, K;
    double p;
    fin >> N >> K >> p;

    double max_expected = 0;
    for (int group_size = K; group_size <= N; group_size += K) {
      int group_num = N / group_size;
      int real_group_size = group_size + (N % K) / group_num;
      int left_inc_size = (N % K) % group_num;

      double cur_expected = 0.0;

      cur_expected += left_inc_size * Possibility(real_group_size + 1, K, p);
      cur_expected += (group_num - left_inc_size) *
                      Possibility(real_group_size, K, p);

      max_expected = max(max_expected, cur_expected);
    }

    fout << "Case #" << case_idx << ": " << max_expected << endl;
  }

  fout.close();
}
