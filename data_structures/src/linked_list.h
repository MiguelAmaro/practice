/* date = February 20th 2021 10:58 pm */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H


// ************************************************************
// TIME: 30 min
// 
// GOAL:
// Make a linked list and all supporting functions
// Reverse the linked list
//
// LOG:
// 1/20/2021 - Just wrote down the idea
// ************************************************************

// sll - singly linked list
// dll - doubly linked list
typedef struct sll_node sll_node;
struct sll_node
{
    u32 data;
    sll_node *next;
};

sll_node *sll_search(sll_node *this, u32 data)
{
    sll_node *result;
    
    if(this == NULLPTR) return (sll_node *)NULLPTR;
    
    if(this->data == data)
    {
        return this;
    }
    else
    {
        return sll_search(this->next, data);
    }
    
    return result;
}

void sll_insert(sll_node *this, u32 data)
{
    
    return;
}

typedef struct dll_node dll_node;
struct dll_node
{
    u32 data;
    dll_node *prev;
    dll_node *next;
};


#endif //LINKED_LIST_H
