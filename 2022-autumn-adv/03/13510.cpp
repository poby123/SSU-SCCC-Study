// g++ 13510.cpp --std=c++17  -o test
// https://www.acmicpc.net/problem/13510

#include <bits/stdc++.h>
using namespace std;

#define MAX 100001

int N;
vector<tuple<int, int, int>> edges;

/** Segment tree */
int tree[4 * MAX];
void seg_update(int node, int nodeL, int nodeR, int index, int val) {
  if (index < nodeL || nodeR < index) {
    return;
  }

  if (nodeL == nodeR) {
    tree[node] = val;
    return;
  }

  int m = (nodeL + nodeR) / 2;
  seg_update(node * 2, nodeL, m, index, val);
  seg_update(node * 2 + 1, m + 1, nodeR, index, val);

  tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int seg_query(int node, int nodeL, int nodeR, int l, int r) {
  if (r < nodeL || nodeR < l) {
    return 0;
  }

  if (l <= nodeL && nodeR <= r) {
    return tree[node];
  }

  int m = (nodeL + nodeR) / 2;
  return max(seg_query(node * 2, nodeL, m, l, r),
             seg_query(node * 2 + 1, m + 1, nodeR, l, r));
}

/** HLD */
int in[MAX], out[MAX], top[MAX], parent[MAX], depth[MAX], tree_size[MAX];
vector<int> inputs[MAX], G[MAX];

int visited[MAX];
void hld_build_graph(int v = 1) {
  visited[v] = 1;

  for (auto next : inputs[v]) {
    if (visited[next]) {
      continue;
    }

    G[v].push_back(next);
    visited[next] = 1;
    hld_build_graph(next);
  }
}

void hld_size(int v = 1) {
  tree_size[v] = 1;
  for (auto& next : G[v]) {
    depth[next] = depth[v] + 1;
    parent[next] = v;

    hld_size(next);
    tree_size[v] += tree_size[next];

    if (tree_size[next] > tree_size[G[v][0]]) {
      swap(next, G[v][0]);  // tree[G[v][0]] is heavy edge.
    }
  }
}

int pv;
void hld_chaining(int v = 1) {
  in[v] = ++pv;

  for (auto& next : G[v]) {
    // if (v, next) is heavy edge, is same chain
    //              is light edge, is new chain
    top[next] = (next == G[v][0] ? top[v] : next);
    hld_chaining(next);
  }

  out[v] = pv;
}

void hld_update(int u, int v, int w) {
  // update the deeper node, to save weight to child's node
  if (depth[u] < depth[v]) {
    swap(u, v);
  }

  seg_update(1, 1, MAX, in[u], w);
}

int hld_query(int a, int b) {
  int result = 0;
  while (top[a] ^ top[b]) {
    if (depth[top[a]] < depth[top[b]]) {
      swap(a, b);
    }
    int st = top[a];
    result = max(result, seg_query(1, 1, MAX, in[st], in[a]));
    a = parent[st];
  }

  if (depth[a] > depth[b]) {
    swap(a, b);
  }

  // each node has a weight value for edge connected to its parent node
  // so to get result for range a ~ b, query (in[a] + 1, in[b])
  result = max(result, seg_query(1, 1, MAX, in[a] + 1, in[b]));
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;

    edges.push_back({u, v, w});
    inputs[u].push_back(v);
    inputs[v].push_back(u);
  }

  hld_build_graph();
  hld_size();
  hld_chaining();

  for (int i = 0; i < N - 1; i++) {
    auto [u, v, w] = edges[i];
    hld_update(u, v, w);
  }

  int M;
  cin >> M;
  for (int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 1) {
      auto [u, v, w] = edges[b - 1];
      hld_update(u, v, c);
      continue;
    }

    cout << hld_query(b, c) << "\n";
  }

  return 0;
}