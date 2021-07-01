/* date = March 15th 2021 0:32 am */

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "LAL.h"

// ************************************************************
// TIME: 30 min
// 
// GOAL:
// Parse a file with a bunch of assembly insturctions mixed with
// text. Use a pattern reconition algorithm to grab all the x64 
// instructions. Create a new file and list each one an a new line.
// Append the file with a duplicate list that contains all the
// instructions in lower case.
//
// LOG:
// 03/15/2021 - Just wrote down the idea
//  
//
// ************************************************************

void parser_parse()
{
    FILE *file_in ;
    file_in = fopen("F:\\Dev_Tools\\4coder\\custom\\languages\\gp_instructions.txt", "r");
    
    FILE *file_out;
    file_out = fopen("F:\\Dev_Tools\\4coder\\custom\\languages\\instructions.txt", "a");
    
    u8 *mem_block     ;
    mem_block = malloc(40); // 20 bytes
    
    u8 *mem_block_head = mem_block;
    u8 *mem_block_tail = mem_block;
    
    fpos_t file_in_pos = 0;
    
    while(!feof(file_in))
    {
        u8 curr_char = (u8)getc(file_in);
        // CHAR IS UPPERCASE
        if( ((curr_char >=  0x41) && (curr_char <=  0x5A)) || (curr_char == 0x2F))
        {
            //BLOCK: A
            *mem_block_tail = curr_char;
            mem_block_tail++;
            
            fgetpos(file_in, &file_in_pos);
            u8 next_char = (u8)getc(file_in);
            
            // NEXT CHAR IS LOWERCASE
            if( (next_char >=  0x61) && (next_char <=  0x7A) )
            {
                *mem_block_tail = 0x00;
                mem_block_tail--;
                
                // WRITE INSTRUCTION
                while(mem_block_head < mem_block_tail)
                {
                    fputc((u32)*mem_block_head, file_out);
                    
                    *mem_block_head = 0x00;
                    mem_block_head++;
                }
                fputc('\n', file_out);
                
                // INSTRUCTION STORED. RESET
                mem_block_head = mem_block;
                mem_block_tail = mem_block;
            }
            // NEXT CHAR IS BACKSLASH
            else if( next_char == 0x2F )
            {
                // WRITE INSTRUCTION
                while(mem_block_head < mem_block_tail)
                {
                    fputc((u32)*mem_block_head, file_out);
                    
                    *mem_block_head = 0x00;
                    mem_block_head++;
                }
                fputc('\n', file_out);
                
                // INSTRUCTION STORED. RESET
                mem_block_head = mem_block;
                mem_block_tail = mem_block;
            }
            // NEXT CHAR IS PERIOD
            else if( next_char == 0x2E )
            {
                // DISCARD STRING
                while(mem_block_head < mem_block_tail)
                {
                    *mem_block_head = 0x00;
                    mem_block_head++;
                }
                // STRING IGNORED. RESET
                mem_block_head = mem_block;
                mem_block_tail = mem_block;
            }
            else
            {
                fsetpos(file_in, &file_in_pos);
            }
            
        }
    }
    
    fclose(file_in );
    fclose(file_out);
    free(mem_block );
    
    return;
}

#endif //FILE_PARSER_H
