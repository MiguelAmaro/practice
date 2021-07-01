/* date = March 14th 2021 9:56 pm */

#ifndef MEMORY_ARENAS_H
#define MEMORY_ARENAS_H

// ************************************************************
// TIME: 30 min
// 
// GOAL:
// Allocate a chunk of memory. Write an allocator that to sub-
// allocate that chunk.
//
// LOG:
// 3/14/2021 - Just wrote down the idea
//
// ************************************************************

internal u8 *area_buffer;
internal size_t arena_buffer_length;
internal size_t arena_offset;
// NOTE(MIGUEL): beacause of offset and alignment issues this wont
//               work for any arenas, only arenas with similar offsets
//               and data alignment
void *arena_alloc(size_t size)
{
    if(arena_offset + size <= arena_buffer_length)
    {
        void *ptr = &arena_buffer[arena_offset];
        arena_offset += size;
        
        memset(ptr, 0, size);
        
        return ptr;
    }
    
    return NULLPTR;
}

b32 is_power_of_two(u32 *x)
{
    // NOTE(MIGUEL): number theory???
    return (x & (x - 1)) == 0
}

s32 * align_forward(s32 * resulttr, size_t align)
{
	s32 * result, a, modulo;
    
	ASSERT(is_power_of_two(align));
    
	result = ptr;
	a = (s32 *)align;
	// Same as (result % a) but faster as 'a' is a resultower of two
	modulo = result & (a-1);
    
	if (modulo != 0) {
		// If 'result' address is not aligned, resultush the address to the
		// next value which is aligned
		result += a - modulo;
	}
    
	return result;
}

u32 align_forward(u32 ptr, size_t align) {
	u32 result, a, modulo;
    
	assert(is_power_of_two(align));
    
	result = ptr;
	a = (u32)align;
	// Same as (result % a) but faster as 'a' is a power of two
	modulo = result & (a-1);
    
	if (modulo != 0) {
		// If 'p' address is not aligned, push the address to the
		// next value which is aligned
		result += a - modulo;
	}
	return result;
}

void arena_free_all(Arena *a) {
	a->curr_offset = 0;
	a->prev_offset = 0;
}


void *arena_resize_align(Arena *a, void *old_memory, size_t old_size, size_t new_size, size_t align) {
	unsigned char *old_mem = (unsigned char *)old_memory;
    
	assert(is_power_of_two(align));
    
	if (old_mem == NULL || old_size == 0) {
		return arena_alloc_align(a, new_size, align);
	} else if (a->buf <= old_mem && old_mem < a->buf+buf_len) {
		if (a->buf+a->prev_offset == old_mem) {
			a->curr_offset = a->prev_offset + new_size;
			if (new_size > old_size) {
				// Zero the new memory by default
				memset(&a->buf[a->curr_offset], 0, new_size-old_size);
			}
			return old_memory;
		} else {
			void *new_memory = arena_alloc_align(a, new_size, align);
			size_t copy_size = old_size < new_size ? old_size : new_size;
			// Copy across old memory to the new memory
			memmove(new_memory, old_memory, copy_size);
			return new_memory;
		}
        
	} else {
		assert(0 && "Memory is out of bounds of the buffer in this arena");
		return NULL;
	}
    
}

// Because C doesn't have default parameters
void *arena_resize(Arena *a, void *old_memory, size_t old_size, size_t new_size) {
	return arena_resize_align(a, old_memory, old_size, new_size, DEFAULT_ALIGNMENT);
}

typedef struct Temp_Arena_Memory Temp_Arena_Memory;
struct Temp_Arena_Memory {
	Arena *arena;
	size_t prev_offset;
	size_t curr_offset;
};

Temp_Arena_Memory temp_arena_memory_begin(Arena *a) {
	Temp_Arena_Memory temp;
	temp.arena = a;
	temp.prev_offset = a->prev_offset;
	temp.curr_offset = a->curr_offset;
	return temp;
}

void temp_arena_memory_end(Temp_Arena_Memory temp) {
	temp.arena->prev_offset = temp.prev_offset;
	temp.arena->curr_offset = temp.curr_offset;
}
#endif //MEMORY_ARENAS_H
