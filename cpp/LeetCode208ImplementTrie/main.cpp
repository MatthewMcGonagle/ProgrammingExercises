// Implementation that stores keys in each level in a std::map.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct TrieNode {

    map<char, TrieNode*> children;
};

class Trie {

    public:

        Trie();
        void insert(string word);
        bool search(string word);
        bool startsWith(string prefix);
        void print();

    private:
        
        TrieNode* root;
        void insertMissing(string::iterator begin, string::iterator end, TrieNode* missing);
};

// Debug functions.

template<typename T>
void myPrint(vector<T> words) {
    
    vector<string>::iterator wordIt;

    for(wordIt = words.begin(); wordIt != words.end() - 1; wordIt++)
        cout << *wordIt << ", ";
    cout << *wordIt << "." << endl;
}

void myPrintString(string word) {

    string::iterator letterIt;
    for(letterIt = word.begin(); letterIt != word.end(); letterIt++)
        cout << *letterIt;
    cout << endl;
}

template<typename T, typename K>
void myPrintMap(map<T,K> m) {

    typename map<T,K>::iterator mapIt;

    if(m.empty())
        cout << "Empty";
    else {
        for(mapIt = m.begin(); mapIt != m.end(); mapIt++) 
            cout << "(" << mapIt -> first
                 << ", " << mapIt -> second << ")  ";
    }

    cout << endl;
}

template void myPrintMap<char, TrieNode*>(map<char, TrieNode*> m);

void printTrie(TrieNode *t);
void printTrieDebug(TrieNode *t);

int main() {

    const char *trieWordsInit[] = {"apple", "orange", "appropriate", "apply", "opal"},
               *searchWordsInit[] = {"ace", "apple", "banana", "application", "opal"};
    vector<string> trieWords(trieWordsInit, trieWordsInit + sizeof(trieWordsInit) / sizeof(char*)),
                   searchWords(searchWordsInit, searchWordsInit + sizeof(searchWordsInit) / sizeof(char*));
    Trie t;

    cout << "Words to put into trie are:" << endl;
    myPrint(trieWords);

    for(vector<string>::iterator wordIt = trieWords.begin(); wordIt != trieWords.end(); wordIt++)
        t.insert(*wordIt);
 
    cout << "Words to search are:" << endl;
    myPrint(searchWords);

    cout << "The trie tree is:" << endl;
    t.print();

    return 1;

}


Trie::Trie() {

    root = new TrieNode;

}

void Trie::insert(string word) {

    TrieNode *current = root, *newChild;
    map<char, TrieNode*>::iterator nextChildIt; 
    string::iterator charIt; 
    bool stillSearching = true;
    
    for(charIt = word.begin(); stillSearching && charIt != word.end(); charIt++) {

        nextChildIt = current -> children . find(*charIt);
        if(nextChildIt == current -> children . end()) {
            stillSearching = false;

            // Add children for the rest of word.
            insertMissing(charIt, word.end(), current);
        } 
        else
            current = nextChildIt -> second;
    }


}

bool Trie::search(string word) {

    return false;

}


bool Trie::startsWith(string prefix) {

    return false;
}

void Trie::print() {

    printTrie(root);

}

void Trie::insertMissing(string::iterator begin, string::iterator end, TrieNode* missing) {

    string::iterator charIt;
    TrieNode *newNode;
    
    for(charIt = begin; charIt != end; charIt++) {

        newNode = new TrieNode;
        missing -> children . insert (pair<char, TrieNode*>(*charIt, newNode));
        missing = newNode;

    }
}

void printTrie(TrieNode *t) {

    TrieNode *current;
    map<char, TrieNode *>::iterator childrenIt;
    queue<TrieNode*> toPrint, endOfLine; 

    if(t == NULL)
        return;
    
    toPrint.push(t);
    endOfLine.push(t);

    while(!toPrint.empty()) {
        current = toPrint.front();
        toPrint.pop();  

        if(current -> children.empty())
            cout << "_ ";

        for(childrenIt = current -> children.begin(); childrenIt != current -> children.end(); childrenIt++) {
            cout << childrenIt -> first << " ";
            toPrint.push(childrenIt -> second);
        }

        if (current == endOfLine.front()) {
            if(!current -> children.empty())
                endOfLine.push( current -> children.rbegin() -> second);
            endOfLine.pop();
            cout << endl;
        }
        else if (!toPrint.empty())
            cout << "| ";
    }
}

void printTrieDebug(TrieNode* t) {

    TrieNode *current;
    queue<TrieNode*> toPrint;
    map<char, TrieNode*>::iterator childIt;

    if(t == NULL)
        cout << "Trie empty" << endl;

    toPrint.push(t);

    while(!toPrint.empty()) {

        current = toPrint.front();
        toPrint.pop();

        cout << "Address: " << current << " -> ";
        if(current -> children.empty())
            cout << "Empty";
        else {
            for(childIt = current->children.begin(); childIt != current -> children.end(); childIt++) {
                cout << "(" << childIt -> first 
                     << ", " << childIt -> second << ") ";
                toPrint.push(childIt -> second);
            }
        }
        cout << endl; 
    }
}
