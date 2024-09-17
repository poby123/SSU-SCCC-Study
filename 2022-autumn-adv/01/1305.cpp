/*
 * g++ --std=c++17 1305.cpp -o test
 * https://www.acmicpc.net/problem/1305
 *
 * 문제요약:
 * 길이가 L인 전광판이 있다.
 * 길이가 L이라는 것은 L개의 문자를 한 번에 표시할 수 있다는 것이다.
 * 광고업자는 길이가 N인 광고를 무한히 붙여서 광고한다.
 * 이때 가능한 광고중에서 가장 짧은 길이를 구하여라.
 *
 * 풀이:
 * 광고판은 반복되어 재생되는데, 이 때의 최소 주기를 구하는 문제이다.
 * 따라서 광고판에 나오는 길이가 L인 문자열을 Cyclic Shift하여 붙인 문자열에서,
 * Prefix와 Suffix가 일치하는 가장 긴 문자열 X를 구한 뒤,
 * L에서 X의 길이를 뺀 것이 가장 짧은 광고의 길이라고 할 수 있다.
 *
 * 광고판의 길이인 L까지의 범위에서 가장 긴 prefix와 suffix가 나온 위치를
 * 의미하는 F[L-1]을 X의 길이라고 생각할 수 있다.
 * 따라서 L - F[L-1]을 구하면 된다.
 *
 * 참고:
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int L;
string S;

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> L >> S;
  auto fail = getFail(S + S);
  cout << L - fail[L - 1];

  return 0;
}