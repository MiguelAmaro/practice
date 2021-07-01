
#define KEY_SIZE 8

typedef struct tree_node_t 
{
	struct  tree_node_t *left ;
	struct  tree_node_t *right;
    u8      key[KEY_SIZE];
    u8     *data;
} tree_node;

#define NODE_HEAP_ISIZE 0x8000
#define DATA_HEAP_ISIZE 0x8000
#define MAX_DATA_LEN 0x1000
#define STATUS_FILE_ERROR 0xE0000001    // Customer exception
#define NODE_SIZE sizeof (TREENODE)

tree_node *fill_tree  (HANDLE, HANDLE, HANDLE);
b32        scan       (tree_node *);
s32        key_compare(u8 *, u8 *, iFile); // NOTE(MIGUEL): da fuck is iFile

s32 binary_tree_sort()
{
    HANDLE input_file = INVALID_HANDLE_VALUE;
    HANDLE heap_nodes  = 0;
    HANDLE heap_records  = 0;
    
    b32 no_print;
    u8 error_msg[256];
    
    tree_node *root;
    
    s32 first_file = options(arg_count, command_line, "n", &no_print, NULL);
    
    
    if()
    {
        report_error();
    }
    
    for()
    {
        input_file = CreateFileA();
        if(input_file == INVALID_HANDLE_VALUE)
        {
            
        }
        
        // NOTE(MIGUEL): exception: try
        {
            heap_nodes = HeapCreate();
            heap_records = HeapCreate();
            
            root = fill_tree();
            
            if(!no_print)
            {
                
            }
        }
        {
            // NOTE(MIGUEL): exception: finally
            if(heap_nodes != NULL) 
            { 
                HeapDestroy(heap_nodes);
                heap_nodes == NULL;
            }
            if(heap_records != NULL)
            {
                HeapDestroy(heap_records);
                heap_records == NULL;
            }
            if(input_file != INVALID_HANDLE_VALUE)
            {
                CloseHandle(input_file);
                input_file = INVALID_HANDLE_VALUE;
            }
        }
        
    }
    
    // NOTE(MIGUEL): exception handling here
    return;
}