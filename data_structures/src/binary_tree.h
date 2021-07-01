/* date = February 20th 2021 10:36 pm */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

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

typedef struct Bt_node Bt_node;
struct Bt_node
{
    u32 data;
    Bt_node *left;
    Bt_node *right;
};

typedef struct Bt Bt;
struct Bt
{
    
    
}

void binary_tree_init(Bt_node *this)
{
    this->left  = NULLPTR;
    this->right = NULLPTR;
    this->data  = 0;
    
    return;
}

void binary_tree_insert(Bt_node *this, u32 data, Bt_node *memory)
{
    Bt_node *target = this;
    
    while(target != NULLPTR)
    {
        if(target.left)
        {
            target = target.left;
        }
        else if(target.right)
        {
            target = target.right;
        }
        else
        {
            target = NULLPTR;
        }
    }
    
    return;
}

void binary_tree_print_fot(Bt_node *this)
{
    
    
    return;
}

#endif //BINARY_TREE_H
