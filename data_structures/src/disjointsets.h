/* date = December 14th 2021 0:35 pm */

#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H

typedef struct ds ds;
struct ds
{
    u32 NodeCount;
    u32 *RelTable;
};

u32 Find(ds *DSet, u32 Node)
{
    return DSet->RelTable[Node];
}

void UnionFind(ds *DSet, u32 x, u32 y) 
{
    u32 NodeA = Find(x);
    u32 NodeB = Find(y);
    
    if (NodeA != NodeB)
    {
        for (u32 Node = 0; Node < DSet->NodeCount; Node++)
        {
            Nodef (DSet->RelTable[Node] == NodeB) 
            {
                DSet->RelTable[Node] = NodeA;
            }
        }
    }
}

b32 DSInit(ds *DSet, u32 Edges[][2], u32 EdgeCount)
{ 
    MemorySetTo(U32_MAX, &DSet->RelTable, DSet->NodeCount);
    
    for(u32 Edge = 0; Edge < EdgeCount; Edge++)
    {
        u32 NodeA = Edges[i][0];
        u32 NodeB = Edges[i][1];
        
        if(DSet->RelTable[NodeA] == NodeA )
        {
            
            
        }
        
        
        DSet.RelTable[NodeA] = NodeA;
        DSet.RelTable[NodeB] = NodeA;
    }
    
    return;
}

b32 DSQuickFind()
{
    
    
    return;
}

#endif //DISJOINTSETS_H
