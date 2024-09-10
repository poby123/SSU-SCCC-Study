// https://www.acmicpc.net/workbook/view/13236

/**
 *
 * 해싱
 * 라빈 카프 알고리즘
 * 문자열의 길이가 L인 문자열을 해시한다고 하자.
 * f("s0s1...sL-1") = s0 * C^(L-1) + s1 * C^(L-2) + ... + s
 *
 * 부분 문자열의 해시
 * H[i] = S[0..i]의 해시값
 * H[i] = s0 * Ci + s1 * Ci-1
 *
 */

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

template <ll P, ll M>
class Hashing {
 private:
  vector<ll> H, C;

 public:
  void build(const string& str) {
    H.resize(str.size() + 1);
    C.resize(str.size() + 1);
    C[0] = 1;

    for (int i = 1; i <= str.size(); i++) {
      H[i] = (H[i - 1] * P + str[i - 1]) % M;
    }

    for (int i = 1; i <= str.size(); i++) {
      C[i] = (C[i - 1] * P) % M;
    }
  }

  ll get(int s, int e) {
    ll result = (H[e] - H[s - 1] * C[e - s + 1]) % M;
    return result >= 0 ? result : result + M;
  }
};

int main() {
  Hashing<100, 1000000007> hash;
  const string s = "test message";

  hash.build(s);

  const ll result = hash.get(0, s.size());
  cout << result << endl;

  return 0;
}