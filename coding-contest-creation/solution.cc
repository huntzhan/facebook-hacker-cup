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

    vector<int> D(N);
    for (int i = 0; i < N; ++i) {
      fin >> D[i];
    }

    // the number of additional problems you'll need to write.
    int count = 0;
    // the first index of unprocessed questions.
    int cur_index = 0;
    // the rating of last problem.
    int pre_rating = INT_MIN;

    while (cur_index < N) {
      // reset.
      pre_rating = INT_MIN;

      for (int i = 0; i < 4; ++i) {
        // corner case: reaching the end of D.
        if (cur_index == N) {
          count += 4 - i;
          break;
        }

        if (pre_rating != INT_MIN &&
            // 1. strictly increasing.
            // 2. difference <= 10.
            (D[cur_index] <= pre_rating || D[cur_index] - pre_rating > 10)) {
          // insert new problem.
          ++count;
          pre_rating += 10;
        } else {
          // use D[cur_index].
          pre_rating = D[cur_index];
          ++cur_index;
        }
      }
    }

    fout << "Case #" << case_idx << ": " << count << endl;
  }

  fout.close();
}
