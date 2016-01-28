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

int AddCost(const long long cost, long long length) {
  const int kBase = 1000000007;
  return (cost + (length * length) % kBase) % kBase;
}

/* O(N^2), pretty slow.
int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N;
    fin >> N;
    vector<pair<int, int>> xh_pairs(N);
    for (int i = 0; i < N; ++i) {
      fin >> xh_pairs[i].first >> xh_pairs[i].second;
    }
    sort(xh_pairs.begin(), xh_pairs.end());

    int cost = 0;
    for (int i = 0; i < N - 1; ++i) {
      int j = i + 1;
      while (true) {
        while (j < N && xh_pairs[j].second < xh_pairs[i].second) {
          ++j;
        }
        if (j == N || xh_pairs[j].second > xh_pairs[i].second) {
          break;
        }
        // xh_pairs[j].second == xh_pairs[i].second.
        cost = AddCost(cost, xh_pairs[j].first - xh_pairs[i].first);
        ++j;
      }
    }

    fout << "Case #" << case_idx << ": " << cost << endl;
  }

  fout.close();
}
*/

using Point = pair<int, int>;
const int kBase = 1000000007;

struct ComparePoint {
  // 1. higher ladder(H_i) comes first.
  // 2. greater ladder base(X_i) comes first.
  bool operator() (const Point &a, const Point &b) const {
    if (a.second > b.second) {
      return true;
    } else if (a.second == b.second) {
      return a.first > b.first;
    } else {
      return false;
    }
  }
};

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N;
    fin >> N;

    vector<Point> xh_pairs(N);
    for (int i = 0; i < N; ++i) {
      fin >> xh_pairs[i].first >> xh_pairs[i].second;
    }
    // O(NlogN)
    sort(xh_pairs.begin(), xh_pairs.end(), ComparePoint());

    long long cost = 0;
    // accumulate the cost base on two pointers technique and set
    // assume ladder bases are unique.
    // the time complexity should be O(NlogN)
    set<int> searched;
    for (int begin = 0, end = 0; begin < N; begin = end) {
      end = begin + 1;
      searched.insert(xh_pairs[begin].first);
      while (end < N && xh_pairs[end].second == xh_pairs[begin].second) {
        auto iter = searched.lower_bound(xh_pairs[end].first);
        if (iter != searched.end() && *iter != xh_pairs[end - 1].first) {
          break;
        }
        searched.insert(xh_pairs[end].first);
        ++end;
      }
      // now, [begin, end) is a valid group for snakes.

      // O(n^2).
      // for (int i = begin; i < end; ++i) {
      //   for (int j = i + 1; j < end; ++j) {
      //     cost = AddCost(cost, xh_pairs[i].first - xh_pairs[j].first);
      //   }
      // }

      int group_size = end - begin;

      long long x = 0, y = 1;

      for (int i = 1; i < group_size; ++i) {
        long long d = xh_pairs[end - 1 - i].first -
                      xh_pairs[end - i].first;

        x += d * y + i * d * (d - 1);
        x %= kBase;

        y += 2 * i * d + 1;
        y %= kBase;

        cost += x;
        cost %= kBase;
      }
    }

    fout << "Case #" << case_idx << ": "
         << cost << endl;
  }

  fout.close();
}
