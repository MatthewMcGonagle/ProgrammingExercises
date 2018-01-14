/**
    main.cpp
    Author: Matthew McGonagle
    LeetCode Problem 002: Add Two Numbers.
    Numbers are represented as a linked list of digits in reverse order. The purpose is to then
    make a function Solution::addTwoNumbers that will find the linked list representation of their sum.

    Current solution passes as faster than 18.71% of all cpp submissions.
**/
#include<iostream> // For testing.
#include<vector> // For constructing test examples.
#include<string>
#include<sstream>

/**
    struct ListNode

    Definition for singly-linked list. This is taken from LeetCode and must
    be defined this way to count as a solution for LeetCode. It is a node
    for a linked list.

    @member val Value held by node.
    @member next Pointer to next node.
**/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/**
    class Solution

    The class that implements our solution. The call and return structure of the member
    function addTwoNumbers is specified by LeetCode.
**/
class Solution {
public:
    /**
        function addTwoNumbers
        
        If exactly one of the input ListNode* is NULL, then just return the other.
        Note this is NOT a copy of the other.
    **/
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2); 

};

/**
    function makeList
    
    Turns a non-negative integer into a list for each digit in reverse order
    (as specified by the LeetCode problem).
    
    @param n The non-negative integer to turn into a list of digits.
    @return The head of the list of the digits in reverse order.
**/
ListNode* makeList(unsigned int n);

/** 
    function printList

    Print a list in order.
    @param list The head of the list to print.
    @return String representation of list.
**/

std::string printList(ListNode* list);

/**
    function deleteList

    Delete a list in order.
    @param list The head of the list to delete.
**/
void deleteList(ListNode* list);

/////////////////////////////////////
//// main executable
////////////////////////////////////

int main() {

    int a = 501049, b = 3209;
    ListNode* aList = makeList(a), * bList = makeList(b), * sum;
    Solution sol;

    std::cout << "a = " << a << std::endl
              << "aList = " << printList(aList) << std::endl
              << "b = " << b << std::endl
              << "bList = " << printList(bList) << std::endl
              << "Testing sum" << std::endl;
    sum = sol.addTwoNumbers(aList, bList); 
    std::cout << "Regular a + b = " << a + b << std::endl
              << "List a + b = " << printList(sum) << std::endl;

    deleteList(aList);
    return 0;
}

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {

    ListNode* sum, * dummyHead;
    int carry = 0, digit;

    if (l1 == NULL && l2 == NULL)
        return NULL;

    if (l1 == NULL)
        return l2;

    if (l2 == NULL)
        return l1;

    dummyHead = new ListNode(0);
    sum = dummyHead; 

    while (l1 != NULL || l2 != NULL || carry != 0) {

        sum -> next = new ListNode(0);
        sum = sum -> next;

        digit = carry;
        if (l1 != NULL) {
            digit += l1 -> val;
            l1 = l1 -> next;
        }
        if (l2 != NULL) {
            digit += l2 -> val;
            l2 = l2 -> next;
        }
        carry = digit / 10; // Integer division!
        digit = digit % 10;

        sum -> val = digit;
    }

    // Clean up dummyHead.
   
    sum = dummyHead -> next;
    delete dummyHead;
 
    return sum;
}

ListNode* makeList(unsigned int n) {

    ListNode* list = NULL, * head;

    if(n == 0)
        return new ListNode(0);

    list  = new ListNode(n % 10);
    head = list;
    n /= 10;

    while(n > 0) {

        list -> next = new ListNode( n % 10 );
        list = list -> next;
        n /= 10;
    }

    return head;
}

std::string printList(ListNode* list){

    std::ostringstream output;

    while(list != NULL) {
        output << list -> val << ", ";
        list = list -> next;
    }

    return output.str(); 
}

void deleteList(ListNode* list) {

    ListNode* next;

    while(list != NULL) {

        next = list -> next;
        delete list;
        list = next;
    }
}
