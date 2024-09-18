/**
 * g++ 14725.cpp --std=c++17  -o test
 *
 * 문제 요약:
 * 각 문자가 string인 트라이
 *
 * 문제 풀이:
 * Trie *ch[26] 대신, map<string, Trie>를 이용하면 된다.
 * 문자 대신에 문자열이 들어가므로 insert(const char *)가 아닌
 * insert(vector<string>)이 되어야한다.
 *
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Trie {
 private:
  map<string, Trie> ch;

 public:
  void insert(const vector<string>& v, int idx = 0) {
    if (idx == v.size()) return;

    auto it = ch.find(v[idx]);
    if (it == ch.end()) {
      it = ch.emplace(v[idx], Trie()).first;
    }
    it->second.insert(v, idx + 1);
  }

  void print(int depth = 0) {
    for (auto& [s, next] : ch) {
      cout << string(depth * 2, '-') << s << endl;
      next.print(depth + 1);
    }
  }
};

int N;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Trie trie;
  cin >> N;

  for (int i = 0; i < N; i++) {
    int K;
    cin >> K;

    vector<string> v(K);
    for (auto& s : v) {
      cin >> s;
    }
    trie.insert(v);
  }

  trie.print();

  return 0;
}