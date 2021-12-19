/* date = December 14th 2021 6:55 am */

#ifndef MEMORY_H
#define MEMORY_H


typedef struct memory_arena memory_arena;
struct memory_arena
{
    size_t  Size;
    size_t  Used;
    void   *BasePtr;
};


inline u32
SafeTruncateu64(u64 Value)
{
    ASSERT(Value <= 0xffffffff);
    
    u32 Result = (u32)Value;
    
    return Result;
}


// NOTE(MIGUEL): Clearing large Amounts of data e.g ~4gb 
//               results in a noticable slow down.
void *MemorySetTo(int Value, void *DestInit, size_t Size)
{
    unsigned char *Dest = (unsigned char *)DestInit;
    
    while(Size--)
        *Dest++ = (unsigned char)Value;
    
    return DestInit;
}

void *MemoryCopy(void *DestInit, void *SourceInit, size_t Size)
{
    unsigned char *Source = (unsigned char *)SourceInit;
    unsigned char *Dest   = (unsigned char *)DestInit;
    
    while(Size--)
        *Dest++ = *Source++;
    
    return DestInit;
}

void
MemoryArenaInit(memory_arena *Arena, size_t Size, void *BasePtr)
{
    Arena->BasePtr = BasePtr;
    Arena->Size    = Size;
    Arena->Used    = 0;
    
    return;
}

void
MemoryArenaDiscard(memory_arena *Arena)
{
    // NOTE(MIGUEL): Clearing large Amounts of data e.g ~4gb 
    //               results in a noticable slow down.
    MemorySetTo(0, Arena->BasePtr, Arena->Used);
    
    Arena->BasePtr = 0;
    Arena->Size    = 0;
    Arena->Used    = 0;
    
    return;
}

#define MEMORY_ARENA_PUSH_STRUCT(Arena,        Type) (Type *)MemoryArenaPushBlock(Arena, sizeof(Type))
#define MEMORY_ARENA_PUSH_ARRAY( Arena, Count, Type) (Type *)MemoryArenaPushBlock(Arena, (Count) * sizeof(Type))
#define MEMORY_ARENA_ZERO_STRUCT(Instance          )         MemoryArenaZeroBlock(sizeof(Instance), &(Instance))
inline void *
MemoryArenaPushBlock(memory_arena *Arena, size_t Size)
{
    ASSERT((Arena->Used + Size) <= Arena->Size);
    
    void *NewArenaPartitionAdress  = (u8 *)Arena->BasePtr + Arena->Used;
    Arena->Used  += Size;
    
    return NewArenaPartitionAdress;
}

inline void
MemoryArenaZeroBlock(memory_index size, void *address)
{
    u8 *byte = (u8 *)address;
    
    while(size--)
    {
        *byte++ = 0;
    }
    
    return;
}


#endif //MEMORY_H
