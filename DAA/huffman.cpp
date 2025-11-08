#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f, Node *l = nullptr, Node *r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};
struct Cmp
{
    bool operator()(Node *a, Node *b) const { return a->freq > b->freq; } // min-heap
};

void buildCodes(Node *root, string path, unordered_map<char, string> &code)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {                                               // leaf => real character
        code[root->ch] = path.empty() ? "0" : path; // single-char edge case -> "0"
        return;
    }
    buildCodes(root->left, path + '0', code);
    buildCodes(root->right, path + '1', code);
}

void freeTree(Node *root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);
    if (s.empty())
    {
        cout << "Empty input\n";
        return 0;
    }

    // 1) Frequency of each char 
    unordered_map<char, int> freq;
    for (char c : s)
        freq[c]++;

    // 2) Build min-heap of leaf nodes
    priority_queue<Node *, vector<Node *>, Cmp> pq;
    for (auto &p : freq)
        pq.push(new Node(p.first, p.second));

    // 3) Combine two smallest until one root remains
    while (pq.size() > 1)
    {
        Node *a = pq.top();
        pq.pop();
        Node *b = pq.top();
        pq.pop();
        pq.push(new Node('\0', a->freq + b->freq, a, b)); // internal node: ch = '\0'
    }
    Node *root = pq.top();

    // 4) DFS to get codes
    unordered_map<char, string> code;
    buildCodes(root, "", code);

    // 5) Encode
    string encoded;
    encoded.reserve(s.size() * 2);
    for (char c : s)
        encoded += code[c];

    // 6) Decode using the tree
    string decoded;
    Node *cur = root;
    for (char bit : encoded)
    {
        cur = (bit == '0') ? cur->left : cur->right;
        if (!cur->left && !cur->right)
        {
            decoded += cur->ch;
            cur = root;
        }
    }

    // Output
    cout << "Huffman Codes:\n";
    for (auto &p : code)
        cout << "'" << p.first << "' : " << p.second << "\n";
    cout << "Encoded: " << encoded << "\n";
    cout << "Decoded: " << decoded << "\n";

    // Optional: compression stats (bits per char)
    long long totalBits = 0;
    for (auto &p : freq)
        totalBits += 1LL * p.second * code[p.first].size();
    cout << fixed << setprecision(3)
         << "Average bits/char: " << (double)totalBits / (double)s.size() << "\n";

    freeTree(root);
    return 0;
}