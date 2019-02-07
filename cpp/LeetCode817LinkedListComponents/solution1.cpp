#include "solution1.h"
#include <iostream>

std::ostream& operator<<( std::ostream& stream, const ListNode& node) {
    stream << node . val; 
    return stream;
}

LinkedList::LinkedList( const std::vector<int> &list ) {
    if( list.size() < 1 ) {
        root = nullptr;
        return;
    }

    root = new ListNode( *list.begin() );
    ListNode *previous = root;
    for( std::vector<int>::const_iterator i = list.begin() + 1; i != list.end(); i++) {
        previous -> next = new ListNode( *i );
        previous = previous -> next;
    } 
}

LinkedList::~LinkedList() {
    ListNode *current = root, *next;

    while( current != nullptr ) {
        next = current -> next; 
        delete current;
        current = next;
    }
}

std::ostream& operator<<( std::ostream& stream, const LinkedList& list ) {
    ListNode *node = list.root;
    while( node != nullptr ) {
        stream << *node << " -> ";
        node = node -> next; 
    }
    stream << "nullptr";
}

int Solution::numComponents( ListNode* head, std::vector<int>& G) {

    ListNode *node = head;
    int nComponents = 0;
    
    if( head == nullptr )
        return 0;
    if( G.size() < 1 )
        return 0;

    points = std::unordered_set<int>(G.begin(), G.end()); 

    while( node != nullptr ) {
        if( findComponent( node ) )
            nComponents++; 

    } 

    return nComponents;
}

/*!
    Automatically move start to next node or node after component.
 */
bool Solution::findComponent( ListNode*& start) {
    bool lastInside;

    // First check if there is any component here.
    lastInside = points.count( start -> val ) > 0;
    start = start -> next;
    if( !lastInside )
        return false;

    while( start != nullptr && lastInside ) {
        lastInside = points.count( start -> val) > 0;
        start = start -> next;
    }

    return true;
}
