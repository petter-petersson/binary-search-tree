#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define BST_MAX(a,b) (((a)>(b))?(a):(b))

//accessor macros
#ifdef DEBUG
#define deref_bst_node_t(_n) (assert((_n)!=0), (_n))
#else
#define deref_bst_node_t(_n) (_n)
#endif
//modify
#define x_left_bst_node_t(_n) (deref_bst_node_t(_n)->left)
#define x_right_bst_node_t(_n) (deref_bst_node_t(_n)->right)
#define x_key_bst_node_t(_n) (deref_bst_node_t(_n)->key)
#define x_value_bst_node_t(_n) (deref_bst_node_t(_n)->value)
#define x_height_bst_node_t(_n) (deref_bst_node_t(_n)->height)
//read
#define left_bst_node_t(_n) ((void)0, x_left_bst_node_t(_n))
#define right_bst_node_t(_n) ((void)0, x_right_bst_node_t(_n))
#define key_bst_node_t(_n) ((void)0, x_key_bst_node_t(_n))
#define value_bst_node_t(_n) ((void)0, x_value_bst_node_t(_n))
#define height_bst_node_t(_n) ((void)0, x_height_bst_node_t(_n))

#define BST_SET_HEIGHT(node) \
  x_height_bst_node_t(node) = 1 + BST_MAX( \
      right_bst_node_t(node) == NULL ? 0 : height_bst_node_t(right_bst_node_t(node)), \
      left_bst_node_t(node) == NULL ? 0 : height_bst_node_t(left_bst_node_t(node)))

typedef struct bst_node_s {
  struct bst_node_s * left;
  struct bst_node_s * right;
  int key;
  void * value;
  int height;
} bst_node_t;

typedef struct bst_s {
  bst_node_t * root;
} bst_t;

typedef void (*traverse_func) (bst_node_t *, void * arg);
bst_t * bst_init();
void bst_add(bst_t * tree, int key, void * value);
void bst_insert(bst_node_t ** node, int key, void * value);
void bst_traverse(bst_node_t * node, traverse_func func, void * arg);
void bst_delete(bst_t * tree, int key);
void bst_free(bst_t * tree);
bst_node_t * bst_find(bst_node_t * node, int key);

/* private */
void bst_node_free(bst_node_t * node);
bst_node_t * bst_rotate_left(bst_node_t * node);
bst_node_t * bst_rotate_right(bst_node_t * node);
bst_node_t * bst_rotate_leftright(bst_node_t * node);
bst_node_t * bst_rotate_rightleft(bst_node_t * node);
int bst_balance(bst_node_t * node);
void bst_node_delete(bst_t * tree, bst_node_t * current_root, bst_node_t * node, int key);
bst_node_t * bst_find_parent(bst_node_t * parent, bst_node_t * node, int key);
bst_node_t * bst_find_min(bst_node_t * node);
#endif
