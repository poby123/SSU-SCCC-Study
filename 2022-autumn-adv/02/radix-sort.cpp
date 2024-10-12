#include <bits/stdc++.h>
using namespace std;

vector<int> countSort(vector<int>& array, int exp) {
  vector<int> count(10, 0);
  vector<int> temp(array.size());

  for (auto i : array) {
    ++count[(i / exp) % 10];
  }

  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  for (int i = array.size() - 1; i >= 0; --i) {
    temp[--count[(array[i] / exp) % 10]] = array[i];
  }

  return temp;
}

vector<int> radixSort(vector<int>& array) {
  const int maximum = *max_element(array.begin(), array.end());
  for (int i = 1; maximum / i > 0; i *= 10) {
    array = countSort(array, i);
  }

  return array;
}

int main() {
  vector<int> array({75, 45, 170, 802, 66, 24, 2, 90});
  const auto result = radixSort(array);

  for (int i : array) {
    cout << i << " ";
  }

  cout << endl;

  return 0;
}