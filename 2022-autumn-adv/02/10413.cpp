/**
 * g++ --std=c++17 10413.cpp -o test
 **/

#include <bits/stdc++.h>
using namespace std;

vector<int> getSuffixArray(const string& s) {
  int n = s.size();
  vector<int> sa(n), isa(n), temp(n);

  auto counting_sort = [&]() {
    vector<int> count(max(256, n), 0);
    for (int i = 0; i < n; i++) {
      ++count[isa[i]];
    }
    partial_sum(count.begin(), count.end(), count.begin());
    for (int i = n - 1; i >= 0; i--) {
      sa[--count[isa[temp[i]]]] = temp[i];
    }
  };

  for (int i = 0; i < n; i++) {
    sa[i] = temp[i] = i;
    isa[i] = s[i];
  }

  counting_sort();

  for (int k = 1;; k <<= 1) {
    int index = 0;
    for (int i = n - k; i < n; i++) {
      temp[index++] = i;
    }

    for (int i = 0; i < n; i++) {
      if (sa[i] >= k) {
        temp[index++] = sa[i] - k;
      }
    }

    counting_sort();
    temp[sa[0]] = 0;

    for (int i = 1; i < n; i++) {
      temp[sa[i]] = temp[sa[i - 1]];
      if (sa[i - 1] + k < n && sa[i] + k < n && isa[sa[i - 1]] == isa[sa[i]] &&
          isa[sa[i - 1] + k] == isa[sa[i] + k]) {
        continue;
      }
      ++temp[sa[i]];
    }

    swap(isa, temp);
    if (isa[sa.back()] + 1 == n) {
      break;
    }
  }

  return sa;
}

vector<int> getLCPArray(string& s, vector<int>& sa) {
  int N = s.length();
  vector<int> lcp(N), isa(N);
  for (int i = 0; i < N; i++) isa[sa[i]] = i;
  for (int i = 0, k = 0; i < N; i++, k = max(k - 1, 0)) {
    if (isa[i] == 0) continue;
    for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
    lcp[isa[i]] = k;
  }
  return lcp;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    string s;
    cin >> s;

    int n = s.size();
    auto sa = getSuffixArray(s);
    auto lcp = getLCPArray(s, sa);

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += max(lcp[i] - lcp[i - 1], 0);
    }
    cout << ans << "\n";
  }

  return 0;
}