/**
 * g++ --std=c++17 suffix-array.cpp -o test
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> radixSort(const string& s) {
  vector<int> result;

  return result;
}

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

    cout << "temp: ";
    for (int i : temp) {
      cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
      pos[sa[i]] = temp[i];
    }

    cout << "sa: ";
    for (int i : sa) {
      cout << i << " ";
    }
    cout << endl;

    cout << "pos: ";
    for (int i : pos) {
      cout << i << " ";
    }
    cout << endl << endl;

    if (temp.back() + 1 == n) {
      break;
    }
  }

  return sa;
}

vector<int> getSuffixArray2(const string& s) {
  int n = s.size();
  vector<int> sa(n), isa(n), temp(n), count(256);

  auto counting_sort = [&]() {
    fill(count.begin(), count.end(), 0);
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

vector<int> getLcpArray(vector<int>& sa, vector<int>& pos, const string& s) {
  int n = s.size();
  vector<int> lcp(n);

  for (int i = 0, j = 0; i < n; i++, j = max(j - 1, 0)) {
    if (pos[i] == 0) continue;
    while (sa[pos[i] - 1] + j < n && sa[pos[i]] + j < n &&
           s[sa[pos[i] - 1] + j] == s[sa[pos[i]] + j]) {
      j++;
    }
    lcp[pos[i]] = j;
  }

  return lcp;
}

vector<int> buildlcp(vector<int>& sa, const string& s) {
  int n = s.size();
  vector<int> lcp(n), isa(n);
  for (int i = 0; i < n; ++i) isa[sa[i]] = i;
  for (int k = 0, i = 0; i < n; ++i)
    if (isa[i]) {
      for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; ++k);
      lcp[isa[i]] = (k ? k-- : 0);
    }
  return lcp;
}

int main() {
  const string s = "abaabcab";
  for (int i = 0; i < s.size(); i++) {
    cout << s.substr(i, s.size()) << ", ";
  }
  cout << endl;

  const vector<int> v = getSuffixArray(s);
  cout << "V1: ";
  for (int i : v) {
    cout << i << " ";
  }
  cout << endl;

  const vector<int> v2 = getSuffixArray2(s);
  cout << "V2: ";
  for (int i : v2) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}