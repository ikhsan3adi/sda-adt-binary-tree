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
 * @brief 1. Membuat tree kosong baru
 * @return BTree Tree kosong yang baru dibuat
 * @author Rizky Satria Gunawan (241511089)
 */
BTree create_tree();

/**
 * @brief 2. Membuat node baru
 * @param info Nilai yang akan disimpan di node
 * @return address Alamat node baru
 * @author Rizky Satria Gunawan (241511089)
 */
address create_node(infotype info);

/**
 * @brief 3. Memeriksa apakah tree kosong
 * @param tree Tree yang akan diperiksa
 * @return true jika kosong, false jika tidak
 * @author Ikhsan Satriadi (241511080)
 */
bool is_empty(BTree tree);

// ==== Traversal (Print) ====

/**
 * @brief 4. Melakukan traversal pre-order dan mencetak nilai node
 * @param node Root dari tree/subtree yang akan ditraversal
 * @author Ikhsan Satriadi (241511080)
 */
void pre_order(address node);

/**
 * @brief 5. Melakukan traversal in-order dan mencetak nilai node
 * @param node Root dari tree/subtree yang akan ditraversal
 * @author Rizky Satria Gunawan (241511089)
 */
void in_order(address node);

/**
 * @brief 6. Melakukan traversal post-order dan mencetak nilai node
 * @param node Root dari tree/subtree yang akan ditraversal
 * @author Yazid Alrasyid (241511093)
 */
void post_order(address node);

/**
 * @brief 7. Melakukan traversal level-order dan mencetak nilai node
 * @param tree Tree yang akan ditraversal
 * @author Ikhsan Satriadi (241511080)
 */
void level_order(BTree tree);

// ==== Search ====

/**
 * @brief 8. Mencari node dengan nilai tertentu
 * @param tree Tree yang akan dicari
 * @param info Nilai yang dicari
 * @return address Alamat node yang dicari, NULL jika tidak ditemukan
 * @author Rizky Satria Gunawan (241511089)
 */
address search(BTree tree, infotype info);

/**
 * @brief 9. Mencari parent dari node tertentu
 * @param tree Tree yang akan dicari
 * @param node Node yang akan dicari parentnya
 * @return address Alamat parent dari node, NULL jika tidak ditemukan atau node adalah root
 * @author Ikhsan Satriadi (241511080)
 */
address find_parent(BTree tree, address node);

// ==== Min/Max ====

/**
 * @brief 10. Mencari node dengan nilai terkecil
 * @param tree Tree yang akan dicari
 * @return address Alamat node dengan nilai terkecil, NULL jika tree kosong
 * @author Yazid Alrasyid (241511093)
 */
address find_min(BTree tree);

/**
 * @brief 11. Mencari node dengan nilai terbesar
 * @param tree Tree yang akan dicari
 * @return address Alamat node dengan nilai terbesar, NULL jika tree kosong
 * @author Yazid Alrasyid (241511093)
 */
address find_max(BTree tree);

// ==== Tree Properties ====

/**
 * @brief 12. Menghitung kedalaman tree
 * @param tree Tree yang akan dihitung kedalamannya
 * @return int Kedalaman tree
 * @author Rizky Satria Gunawan (241511089)
 */
int get_depth(BTree tree);

/**
 * @brief 13. Menghitung tinggi dari suatu node
 * @param node Node yang akan dihitung tingginya
 * @return int Tinggi node, -1 jika node NULL
 * @author Rizky Satria Gunawan (241511089)
 */
int get_height(address node);

/**
 * @brief 14. Menghitung jumlah node dalam tree
 * @param tree Tree yang akan dihitung
 * @return int Jumlah node dalam tree
 * @author Rizky Satria Gunawan (241511089)
 */
int count_nodes(BTree tree);

/**
 * @brief 15. Menghitung jumlah leaf node dalam tree
 * @param tree Tree yang akan dihitung
 * @return int Jumlah leaf node dalam tree
 * @author Yazid Alrasyid (241511093)
 */
int count_leaves(BTree tree);

// ==== Insert ====

/**
 * @brief 16. Menyisipkan node baru ke dalam Balance Tree
 * @param tree Tree yang akan disisipkan node baru
 * @param info Nilai yang akan disisipkan
 * @return void
 * @author Ikhsan Satriadi (241511080)
 */
void insert_balance(BTree *tree, infotype info);

/**
 * @brief 17. Menyisipkan node sebagai child kiri dari node tertentu
 * @param parent Node parent
 * @param info Nilai yang akan disisipkan
 * @return void
 * @author Yazid Alrasyid (241511093)
 */
void insert_left(address parent, infotype info);

/**
 * @brief 18. Menyisipkan node sebagai child kanan dari node tertentu
 * @param parent Node parent
 * @param info Nilai yang akan disisipkan
 * @return void
 * @author Yazid Alrasyid (241511093)
 */
void insert_right(address parent, infotype info);

// ==== Delete ====

/**
 * @brief 19. Menghapus node dengan nilai tertentu dari BST
 * @param tree Tree yang akan dihapus nodenya
 * @param info Nilai yang akan dihapus
 * @return void
 * @author Ikhsan Satriadi (241511080)
 */
void delete_node(BTree *tree, infotype info);

/**
 * @brief 20. Menghapus semua node dalam tree dan membebaskan memori
 * @param tree Tree yang akan dihapus
 * @return void
 * @author Yazid Alrasyid (241511093)
 */
void clear_tree(BTree *tree);

// ==== Copy dan Compare ====

/**
 * @brief 21. Membuat salinan dari tree
 * @param tree Tree yang akan disalin
 * @return BTree Salinan tree
 * @author Ikhsan Satriadi (241511080)
 */
BTree copy_tree(BTree tree);

/**
 * @brief 22. Memeriksa apakah dua tree identik
 * @param tree1 Tree pertama
 * @param tree2 Tree kedua
 * @return true jika identik, false jika tidak
 * @author Ikhsan Satriadi (241511080)
 */
bool is_equal(BTree tree1, BTree tree2);

#endif