/* date = February 20th 2021 4:01 pm */
#ifndef DISCRETE_MATH_H
#define DISCRETE_MATH_H
#include "LAL.h"
#include "stdlib.h"

// ************************************************************
// TIME: 30 min
// 
// GOAL:
// Create a function that takes two sets and a callback. The Callback
// will determine if 2 elements of respective sets are related under
// some rule defined. It'll return in an array tuples of related elements
//
// LOG:
// 1/20/2021 -
// A dynamically growing array would be usefull for the result
// especially considering set with large cardianlity space-time is O(n^2) & O(n^2)
// created a tupple struct. heap allocated in the function and stored block addres
// in the result ptr. typedefed u32 ptrs as sets and used them as my parameters also
// passing in the size of each set. the rule function was also typedefed as a function
// taking 2 u32s
// 
// ************************************************************

typedef b32 rule(u32 a, u32 b);
typedef u32* set;
typedef struct { u32 a; u32 b; } tuple;

// NOTE(MIGUEL): Logical Connective
enum lc
{
    conjunction,
    disjunction,
    conditional,
    biconditional,
};

u32 g_A[5] = {1,2,3,4,5};
tuple *g_R; // Free this shit for or not whatever

void parse_logical_statement()
{
    
    return;
}

void print_truth_table()
{
    
    return;
}

void find_pairs_that_are_related(set A, u32 size_A, set B, u32 size_B, rule is_related, tuple *result)
{
    u32 *a = 0;
    u32 *b = 0;
    
    result = malloc(sizeof(tuple) * (size_A * size_B));
    
    for(u32 i = 0; i < size_A; i++)
    {
        a = A + i;
        
        for(u32 j = 0; j < size_B; j++)
        {
            b = B + j;
            
            if(is_related(*a, *b))
            {
                printf(" (%d, %d)  \n", *a, *b);
                
                result->a = *a;
                result->b = *b;
                
                result++;
            }
        }
    }
    
    return;
}

#endif //DISCRETE_MATH_H
