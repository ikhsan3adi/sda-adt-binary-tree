/// Nama File   : main.c
/// Deskripsi   : File driver untuk ADT Binary Tree Dinamis
/// Dibuat oleh : Ikhsan Satriadi (241511080)
///               Yazid Alrasyid (241511093)
///               Rizky Satria Gunawan (241511089)
/// Tanggal     : 14-05-2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "btree/btree.h"

void print_menu()
{
    printf("\n===== BINARY TREE MENU =====\n");
    printf("1.  Buat tree baru\n");
    printf("2.  Tambah node\n");
    printf("3.  Tambah node di kiri\n");
    printf("4.  Tambah node di kanan\n");
    printf("5.  Hapus node\n");
    printf("6.  Cari node\n");
    printf("7.  Cari parent\n");
    printf("8.  Cari nilai minimum\n");
    printf("9.  Cari nilai maksimum\n");
    printf("10. Tampilkan pre-order\n");
    printf("11. Tampilkan in-order\n");
    printf("12. Tampilkan post-order\n");
    printf("13. Tampilkan level-order\n");
    printf("14. Hitung jumlah node\n");
    printf("15. Hitung jumlah daun\n");
    printf("16. Hitung kedalaman tree\n");
    printf("17. Salin tree\n");
    printf("18. Bandingkan tree\n");
    printf("19. Hapus semua node\n");
    printf("0.  Keluar\n");
    printf("Pilihan Anda: ");
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void pause()
{
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}

BTree buat_tree_manual()
{
    BTree tree = create_tree();

    address root = create_node('A');
    tree.root = root;

    insert_left(root, 'B');
    insert_right(root, 'C');

    insert_left(root->left, 'D');
    insert_right(root->left, 'E');

    insert_left(root->right, 'F');
    insert_right(root->right, 'G');

    printf("Tree contoh dibuat dengan struktur:\n");
    printf("    A    \n");
    printf("   / \\   \n");
    printf("  B   C  \n");
    printf(" / \\ / \\\n");
    printf("D  E F  G\n");

    return tree;
}

void cetak_header()
{
    printf("\n===== HASIL =====\n");
}

void tampilkan_traversal(BTree tree)
{
    cetak_header();

    if (is_empty(tree))
    {
        printf("Tree kosong!\n");
        return;
    }

    printf("Pre-order  : ");
    pre_order(tree.root);
    printf("\n");

    printf("In-order   : ");
    in_order(tree.root);
    printf("\n");

    printf("Post-order : ");
    post_order(tree.root);
    printf("\n");

    printf("Level-order: ");
    level_order(tree);
    printf("\n");
}

void proses_buat_tree(BTree *tree)
{
    char pilihan;

    printf("\nPilih opsi pembuatan tree:\n");
    printf("1. Tree kosong\n");
    printf("2. Tree contoh\n");
    printf("Pilihan Anda: ");
    scanf(" %c", &pilihan);
    clear_input_buffer();

    if (pilihan == '1')
    {
        *tree = create_tree();
        printf("Tree kosong berhasil dibuat!\n");
    }
    else if (pilihan == '2')
    {
        *tree = buat_tree_manual();
    }
    else
    {
        printf("Pilihan tidak valid. Tree kosong dibuat.\n");
        *tree = create_tree();
    }
}

void proses_tambah_node(BTree *tree)
{
    char nilai;

    printf("\nMasukkan nilai node (karakter): ");
    scanf(" %c", &nilai);
    clear_input_buffer();

    insert_balance(tree, nilai);
    printf("Node dengan nilai '%c' berhasil ditambahkan!\n", nilai);

    tampilkan_traversal(*tree);
}

void proses_tambah_kiri(BTree tree)
{
    char nilai_parent, nilai_child;

    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak dapat menambahkan node.\n");
        return;
    }

    printf("\nMasukkan nilai node parent (karakter): ");
    scanf(" %c", &nilai_parent);
    clear_input_buffer();

    address parent = search(tree, nilai_parent);
    if (parent == NULL)
    {
        printf("Node dengan nilai '%c' tidak ditemukan!\n", nilai_parent);
        return;
    }

    printf("Masukkan nilai node child (karakter): ");
    scanf(" %c", &nilai_child);
    clear_input_buffer();

    insert_left(parent, nilai_child);
    printf("Node dengan nilai '%c' berhasil ditambahkan sebagai child kiri dari '%c'!\n",
           nilai_child, nilai_parent);

    tampilkan_traversal(tree);
}

void proses_tambah_kanan(BTree tree)
{
    char nilai_parent, nilai_child;

    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak dapat menambahkan node.\n");
        return;
    }

    printf("\nMasukkan nilai node parent (karakter): ");
    scanf(" %c", &nilai_parent);
    clear_input_buffer();

    address parent = search(tree, nilai_parent);
    if (parent == NULL)
    {
        printf("Node dengan nilai '%c' tidak ditemukan!\n", nilai_parent);
        return;
    }

    printf("Masukkan nilai node child (karakter): ");
    scanf(" %c", &nilai_child);
    clear_input_buffer();

    insert_right(parent, nilai_child);
    printf("Node dengan nilai '%c' berhasil ditambahkan sebagai child kanan dari '%c'!\n",
           nilai_child, nilai_parent);

    tampilkan_traversal(tree);
}

void proses_hapus_node(BTree *tree)
{
    char nilai;

    if (is_empty(*tree))
    {
        printf("Tree kosong! Tidak ada node yang dapat dihapus.\n");
        return;
    }

    printf("\nMasukkan nilai node yang akan dihapus (karakter): ");
    scanf(" %c", &nilai);
    clear_input_buffer();

    if (search(*tree, nilai) == NULL)
    {
        printf("Node dengan nilai '%c' tidak ditemukan!\n", nilai);
        return;
    }

    delete_node(tree, nilai);
    printf("Node dengan nilai '%c' berhasil dihapus!\n", nilai);

    tampilkan_traversal(*tree);
}

void proses_cari_node(BTree tree)
{
    char nilai;

    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak ada node yang dapat dicari.\n");
        return;
    }

    printf("\nMasukkan nilai node yang akan dicari (karakter): ");
    scanf(" %c", &nilai);
    clear_input_buffer();

    address hasil = search(tree, nilai);

    cetak_header();
    if (hasil != NULL)
    {
        printf("Node dengan nilai '%c' ditemukan!\n", nilai);

        if (hasil->left != NULL)
        {
            printf("- Child kiri: %c\n", hasil->left->info);
        }
        else
        {
            printf("- Child kiri: (tidak ada)\n");
        }

        if (hasil->right != NULL)
        {
            printf("- Child kanan: %c\n", hasil->right->info);
        }
        else
        {
            printf("- Child kanan: (tidak ada)\n");
        }
    }
    else
    {
        printf("Node dengan nilai '%c' tidak ditemukan!\n", nilai);
    }
}

void proses_cari_parent(BTree tree)
{
    char nilai;

    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak ada node yang dapat dicari.\n");
        return;
    }

    printf("\nMasukkan nilai node yang akan dicari parentnya (karakter): ");
    scanf(" %c", &nilai);
    clear_input_buffer();

    address node = search(tree, nilai);
    if (node == NULL)
    {
        printf("Node dengan nilai '%c' tidak ditemukan!\n", nilai);
        return;
    }

    address parent = find_parent(tree, node);

    cetak_header();
    if (parent != NULL)
    {
        printf("Parent dari node '%c' adalah '%c'.\n", nilai, parent->info);
    }
    else
    {
        printf("Node '%c' adalah root, tidak memiliki parent.\n", nilai);
    }
}

void proses_cari_min(BTree tree)
{
    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak ada nilai minimum.\n");
        return;
    }

    address min = find_min(tree);

    cetak_header();
    printf("Nilai minimum dalam tree adalah: %c\n", min->info);
}

void proses_cari_max(BTree tree)
{
    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak ada nilai maksimum.\n");
        return;
    }

    address max = find_max(tree);

    cetak_header();
    printf("Nilai maksimum dalam tree adalah: %c\n", max->info);
}

void proses_tampilkan_preorder(BTree tree)
{
    cetak_header();

    if (is_empty(tree))
    {
        printf("Tree kosong!\n");
        return;
    }

    printf("Pre-order: ");
    pre_order(tree.root);
    printf("\n");
}

void proses_tampilkan_inorder(BTree tree)
{
    cetak_header();

    if (is_empty(tree))
    {
        printf("Tree kosong!\n");
        return;
    }

    printf("In-order: ");
    in_order(tree.root);
    printf("\n");
}

void proses_tampilkan_postorder(BTree tree)
{
    cetak_header();

    if (is_empty(tree))
    {
        printf("Tree kosong!\n");
        return;
    }

    printf("Post-order: ");
    post_order(tree.root);
    printf("\n");
}

void proses_tampilkan_levelorder(BTree tree)
{
    cetak_header();

    if (is_empty(tree))
    {
        printf("Tree kosong!\n");
        return;
    }

    printf("Level-order: ");
    level_order(tree);
    printf("\n");
}

void proses_hitung_node(BTree tree)
{
    int jumlah = count_nodes(tree);

    cetak_header();
    printf("Jumlah node dalam tree: %d\n", jumlah);
}

void proses_hitung_daun(BTree tree)
{
    int jumlah = count_leaves(tree);

    cetak_header();
    printf("Jumlah daun dalam tree: %d\n", jumlah);
}

void proses_hitung_kedalaman(BTree tree)
{
    int kedalaman = get_depth(tree);

    cetak_header();
    printf("Kedalaman tree: %d\n", kedalaman);
}

void proses_salin_tree(BTree tree, BTree *tree2)
{
    if (is_empty(tree))
    {
        printf("Tree kosong! Tidak ada yang dapat disalin.\n");
        return;
    }

    *tree2 = copy_tree(tree);

    cetak_header();
    printf("Tree berhasil disalin!\n");

    printf("\nTree asli:\n");
    printf("Pre-order: ");
    pre_order(tree.root);
    printf("\n");

    printf("\nTree salinan:\n");
    printf("Pre-order: ");
    pre_order(tree2->root);
    printf("\n");
}

void proses_bandingkan_tree(BTree tree1, BTree tree2)
{
    cetak_header();

    if (is_equal(tree1, tree2))
    {
        printf("Kedua tree identik!\n");
    }
    else
    {
        printf("Kedua tree berbeda!\n");
    }

    printf("\nTree 1:\n");
    printf("Pre-order: ");
    if (!is_empty(tree1))
    {
        pre_order(tree1.root);
    }
    else
    {
        printf("(kosong)");
    }
    printf("\n");

    printf("\nTree 2:\n");
    printf("Pre-order: ");
    if (!is_empty(tree2))
    {
        pre_order(tree2.root);
    }
    else
    {
        printf("(kosong)");
    }
    printf("\n");
}

void proses_hapus_semua(BTree *tree)
{
    if (is_empty(*tree))
    {
        printf("Tree sudah kosong!\n");
        return;
    }

    clear_tree(tree);

    cetak_header();
    printf("Semua node berhasil dihapus!\n");
}

int main()
{
    BTree tree = create_tree();
    BTree tree2 = create_tree();
    int pilihan;
    bool jalan = true;

    printf("PROGRAM BINARY TREE\n");
    printf("===================\n");

    while (jalan)
    {
        print_menu();
        scanf("%d", &pilihan);
        clear_input_buffer();

        switch (pilihan)
        {
        case 1:
            proses_buat_tree(&tree);
            break;
        case 2:
            proses_tambah_node(&tree);
            break;
        case 3:
            proses_tambah_kiri(tree);
            break;
        case 4:
            proses_tambah_kanan(tree);
            break;
        case 5:
            proses_hapus_node(&tree);
            break;
        case 6:
            proses_cari_node(tree);
            break;
        case 7:
            proses_cari_parent(tree);
            break;
        case 8:
            proses_cari_min(tree);
            break;
        case 9:
            proses_cari_max(tree);
            break;
        case 10:
            proses_tampilkan_preorder(tree);
            break;
        case 11:
            proses_tampilkan_inorder(tree);
            break;
        case 12:
            proses_tampilkan_postorder(tree);
            break;
        case 13:
            proses_tampilkan_levelorder(tree);
            break;
        case 14:
            proses_hitung_node(tree);
            break;
        case 15:
            proses_hitung_daun(tree);
            break;
        case 16:
            proses_hitung_kedalaman(tree);
            break;
        case 17:
            proses_salin_tree(tree, &tree2);
            break;
        case 18:
            proses_bandingkan_tree(tree, tree2);
            break;
        case 19:
            proses_hapus_semua(&tree);
            break;
        case 0:
            jalan = false;
            printf("\nTerima kasih\n");
            break;
        default:
            printf("\nPilihan tidak valid. Silakan pilih lagi.\n");
        }

        if (jalan && pilihan >= 0 && pilihan <= 19)
        {
            pause();
        }
    }

    clear_tree(&tree);
    clear_tree(&tree2);

    return 0;
}