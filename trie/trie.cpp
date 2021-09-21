#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  // write your code here

  edges root;
  t.push_back( root );

  for (const auto& pattern : patterns) {

      int i = 0, j = 0;

      while ( t[i].find(pattern[j]) != t[i].end() ) {

          i = t[i][pattern[j]];
          j += 1;

      }
      edges val;
      t.push_back( val );
      t[i][pattern[j]] = t.size() - 1;

      j += 1;

      while (j < pattern.size()) {

          edges newVal;
          t.push_back( newVal );
          t[t.size() - 2][pattern[j]] = t.size() - 1;
          j += 1;
      }
  }

  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  string s;
  std::cin >> s;
 
  return 0;
}