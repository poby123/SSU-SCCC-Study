/**
 * g++ --std=c++17 5052.cpp -o test
 *
 * https://www.acmicpc.net/problem/5052
 *
 * 문제요약:
 * 숫자로 이루어진 N개의 문자열이 주어질 때,
 * 어떤 문자열이 다른 문자열의 접두사가 되는지 출력하라.
 *
 * 문제풀이:
 * 두가지 정도 방법이 있는데,
 * 첫 번째 방법은 문자열 배열을 정렬 후, 이전 배열이 다음 배열의 접두사가 되는지
 * 확인하는 것이다. 단순히 substring하여 비교하면 된다.
 *
 * 두 번째 방법은 트라이를 이용하는 방법이다.
 * 문자열 배열로 트라이를 구성한 뒤, 문자열 배열을 정렬하여 트라이를 하나씩
 * 탐색한다. 만약, 어떤 문자열을 검색하는데, 중간에 어떤 노드에서 끝난다면
 * 접두사인 문자열이 있다는 의미다.
 */

#include <bits/stdc++.h>
using namespace std;

class Trie {
 public:
  Trie* ch[10];
  int key;

  Trie() {
    fill(ch, ch + 10, nullptr);
    key = -1;
  }

  void insert(const char* s, int id) {
    if (*s == 0) {
      key = id;
      return;
    }

    if (!ch[*s - '0']) {
      ch[*s - '0'] = new Trie();
    }

    ch[*s - '0']->insert(s + 1, id);
  }

  int findUntilEnd(const char* s) {
    if (*s == 0) {
      return -1;
    }

    if (!ch[*s - '0']) {
      return -1;
    }

    // if end during find
    if (ch[*s - '0']->key != -1) {
      return ch[*s - '0']->key;
    }

    return ch[*s - '0']->findUntilEnd(s + 1);
  }
};

bool solve() {
  int N;
  cin >> N;
  auto trie = new Trie();

  vector<string> v(N);
  sort(v.begin(), v.end());

  for (int i = 0; i < N; i++) {
    cin >> v[i];
    trie->insert(v[i].c_str(), i);
  }

  for (int i = 0; i < N; i++) {
    int key = trie->findUntilEnd(v[i].c_str());
    if (key != i) {
      return false;
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    auto ans = solve();
    cout << (ans ? "YES" : "NO") << endl;
  }

  return 0;
}