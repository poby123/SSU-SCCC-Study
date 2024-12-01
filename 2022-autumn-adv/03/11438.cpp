// g++ 11438.cpp --std=c++17 -o test

#include <bits/stdc++.h>
using namespace std;
#define MAX 100001

/** HLD */
int in[MAX], out[MAX], depth[MAX], top[MAX], parent[MAX], tree_size[MAX];
vector<int> inputs[MAX], G[MAX];

int visited[MAX];
void hld_build_graph(int v = 1) {
  visited[v] = 1;

  for (auto i : inputs[v]) {
    if (visited[i]) {
      continue;
    }

    visited[i] = 1;
    G[v].push_back(i);
    hld_build_graph(i);
  }
}

void hld_size(int v = 1) {
  tree_size[v] = 1;

  for (auto& i : G[v]) {
    depth[i] = depth[v] + 1;
    parent[i] = v;

    hld_size(i);
    tree_size[v] += tree_size[i];

    if (tree_size[i] > tree_size[G[v][0]]) {
      swap(i, G[v][0]);
    }
  }
}

int pv;
void hld_chaining(int v = 1) {
  in[v] = ++pv;

  for (auto& i : G[v]) {
    top[i] = (i == G[v][0] ? top[v] : i);
    hld_chaining(i);
  }

  out[v] = pv;
}

int hld_lca(int a, int b) {
  while (top[a] ^ top[b]) {
    if (depth[top[a]] < depth[top[b]]) {
      swap(a, b);
    }
    int st = top[a];
    a = parent[st];
  }

  if (depth[a] > depth[b]) {
    swap(a, b);
  }

  return a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N;

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    inputs[u].push_back(v);
    inputs[v].push_back(u);
  }

  hld_build_graph();
  hld_size();
  hld_chaining();

  cin >> M;
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    cout << hld_lca(a, b) << "\n";
  }

  return 0;
}