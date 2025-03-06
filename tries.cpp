student@PRLAB-8:~/6015$ ls
a.out  avltree.cpp  splaytree.cpp  tris.cpp
student@PRLAB-8:~/6015$ cat tris.cpp
#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isLeaf;

    TrieNode() {
        isLeaf = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode* root, const string& key) {
    TrieNode* curr = root;
    for (char c : key) {
        if (curr->children[c - 'a'] == nullptr) {
            TrieNode* newNode = new TrieNode();
            curr->children[c - 'a'] = newNode;
        }
        curr = curr->children[c - 'a'];
    }
    curr->isLeaf = true;
}

bool search(TrieNode* root, const string& key) {
    TrieNode* curr = root;
    for (char c : key) {
        if (curr->children[c - 'a'] == nullptr)
            return false;
        curr = curr->children[c - 'a'];
    }
    return curr->isLeaf;
}

bool spellCheck(TrieNode* root, const string& key) {
    return search(root, key);
}

void autocompleteHelper(TrieNode* node, const string& prefix, vector<string>& results) {
    if (node->isLeaf)
        results.push_back(prefix);

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            autocompleteHelper(node->children[i], prefix + char(i + 'a'), results);
        }
    }
}

vector<string> autocomplete(TrieNode* root, const string& prefix) {
    vector<string> results;
    TrieNode* curr = root;

    for (char c : prefix) {
        if (curr->children[c - 'a'] == nullptr)
            return results;
        curr = curr->children[c - 'a'];
    }

    autocompleteHelper(curr, prefix, results);
    return results;
}

bool deleteHelper(TrieNode* node, const string& key, int index) {
    if (index == key.size()) {
        if (!node->isLeaf)
            return false;
        node->isLeaf = false;
        return true;
    }

    char c = key[index];
    TrieNode* childNode = node->children[c - 'a'];
    if (childNode == nullptr)
        return false;

    bool deleted = deleteHelper(childNode, key, index + 1);

    if (deleted) {
        node->children[c - 'a'] = nullptr;
        if (!node->isLeaf) {
            for (int i = 0; i < 26; i++) {
                if (node->children[i] != nullptr) {
                    return true;
                }
            }
            return true;
        }
    }
    return false;
}

void remove(TrieNode* root, const string& key) {
    deleteHelper(root, key, 0);
}

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Insert a word\n";
    cout << "2. Delete a word\n";
    cout << "3. Spell Check\n";
    cout << "4. Autocomplete\n";
    cout << "5. Search a word\n";
    cout << "6. Exit\n";
}

int main() {
    TrieNode* root = new TrieNode();
    
    int choice;
    string word;
    vector<string> suggestions;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the word to insert: ";
                cin >> word;
                insert(root, word);
                cout << "Word inserted successfully.\n";
                break;
            
            case 2:
                cout << "Enter the word to delete: ";
                cin >> word;
                remove(root, word);
                cout << "Word deleted successfully (if it existed).\n";
                break;
            
            case 3:
                cout << "Enter the word for spell check: ";
                cin >> word;
                if (spellCheck(root, word))
                    cout << "The word is correct.\n";
                else
                    cout << "The word is incorrect.\n";
                break;
            
            case 4:
                cout << "Enter the prefix for autocomplete: ";
                cin >> word;
                suggestions = autocomplete(root, word);
                if (suggestions.empty()) {
                    cout << "No suggestions found.\n";
                } else {
                    cout << "Autocomplete suggestions: ";
                    for (const string& suggestion : suggestions) {
                        cout << suggestion << " ";
                    }
                    cout << endl;
                }
                break;
            
            case 5:
                cout << "Enter the word to search: ";
                cin >> word;
                if (search(root, word))
                    cout << "The word is present in the Trie.\n";
                else
                    cout << "The word is not present in the Trie.\n";
                break;
            
            case 6:
                cout << "Exiting the program.\n";
                return 0;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
