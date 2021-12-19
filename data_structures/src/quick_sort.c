#include "types.h"

void quick_sort (s32 array[], s32 count, s32 low_index, s32 high_index);
s32  partition  (s32 array[], s32 count, s32 low_index, s32 high_index);
void swap_s32   (s32 *a, s32 *b);
void array_print(s32 array[], s32 count);


void quick_sort(s32 array[], s32 count, s32 low_index, s32 high_index)
{
    s32 split_index;
    
    if((high_index - low_index) > 0) //  <- recursive base case
    {
        split_index = partition(array, count, low_index, high_index);
        
        quick_sort(array, count, low_index      , split_index - 1);
        quick_sort(array, count, split_index + 1, high_index     );
    }
    
    return;
}


s32 partition(s32 array[], s32 count, s32 low_index, s32 high_index)
{
    s32 pivot      = high_index;
    s32 first_high = low_index ;
    
    for(s32 index = low_index; index < high_index; index++)
    {
        if(array[index] < array[pivot])
        {
            array_print(array, count);
            
            printf("index     : %d \n"
                   "pivot     : %d \n"
                   "first high: %d \n"
                   "swap: %d <-> %d \n"
                   " \n",
                   array[index],
                   array[pivot],
                   array[first_high],
                   array[index], array[first_high]);
            
            swap_s32(&array[index], &array[first_high]);
            
            array_print(array, count);
            
            first_high++;
        }
    }
    
    swap_s32(&array[pivot], &array[first_high]);
    
    return first_high;
}


void swap_s32(s32 *a, s32 *b)
{
    s32 last_a_value = *a;
    
    *a = *b;
    *b = last_a_value;
    
    return;
}


void array_print(s32 array[], s32 count)
{
    printf("{");
    
    for(s32 index = 0; index < count; index++)
    {
        printf(" %d, ", array[index]);
    }
    
    printf("}\n");
    
    return;
}
