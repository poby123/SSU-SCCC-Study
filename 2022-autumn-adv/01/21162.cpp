/**
 * g++ --std=c++17 21162.cpp -o test
 *
 * 문제 요약:
 * 길이가 N인 수열이 주어지는데, 이 수열을 길이가 0이 아닌 두 부분으로 나누어서
 * 두 부분의 순서를 각각 반대로 한 뒤 다시 이어붙인다고 해보자. 이렇게해서
 * 만들어지는 N-1개의 수열을 사전순으로 정렬했을 때, K번째 오는 수열을 알아보자.
 *
 * 풀이:
 * https://justicehui.github.io/ps/2021/03/09/BOJ21162/
 *
 * 1 2 3 4 5 이런 수열이 있다고 할 때, 문제에서 시키는 대로 해보면
 *
 * 1 5 4 3 2
 * 2 1 5 4 3
 * 3 2 1 5 4
 * 4 3 2 1 5
 *
 * 위와 같은 수열이 만들어지는데, 잘 보면 한 칸씩 밀리는 것을 볼 수 있다.
 * 이런 수열을 Cyclic Shift 하다고 하는데,
 * 입력으로 들어온 수열을 뒤집어서 5 4 3 2 1 로 생각하면,
 * [1, N)번 Cyclic Shift한 수열을 만들게 됨을 알 수 있다.
 *
 * Cyclic Shift는 문자열을 두 배로 늘리면 처리하기 쉬워진다.
 * 5 4 3 2 1 5 4 3 2 1
 *
 * 우리는 A[2..N+1], A[3..N+2], ... , A[N..2N-1]을 사전순으로 정렬했을 때 K번째
 * 문자열을 찾으면 된다.
 *
 * 어떤 두 문자열 A, B가 있을 때, A가 B보다 사전순으로 앞선다면
 * A[0..X-1] == B[0..X-1]이며, A[X] < B[X] 라는 것을 의미한다.
 * 따라서 두 문자열이 처음으로 달라지는 위치를 파라메트릭 서치를 이용해
 * O(logN)에 찾아 문자열을 비교할 수 있으며,
 * 따라서 N개의 문자열을 O(Nlog^2N)에 정렬할 수 있다.
 *
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <ll P, ll M>
class Hashing {
 private:
  vector<ll> H, C;

 public:
  void build(const vector<int>& v) {
    H.resize(v.size() + 1);
    C.resize(v.size() + 1);
    C[0] = 1;

    for (int i = 1; i <= v.size(); i++) {
      H[i] = (H[i - 1] * P + v[i - 1]) % M;
    }

    for (int i = 1; i <= v.size(); i++) {
      C[i] = (C[i - 1] * P) % M;
    }
  }

  ll get(int s, int e) {
    ++s;
    ++e;
    ll result = (H[e] - H[s - 1] * C[e - s + 1]) % M;
    return result >= 0 ? result : result + M;
  }
};

int N, K;
vector<int> V;
Hashing<524287, 998244353> H1;

/** 처음으로 달라지는 위치를 찾습니다. */
bool cmp(int a, int b) {
  int l = 0, r = N - 1;

  while (l < r) {
    int m = (l + r + 1) / 2;
    auto h1 = H1.get(a, a + m - 1), h2 = H1.get(b, b + m - 1);

    if (h1 == h2)
      l = m;
    else
      r = m - 1;
  }

  if (l == N - 1) return false;
  return V[a + l] < V[b + l];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> K;
  V.resize(N);

  for (auto& i : V) cin >> i;
  reverse(V.begin(), V.end());
  for (int i = 0; i < N - 1; i++) V.push_back(V[i]);

  H1.build(V);

  vector<int> O(N - 1);
  iota(O.begin(), O.end(), 1);
  stable_sort(O.begin(), O.end(), cmp);
  for (int i = 0; i < N; i++) cout << V[O[K - 1] + i] << " ";
}
