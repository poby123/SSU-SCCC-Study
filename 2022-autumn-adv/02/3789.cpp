/**
 * g++ --std=c++17 3789.cpp -o test
 *
 * 문제 요약:
 * 문자열 S가 주어지면, S의 cyclic shift 중
 * 사전 순으로 가장 앞선 문자열을 구하는 문제
 *
 * 풀이:
 * SS의 Suffix Array를 구한 뒤, |S| 이상인 접미사 가운데, 가장 앞선 접미사를
 * 구하면 된다.
 *
 **/

#include <bits/stdc++.h>
using namespace std;

vector<int> getSuffixArray(const string& s) {
  int n = s.size();
  vector<int> sa(n), pos(n), temp(n);

  for (int i = 0; i < n; i++) {
    sa[i] = i;
    pos[i] = s[i];
  }

  for (int k = 1;; k <<= 1) {
    auto cmp = [&](int a, int b) {
      if (pos[a] != pos[b]) {
        return pos[a] < pos[b];
      }

      if (a + k < n && b + k < n) {
        return pos[a + k] < pos[b + k];
      }

      return a > b;
    };

    sort(sa.begin(), sa.end(), cmp);

    for (int i = 1; i < n; i++) {
      temp[i] = temp[i - 1] + cmp(sa[i - 1], sa[i]);
    }

    for (int i = 0; i < n; i++) {
      pos[sa[i]] = temp[i];
    }

    if (temp.back() + 1 == n) {
      break;
    }
  }

  return sa;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int x;
    string s;
    cin >> x >> s;

    string ss = s + s;
    const auto suffix_array = getSuffixArray(ss);

    int suffix_index = -1;
    for (int i = 0; i < ss.size(); i++) {
      if (suffix_array[i] > s.size()) {
        continue;
      }

      if (suffix_index == -1) {
        suffix_index = suffix_array[i];
        continue;
      }

      if (ss.substr(suffix_index, s.size()) ==
          ss.substr(suffix_array[i], s.size())) {
        suffix_index = min(suffix_index, suffix_array[i]);
        continue;
      }

      break;
    }

    cout << suffix_index << "\n";
  }

  return 0;
}