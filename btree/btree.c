/// Nama File   : btree.c
/// Deskripsi   : File body untuk ADT Binary Tree Dinamis
/// Dibuat oleh : Ikhsan Satriadi (241511080)
///               Yazid Alrasyid (241511093)
///               Rizky Satria Gunawan (241511089)
/// Tanggal     : 13-05-2025

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

/** @author Rizky Satria Gunawan (241511089) */
BTree create_tree()
{
  BTree tree;
  tree.root = NULL;
  return tree;
}

/** @author Rizky Satria Gunawan (241511089) */
address create_node(infotype info)
{
  address new_node = (address)malloc(sizeof(BTreeNode));
  if (new_node != NULL)
  {
    new_node->info = info;
    new_node->left = NULL;
    new_node->right = NULL;
  }
  return new_node;
}

/** @author Ikhsan Satriadi (241511080) */
bool is_empty(BTree tree)
{
  return tree.root == NULL;
}

/**
 * Rekursif
 *  @author Ikhsan Satriadi (241511080) */
void pre_order(address node)
{
  if (node != NULL)
  {
    printf("%c ", node->info);
    pre_order(node->left);
    pre_order(node->right);
  }
}

/**
 * Rekursif
 *  @author Rizky Satria Gunawan (241511089) */
void in_order(address node)
{
  if (node != NULL)
  {
    in_order(node->left);
    printf("%c ", node->info);
    in_order(node->right);
  }
}

/**
 * Rekursif
 * @author Yazid Alrasyid (241511093) */
void post_order(address node)
{
  if (node != NULL)
  {
    post_order(node->left);
    post_order(node->right);
    printf("%c ", node->info);
  }
}

/**
 * Looping/Iterasi
 *  @author Ikhsan Satriadi (241511080) */
void level_order(BTree tree)
{
  if (is_empty(tree))
  {
    return;
  }

  address queue[100];
  int front = 0, rear = 0;

  queue[rear++] = tree.root;

  while (front < rear)
  {
    address current = queue[front++];
    printf("%c ", current->info);

    if (current->left != NULL)
    {
      queue[rear++] = current->left;
    }

    if (current->right != NULL)
    {
      queue[rear++] = current->right;
    }
  }
}

/**
 * Looping/Iterasi
 * @author Rizky Satria Gunawan (241511089) */
address search(BTree tree, infotype info)
{
  address current = tree.root;

  while (current != NULL)
  {
    if (current->info == info)
    {
      return current;
    }

    if (info < current->info)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  return NULL;
}

/**
 * Looping/Iterasi
 *  @author Ikhsan Satriadi (241511080) */
address find_parent(BTree tree, address node)
{
  if (is_empty(tree) || tree.root == node)
  {
    return NULL;
  }

  address current = tree.root;
  address parent = NULL;

  while (current != NULL && current != node)
  {
    parent = current;

    if (node->info < current->info)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  if (current == node)
  {
    return parent;
  }
  else
  {
    return NULL;
  }
}

/**
 * Looping/Iterasi
 *  @author Yazid Alrasyid (241511093) */
address find_min(BTree tree)
{
  if (is_empty(tree))
  {
    return NULL;
  }

  address current = tree.root;

  while (current->left != NULL)
  {
    current = current->left;
  }

  return current;
}

/**
 * Looping/Iterasi
 *  @author Yazid Alrasyid (241511093) */
address find_max(BTree tree)
{
  if (is_empty(tree))
  {
    return NULL;
  }

  address current = tree.root;

  while (current->right != NULL)
  {
    current = current->right;
  }

  return current;
}

/** @author Rizky Satria Gunawan (241511089) */
int get_depth(BTree tree)
{
  return get_height(tree.root);
}

/**
 * Rekursif
 * @author Rizky Satria Gunawan (241511089) */
int get_height(address node)
{
  if (node == NULL)
  {
    return -1;
  }

  int left_height = get_height(node->left);
  int right_height = get_height(node->right);

  if (left_height > right_height)
  {
    return (left_height + 1);
  }
  else
  {
    return (right_height + 1);
  }
}

/**
 *  Looping/Iterasi
 *  @author Rizky Satria Gunawan (241511089)
 */
int count_nodes(BTree tree)
{
  if (is_empty(tree))
  {
    return 0;
  }

  int count = 0;
  address queue[100];
  int front = 0, rear = 0;

  queue[rear++] = tree.root;

  while (front < rear)
  {
    address current = queue[front++];
    count++;

    if (current->left != NULL)
    {
      queue[rear++] = current->left;
    }

    if (current->right != NULL)
    {
      queue[rear++] = current->right;
    }
  }

  return count;
}

/** @author Yazid Alrasyid (241511093) */
int count_leaves_recursive(address node)
{
  if (node == NULL)
  {
    return 0;
  }

  if (node->left == NULL && node->right == NULL)
  {
    return 1;
  }

  return count_leaves_recursive(node->left) + count_leaves_recursive(node->right);
}

/**
 * Rekursif
 * @author Yazid Alrasyid (241511093)
 */
int count_leaves(BTree tree)
{
  return count_leaves_recursive(tree.root);
}

/**
 *  Looping/Iterasi
 * @author Ikhsan Satriadi (241511080)
 **/
void insert_balance(BTree *tree, infotype info)
{
  address new_node = create_node(info);

  if (new_node == NULL)
  {
    return;
  }

  if (is_empty(*tree))
  {
    tree->root = new_node;
    return;
  }

  address current = tree->root;
  address parent = NULL;

  while (current != NULL)
  {
    parent = current;

    if (info < current->info)
    {
      current = current->left;
    }
    else if (info > current->info)
    {
      current = current->right;
    }
    else
    {
      free(new_node);
      return;
    }
  }

  if (info < parent->info)
  {
    parent->left = new_node;
  }
  else
  {
    parent->right = new_node;
  }
}

/** @author Yazid Alrasyid (241511093) */
void insert_left(address parent, infotype info)
{
  if (parent == NULL)
  {
    return;
  }

  if (parent->left != NULL)
  {
    free(parent->left);
  }

  parent->left = create_node(info);
}

/** @author Yazid Alrasyid (241511093) */
void insert_right(address parent, infotype info)
{
  if (parent == NULL)
  {
    return;
  }

  if (parent->right != NULL)
  {
    free(parent->right);
  }

  parent->right = create_node(info);
}

/**
 * Looping/Iterasi
 * @author Ikhsan Satriadi (241511080) */
void delete_node(BTree *tree, infotype info)
{
  if (is_empty(*tree))
  {
    return;
  }

  address current = tree->root;
  address parent = NULL;
  int is_left_child = 0;

  while (current != NULL && current->info != info)
  {
    parent = current;

    if (info < current->info)
    {
      current = current->left;
      is_left_child = 1;
    }
    else
    {
      current = current->right;
      is_left_child = 0;
    }
  }

  if (current == NULL)
  {
    return;
  }

  if (current->left == NULL && current->right == NULL)
  {
    if (current == tree->root)
    {
      tree->root = NULL;
    }
    else if (is_left_child)
    {
      parent->left = NULL;
    }
    else
    {
      parent->right = NULL;
    }
    free(current);
  }
  else if (current->right == NULL)
  {
    if (current == tree->root)
    {
      tree->root = current->left;
    }
    else if (is_left_child)
    {
      parent->left = current->left;
    }
    else
    {
      parent->right = current->left;
    }
    free(current);
  }
  else if (current->left == NULL)
  {
    if (current == tree->root)
    {
      tree->root = current->right;
    }
    else if (is_left_child)
    {
      parent->left = current->right;
    }
    else
    {
      parent->right = current->right;
    }
    free(current);
  }
  else
  {
    address successor = current->right;
    address successor_parent = current;

    while (successor->left != NULL)
    {
      successor_parent = successor;
      successor = successor->left;
    }

    if (successor_parent != current)
    {
      successor_parent->left = successor->right;
      successor->right = current->right;
    }

    successor->left = current->left;

    if (current == tree->root)
    {
      tree->root = successor;
    }
    else if (is_left_child)
    {
      parent->left = successor;
    }
    else
    {
      parent->right = successor;
    }

    free(current);
  }
}

/** @author Yazid Alrasyid (241511093) */
void clear_tree_recursive(address node)
{
  if (node != NULL)
  {
    clear_tree_recursive(node->left);
    clear_tree_recursive(node->right);
    free(node);
  }
}

/**
 * Rekursif
 * @author Yazid Alrasyid (241511093)
 */
void clear_tree(BTree *tree)
{
  clear_tree_recursive(tree->root);
  tree->root = NULL;
}

/** @author Ikhsan Satriadi (241511080) */
address copy_node_recursive(address node)
{
  if (node == NULL)
  {
    return NULL;
  }

  address new_node = create_node(node->info);
  new_node->left = copy_node_recursive(node->left);
  new_node->right = copy_node_recursive(node->right);

  return new_node;
}

/**
 * Rekursif
 *  @author Ikhsan Satriadi (241511080)*/
BTree copy_tree(BTree tree)
{
  BTree new_tree = create_tree();
  new_tree.root = copy_node_recursive(tree.root);
  return new_tree;
}

/** @author Ikhsan Satriadi (241511080) */
int is_equal_recursive(address node1, address node2)
{
  if (node1 == NULL && node2 == NULL)
  {
    return 1;
  }

  if (node1 == NULL || node2 == NULL)
  {
    return 0;
  }

  return (node1->info == node2->info) &&
         is_equal_recursive(node1->left, node2->left) &&
         is_equal_recursive(node1->right, node2->right);
}

/**
 * Rekursif
 *  @author Ikhsan Satriadi (241511080) */
bool is_equal(BTree tree1, BTree tree2)
{
  return is_equal_recursive(tree1.root, tree2.root);
}
