// g++ test.cpp --std=c++17  -o test

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define MAX 1000000

const int h = ((int)ceil(log2(MAX)));
const int treeSize = (1 << (h + 1));

struct Seg
{
  vector<ll> tree = vector<ll>(treeSize, 0);
  int sz = treeSize >> 1;

  void update(int x, ll v)
  {
    x |= sz;
    ll diff = v - tree[x];
    tree[x] = v;
    while (x >>= 1)
    {
      tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }
  }

  ll query(int l, int r)
  {
    l |= sz, r |= sz;
    ll ret = 0;
    while (l <= r)
    {
      if (l & 1)
        ret += tree[l++];
      if (~r & 1)
        ret += tree[r--];
      l >>= 1, r >>= 1;
    }
    return ret;
  }
} seg;

int N, M, K;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M >> K;
  for (int i = 1; i <= N; i++)
  {
    ll x;
    cin >> x;
    seg.update(i, x);
  }

  for (int i = 0; i < M + K; i++)
  {
    ll a, b, c;
    cin >> a >> b >> c;
    if (a == 1)
    {
      seg.update(b, c);
    }
    else
    {
      cout << seg.query(b, c) << "\n";
    }
  }

  return 0;
}
