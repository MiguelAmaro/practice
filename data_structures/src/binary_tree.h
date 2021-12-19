/* date = February 20th 2021 10:36 pm */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "memory.h"
#include "types.h"

//************************************************************
// TIME: 30 min
//
// GOAL:
// Create a binary tree and functions that support it
// Figure out how to test it
//
// LOG:
// 1/20/2021 - Just wrote down the idea
// 1/22/2021 -
// Binary trees need to havfe their positions sorted by
// where they are in the tree. The value might be the key
// to determining whinch node to use for the next new allocation.
//
//
// ************************************************************

typedef struct bt_node bt_node;
struct bt_node
{
    u32 data;
    bt_node *left;
    bt_node *right;
};

void BinaryTreeInit(bt_node *this, memory_arena *Arena)
{
    this = (bt_node *)MEMORY_ARENA_PUSH_STRUCT(Arena, bt_node);
    
    this->left  = NULLPTR;
    this->right = NULLPTR;
    this->data  = 0;
    
    return;
}

void BinaryTreeInsert(bt_node *this, u32 data, memory_arena *Arena)
{
    bt_node *target = this;
    
    while(target != NULLPTR)
    {
        if(target->left)
        {
            target = target->left;
        }
        else if(target->right)
        {
            target = target->right;
        }
        else
        {
            target = NULLPTR;
        }
    }
    
    return;
}

void BinaryTreePrint1(bt_node *this)
{
    
    
    return;
}

#endif //BINARY_TREE_H
