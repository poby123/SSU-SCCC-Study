/*
 * g++ --std=c++17 4354.cpp -o test
 * https://www.acmicpc.net/problem/4354
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> getFail(const string& S) {
  int n = S.size();
  vector<int> fail(n, 0);

  for (int i = 1, j = 0; i < n; i++) {
    while (j > 0 && S[i] != S[j]) j = fail[j - 1];
    if (S[i] == S[j]) {
      fail[i] = ++j;
    }
  }

  return fail;
}

auto canDivide = [](int a, int b) -> bool { return a % b == 0; };

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (1) {
    string S;
    cin >> S;
    if (S == ".") {
      break;
    }

    const auto fail = getFail(S);
    const int n = S.size();
    if (!canDivide(n, n - fail[n - 1])) {
      cout << 1 << endl;
      continue;
    }

    cout << n / (n - fail[n - 1]) << endl;
  }

  return 0;
}