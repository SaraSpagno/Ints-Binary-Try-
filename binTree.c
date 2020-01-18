#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "binTree.h"

typedef struct BinTree {
    int val;
    struct BinTree* left;
    struct BinTree* right;
} BinTree;


BinTree* create_bin_tree(int val) {
    BinTree* root = malloc(sizeof(BinTree));
    if (root == NULL) {
        return NULL;
    }
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void destroy_bin_tree(BinTree* root) {
    if (root == NULL) {
        return;
    }
    destroy_bin_tree(root->left);
    destroy_bin_tree(root->right);
    free(root);
}

int size_of_bin_tree(BinTree* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + size_of_bin_tree(root->left) + size_of_bin_tree(root->right);
}

BinTree* find_in_bin_tree(BinTree* root, int val) {
    if (root == NULL) {
        return NULL;
    }
    if (root->val > val) {
        return find_in_bin_tree(root->left, val);
    }
    if (root->val < val) {
        return find_in_bin_tree(root->right, val);
    }
    return root;
}

Result add_to_bin_tree(BinTree* root, int val) {
    if (root == NULL) {
        return FAILURE;
    }
    if (root->val > val) {
        if (root->left != NULL) {
            return add_to_bin_tree(root->left, val);
        }
        root->left = create_bin_tree(val);
        if (root->left == NULL) {
            return MEM_ERROR;
        } else {
            return SUCEESS;
        }
    }
    if (root->val < val) {
        if (root->right != NULL) {
            return add_to_bin_tree(root->right, val);
        }
        root->right = create_bin_tree(val);
        if (root->right == NULL) {
            return MEM_ERROR;
        } else {
            return SUCEESS;
        }
    }
    return FAILURE;
}

BinTree* create_bin_tree_from_arr(int arr[], int size) {
    if (size == 0) {
        return NULL;
    }
    BinTree* root = create_bin_tree(arr[0]);
    if (root == NULL) {
        return NULL;
    }
    for (int i = 1; i < size; i++) {
        Result result = add_to_bin_tree(root, arr[i]);
        if (result != SUCEESS) {
            destroy_bin_tree(root);
            return NULL;
        }
    }
    return root;
}

static int arr_from_tree_pre_order(BinTree* root, int arr[], int size, int last);
static Result remove_from_arr(int arr[], int size, int val);

Result remove_from_bin_tree(BinTree** rootPtr, int val) {
    assert(rootPtr != NULL);
    BinTree* root = *rootPtr;
    if (!find_in_bin_tree(root, val)) {
        return FAILURE;
    }
    int size = size_of_bin_tree(root);
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        return MEM_ERROR;
    }
    int last = arr_from_tree_pre_order(root, arr, size, -1);
    assert(last == size - 1);

    Result result = remove_from_arr(arr, size, val);
    assert(result == SUCEESS);

    BinTree* new_root = create_bin_tree_from_arr(arr, size-1);
    if (new_root == NULL) {
        free(arr);
        return MEM_ERROR;
    }

    free(arr);
    destroy_bin_tree(*rootPtr);
    *rootPtr = new_root;
    return SUCEESS;
}

void print_pre_order(BinTree* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    print_pre_order(root->left);
    print_pre_order(root->right);
}

void print_in_order(BinTree* root) {
    if (root == NULL) {
        return;
    }
    print_in_order(root->left);
    printf("%d ", root->val);
    print_in_order(root->right);
}

void print_post_order(BinTree* root) {
    if (root == NULL) {
        return;
    }
    print_post_order(root->left);
    print_post_order(root->right);
    printf("%d ", root->val);
}


static int arr_from_tree_pre_order(BinTree* root, int arr[], int size, int last) {
    if (root == NULL) {
        return last;
    }
    int i = last + 1;
    assert(i < size);
    arr[i] = root->val;
    last = arr_from_tree_pre_order(root->left, arr, size, i);
    return arr_from_tree_pre_order(root->right, arr, size, last);
}

static Result remove_from_arr(int arr[], int size, int val) {
    int val_idx = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) {
            val_idx = i;
            break;
        }
    }
    if (val_idx == -1) {
        return FAILURE;
    }
    for (int i = val_idx; i < size - 1; i++) {
        arr[i] = arr[i+1];
    }
    arr[size-1] = 0;
    return SUCEESS;
}
