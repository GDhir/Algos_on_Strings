#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
using std::hash;
using std::queue;

using edgeType = std::pair<int, int>;

struct hashPair {
    int operator()(const edgeType val) const {

        return hash<int>()(val.first) ^ hash<int>{}(val.second);

    }
};
class Node {

public:
    unordered_map< edgeType, Node*, hashPair > edges;
    int suffixStart;

    Node() {

        suffixStart = -1;

    }

};

std::tuple<int, int, bool> prefixMatch( edgeType edge, const string& text, int k ) {

    int idx = edge.first;

    for (; idx <= edge.second; idx++) {

        if (text[idx] != text[k]) {

            if (idx == edge.first) {
                return std::make_tuple(-1, 0, false);
            }
            else {
                return std::make_tuple(idx - 1, k, false);
            }
        }
        k += 1;
    }

    return std::make_tuple(idx - 1, k, true);
}


Node* buildSuffixTree( const string& text ) {

    int k = 0;
    auto root = new Node();
    auto curr = root;
    std::tuple<int, int, bool> result;

    while (k < text.size()) {

        curr = root;
        auto edgeIt = curr->edges.begin();
        int offset = k;

        while (1) {

            std::get<2>(result) = false;

            if (curr->edges.size() == 0) {
                auto newNode = new Node();
                newNode->suffixStart = k;
                curr->edges[std::make_pair(offset, text.size() - 1)] = newNode;
                break;
            }

            edgeIt = curr->edges.begin();
            
            while ( edgeIt != curr->edges.end() ) {
                result = prefixMatch( edgeIt->first, text, offset );

                if (std::get<0>(result) == -1) {
                    edgeIt++;
                }
                else {
                    break;
                }

            }

            if ( !std::get<2>(result) ) {

                Node* newNode1 = new Node();
                Node* newNode2 = new Node();

                if (edgeIt != curr->edges.end()) {
                    // Matches and break the edge in the middle
                    auto first = edgeIt->first.first;
                    auto second = edgeIt->first.second;
                    auto prevNode = edgeIt->second;

                    curr->edges.erase( edgeIt->first );
                    curr->edges[ std::make_pair( first, std::get<0>(result) ) ] = newNode1;

                    newNode1->edges[ std::make_pair( std::get<0>(result) + 1, second ) ] = prevNode;
                    newNode1->edges[std::make_pair(std::get<1>(result), text.size() - 1)] = newNode2;
                    newNode2->suffixStart = k;
                }
                else {
                    // Does not match at all. Create a new edge.
                    if (std::get<0>(result) == -1) {
                       curr->edges[std::make_pair(offset, text.size() - 1)] = newNode1;
                       newNode1->suffixStart = k;
                    }

                }
                break;
            }
            else {
                curr = edgeIt->second;
                offset = std::get<1>(result);
                continue;
            }
        }

        k += 1;

    }

    return root;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;

  Node* tree = buildSuffixTree( text );

  std::queue<Node*> val;
  val.push(tree);

  while ( !val.empty() ) {

      auto node = val.front();
      val.pop();

      for (auto& edge : node->edges) {

          result.push_back( text.substr( edge.first.first, edge.first.second - edge.first.first + 1 ) );
          val.push( edge.second );
      }

  }

  // Implement this function yourself
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }

  int name;
  cin >> name;

  return 0;
}
