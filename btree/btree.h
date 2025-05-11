/// Nama File   : btree.h
/// Deskripsi   : File header untuk ADT Binary Tree Dinamis
/// Dibuat oleh : Ikhsan Satriadi (241511080)
///               Yazid Alrasyid (241511093)
///               Rizky Satria Gunawan (241511089)
/// Tanggal     : 11-05-2025

#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>

typedef char infotype;

typedef struct BTreeNode BTreeNode;

struct BTreeNode
{
  infotype info;
  BTreeNode *left;
  BTreeNode *right;
};

typedef struct BTree
{
  BTreeNode *root;
} BTree;

typedef BTreeNode *address;

// ==== Inisialisasi dan Pembuatan Tree ====

/**
 * @brief Membuat tree kosong baru
 * @return BTree Tree kosong yang baru dibuat
 * @author <nama>(<nim>)
 */
BTree create_tree();

/**
 * @brief Membuat node baru
 * @param info Nilai yang akan disimpan di node
 * @return address Alamat node baru
 * @author <nama>(<nim>)
 */
address create_node(infotype info);

/**
 * @brief Memeriksa apakah tree kosong
 * @param tree Tree yang akan diperiksa
 * @return true jika kosong, false jika tidak
 * @author <nama>(<nim>)
 */
bool is_empty(BTree tree);

// ==== Traversal ====

/**
 * @brief Melakukan traversal pre-order dan mencetak nilai node
 * @param node Root dari tree/subtree yang akan ditraversal
 * @author <nama>(<nim>)
 */
void pre_order(address node);

/**
 * @brief Melakukan traversal in-order dan mencetak nilai node
 * @param node Root dari tree/subtree yang akan ditraversal
 * @author <nama>(<nim>)
 */
void in_order(address node);

/**
 * @brief Melakukan traversal post-order dan mencetak nilai node
 * @param node Root dari tree/subtree yang akan ditraversal
 * @author <nama>(<nim>)
 */
void post_order(address node);

/**
 * @brief Melakukan traversal level-order dan mencetak nilai node
 * @param tree Tree yang akan ditraversal
 * @author <nama>(<nim>)
 */
void level_order(BTree tree);

// ==== Search ====

/**
 * @brief Mencari node dengan nilai tertentu
 * @param tree Tree yang akan dicari
 * @param info Nilai yang dicari
 * @return address Alamat node yang dicari, NULL jika tidak ditemukan
 * @author <nama>(<nim>)
 */
address search(BTree tree, infotype info);

/**
 * @brief Mencari parent dari node tertentu
 * @param tree Tree yang akan dicari
 * @param node Node yang akan dicari parentnya
 * @return address Alamat parent dari node, NULL jika tidak ditemukan atau node adalah root
 * @author <nama>(<nim>)
 */
address find_parent(BTree tree, address node);

// ==== Min/Max ====

/**
 * @brief Mencari node dengan nilai terkecil
 * @param tree Tree yang akan dicari
 * @return address Alamat node dengan nilai terkecil, NULL jika tree kosong
 * @author <nama>(<nim>)
 */
address find_min(BTree tree);

/**
 * @brief Mencari node dengan nilai terbesar
 * @param tree Tree yang akan dicari
 * @return address Alamat node dengan nilai terbesar, NULL jika tree kosong
 * @author <nama>(<nim>)
 */
address find_max(BTree tree);

// ==== Tree Properties ====

/**
 * @brief Menghitung kedalaman tree
 * @param tree Tree yang akan dihitung kedalamannya
 * @return int Kedalaman tree
 * @author <nama>(<nim>)
 */
int get_depth(BTree tree);

/**
 * @brief Menghitung tinggi dari suatu node
 * @param node Node yang akan dihitung tingginya
 * @return int Tinggi node, -1 jika node NULL
 * @author <nama>(<nim>)
 */
int get_height(address node);

/**
 * @brief Menghitung jumlah node dalam tree
 * @param tree Tree yang akan dihitung
 * @return int Jumlah node dalam tree
 * @author <nama>(<nim>)
 */
int count_nodes(BTree tree);

/**
 * @brief Menghitung jumlah leaf node dalam tree
 * @param tree Tree yang akan dihitung
 * @return int Jumlah leaf node dalam tree
 * @author <nama>(<nim>)
 */
int count_leaves(BTree tree);

// ==== Insert ====

/**
 * @brief Menyisipkan node baru ke dalam Binary Search Tree
 * @param tree Tree yang akan disisipkan node baru
 * @param info Nilai yang akan disisipkan
 * @return void
 * @author <nama>(<nim>)
 */
void insert_bst(BTree *tree, infotype info);

/**
 * @brief Menyisipkan node sebagai child kiri dari node tertentu
 * @param parent Node parent
 * @param info Nilai yang akan disisipkan
 * @return void
 * @author <nama>(<nim>)
 */
void insert_left(address parent, infotype info);

/**
 * @brief Menyisipkan node sebagai child kanan dari node tertentu
 * @param parent Node parent
 * @param info Nilai yang akan disisipkan
 * @return void
 * @author <nama>(<nim>)
 */
void insert_right(address parent, infotype info);

// ==== Delete ====

/**
 * @brief Menghapus node dengan nilai tertentu dari BST
 * @param tree Tree yang akan dihapus nodenya
 * @param info Nilai yang akan dihapus
 * @return void
 * @author <nama>(<nim>)
 */
void delete_node(BTree *tree, infotype info);

/**
 * @brief Menghapus semua node dalam tree dan membebaskan memori
 * @param tree Tree yang akan dihapus
 * @return void
 * @author <nama>(<nim>)
 */
void clear_tree(BTree *tree);

// ==== Balancing ====

/**
 * @brief Memeriksa apakah tree seimbang
 * @param tree Tree yang akan diperiksa
 * @return true jika seimbang, false jika tidak
 * @author <nama>(<nim>)
 */
bool is_balanced(BTree tree);

/**
 * @brief Mendapatkan faktor keseimbangan suatu node
 * @param node Node yang akan dihitung faktor keseimbangannya
 * @return int Faktor keseimbangan node
 * @author <nama>(<nim>)
 */
int get_balance_factor(address node);

/**
 * @brief Melakukan rotasi kiri pada node
 * @param node Node yang akan dirotasi
 * @return address Node hasil rotasi
 * @author <nama>(<nim>)
 */
address rotate_left(address node);

/**
 * @brief Melakukan rotasi kanan pada node
 * @param node Node yang akan dirotasi
 * @return address Node hasil rotasi
 * @author <nama>(<nim>)
 */
address rotate_right(address node);

/**
 * @brief Menyeimbangkan tree menggunakan algoritma AVL
 * @param tree Tree yang akan diseimbangkan
 * @return void
 * @author <nama>(<nim>)
 */
void balance_tree(BTree *tree);

// ==== Copy dan Compare ====

/**
 * @brief Membuat salinan dari tree
 * @param tree Tree yang akan disalin
 * @return BTree Salinan tree
 * @author <nama>(<nim>)
 */
BTree copy_tree(BTree tree);

/**
 * @brief Memeriksa apakah dua tree identik
 * @param tree1 Tree pertama
 * @param tree2 Tree kedua
 * @return true jika identik, false jika tidak
 * @author <nama>(<nim>)
 */
bool is_equal(BTree tree1, BTree tree2);

/**
 * @brief Memeriksa apakah tree adalah Binary Search Tree
 * @param tree Tree yang akan diperiksa
 * @return true jika BST, false jika bukan
 * @author <nama>(<nim>)
 */
bool is_bst(BTree tree);

#endif