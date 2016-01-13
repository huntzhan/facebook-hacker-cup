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


int CountSegments(const vector<char> &G, const int N) {
  int count = 0;
  int begin, end;
  for (begin = 1; begin <= N; begin = end) {
    end = begin + 1;
    if (G[begin] != '.') {
      continue;
    }
    while (G[end] == '.') {
      ++end;
    }
    ++count;
  }
  return count;
}

int RemoveUnnecessaryGuards(vector<char> &base,
                            const vector<char> &other,
                            const int N) {
  int count = 0;
  for (int i = 1; i <= N; ++i) {
    if (base[i] != '.') {
      continue;
    }
    if (other[i] == '.' && other[i - 1] != '.' && other[i + 1] != '.') {
      ++count;
      // one consecutive segment could at most remove one unnecessary guard.
      int left = i - 1;
      while (base[left] == '.') {
        base[left] = 'X';
        --left;
      }
      int right = i;
      while (base[right] == '.') {
        base[right] = 'X';
        ++right;
      }
    }
  }
  return count;
}

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int N;
    fin >> N;

    // insert sentinels to simplfy the implementation.
    vector<char> G1(N + 2), G2(N + 2);
    G1[0] = 'X';
    G2[0] = 'X';
    G1[N + 1] = 'X';
    G2[N + 1] = 'X';

    for (int i = 1; i <= N; ++i) {
      fin >> G1[i];
    }
    for (int i = 1; i <= N; ++i) {
      fin >> G2[i];
    }

    int count = 0;
    count += CountSegments(G1, N);
    count += CountSegments(G2, N);
    count -= RemoveUnnecessaryGuards(G1, G2, N);
    count -= RemoveUnnecessaryGuards(G2, G1, N);
    
    fout << "Case #" << case_idx << ": " << count << endl;
  }

  fout.close();
}
