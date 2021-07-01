#include "stdio.h"
#include "LAL.h"

#define WIN32_EXAMPLE_SELECT (122)
#include "example_switch.h"

u32 main(u32 arg_count, u8 *command_line[])
{
    //~ WIN 32 PROGRAMMING
    
    // NOTE(MIGUEL): ANSI
    WIN32_EXAMPLE(11, copy_file_stdlib     (arg_count, command_line));
    WIN32_EXAMPLE(12, copy_file_win32      (arg_count, command_line));
    
    
    // NOTE(MIGUEL):  example 21 (report error)  provides fucnitons for many examples
    WIN32_EXAMPLE(22, file_concat_to_stdout(arg_count, command_line)); // NOTE(MIGUEL): works!!!
    WIN32_EXAMPLE(23, file_encryption      (arg_count, command_line)); // NOTE(MIGUEL): works!!!
    // NOTE(MIGUEL):  example 25 provides functions for 2-6, 11-?, 15-?
    WIN32_EXAMPLE(26, print_current_dir    (arg_count, command_line)); // NOTE(MIGUEL): works!!!
    
    // NOTE(MIGUEL): UNICODE (UTF-16)
    WIN32_EXAMPLE(31, record_access           (arg_count, command_line)); // NOTE(MIGUEL): seems to wodk!! must study
    WIN32_EXAMPLE(32, file_list_dir_traversal (arg_count, command_line)); // NOTE(MIGUEL): not tested
    WIN32_EXAMPLE(33, setting_file_times      (arg_count, command_line)); // NOTE(MIGUEL): not tested
    WIN32_EXAMPLE(34, listing_registry_keys   (arg_count, command_line)); // NOTE(MIGUEL): not tested
    
    // NOTE(MIGUEL):  example 41 (report exception)  provides fucnitons for many examples
    WIN32_EXAMPLE(42, to_upper                            (arg_count, command_line)); // NOTE(MIGUEL): not tested
    WIN32_EXAMPLE(43, exception_and_termination_processing(arg_count, command_line)); // NOTE(MIGUEL): broken
    // NOTE(MIGUEL):  example 44 provides functions for 4-3
    WIN32_EXAMPLE(45, signal_handling                     (arg_count, command_line)); // NOTE(MIGUEL): broken
    
    WIN32_EXAMPLE(51, binary_tree_sort                             (arg_count, command_line));// NOTE(MIGUEL): broken
    // NOTE(MIGUEL):  example 5-2  provides fucnitons for 5-1
    // NOTE(MIGUEL):  example 5-3  provides fucnitons for 5-1
    WIN32_EXAMPLE(54, memory_mapped_file_sorting                   (arg_count, command_line)); // NOTE(MIGUEL): broken
    WIN32_EXAMPLE(55, memory_mapped_file_sorting_with_base_pointers(arg_count, command_line)); // NOTE(MIGUEL): broken
    // NOTE(MIGUEL):  example 5-6 provides functions for 5-5
    WIN32_EXAMPLE(57, explicit_linking_file_conversion             (arg_count, command_line));// NOTE(MIGUEL): broken
    
    //WIN32_EXAMPLE(61, pattern_search_multi_process              (arg_count, command_line));// NOTE(MIGUEL): broken
    // ...
    //WIN32_EXAMPLE(67, process_monitoring                        (arg_count, command_line));// NOTE(MIGUEL): broken
    
    //WIN32_EXAMPLE(71, pattern_search_multi_threaded         (arg_count, command_line));// NOTE(MIGUEL): broken
    //WIN32_EXAMPLE(72, merge_sort_multi_threaded             (arg_count, command_line));// NOTE(MIGUEL): broken
    
    //WIN32_EXAMPLE(111, interprocess_communication            (arg_count, command_line));// NOTE(MIGUEL): broken
    // ...
    //WIN32_EXAMPLE(115, mail_slot_server                      (arg_count, command_line));// NOTE(MIGUEL): broken
    
    WIN32_EXAMPLE(121, socket_based_client                        (arg_count, command_line));// NOTE(MIGUEL): broken
    WIN32_EXAMPLE(122, socket_based_server                        (arg_count, command_line));// NOTE(MIGUEL): broken
    // ....
    //WIN32_EXAMPLE(126, streaming_socket_multi_threaded           (arg_count, command_line));// NOTE(MIGUEL): broken
    
    return 0;
}