#pragma once

#include <vector>
#include <ostream>
#include <set>
#include <unordered_set>

/*! ListNode is specified by the problem. We are unable to change its structure.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}

};

/*! LinkedList is to help us test our solution. 
 */
struct LinkedList {
    ListNode *root;
    
    LinkedList() : root(nullptr) {}
    LinkedList( const std::vector<int> &list );
    ~LinkedList();
};

std::ostream& operator<<( std::ostream& stream, const LinkedList& node);
std::ostream& operator<<( std::ostream& stream, const ListNode& node); 

class Solution {
public:
    int numComponents(ListNode* head, std::vector<int>& G);

private:
    bool findComponent(ListNode*& start);
    std::unordered_set<int> points;
};
