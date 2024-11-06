// g++ test.cpp --std=c++17  -o test

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define MAX 9
using pp = pair<int, int>;
vector<pp> blanks;

int N;
int G[MAX][MAX] = {0};
bool isDone;

const int dy[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
const int dx[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

bool isAvailable(int n, int y, int x) {
  int sy = y / 3 * 3;
  int sx = x / 3 * 3;

  for (int i = 0; i < MAX; i++) {
    if (G[y][i] == n) {
      return false;
    }

    if (G[i][x] == n) {
      return false;
    }

    if (G[sy + dy[i]][sx + dx[i]] == n) {
      return false;
    }
  }

  return true;
}

void solve(int i) {
  if (i == blanks.size()) {
    isDone = true;
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < MAX; j++) {
        cout << G[i][j];
      }
      cout << "\n";
    }

    return;
  }

  auto [y, x] = blanks[i];
  for (int t = 1; t < 10; t++) {
    if (isDone) {
      return;
    }

    if (!isAvailable(t, y, x)) {
      continue;
    }

    G[y][x] = t;
    solve(i + 1);
    G[y][x] = 0;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  blanks.reserve(80);

  for (int i = 0; i < MAX; i++) {
    string str;
    getline(cin, str);

    for (int j = 0; j < MAX; j++) {
      G[i][j] = str[j] - '0';

      if (!G[i][j]) {
        blanks.push_back({i, j});
      }
    }
  }

  solve(0);

  return 0;
}