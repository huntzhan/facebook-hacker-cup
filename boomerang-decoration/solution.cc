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
    int N;
    fin >> N;

    string A, B;
    fin >> A >> B;

    vector<int> ldp(N);
    ldp[0] = 1;
    for (int i = 1; i < N; ++i) {
      ldp[i] = B[i] == B[i - 1]? ldp[i - 1] : ldp[i - 1] + 1;
    }
    ldp[0] = A[0] == B[0]? 0 : 1;
    for (int i = 1; i < N; ++i) {
      ldp[i] = A[i] == B[i]? ldp[i - 1] : ldp[i];
    }

    vector<int> rdp(N);
    rdp[N - 1] = 1;
    for (int i = N - 2; i >= 0; --i) {
      rdp[i] = B[i] == B[i + 1]? rdp[i + 1] : rdp[i + 1] + 1;
    }
    rdp[N - 1] = A[N - 1] == B[N - 1]? 0 : 1;
    for (int i = N - 2; i >= 0; --i) {
      rdp[i] = A[i] == B[i]? rdp[i + 1] : rdp[i];
    }
    
    int min_time = INT_MAX;
    for (int i = 0; i < N - 1; ++i) {
      int cur_min_time = max(ldp[i], rdp[i + 1]);
      min_time = min(min_time, cur_min_time);
    }

    fout << "Case #" << case_idx << ": " << min_time << endl;
  }

  fout.close();
}
