#include <bits/stdc++.h>
using namespace std;

class Trie {
 public:
  Trie *ch[26];
  int key;

  Trie() {
    fill(ch, ch + 26, nullptr);
    key = -1;
  }

  void insert(const char *s, int id) {
    // is null
    if (*s == 0) {
      key = id;
      return;
    }

    if (!ch[*s - 'a']) {
      ch[*s - 'a'] = new Trie();
    }

    ch[*s - 'a']->insert(s + 1, id);
  }

  int find(const char *s) {
    // is null
    if (*s == 0) {
      return key;
    }

    if (!ch[*s - 'a']) {
      return -1;
    }

    return ch[*s - 'a']->find(s + 1);
  }
};

int main() { return 0; }