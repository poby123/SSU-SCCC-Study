// g++ test.cpp --std=c++17  -o test

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define MAX 101

int N, M;
int dp_mem[MAX][MAX * MAX], mem[MAX], cost[MAX];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    cin >> mem[i];
  }

  int sum_cost = 0;
  for (int i = 1; i <= N; i++) {
    cin >> cost[i];
    sum_cost += cost[i];
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= sum_cost; j++) {
      if (j - cost[i] >= 0) {
        dp_mem[i][j] = max(dp_mem[i][j], dp_mem[i - 1][j - cost[i]] + mem[i]);
      }
      dp_mem[i][j] = max(dp_mem[i][j], dp_mem[i - 1][j]);
    }
  }

  for (int j = 0; j <= sum_cost; j++) {
    if (dp_mem[N][j] >= M) {
      cout << j << "\n";
      break;
    }
  }

  return 0;
}
