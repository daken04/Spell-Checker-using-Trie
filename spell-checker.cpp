#include <iostream>
#include <vector>
using namespace std;

struct TrieNode
{
    TrieNode *points[26];
    bool flag = false;

    bool hasKey(char ch)
    {
        return points[ch - 'a'] != nullptr;
    }

    void insert(char ch, TrieNode *node)
    {
        points[ch - 'a'] = node;
    }
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    vector<string> Autocomplete(string word)
    {
        TrieNode *node = root;

        for (int i = 0; i < word.length(); i++)
        {
            if (!node->hasKey(word[i]))
            {
                return {};
            }

            node = node->points[word[i] - 'a'];
        }

        vector<string> results;

        dfs(node, word, results);

        return results;
    }

    vector<string> Autocorrect(string word, vector<string> &input)
    {
        vector<string> autocorrected;
        customMergeSort(input);
        for (auto z : input)
        {
            int temp = Levenshtein_distance(z, word);

            if (temp <= 3)
            {
                autocorrected.push_back(z);
            }
        }

        return autocorrected;
    }

    void dfs(TrieNode *node, string current, vector<string> &results)
    {
        if (node->flag)
        {
            results.push_back(current);
        }

        for (int i = 0; i < 26; i++)
        {
            if (node->points[i])
            {
                char ch = i + 'a';
                dfs(node->points[i], current + ch, results);
            }
        }
    }

    int Levenshtein_distance(string s1, string s2)
    {
        int n1 = s1.size();
        int n2 = s2.size();

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 0; i <= n1; i++)
        {
            for (int j = 0; j <= n2; j++)
            {
                if (i == 0)
                {
                    dp[i][j] = j;
                    continue;
                }

                if (j == 0)
                {
                    dp[i][j] = i;
                    continue;
                }

                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                }
            }
        }

        return dp[n1][n2];
    }

    int Spell_check(string word)
    {
        TrieNode *node = root;

        for (int i = 0; i < word.length(); i++)
        {
            if (!node->hasKey(word[i]))
            {
                return false;
            }

            node = node->points[word[i] - 'a'];
        }

        if (node->flag == true)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void Insert(string word)
    {
        TrieNode *node = root;

        for (int i = 0; i < word.length(); i++)
        {
            if (!node->hasKey(word[i]))
            {
                node->insert(word[i], new TrieNode());
            }

            node = node->points[word[i] - 'a'];
        }

        node->flag = true;
    }

    // Custom Merge Sort function for sorting the vector
    void customMergeSort(vector<string> &vec)
    {
        int n = vec.size();
        if (n <= 1)
        {
            return;
        }

        vector<string> left(vec.begin(), vec.begin() + n / 2);
        vector<string> right(vec.begin() + n / 2, vec.end());

        customMergeSort(left);
        customMergeSort(right);

        int i = 0, j = 0, k = 0;
        int leftSize = left.size();
        int rightSize = right.size();

        while (i < leftSize && j < rightSize)
        {
            if (left[i] < right[j])
            {
                vec[k++] = left[i++];
            }
            else
            {
                vec[k++] = right[j++];
            }
        }

        while (i < leftSize)
        {
            vec[k++] = left[i++];
        }

        while (j < rightSize)
        {
            vec[k++] = right[j++];
        }
    }
};

int main()
{
    Trie t;

    int n, q;
    cin >> n >> q;

    vector<string> input;

    while (n--)
    {
        string s;
        cin >> s;

        input.push_back(s);

        t.Insert(s);
    }

    while (q--)
    {
        int m;
        cin >> m;

        string st;
        cin >> st;

        if (m == 1)
        {
            cout << t.Spell_check(st) << endl;
        }
        else if (m == 2)
        {
            vector<string> temp = t.Autocomplete(st);
            cout << temp.size() << endl;
            for (auto z : temp)
            {
                cout << z << endl;
            }
        }
        else if (m == 3)
        {
            vector<string> temp2 = t.Autocorrect(st, input);
            cout << temp2.size() << endl;
            for (auto z : temp2)
            {
                cout << z << endl;
            }
        }
    }
}
