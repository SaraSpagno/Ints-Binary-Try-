#include <stdio.h>
#include "binTree.h"

void printTree(BinTree* root) {
    printf("Pre Order: ");
    print_pre_order(root);
    printf("\n");
    printf("In Order: ");
    print_in_order(root);
    printf("\n");
    printf("Post Order: ");
    print_post_order(root);
    printf("\n\n");
}

void printTreeInOrder(BinTree* root) {
    printf("In Order: ");
    print_in_order(root);
    printf("\n");
}

void main() {
    int arr[] = {8,9,2,1,4,3,6,5,7};
    int size = sizeof(arr) / sizeof(int);
    BinTree* root = create_bin_tree_from_arr(arr, size);
    printTree(root);
    BinTree* sub_root = find_in_bin_tree(root, 2);
    printTreeInOrder(sub_root);
    remove_from_bin_tree(&root, 4);
    printTreeInOrder(root);
    remove_from_bin_tree(&root, 8);
    printTreeInOrder(root);
    sub_root = find_in_bin_tree(root, 6);
    printTreeInOrder(sub_root);
    destroy_bin_tree(root);
}
