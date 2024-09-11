/*
 * g++ --std=c++17 17228.cpp -o test
 * https://www.acmicpc.net/problem/17228
 *
 * 문제요약:
 * 그래프의 간선마다 문자가 하나씩 존재한다.
 * 1번 노드에서 출발하며, 1번 노드에서는 다른 모든 노드에 도달할 수 있다.
 * 간선을 지날 때마다 얻는 문자를 순서대로 나열하여 문자열로 만들 때,
 * 입력으로 주어지는 문자열이 몇 번 등장하는지 구하여라.
 * 등장한다는 것은 부분 문자열도 포함한다.
 *
 * 풀이:
 * 입력으로 주어진 문자열이 문자열 배열의 부분 문자열로 몇 번 등장하는지 세는
 * 문제다. DFS를 통해 노드를 방문하며 문자열S 을 하나씩 만들어간다.
 * 노드에 방문할 때마다 S[..r]까지의 해시값인 H[r]을 계산하여 스택에
 * 추가하며, 스택의 크기가 입력 문자열의 길이 이상이라면 부분문자열의 해시값인
 * H[l..r]을 구하여 비교한다. 이때 부분 문자열의 길이는 입력으로 주어지는
 * 문자열의 길이와 같아야 할 것이므로, r-l+1은 입력으로 주어지는 문자열의 길이와
 * 같으며, H[l..r] = H[r] - H[l-1] * C^(r-l+1) 에서
 * C^(r-l+1)은 C^(입력으로 주어지는 문자열의 길이)와 같다.
 *
 * 참고:
 * (x % M + M) % M
 * 이런식의 나머지 연산을 하면 x가 음수일 때도 올바르게 양수 나머지를 구할 수
 * 있다. 부호 문제를 고려하지 않고 안전하게 할 때 좋은 것 같다.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll P = 524287, M = 998244353;

int N;
string S;
ll H, C = 1;
vector<ll> Stack;
vector<pair<int, char>> G[500001];
int ans = 0;

void dfs(int x) {
  if (Stack.size() > S.size()) {
    ll cur = (Stack.back() - Stack[Stack.size() - S.size() - 1] * C);
    cur = (cur % M + M) % M;
    ans += cur == H;
  }

  for (auto [next, flower] : G[x]) {
    Stack.push_back((Stack.back() * P + flower) % M);
    dfs(next);
    Stack.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  for (int i = 0; i < N; i++) {
    int s, e;
    char f;
    cin >> s >> e >> f;

    G[s].emplace_back(e, f);
  }

  cin.clear();
  cin >> S;

  for (char i : S) {
    H = (H * P + i) % M;
    C = (C * P) % M;
  }

  Stack.push_back(0);
  dfs(1);

  cout << ans;

  return 0;
}