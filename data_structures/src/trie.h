/* date = June 10th 2021 2:37 pm */

#ifndef TRIE_H
#define TRIE_H
#incldue "LAL.h"

// NOTE(MIGUEL): Assuming alphabet is english
// NOTE(MIGUEL): Assuming ansi encoding
// NOTE(MIGUEL): fixed array of child refrences(i know it wastefull)
typedef struct Trie_node Trie_node
struct Trie_node
{
    u8 letter;
    Trie_node *children[26];
}

void trie_init(Trie_node *this)
{
    this.letter = 0x00;
    // NOTE(MIGUEL): what eslse shoult i do
    
    return;
}

void trie_insert(Trie_node *this, u8 *string)
{
    // NOTE(MIGUEL): beadth first search
    return;
}

#endif //TRIE_H
