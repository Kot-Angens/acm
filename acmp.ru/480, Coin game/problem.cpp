#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

ostream& print(const vector<int>& v, ostream& os) {
  copy(v.begin(), v.end(), ostream_iterator<vector<int>::value_type>(os, " "));
  return os;
}

ostream& print(const vector<vector<int> >& v, ostream& os) {
  for (vector<vector<int> >::const_iterator i = v.begin(); i != v.end(); ++i) {
    print(*i, os) << endl;
  }
  return os;
}

void solve(istream& is, ostream& os) {
  int N; is >> N;
  vector<int> v(N, 0);
  for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
    is >> *i;
  int K; is >> K;
  vector<int> s(N, 0);
  s[N - 1] = v[N - 1];
  for (int i = N - 2; i >= 0; --i)
    s[i] = s[i + 1] + v[i];
  vector<vector<int> > dp(K + 1, vector<int>(N, -1));
  for (int r = N - 1; r >= 0; --r) {
    for (int m = 1; m <= K; ++m) {
      if (r + m >= N)
        dp[m][r] = s[r];
      else {
        int max_gain = -1;
        for (int i = 1; i <= m; ++i) {
          int t = s[r] - dp[i][r + i];
          if (t > max_gain || i == 1)
            max_gain = t;
        }
        assert(max_gain != -1);
        dp[m][r] = max_gain;
      }
    }
  }
  os << dp[K][0] << endl;
}

#ifdef int
#undef int
#endif

#include <ctime>

void run(const string& test_name, const char* input, const char* output) {
  const char* liner = "--------";
  stringstream is(input);
  stringstream os;
  clock_t started = clock();
  solve(is, os);
  clock_t elapsed = clock() - started;
  if (os.str() != output) {
    cerr << "Case '" << test_name << "': FAILED" << endl;
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else {
    cerr << "Case '" << test_name << "': OK";
    if (elapsed > CLOCKS_PER_SEC / 200)
      cerr << " time " << elapsed * (1.0/CLOCKS_PER_SEC) << "s";
    cerr << endl;
  }
}

void run_test(const string& test_name) {
  ifstream test(test_name.c_str());
  if (test.fail()) return;
  ostringstream input, output;
  string line;
  bool is_input = true;
  while (getline(test, line)) {
    if (line.substr(0, 5) == "~~~~~")
      is_input = false;
    else
      (is_input ? input : output) << line << endl;
  }
  run(test_name, input.str().c_str(), output.str().c_str());
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

  string test_name; // = "test-0.tst";

  if (!test_name.empty()) {
    run_test(test_name);  
  } else {
    int case_id = 0;
    while (case_id < 100) {
      ostringstream fmt;
      fmt << "test-" << setfill('0') << setw(2) << case_id << ".tst";
      test_name = fmt.str();
      run_test(test_name);
      case_id += 1;
    }    
  }

#else

  ifstream is("input.txt");
  ofstream os("output.txt");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
