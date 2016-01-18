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

using LaundryState = pair<long long, long long>;

using MinLaundryHeap =
    priority_queue<LaundryState, vector<LaundryState>, greater<LaundryState>>;

int main() {
  int T;
  fin >> T;

  for (int case_idx = 1; case_idx <= T; ++case_idx) {
    int L, N, M, D;
    fin >> L >> N >> M >> D;

    vector<long long> end_times;
    MinLaundryHeap min_laundry_heap;
    // init min_laundry_heap.
    for (int i = 0; i < N; ++i) {
      int w;
      fin >> w;
      min_laundry_heap.emplace(w - 1, w);
    }

    // greedy strategy to find the minimum end time, O(L * log(N))
    for (int l = 0; l < L; ++l) {
      auto laundry_state = min_laundry_heap.top();
      min_laundry_heap.pop();

      end_times.push_back(laundry_state.first);

      // update next end time and push back to heap.
      laundry_state.first += laundry_state.second;
      min_laundry_heap.push(laundry_state);
    }

    // dry the cloths, O(L)
    vector<long long> dryer_end_times(M, 0);
    int dryer_index = 0;
    for (const auto laundry_end_time : end_times) {
      auto dryer_end_time = dryer_end_times[dryer_index];
      dryer_end_times[dryer_index] = max(dryer_end_time, laundry_end_time) + D;
  
      dryer_index = (dryer_index + 1) % M;
    }

    // return last calculated time.
    auto total_end_time = dryer_end_times[(dryer_index - 1 + M) % M] + 1;

    fout << "Case #" << case_idx << ": " << total_end_time << endl;
  }

  fout.close();
}
