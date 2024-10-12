// g++ test.cpp --std=c++17  -o test

#include <bits/stdc++.h>
using namespace std;

int N, R, Q;
vector<vector<int>> G;
vector<int> numberOfNode;

int dfs(int node, int source) {
  for (auto next : G[node]) {
    if (next == source) {
      continue;
    }
    numberOfNode[node] += dfs(next, node);
  }
  return numberOfNode[node];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> R >> Q;
  G.resize(N + 1);
  numberOfNode.resize(N + 1, 1);

  for (int i = 0; i < N; i++) {
    G[i].reserve(4);
  }

  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  dfs(R, 0);

  for (int i = 0; i < Q; i++) {
    int x;
    cin >> x;
    cout << numberOfNode[x] << "\n";
  }

  return 0;
}