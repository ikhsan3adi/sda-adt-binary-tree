/// Nama File   : btree.c
/// Deskripsi   : File body untuk ADT Binary Tree Dinamis
/// Dibuat oleh : Ikhsan Satriadi (241511080)
///               Yazid Alrasyid (241511093)
///               Rizky Satria Gunawan (241511089)
/// Tanggal     : 11-05-2025

#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodeStack
{
  address node;
  struct NodeStack *next;
} NodeStack;

typedef struct NodeQueue
{
  address node;
  struct NodeQueue *next;
} NodeQueue;

NodeStack *create_stack_node(address node)
{
  NodeStack *stack_node = (NodeStack *)malloc(sizeof(NodeStack));
  stack_node->node = node;
  stack_node->next = NULL;
  return stack_node;
}

bool is_stack_empty(NodeStack *stack)
{
  return stack == NULL;
}

void push(NodeStack **stack, address node)
{
  NodeStack *new_node = create_stack_node(node);
  new_node->next = *stack;
  *stack = new_node;
}

address pop(NodeStack **stack)
{
  if (is_stack_empty(*stack))
    return NULL;

  NodeStack *temp = *stack;
  *stack = (*stack)->next;
  address popped = temp->node;
  free(temp);

  return popped;
}

address peek(NodeStack *stack)
{
  if (is_stack_empty(stack))
    return NULL;
  return stack->node;
}

NodeQueue *create_queue_node(address node)
{
  NodeQueue *queue_node = (NodeQueue *)malloc(sizeof(NodeQueue));
  queue_node->node = node;
  queue_node->next = NULL;
  return queue_node;
}

bool is_queue_empty(NodeQueue *front)
{
  return front == NULL;
}

void enqueue(NodeQueue **front, NodeQueue **rear, address node)
{
  NodeQueue *new_node = create_queue_node(node);

  if (*rear == NULL)
  {
    *front = *rear = new_node;
    return;
  }

  (*rear)->next = new_node;
  *rear = new_node;
}

address dequeue(NodeQueue **front, NodeQueue **rear)
{
  if (is_queue_empty(*front))
    return NULL;

  NodeQueue *temp = *front;
  address dequeued = temp->node;

  *front = temp->next;

  if (*front == NULL)
    *rear = NULL;

  free(temp);
  return dequeued;
}

// ==== Inisialisasi dan Pembuatan Tree ====
BTree create_tree()
{
  BTree tree;
  tree.root = NULL;
  return tree;
}

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

bool is_empty(BTree tree)
{
  return tree.root == NULL;
}

// ==== Traversal ====
void pre_order(address node)
{
  if (node == NULL)
    return;

  NodeStack *stack = NULL;
  push(&stack, node);

  while (!is_stack_empty(stack))
  {
    address current = pop(&stack);
    printf("%c ", current->info);

    // Dorong ke kanan terlebih dahulu agar yang kiri diproses terlebih dahulu (LIFO)
    if (current->right)
      push(&stack, current->right);
    if (current->left)
      push(&stack, current->left);
  }
}

void in_order(address node)
{
  if (node == NULL)
    return;

  NodeStack *stack = NULL;
  address current = node;

  while (current != NULL || !is_stack_empty(stack))
  {
    while (current != NULL)
    {
      push(&stack, current);
      current = current->left;
    }

    current = pop(&stack);
    printf("%c ", current->info);

    current = current->right;
  }
}

void post_order(address node)
{
  if (node == NULL)
    return;

  NodeStack *s1 = NULL;
  NodeStack *s2 = NULL;

  push(&s1, node);

  // First traverse into s2
  while (!is_stack_empty(s1))
  {
    address current = pop(&s1);
    push(&s2, current);

    if (current->left)
      push(&s1, current->left);
    if (current->right)
      push(&s1, current->right);
  }

  while (!is_stack_empty(s2))
  {
    address current = pop(&s2);
    printf("%c ", current->info);
  }
}

void level_order(BTree tree)
{
  if (is_empty(tree))
    return;

  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);
    printf("%c ", current->info);

    if (current->left)
      enqueue(&front, &rear, current->left);
    if (current->right)
      enqueue(&front, &rear, current->right);
  }
}

// ==== Search ====
address search(BTree tree, infotype info)
{
  if (is_empty(tree))
    return NULL;

  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);

    if (current->info == info)
      return current;

    if (current->left)
      enqueue(&front, &rear, current->left);
    if (current->right)
      enqueue(&front, &rear, current->right);
  }

  return NULL;
}

address find_parent(BTree tree, address node)
{
  if (is_empty(tree) || tree.root == node)
    return NULL;

  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);

    if ((current->left == node) || (current->right == node))
      return current;

    if (current->left)
      enqueue(&front, &rear, current->left);
    if (current->right)
      enqueue(&front, &rear, current->right);
  }

  return NULL;
}

// ==== Min/Max ====
address find_min(BTree tree)
{
  if (is_empty(tree))
    return NULL;

  address current = tree.root;

  // Untuk BST, node paling kiri adalah simpul minimum
  while (current->left != NULL)
  {
    current = current->left;
  }

  return current;
}

address find_max(BTree tree)
{
  if (is_empty(tree))
    return NULL;

  address current = tree.root;

  // Untuk BST, node paling kanan adalah maksimum
  while (current->right != NULL)
  {
    current = current->right;
  }

  return current;
}

// ==== Tree Properti ====
int get_depth(BTree tree)
{
  return get_height(tree.root);
}

int get_height(address node)
{
  if (node == NULL)
    return -1;

  int height = -1;
  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, node);
  enqueue(&front, &rear, NULL);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);

    if (current == NULL)
    {
      height++;
      if (!is_queue_empty(front))
      {
        enqueue(&front, &rear, NULL);
      }
    }
    else
    {
      if (current->left)
        enqueue(&front, &rear, current->left);
      if (current->right)
        enqueue(&front, &rear, current->right);
    }
  }

  return height;
}

int count_nodes(BTree tree)
{
  if (is_empty(tree))
    return 0;

  int count = 0;
  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);
    count++;

    if (current->left)
      enqueue(&front, &rear, current->left);
    if (current->right)
      enqueue(&front, &rear, current->right);
  }

  return count;
}

int count_leaves(BTree tree)
{
  if (is_empty(tree))
    return 0;

  int leaf_count = 0;
  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);

    // Jika node tidak memiliki anak, maka simpul tersebut adalah daun
    if (current->left == NULL && current->right == NULL)
      leaf_count++;

    if (current->left)
      enqueue(&front, &rear, current->left);
    if (current->right)
      enqueue(&front, &rear, current->right);
  }

  return leaf_count;
}

// ==== Insert ====
void insert_bst(BTree *tree, infotype info)
{
  address new_node = create_node(info);
  if (new_node == NULL)
    return;

  // Jika pohon kosong, jadikan node baru sebagai root
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
      current = current->left;
    else if (info > current->info)
      current = current->right;
    else
      return;
  }

  if (info < parent->info)
    parent->left = new_node;
  else
    parent->right = new_node;
}

void insert_left(address parent, infotype info)
{
  if (parent == NULL)
    return;

  if (parent->left != NULL)
    return;

  address new_node = create_node(info);
  if (new_node != NULL)
    parent->left = new_node;
}

void insert_right(address parent, infotype info)
{
  if (parent == NULL)
    return;

  if (parent->right != NULL)
    return;

  address new_node = create_node(info);
  if (new_node != NULL)
    parent->right = new_node;
}

// ==== Delete ====
void delete_node(BTree *tree, infotype info)
{
  if (is_empty(*tree))
    return;

  address current = tree->root;
  address parent = NULL;
  bool is_left_child = false;

  // Temukan node yang akan dihapus
  while (current != NULL && current->info != info)
  {
    parent = current;

    if (info < current->info)
    {
      current = current->left;
      is_left_child = true;
    }
    else
    {
      current = current->right;
      is_left_child = false;
    }
  }

  if (current == NULL)
    return; // Node not found

  // Case 1: Node adalah daun
  if (current->left == NULL && current->right == NULL)
  {
    if (current == tree->root)
      tree->root = NULL;
    else if (is_left_child)
      parent->left = NULL;
    else
      parent->right = NULL;

    free(current);
  }
  // Case 2: Node memiliki satu anak
  else if (current->left == NULL)
  {
    if (current == tree->root)
      tree->root = current->right;
    else if (is_left_child)
      parent->left = current->right;
    else
      parent->right = current->right;

    free(current);
  }
  else if (current->right == NULL)
  {
    if (current == tree->root)
      tree->root = current->left;
    else if (is_left_child)
      parent->left = current->left;
    else
      parent->right = current->left;

    free(current);
  }
  // Case 3: Node memiliki dua anak
  else
  {
    address successor = current->right;
    address successor_parent = current;

    // Temukan successor (node terkecil di subtree kanan)
    while (successor->left != NULL)
    {
      successor_parent = successor;
      successor = successor->left;
    }

    // Ganti nilai current dengan successor
    if (successor_parent != current)
    {
      successor_parent->left = successor->right;
      successor->right = current->right;
    }

    if (current == tree->root)
      tree->root = successor;
    else if (is_left_child)
      parent->left = successor;
    else
      parent->right = successor;

    successor->left = current->left;
    free(current);
  }
}

void clear_tree(BTree *tree)
{
  if (is_empty(*tree))
    return;

  NodeQueue *nodes_to_delete = NULL;
  NodeQueue *nodes_end = NULL;

  enqueue(&nodes_to_delete, &nodes_end, tree->root);

  while (!is_queue_empty(nodes_to_delete))
  {
    address current = dequeue(&nodes_to_delete, &nodes_end);

    if (current->left)
      enqueue(&nodes_to_delete, &nodes_end, current->left);
    if (current->right)
      enqueue(&nodes_to_delete, &nodes_end, current->right);

    free(current);
  }

  tree->root = NULL;
}

// ==== Balancing ====
bool is_balanced(BTree tree)
{
  if (is_empty(tree))
    return true;

  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;

  enqueue(&front, &rear, tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);

    int balance_factor = get_balance_factor(current);
    if (balance_factor < -1 || balance_factor > 1)
      return false;

    if (current->left)
      enqueue(&front, &rear, current->left);
    if (current->right)
      enqueue(&front, &rear, current->right);
  }

  return true;
}

int get_balance_factor(address node)
{
  if (node == NULL)
    return 0;

  int left_height = get_height(node->left);
  int right_height = get_height(node->right);

  return left_height - right_height;
}

address rotate_left(address node)
{
  if (node == NULL || node->right == NULL)
    return node;

  address new_root = node->right;
  node->right = new_root->left;
  new_root->left = node;

  return new_root;
}

address rotate_right(address node)
{
  if (node == NULL || node->left == NULL)
    return node;

  address new_root = node->left;
  node->left = new_root->right;
  new_root->right = node;

  return new_root;
}

// Struktur untuk menyimpan informasi node di stack
typedef struct
{
  int start;
  int end;
  address parent;
  bool is_left;
} BalanceTask;

// Implementasi iteratif untuk membangun balanced tree
address build_balanced_tree_iterative(infotype *values, int n)
{
  if (n == 0)
    return NULL;

  BalanceTask *tasks = (BalanceTask *)malloc(n * sizeof(BalanceTask));
  if (!tasks)
    return NULL;

  int top = 0;
  address root = NULL;

  tasks[0].start = 0;
  tasks[0].end = n - 1;
  tasks[0].parent = NULL;
  tasks[0].is_left = false;

  // Proses semua tugas
  while (top >= 0)
  {
    BalanceTask task = tasks[top--];
    int start = task.start;
    int end = task.end;

    if (start <= end)
    {
      int mid = (start + end) / 2;

      address new_node = create_node(values[mid]);
      if (!new_node)
        continue;

      if (task.parent == NULL)
      {
        root = new_node;
      }
      else if (task.is_left)
      {
        task.parent->left = new_node;
      }
      else
      {
        task.parent->right = new_node;
      }

      // Tambahkan tugas untuk subtree kanan
      if (mid + 1 <= end)
      {
        top++;
        tasks[top].start = mid + 1;
        tasks[top].end = end;
        tasks[top].parent = new_node;
        tasks[top].is_left = false;
      }

      // Tambahkan tugas untuk subtree kiri
      if (start <= mid - 1)
      {
        top++;
        tasks[top].start = start;
        tasks[top].end = mid - 1;
        tasks[top].parent = new_node;
        tasks[top].is_left = true;
      }
    }
  }

  free(tasks);
  return root;
}

void balance_tree(BTree *tree)
{
  if (is_empty(*tree))
    return;

  int count = count_nodes(*tree);

  infotype *sorted_values = (infotype *)malloc(count * sizeof(infotype));
  if (!sorted_values)
    return;

  // Traversal in-order untuk mendapatkan nilai terurut
  NodeStack *stack = NULL;
  address current = tree->root;
  int index = 0;

  while (current != NULL || !is_stack_empty(stack))
  {
    while (current != NULL)
    {
      push(&stack, current);
      current = current->left;
    }

    current = pop(&stack);
    sorted_values[index++] = current->info;
    current = current->right;
  }

  clear_tree(tree);

  tree->root = build_balanced_tree_iterative(sorted_values, count);

  free(sorted_values);
}

// ==== Copy and Compare ====
BTree copy_tree(BTree tree)
{
  BTree new_tree = create_tree();
  if (is_empty(tree))
    return new_tree;

  NodeQueue *front = NULL;
  NodeQueue *rear = NULL;
  NodeQueue *new_front = NULL;
  NodeQueue *new_rear = NULL;

  new_tree.root = create_node(tree.root->info);

  enqueue(&front, &rear, tree.root);
  enqueue(&new_front, &new_rear, new_tree.root);

  while (!is_queue_empty(front))
  {
    address current = dequeue(&front, &rear);
    address new_current = dequeue(&new_front, &new_rear);

    if (current->left)
    {
      new_current->left = create_node(current->left->info);
      enqueue(&front, &rear, current->left);
      enqueue(&new_front, &new_rear, new_current->left);
    }

    if (current->right)
    {
      new_current->right = create_node(current->right->info);
      enqueue(&front, &rear, current->right);
      enqueue(&new_front, &new_rear, new_current->right);
    }
  }

  return new_tree;
}

bool is_equal(BTree tree1, BTree tree2)
{
  if (is_empty(tree1) && is_empty(tree2))
    return true;

  if (is_empty(tree1) || is_empty(tree2))
    return false;

  NodeQueue *front1 = NULL;
  NodeQueue *rear1 = NULL;
  NodeQueue *front2 = NULL;
  NodeQueue *rear2 = NULL;

  enqueue(&front1, &rear1, tree1.root);
  enqueue(&front2, &rear2, tree2.root);

  while (!is_queue_empty(front1) && !is_queue_empty(front2))
  {
    address current1 = dequeue(&front1, &rear1);
    address current2 = dequeue(&front2, &rear2);

    if (current1->info != current2->info)
      return false;

    if ((current1->left == NULL && current2->left != NULL) ||
        (current1->left != NULL && current2->left == NULL))
      return false;

    if ((current1->right == NULL && current2->right != NULL) ||
        (current1->right != NULL && current2->right == NULL))
      return false;

    if (current1->left)
    {
      enqueue(&front1, &rear1, current1->left);
      enqueue(&front2, &rear2, current2->left);
    }

    if (current1->right)
    {
      enqueue(&front1, &rear1, current1->right);
      enqueue(&front2, &rear2, current2->right);
    }
  }

  return is_queue_empty(front1) && is_queue_empty(front2);
}

bool is_bst(BTree tree)
{
  if (is_empty(tree))
    return true;

  NodeStack *stack = NULL;
  address current = tree.root;
  infotype prev = '\0';
  bool first = true;

  while (current != NULL || !is_stack_empty(stack))
  {
    while (current != NULL)
    {
      push(&stack, current);
      current = current->left;
    }

    current = pop(&stack);

    if (!first && current->info <= prev)
      return false;

    if (first)
      first = false;

    prev = current->info;
    current = current->right;
  }

  return true;
}