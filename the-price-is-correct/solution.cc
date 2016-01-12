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
    int N, P;
    fin >> N >> P;

    vector<int> B(N, 0);
    for (int i = 0; i < N; ++i) {
      fin >> B[i];
    }

    // two pointers.
    int end = -1;
    // damn!!!
    long long count = 0;
    int range_sum = 0;

    // O(n) complexity.
    for (int begin = 0; begin < N; ++begin) {
      // promise: range_sum is the sum of B[begin, end) and range_sum <= P.
      if (end < begin) {
        end = begin;
        range_sum = 0;
      }
      while (end < N && range_sum + B[end] <= P) {
        range_sum += B[end];
        ++end;
      }
      count += end - begin;
      range_sum -= B[begin];
    }

    fout << "Case #" << case_idx << ": " << count << endl;
  }

  fout.close();
}
