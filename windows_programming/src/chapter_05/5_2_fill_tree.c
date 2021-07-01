


b32 binary_tree_insert (tree_node **root, tree_node* node);


tree_node *binary_tree_fill(HANDLE input_file, HANDLE heap_node, HANDLE heap_data)
{
    tree_node *root = NULLPTR;
    tree_node *node = NULLPTR;
    
    u32 bytes_read;
    b32 at_carrage_return;
    
    u8 *buffer[MAX_DATA_LEN];
    u8 *string;
    
    while(true)
    {
        node = HeapAlloc(heap_node, NULL, (KEY_SIZE + string_get_length(buffer) + 1));
        
        for(u32 i = 0; i < MAX_DATA_LEN; i++)
        {
            ReadFile(input_file, &buffer, sizeof(u8), &bytes_read, NULL);
            
            if(at_carrage_return && buffer[i] == '\n')
            {
                break;
            }
            
            at_carrage_return = (buffer[i] == '\r');
        }
        
        buffer[i - 1]= '\0';
        
        string = HeapAlloc(heap_data, NULL, KEY_SIZE + string_get_length(buffer) + 1);
        
        memcpy(string, node->key, KEY_SIZE);// NOTE(MIGUEL): may implement my own
        
        string_concat(string, buffer);
        
        node->data = string;
        
        binary_tree_insert(&root, node);
    }
    
    return;
}

b32 binary_tree_insert (tree_node **root, tree_node* node)
{
    
    return;
}