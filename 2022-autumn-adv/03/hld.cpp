#include <bits/stdc++.h>
using namespace std;

struct Seg
{
    int tree[1 << 18];
    int sz = 1 << 17;

    void update(int x, int v)
    {
        x |= sz;
        tree[x] += v;
        while (x >>= 1)
        {
            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        }
    }

    int query(int l, int r)
    {
        l |= sz, r |= sz;
        int ret = 0;
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

int sz[101010], depth[101010], parent[101010], top[101010], in[101010], out[101010];
vector<int> g[101010];
vector<int> inp[101010]; // 입력 / 양방향 그래프

int chk[101010];
void dfs(int v = 1)
{
    chk[v] = 1;
    for (auto i : inp[v])
    {
        if (chk[i])
            continue;
        chk[i] = 1;
        g[v].push_back(i);
        dfs(i);
    }
}

void dfs1(int v = 1)
{
    sz[v] = 1;
    for (auto &i : g[v])
    {
        depth[i] = depth[v] + 1;
        parent[i] = v;
        dfs1(i);
        sz[v] += sz[i];
        if (sz[i] > sz[g[v][0]])
            swap(i, g[v][0]);
    }
}

int pv;
void dfs2(int v = 1)
{
    in[v] = ++pv;
    for (auto i : g[v])
    {
        top[i] = i == g[v][0] ? top[v] : i;
        dfs2(i);
    }
    out[v] = pv;
}

void update(int v, int w)
{
    seg.update(in[v], w);
}

int query(int a, int b)
{
    int ret = 0;
    while (top[a] ^ top[b])
    {
        if (depth[top[a]] < depth[top[b]])
            swap(a, b);
        int st = top[a];
        ret += seg.query(in[st], in[a]);
        a = parent[st];
    }
    if (depth[a] > depth[b])
        swap(a, b);
    ret += seg.query(in[a], in[b]);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q; // 정점 개수, 쿼리 개수
    for (int i = 1; i < n; i++)
    {
        int s, e;
        cin >> s >> e;
        inp[s].push_back(e);
        inp[e].push_back(s);
    }
    dfs();
    dfs1();
    dfs2();
    while (q--)
    {
        // 1 v w : update v w
        // 2 s e : query s e
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1)
            update(a, b);
        else
            cout << query(a, b) << "\n";
    }
}