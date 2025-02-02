#include <huffman_code.h>
#include <stdlib.h>
#include <stdbool.h>


data_node* get_frequency_table(char* input_data, int* size_out) {
    data_node* freq_table = NULL;
    int table_size = 0;
    
    // Process each character in the input string
    for (int i = 0; input_data[i] != '\0'; i++) {
        char current = input_data[i];
        
        // Check if we've seen this character before
        int found = 0;
        for (int j = 0; j < table_size; j++) {
            if (freq_table[j].data == current) {
                freq_table[j].freq++;
                found = 1;
                break;
            }
        }
        
        // If it's a new character, add it to the table
        if (!found) {
            data_node* temp = realloc(freq_table, sizeof(data_node) * (table_size + 1));
            if (!temp) {
                free(freq_table);  // Clean up on allocation failure
                *size_out = 0;
                return NULL;
            }
            freq_table = temp;
            
            // Initialize the new entry
            freq_table[table_size].data = current;
            freq_table[table_size].freq = 1;
            table_size++;
        }
    }
    
    *size_out = table_size;
    return freq_table;
}

data_node* sort_nodes_by_freq(data_node* input_data, int table_size)
{
    // Using bubble sort
    for(int i=0; i < table_size; i++)
    {
        for(int j=0; j < table_size - i - 1; j++)
        {
            if(input_data[j].freq < input_data[j + 1].freq)
            {
                data_node temp_node = input_data[j];
                input_data[j] = input_data[j+1];
                input_data[j+1] = temp_node;
            }
        }
    }

    return input_data;
}


