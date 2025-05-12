/// Nama File   : main.c
/// Deskripsi   : File driver untuk ADT Binary Tree Dinamis
/// Dibuat oleh : Ikhsan Satriadi (241511080)
///               Yazid Alrasyid (241511093)
///               Rizky Satria Gunawan (241511089)
/// Tanggal     : 11-05-2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "btree/btree.h"

void print_tree_info(BTree tree) {
    printf("Tree properti:\n");
    printf("- Depth: %d\n", get_depth(tree));
    printf("- Jumlah node: %d\n", count_nodes(tree));
    printf("- Jumlah daun: %d\n", count_leaves(tree));
    printf("- Itu BST: %s\n", is_bst(tree) ? "Yes" : "No");
    printf("- Itu balanced: %s\n", is_balanced(tree) ? "Yes" : "No");
    
    printf("Traversals:\n");
    printf("- Pre-order: ");
    pre_order(tree.root);
    printf("\n");
    
    printf("- In-order: ");
    in_order(tree.root);
    printf("\n");
    
    printf("- Post-order: ");
    post_order(tree.root);
    printf("\n");
    
    printf("- Level-order: ");
    level_order(tree);
    printf("\n");
}

void test_bst() {
    printf("\n===== BST Tree Test =====\n");
    BTree bst = create_tree();
    
    // Create a BST
    insert_bst(&bst, 'F');
    insert_bst(&bst, 'B');
    insert_bst(&bst, 'A');
    insert_bst(&bst, 'D');
    insert_bst(&bst, 'C');
    insert_bst(&bst, 'E');
    insert_bst(&bst, 'G');
    insert_bst(&bst, 'I');
    insert_bst(&bst, 'H');
    
    print_tree_info(bst);
    
    printf("\nMencari nilai min dan max :\n");
    address min_node = find_min(bst);
    address max_node = find_max(bst);
    printf("Nilai min: %c\n", min_node ? min_node->info : ' ');
    printf("Nilai max: %c\n", max_node ? max_node->info : ' ');
    
    printf("\nMencari untuk 'D':\n");
    address d_node = search(bst, 'D');
    if (d_node) {
        printf("Ditemukan D! Parent itu: ");
        address parent = find_parent(bst, d_node);
        if (parent)
            printf("%c\n", parent->info);
        else
            printf("tidak ada (root)\n");
    } else {
        printf("D tidak ditemukan\n");
    }
    
    printf("\nMenghapus 'D':\n");
    delete_node(&bst, 'D');
    print_tree_info(bst);
    
    printf("\nMenyalin tree:\n");
    BTree bst_copy = copy_tree(bst);
    printf("Original tree: ");
    level_order(bst);
    printf("\nDisalin tree: ");
    level_order(bst_copy);
    printf("\nApakah mereka sama? %s\n", is_equal(bst, bst_copy) ? "Iya" : "Tidak");
    
    printf("\nBalancing tree:\n");
    balance_tree(&bst);
    print_tree_info(bst);
    
    // Clean up
    printf("\nClearing trees\n");
    clear_tree(&bst);
    clear_tree(&bst_copy);
}

void test_general_tree() {
    printf("\n===== General Tree Test =====\n");
    BTree tree = create_tree();
    
    // Create a general binary tree (not necessarily a BST)
    tree.root = create_node('A');
    insert_left(tree.root, 'B');
    insert_right(tree.root, 'C');
    
    insert_left(tree.root->left, 'D');
    insert_right(tree.root->left, 'E');
    
    insert_left(tree.root->right, 'F');
    
    print_tree_info(tree);
    
    printf("\nIs it a BST? %s\n", is_bst(tree) ? "Yes" : "No");
    
    // Testing rotations
    printf("\nMelakukan rotasi kanan di root:\n");
    tree.root = rotate_right(tree.root);
    print_tree_info(tree);
    
    printf("\nMelakukan rotasi kiri di root:\n");
    tree.root = rotate_left(tree.root);
    print_tree_info(tree);
    
    clear_tree(&tree);
}

int main(int argc, char const *argv[]) {
    printf("Binary Tree ADT Test Program\n\n");
    
    test_bst();
    test_general_tree();
    
    printf("\nSelesai\n");
    
    return 0;
}