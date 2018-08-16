/**
    LeetCode 146 LRU Cache

    Implement a Least Recently Used (LRU) Cache data structure. It is constructed with a certain capacity
    and should support two operations:

    1) get(key) Gets the value associated with the key if it exists, otherwise return -1.
    
    2) put(key, value) Inserts key and value. If the cache is already at capacity, then remove the
       least recently used item.

    Solution Idea: Store keys and values in a binary search tree using a standard ordered map. The 
    quanitity of "recenlty used" will be stored as a doubly linked list (non-ciruclar) among the values in the map.
    We separately store the beginning and end of the list. A key is always put at the head of the list.
    The end of the list is always the Least Recently Used item.

    Passes as beating 16.8% of all cpp submissions.
**/

#include<iostream>
#include<map>
#include<vector>

// Leet code requires us to use the standard namespace.
using namespace std;

/** 
    Holds the value of the key as well as the keys to the parent and child in list of recently used. We
    store the keys instead of pointers as the container for our map may be updated in non-trivial ways if
    as we insert and delete elements.
**/

struct KeyInfo {

    int value, parent, child;

    KeyInfo(int v, int p, int c) : value(v), parent(p), child(c) {}

};

/**
    The implementation of the LRU Cache. The form of the methods LRUCache(), get(), and put() are all
    specified by the Leet Code Problem.    

**/

class LRUCache {

public:

    LRUCache(int capacity); 
    int get(int key);
    void put(int key, int value);

private:
    
    void initializeCache(int key, int value);
    void nonEmptyAdd(int key, int value);
    void upgradeFront(map<int, KeyInfo>::iterator toMove); 
    void removeLeastUsed();

    inline const int& key(map<int, KeyInfo>::iterator pair) {return pair -> first;}
    inline KeyInfo& info(map<int, KeyInfo>::iterator pair) {return pair -> second;}
    inline int& parent(map<int, KeyInfo>::iterator pair) {return pair -> second . parent;}
    inline int& child(map<int, KeyInfo>::iterator pair) {return pair -> second . child;}

    int capacity, front, leastUsed;
    const static int ARBITRARY = -1;
    map<int, KeyInfo> cache;

};

int main() {

    // Failed input
    // ["LRUCache","put","put","put","put","get","get","get","get","put","get","get","get","get","get"]
    // [[3],[1,1],[2,2],[3,3],[4,4],[4],[3],[2],[1],[5,5],[1],[2],[3],[4],[5]]
    // Output 
    // [null,null,null,null,null,4,3,2,-1,null,-1,2,-1,4,5]
    // Expected
    // [null,null,null,null,null,4,3,2,-1,null,-1,2,3,-1,5]

    const int GET = -1;
    //int pairsArray[][2] = {{1, 1}, {2, 2}, {GET, 1}, {3, 3}, {GET, 2}, {4, 4}, {GET, 1}, {GET, 3}, {GET, 4}};
    int pairsArray[][2] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {GET, 4}, {GET, 3}, {GET, 2}, {GET, 1}, {5, 5}, {GET, 1}, {GET, 2}, {GET, 3}, {GET, 4}, {GET, 5}};
    int capacity = 3, output;
    vector<int[2]> pairs(pairsArray, pairsArray + sizeof(pairsArray) / sizeof(int) / 2);

    LRUCache cache(capacity);

    for (int i = 0; i < pairs.size(); i++) {
        cout << "(";
        if( pairs[i][0] == GET) 
            cout << "GET";
        else
            cout << pairs[i][0];
        cout << ", " << pairs[i][1] << ")   ";
    }

    cout << endl << "TESTING LRUCache" << endl;

    for (int i = 0; i < pairs.size(); i++) {

        cout << "i = " << i << endl;
        if(pairs[i][0] == GET) {
            cout << "Getting " << pairs[i][1]; 
            output = cache.get(pairs[i][1]);
            cout << " output = " << output << endl;
        }

        else { 

            cout << "Putting (" << pairs[i][0] << ", " << pairs[i][1] << ")" << endl; 
            cache.put(pairs[i][0], pairs[i][1]);
        }

    }
    cout << "Finished testing LRUCache" << endl; 

    return 0;
}

LRUCache::LRUCache(int c) {

    capacity = c;

}

void LRUCache::initializeCache(int key, int value) { 

    KeyInfo newItem(value, ARBITRARY, ARBITRARY);
    
    cache.insert(pair<int, KeyInfo>(key, newItem));
    front = key;
    leastUsed = key;

}

int LRUCache::get(int key) {

    map<int, KeyInfo>::iterator lookup;

    lookup = cache.find(key);

    if(lookup == cache.end())
        return -1;

    upgradeFront(lookup);

    return lookup -> second.value; 
}

void LRUCache::put(int key, int value) {

    map<int, KeyInfo>::iterator lookup;

    // First look at the case that the cache is empty. If so, then we need to initialize the front and leastUsed. 
    if(cache.empty()) {

        initializeCache(key, value); 
        return;
    }

    lookup = cache.find(key);
    // If the key is already in the cache, then put the value and then update
    // the most recently used. If the key is not in the cache, then check the
    // size of the cache versus its capacity.

    if(lookup != cache.end()) {

        lookup -> second.value = value;
        upgradeFront(lookup);
        return;
    } 

    else  {

        nonEmptyAdd(key, value);

        if(cache.size() > capacity)
            removeLeastUsed();

    }



}

void LRUCache::nonEmptyAdd(int key, int value) {

    KeyInfo newItem(value, ARBITRARY, front); 
    map<int, KeyInfo>::iterator oldFront;

    oldFront = cache.find(front);
    (oldFront -> second) . parent = key;
    cache.insert(pair<int, KeyInfo>(key, newItem));
    front = key; 

}

void LRUCache::upgradeFront(map<int, KeyInfo>::iterator toMove) {

    map<int, KeyInfo>::iterator previousFront, oldParent, oldChild;

    // First check if toMove is already the front.

    if (key(toMove) == front)
        return;

    // Check if the new toMove used to be the old least used. If it was, then we
    // just need to update leastUsed to be toMove's old parent. 
    // Else, we need to connect its old parent to its old child. 

    oldParent = cache.find( parent(toMove) );

    if (key(toMove) == leastUsed) 

        leastUsed = key(oldParent);
         
    else {

        oldChild = cache.find( child(toMove) ); 
        child(oldParent) = child(toMove);
        parent(oldChild) = parent(toMove);
        
    } 

    // Now put toMove at the front.

    child(toMove) = front;
    previousFront = cache.find(front);
    front = key(toMove);
    parent(previousFront) = front; 

}

void LRUCache::removeLeastUsed() {

    map<int, KeyInfo>::iterator oldLeast;

    oldLeast = cache.find(leastUsed);
    leastUsed = oldLeast -> second . parent;
    cache.erase(oldLeast); 

}
