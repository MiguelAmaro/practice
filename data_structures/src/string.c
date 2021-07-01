
u32 string_get_length(u8 *string);
u32 utf8_to_u32      (u8 *string);

internal u32
string_get_length(u8 *string)
{
    u32 count = 0;
    
    while(*string++) { ++count; }
    
    return count;
}


u32 string_to_u32(u8 *string)
{
    u32 length =      0;
    u32 value  =      0;
    u32 tens   =      1;
    u8 *str    = string;
    
    for(str = string; *str != '\0';)
    { 
        length++; // NOTE(MIGUEL): keep this on top for reasons
        length *= (*str >= '0' && *str <= '9');
        
        tens *= 10;
        str++;
    }
    
    printf("string_to_u32 debug:\n");
    printf("tens: %d\n", length);
    str  = string   ;
    tens = tens / 10; 
    
    for(u32 i = 0; i < length; i++)
    {
        value += tens * (*str++ - 48);
        printf("tens: %d\n", tens);
        tens /= 10;
    }
    
    printf("%d \n", value);
    
    return value;
}

void string_copy(u8 *dest, u32 dest_len, u8 *src, u32 src_len)
{
    // NOTE(MIGUEL): not tested !!!
    for(u32 index = 0; (index < dest_len) && (index < src_len); index++)
    {
        dest[index] = src[index]; 
    }
    
    return;
}
