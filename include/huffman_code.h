#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct data_node {
    char data;
    unsigned freq;
} data_node;


data_node* get_frequency_table(char* input_data, int* size_out);
data_node* sort_nodes_by_freq(data_node* input_data, int table_size);


#ifdef __cplusplus
}
#endif