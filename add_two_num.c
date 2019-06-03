#include <stdlib.h>
#include <stdio.h>

struct ListNode{
    int val;
    struct ListNode* next;
    
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    
    struct ListNode *l1_ptr, *l2_ptr;
    l1_ptr = l1;
    l2_ptr = l2;
    struct ListNode *result_list, *result_ptr;
    result_list = result_ptr = NULL;
    int carry = 0;
    int add_num1, add_num2;
    add_num1 = add_num2 = 0;
    
    // travers two list to compute the result
    while(l1_ptr != NULL || l2_ptr != NULL){
        add_num1 = l1_ptr ? l1_ptr -> val : 0;
        add_num2 = l2_ptr ? l2_ptr -> val : 0;
        int tempval = add_num1 + add_num2 + carry;
        int carry = tempval / 10;
        int resultval = tempval % 10;
        struct ListNode *storeNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        storeNode -> val = resultval;
        storeNode -> next = NULL;
        if(result_ptr == NULL)
            result_list = result_ptr = storeNode;
        else{
            result_ptr->next = storeNode;
            result_ptr = storeNode;
        }
        l1_ptr = l1_ptr ? l1_ptr -> next : NULL;
        l2_ptr = l2_ptr ? l2_ptr -> next : NULL;
    }
    
    // deal with the condition: the last carry is equal to 1
    if(carry == 1){
        struct ListNode * storeNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        storeNode -> val = 1;
        storeNode -> next = NULL;
        result_ptr->next = storeNode;
        result_ptr = storeNode;
    }
    
    return result_list;
}

int main()
{
    struct ListNode *list1, *list2, *list3;
    list3 = list1 = list2 = NULL;

    struct ListNode *storeNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    list1 = storeNode;
    storeNode->val = 4;
    storeNode->next = NULL;

    storeNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    list2 = storeNode;
    storeNode->val = 6;
    storeNode->next = NULL;

    list3 = addTwoNumbers(list1,list2);
}