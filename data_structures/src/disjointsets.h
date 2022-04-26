/* date = December 14th 2021 0:35 pm */

#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

typedef struct ds ds;
struct ds
{
    u32 NodeCount;
    u32 *Root;
    u32 *Parent;
    u32 *Rank; // NOTE(MIGUEL): Height
};

u32 GetRoot(ds *DSet, u32 Node)
{
    return DSet->Root[Node];
}

u32 GetParentNode(ds *DSet, u32 Node)
{
    return DSet->Parent[Node];
}

void Union(ds *DSet, u32 x, u32 y)
{
    u32 RootX = 0;
    u32 RootY = 0;
    
    // NOTE(MIGUEL): Rank
    RootX = GetRoot(DSet, x);
    RootY = GetRoot(DSet, y);
    
    if (RootX != RootY) // NOTE(MIGUEL): Check to see if its already in the set.
    {
        if(DSet->Rank[RootX] > DSet->Rank[RootY])
        {
            DSet->Root[RootY] = RootX;
            DSet->Parent[y]   = x;
        }
        else if(DSet->Rank[RootX] < DSet->Rank[RootY])
        {
            DSet->Root[RootX] = RootY;
            DSet->Parent[x]   = y;
        }
        else
        {
            DSet->Root[RootY] = RootX;
            DSet->Parent[y]   = x;
            DSet->Rank[RootX] += 1;
        }
    }
    
    return;
}

// NOTE(MIGUEL): Returns Root - O(N)
u32 UnionFind(ds *DSet, u32 x, u32 y) 
{
    u32 NodeA = GetRoot(DSet, x);
    u32 NodeB = GetRoot(DSet, y);
    
    if (NodeA != NodeB)
    {
        for (u32 Node = 0; Node < DSet->NodeCount; Node++)
        {
            if(DSet->Root[Node] == NodeB) 
            {
                DSet->Root[Node] = NodeA;
            }
        }
    }
    
    return;
}

b32 IsConnected(ds *DSet, u32 x, u32 y)
{
    return GetRoot(DSet, x) == GetRoot(DSet, y);
}

void DSInit(ds *DSet)
{ 
    // NOTE(MIGUEL): Initialize all node to be the root nodes of themselves.
    for(u32 Node = 0; Node < DSet->NodeCount; Node++)
    {
        DSet->Root  [Node] = Node;
        DSet->Parent[Node] = Node;
        DSet->Rank  [Node] = 1; // NOTE(MIGUEL): Height of each tree
    }
    
    return;
}

#if 0
b32 DSQuickFind()
{
    
    
    return;
}
#endif

void PrintDisjointSet(ds *DSet)
{
    
    for(u32 Node = 0; Node < DSet->NodeCount; Node++)
    {
        printf("Node %d -> Root: %d | "
               "Height: %d | "
               "Parent: %d \n",
               Node,
               DSet->Root[Node],
               DSet->Rank[Node],
               DSet->Parent[Node]);
    }
    
    return;
}

#endif //DISJOINTSETS_H
