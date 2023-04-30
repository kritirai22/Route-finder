#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    bool isEndOfWord;

    TrieNode()
    {
        isEndOfWord = false;
    }
};

class Trie
{
public:
    int total_nodes;
    int total_words;
    TrieNode *root;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(string str);
    TrieNode *search_exact(string str);
    vector<string> search_pre(string str);
    void draw(TrieNode *current, int depth);
};

void Trie::insert(string str)
{
    TrieNode *current = root;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            current->children.insert(make_pair(ch, new TrieNode()));
            current = current->children[ch];
        }
    }

    current->isEndOfWord = true;
}

TrieNode *Trie::search_exact(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    TrieNode *current = root;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            return NULL;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\n"
         << current->isEndOfWord << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return current->isEndOfWord ? current : NULL;
}

void get_words_dfs(TrieNode *current, string pre, vector<string> &results)
{
    if (current == NULL)
    {
        return;
    }
    if (current->isEndOfWord)
    {
        results.push_back(pre);
    }

    for (auto i : current->children)
    {
        get_words_dfs(i.second, (pre + i.first), results);
    }
}

vector<string> Trie::search_pre(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    auto start = chrono::high_resolution_clock::now(); // to calculate time

    TrieNode *current = root;
    vector<string> results;

    for (int i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else if (current->children.find(ch) == current->children.end())
        {
            return results;
        }
    }

    get_words_dfs(current, str, results);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << "available locations: " << "\033[0m\n";

    return results;
}



vector<string> global_search(vector<string> v, string pat)
{
    transform(pat.begin(), pat.end(), pat.begin(), ::tolower);
    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : v)
    {
        bool match = true;
        for(int j=0; j<( str.size()-pat.size() +1);j++)
        {
            for(int i=0; i<pat.size(); i++)
            {
                if(str[j+i] != pat[i])
                {
                    match = false;
                    break;
                }
            }
            if (match) {
                results.push_back(str);
                break;
            }
            match = true;
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}

