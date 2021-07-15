#ifndef EXAMPLE_SWITCH_H
#define EXAMPLE_SWITCH_H

#include "base.h"

global u32 g_selected_example = WIN32_EXAMPLE_SELECT;

#define WIN32_EXAMPLE(example_number, function_call) \
if(g_selected_example == (example_number)) return (function_call)


//- CHAPTER 01 
#if WIN32_EXAMPLE_SELECT == (11)
#include "chapter_01\1_1_copy_file_stdlib.c"
#else
u32 copy_file_stdlib  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (12)
#include "chapter_01\1_2_copy_file_win32.c"
#else
u32 copy_file_win32  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (13)
#include "chapter_01\1_3_copy_file_win32_function.c"
#else
u32 copy_file_win32_function  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 02 
#if WIN32_EXAMPLE_SELECT == (21)
#include "chapter_02\2_1_report_error.c"
#else
u32 report_error  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (22)
#include "chapter_02\2_2_file_concat_to_stdout.c"
#else
u32 file_concat_to_stdout  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (23)
#include "chapter_02\2_3_file_encryption.c"
#else
u32 file_encryption  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (25)
#include "chapter_02\2_5_console_prompt_print_utils.c"
#else
u32 console_prompt_print_utils  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (26)
#include "chapter_02\2_6_print_current_dir.c"
#else
u32 print_current_dir  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 03 
#if WIN32_EXAMPLE_SELECT == (31)
#include "chapter_03\3_1_record_access.c"
#else
u32 record_access  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (32)
#include "chapter_03\3_2_file_list_dir_traversal.c"
#else
u32 file_list_dir_traversal  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (33)
#include "chapter_03\3_3_setting_file_times.c"
#else
u32 setting_file_times  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (34)
#include "chapter_03\3_4_listing_registry_keys.c"
#else
u32 listing_registry_keys  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 04 
#if WIN32_EXAMPLE_SELECT == (41)
#include "chapter_04\4_1_report_exception.c"
#else
u32 report_exception  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (42)
#include "chapter_04\4_2_to_upper.c"
#else
u32 to_upper  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (43)
#include "chapter_04\4_3_exception_and_termination_processing.c"
#else
u32 exception_and_termination_processing  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (45)
#include "chapter_04\4_5_signal_handling.c"
#else
u32 signal_handling  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 05 
#if WIN32_EXAMPLE_SELECT == (51)
#include "chapter_05\5_1_binary_tree_sort.c"
#else
u32 binary_tree_sort  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (52)
#include "chapter_05\5_2_fill_tree.c"
#else
u32 fill_tree  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (53)
#include "chapter_05\5_3_memory_mapped_file_conversion.c"
#else
u32 memory_mapped_file_conversion  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (54)
#include "chapter_05\5_4_memory_mapped_file_sorting.c"
#else
u32 memory_mapped_file_sorting  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (55)
#include "chapter_05\5_5_memory_mapped_file_sorting_with_base_pointers.c"
#else
u32 memory_mapped_file_sorting_with_base_pointers  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (56)
#include "chapter_05\5_6_memory_mapped_sorting.c"
#else
u32 memory_mapped_sorting  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (57)
#include "chapter_05\5_7_explicit_linking_file_conversion.c"
#else
u32 explicit_linking_file_conversion  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 06 
#if WIN32_EXAMPLE_SELECT == (61)
#include "chapter_06\6_1_parallel_search.c"
#else
u32 parallel_search  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (62)
#include "chapter_06\6_2_print_proc_execution_time.c"
#else
u32 print_proc_execution_time  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (63)
#include "chapter_06\6_3_job_shell.c"
#else
u32 job_shell  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 07 
#if WIN32_EXAMPLE_SELECT == (71)
#include "chapter_07\7_1_multithread_pattern_search.c"
#else
u32 multithread_pattern_search  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (72)
#include "chapter_07\7_2_sort_multithread.c"
#else
u32 sort_multithread  (u32 arg_count, u8 *command_line[])
{ return 1; }
#endif

//- CHAPTER 08 
//- CHAPTER 09 
//- CHAPTER 10 
//- CHAPTER 11 
//- CHAPTER 12 
#if WIN32_EXAMPLE_SELECT == (121)
#include "chapter_12\12_1_socket_based_client.c"
#else
u32 socket_based_client  (u32 arg_count, u8 *args[])
{ return 1; }
#endif

#if WIN32_EXAMPLE_SELECT == (122)
#include "chapter_12\12_2_socket_based_server.c"
#else
u32 socket_based_server  (u32 arg_count, u8 *args[])
{ return 1; }
#endif

#endif