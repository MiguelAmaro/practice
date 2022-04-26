#include "stdio.h"

#include "base_includes.h"
#include "base_includes.c"

#define WIN32_EXAMPLE_SELECT (0)
#include "example_switch.h"

#define Prints32(x) printf("%s = %d\n"  , #x, (s32)(x))
#define Prints64(x) printf("%s = %lld\n", #x, (s64)(x))

#define Printu32(x) printf("%s = %u\n"  , #x, (u32)(x))
#define Printu64(x) printf("%s = %llu\n", #x, (u64)(x))

#define Printf32(x) printf("%s = %e [%f]\n", #x, (f32)(x), (f32)(x))
#define Printf64(x) printf("%s = %e [%f]\n", #x, (f64)(x), (f64)(x))


typedef struct
{
  int a;
  int b;
  int c;
  int d;
} test; 

u32 main(u32 arg_count, u8 *command_line[])
{
  //~ BASE TESTING
  printf("cl      = %d\n", COMPILER_CL    );
  printf("clang   = %d\n", COMPILER_CLANG );
  printf("gcc     = %d\n", COMPILER_GCC   );
  printf("windows = %d\n", OS_WINDOWS );
  printf("linux   = %d\n", OS_LINUX   );
  printf("mac     = %d\n", OS_MAC     );
  printf("x64     = %d\n", ARCH_X64   );
  printf("x86     = %d\n", ARCH_X86   );
  printf("arm32   = %d\n", ARCH_ARM32 );
  printf("arm64   = %d\n", ARCH_ARM64 );
  
  int foo[100];
  
  
  for(int i = 0; i < ARRAY_COUNT(foo); i += 1 )
  {
    foo[i] = i;
  }
  
  int bar[100];
  MEMORY_COPY_ARRAY(bar, foo);
  EVALPRINTS32(bar[50]);
  EVALPRINTS32(MEMORY_MATCH(foo, bar, sizeof(foo)));
  MEMORY_ZERO_ARRAY(bar);
  EVALPRINTS32(bar[50]);
  EVALPRINTS32(MEMORY_MATCH(foo, bar, sizeof(foo)));
  
  EVALPRINTS32(MEMBER_OFFSET(test, a));
  EVALPRINTS32(MEMBER_OFFSET(test, b));
  EVALPRINTS32(MEMBER_OFFSET(test, c));
  EVALPRINTS32(MEMBER_OFFSET(test, d));
  
  EVALPRINTS32(min_s8);
  EVALPRINTS32(min_s16);
  EVALPRINTS32(min_s32);
  EVALPRINTS64(min_s64);
  
  EVALPRINTS32(max_s8);
  EVALPRINTS32(max_s16);
  EVALPRINTS32(max_s32);
  EVALPRINTS64(max_s64);
  
  EVALPRINTU32(max_u8);
  EVALPRINTU32(max_u16);
  EVALPRINTU32(max_u32);
  EVALPRINTU64(max_u64);
  
  EVALPRINTF64(f32_infinity());
  EVALPRINTF64(f32_infinity_negative());
  
  EVALPRINTF64(f32_infinity());
  EVALPRINTF64(f32_infinity_negative());
  
  
  EVALPRINTF64(f32_sqrt(100.0f));
  EVALPRINTF64(f32_sin(tau_f32 * 0.3f));
  EVALPRINTF64(f32_cos(tau_f32 * 0.3f));
  EVALPRINTF64(f32_tan(0.5f));
  
  
  EVALPRINTF64(f64_sqrt(100.0));
  EVALPRINTF64(f64_sin(tau_f64 * 0.3));
  EVALPRINTF64(f64_cos(tau_f64 * 0.3));
  EVALPRINTF64(f64_tan(0.5));
  
  EVALPRINTF64(lerp(0.0f, 0.3f, 1.0f));
  EVALPRINTF64(lerp(10.0f, 0.5f, 100.0f));
  EVALPRINTF64(lerp(0.0f, 0.3f, 1.0f));
  EVALPRINTF64(unlerp(10.0f, unlerp(10.0f, 0.5f, 100.0f), 1.0f));
  
  
  ASSERT(1);
  ASSERT(50 < 100 );
  
  printf("hello world");
  
  
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