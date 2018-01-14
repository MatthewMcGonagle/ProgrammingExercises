/**
    main.cpp
    Author: Matthew McGonagle
    LeetCode Problem 002: Add Two Numbers.
    Numbers are represented as a linked list of digits in reverse order. The purpose is to then
    make a function Solution::addTwoNumbers that will find the linked list representation of their sum.

    Current solution passes as faster than amount between 37% and 55% of all cpp submissions.
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

private:

    /**
        function doCarry

        Alter the sum of two digits and a carry to find the correct digit here and the
        carry for the next digit.

        @param sum Reference to the sum of the digits and carry for the current decimal place.
        @return The new carry.
    **/
    inline int doCarry(int &sum);

    /**
        function carryOneNumber

        Do the carries for when there is only one number left.

        @param head Pointer to the last digit of the sum that these results will be
            attached to.
        @param num The list of digits to apply the carries to.
        @param carry The carry to apply to the first digit.
    **/
    void carryOneNumber(ListNode* head, ListNode* num, int carry);
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

    // Loop over the digits of both numbers until one is done.

    while (l1 != NULL && l2 != NULL) {

        sum -> next = new ListNode(0);
        sum = sum -> next;

        digit = carry;

        digit += l1 -> val;
        l1 = l1 -> next;
        
        digit += l2 -> val;
        l2 = l2 -> next;

        carry = doCarry(digit);
        sum -> val = digit;
    }

    // Now check to see if one number still has digits left, else deal with any remaining carry.

    if (l1 != NULL) 
        carryOneNumber(sum, l1, carry); 
    else if (l2 != NULL)
        carryOneNumber(sum, l2, carry);
    else if (carry > 0) // Just need to add digit of '1'.
        sum -> next = new ListNode(1);

    // Clean up dummyHead.
   
    sum = dummyHead -> next;
    delete dummyHead;
 
    return sum;
}

int Solution::doCarry(int &sum) {

    // Avoid using more costly division and modulo operations.

    // Sum of digits and carry is at most 19 (digit 9 + digit 9 + carry 1).
    // So cheaper logic tells us the carry operation.

    if (sum > 9) {
        sum -= 10;
        return 1;            
    }
    else {
       return 0; 
    }
}

void Solution::carryOneNumber(ListNode *head, ListNode* num, int carry) {

    ListNode *newNum = head;
    int digit;

    while(num != NULL && carry != 0) {

        newNum -> next = new ListNode(0);
        newNum = newNum -> next;

        digit = num -> val + carry;
        carry = doCarry(digit);
        newNum -> val = digit;

        num = num -> next;
    } 

    if(carry > 0) 
        newNum -> next = new ListNode(1); 
    else
        newNum -> next = num;
         
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
