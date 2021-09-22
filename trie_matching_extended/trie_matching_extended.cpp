#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	Node* nodes[Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;

	auto root = new Node();
	auto curr = root;

	for (const auto& pattern : patterns) {

		int i = 0;
		curr = root;

		while (i < pattern.size()) {

			if (curr->next[letterToIndex(pattern[i])] != -1) {
				curr = curr->nodes[letterToIndex(pattern[i])];
				i += 1;
			}
			else {
				auto newNode = new Node();
				curr->nodes[letterToIndex(pattern[i])] = newNode;
				curr->next[letterToIndex(pattern[i])] = 1;
				curr = curr->nodes[letterToIndex(pattern[i])];
				i += 1;
			}

		}
		curr->patternEnd = true;
	}


	int k = 0, idx = 0;
	curr = root;
	while (k < text.size()) {

		idx = k;
		curr = root;

		while ( idx < text.size() ) {

			if (curr->patternEnd == true) {
				result.push_back(k);
				break;
			}
			else if (curr->next[letterToIndex(text[idx])] == -1) {
				break;
			}
			else {
				curr = curr->nodes[letterToIndex(text[idx])];
				idx += 1;
			}
		}

		if (idx == text.size() && curr->patternEnd == true) {
			result.push_back(k);
		}

		k += 1;
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	int name;
	std::cin >> name;

	return 0;
}
