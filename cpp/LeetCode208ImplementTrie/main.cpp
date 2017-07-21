// Implementation that stores keys in each level in a std::map.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct TrieNode {

    map<char, TrieNode*> children;
    bool isEnd;

    TrieNode() : isEnd(false), children() {}
};

class Trie {

    public:

        Trie();
        void insert(string word);
        bool search(string word);
        bool startsWith(string prefix);
        void print();

    private:
        
        TrieNode* root, * searchPoint;
        bool stringFound;
        TrieNode* insertMissing(string::iterator begin, string::iterator end, TrieNode* missing);
        void searchString(string &word);
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

    // Correct output = {null, null, true, false, null, true, null, true}
    const char *trieWordsInit[] = {"abc", "ab", "ab"},
               *searchWordsInit[] = {"abc", "ab"};
    // const char *trieWordsInit[] = {"apple", "orange", "appropriate", "apply", "opal", "apples"},
    //            *searchWordsInit[] = {"ace", "apple", "banana", "application", "opal", "apples", "oranges", "acer", "app"};
    vector<string> trieWords(trieWordsInit, trieWordsInit + sizeof(trieWordsInit) / sizeof(char*)),
                   searchWords(searchWordsInit, searchWordsInit + sizeof(searchWordsInit) / sizeof(char*));
    Trie t;
    bool wordFound;

    cout << "Words to put into trie are:" << endl;
    myPrint(trieWords);

    for(vector<string>::iterator wordIt = trieWords.begin(); wordIt != trieWords.end(); wordIt++)
        t.insert(*wordIt);
 
    cout << "Words to search are:" << endl;
    myPrint(searchWords);

    cout << "The trie tree is:" << endl;
    t.print();
    cout << endl;
    
    cout << std::boolalpha;
    cout << "The results of searching are" << endl;
    for(vector<string>::iterator wordIt = searchWords.begin(); wordIt != searchWords.end(); wordIt++) {
        cout << *wordIt << " = ";
        wordFound = t.search(*wordIt);
        cout << wordFound << ", ";
    }
    cout << endl;

    cout << "The results for searching prefixes are" << endl;
    for(vector<string>::iterator wordIt = searchWords.begin(); wordIt != searchWords.end(); wordIt++) {
        cout << *wordIt << " = ";
        wordFound = t.startsWith(*wordIt);
        cout << wordFound << ", ";
    }
    cout << endl;

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
            current = insertMissing(charIt, word.end(), current);
        } 
        else
            current = nextChildIt -> second;
    }
    current -> isEnd = true;

}

bool Trie::search(string word) {

    // Make sure word is contained in the trie.
    searchString(word);
    if(!stringFound)
        return false;
    // for( charIt = word.begin(); charIt != word.end(); charIt++) {

    //     nextNodeIt = current -> children . find(*charIt);

    //     if (nextNodeIt == current -> children . end() ) 
    //         return false;

    //     else 
    //         current = nextNodeIt -> second;
    // }

    // The pointer current should now be pointing to an end node if word is actually a key instead of just
    // a prefix.
    if (searchPoint -> isEnd)
        return true;
    else
        return false;

}


bool Trie::startsWith(string prefix) {

    searchString(prefix);
    
    return stringFound;
}

void Trie::print() {

    printTrie(root);

}

// Afer insertion is done, insertMissing returns a pointer to the terminal node.
TrieNode* Trie::insertMissing(string::iterator begin, string::iterator end, TrieNode* missing) {

    string::iterator charIt;
    TrieNode *newNode;
    
    for(charIt = begin; charIt != end; charIt++) {

        newNode = new TrieNode;
        missing -> children . insert (pair<char, TrieNode*>(*charIt, newNode));
        missing = newNode;

    }
    return missing;
}


void Trie::searchString(string &word) {

    string::iterator charIt;
    map<char, TrieNode*>::iterator nextNodeIt;

    searchPoint = root;

    // If loop successfully finishes, searchPoint should point to the terminal node.
    for(charIt = word.begin(); charIt != word.end(); charIt++) {
        nextNodeIt = searchPoint -> children . find(*charIt);
        if(nextNodeIt == searchPoint -> children.end() ) {
            stringFound = false;
            return;
        }
        else 
            searchPoint = nextNodeIt -> second;
    }    
    stringFound = true;
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
            cout << childrenIt -> first;
            if (childrenIt -> second -> isEnd)
                cout << "E";
            else
                cout << " ";
            cout  <<  " ";
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
                cout << "(" << childIt -> first;
                if (childIt -> second -> isEnd)
                    cout << " E"; 
                cout << ", " << childIt -> second << ") ";
                toPrint.push(childIt -> second);
            }
        }
        cout << endl; 
    }
}

