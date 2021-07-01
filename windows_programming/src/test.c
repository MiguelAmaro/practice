#ifndef EXAMPLE_SWITCH_H
#define EXAMPLE_SWITCH_H

#include "LAL.h"

global u32 g_selected_example = WIN32_EXAMPLE_SELECT;

#define WIN32_EXAMPLE(example_number, function_call) \
if(g_selected_example == (example_number)) return (function_call)


//- CHAPTER 01 
#if WIN32_EXAMPLE_SELECT == (11)
#include "1_1_copy_file_stdlib.c"
#else
u32 1_1_copy_file_stdlib  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (12)
#include "1_2_copy_file_win32.c"
#else
u32 1_2_copy_file_win32  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (13)
#include "1_3_copy_file_win32_function.c"
#else
u32 1_3_copy_file_win32_function  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 02 
#if WIN32_EXAMPLE_SELECT == (21)
#include "2_1_report_error.c"
#else
u32 2_1_report_error  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (22)
#include "2_2_file_concat_to_stdout.c"
#else
u32 2_2_file_concat_to_stdout  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (23)
#include "2_3_file_encryption.c"
#else
u32 2_3_file_encryption  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (25)
#include "2_5_console_prompt_print_utils.c"
#else
u32 2_5_console_prompt_print_utils  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (26)
#include "2_6_print_current_dir.c"
#else
u32 2_6_print_current_dir  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 03 
#if WIN32_EXAMPLE_SELECT == (31)
#include "3_1_record_access.c"
#else
u32 3_1_record_access  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (32)
#include "3_2_file_list_dir_traversal.c"
#else
u32 3_2_file_list_dir_traversal  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (33)
#include "3_3_setting_file_times.c"
#else
u32 3_3_setting_file_times  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (34)
#include "3_4_listing_registry_keys.c"
#else
u32 3_4_listing_registry_keys  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 04 
#if WIN32_EXAMPLE_SELECT == (41)
#include "4_1_report_exception.c"
#else
u32 4_1_report_exception  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (42)
#include "4_2_to_upper.c"
#else
u32 4_2_to_upper  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (43)
#include "4_3_exception_and_termination_processing.c"
#else
u32 4_3_exception_and_termination_processing  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (44)
#include "4_4_filter.c"
#else
u32 4_4_filter  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (45)
#include "4_5_signal_handling.c"
#else
u32 4_5_signal_handling  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 05 
#if WIN32_EXAMPLE_SELECT == (51)
#include "5_1_binary_tree_sort.c"
#else
u32 5_1_binary_tree_sort  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (52)
#include "5_2_fill_tree.c"
#else
u32 5_2_fill_tree  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (53)
#include "5_3_memory_mapped_file_conversion.c"
#else
u32 5_3_memory_mapped_file_conversion  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (54)
#include "5_4_memory_mapped_file_sorting.c"
#else
u32 5_4_memory_mapped_file_sorting  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (55)
#include "5_5_memory_mapped_file_sorting_with_base_pointers.c"
#else
u32 5_5_memory_mapped_file_sorting_with_base_pointers  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (56)
#include "5_6_memory_mapped_sorting.c"
#else
u32 5_6_memory_mapped_sorting  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (57)
#include "5_7_explicit_linking_file_conversion.c"
#else
u32 5_7_explicit_linking_file_conversion  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 06 
#if WIN32_EXAMPLE_SELECT == (61)
#include "6_1_parallel_search.c"
#else
u32 6_1_parallel_search  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (62)
#include "6_2_print_proc_execution_time.c"
#else
u32 6_2_print_proc_execution_time  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (63)
#include "6_3_job_shell.c"
#else
u32 6_3_job_shell  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 07 
#if WIN32_EXAMPLE_SELECT == (71)
#include "7_1_multithread_pattern_search.c"
#else
u32 7_1_multithread_pattern_search  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (72)
#include "7_2_sort_multithread.c"
#else
u32 7_2_sort_multithread  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 08 
//- CHAPTER 09 
//- CHAPTER 10 
//- CHAPTER 11 
//- CHAPTER 12 
#if WIN32_EXAMPLE_SELECT == (1_)
#include "12_1"
#else
u32 12  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (1_)
#include "12_2_socket_based_servers.c"
#else
u32 12_2_socket_based_servers  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 13 
//- CHAPTER 14 
//- CHAPTER 15 
