#ifndef __BIN_TREE_H
#define __BIN_TREE_H

typedef struct BinTree BinTree;

typedef enum {
    SUCEESS, FAILURE, MEM_ERROR
} Result;

BinTree* create_bin_tree(int val);
BinTree* find_in_bin_tree(BinTree* root, int val);
Result add_to_bin_tree(BinTree* root, int val);
Result remove_from_bin_tree(BinTree** rootPtr, int val);
BinTree* create_bin_tree_from_arr(int arr[], int size);

int size_of_bin_tree(BinTree* root);
void destroy_bin_tree(BinTree* root);

void print_pre_order(BinTree* root);
void print_in_order(BinTree* root);
void print_post_order(BinTree* root);

#endif
