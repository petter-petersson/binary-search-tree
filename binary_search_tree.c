#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binary_search_tree.h"

bst_t * bst_init() {
  bst_t * tree = malloc(sizeof(bst_t));
  if (tree == NULL) {
    fprintf(stderr, "warn: failed to allocate memory for bst_t\n");
  }
  tree->root = NULL;
  return tree;
}

void bst_add(bst_t * tree, int key, void * value) {
  bst_insert(&(tree->root), key, value);
}

void bst_insert(bst_node_t ** node, int key, void * value){
  if(*node == NULL){
    *node = malloc(sizeof(bst_node_t));
    if(*node == NULL){
      fprintf(stderr, "could not allocate memory for node\n");
      return;
    }
    x_left_bst_node_t(*node) = NULL;
    x_right_bst_node_t(*node) = NULL;
    x_key_bst_node_t(*node) = key;
    x_value_bst_node_t(*node) = value;
    x_height_bst_node_t(*node) = 0;
    return;
  }
  if(key_bst_node_t(*node) == key){
    x_value_bst_node_t(*node) = value;
    return;
  }
  if(key < key_bst_node_t(*node)){
    bst_insert(&(x_left_bst_node_t(*node)), key, value);
  } else {
    bst_insert(&(x_right_bst_node_t(*node)), key, value);
  }
  BST_SET_HEIGHT(*node);

  int balance = bst_balance(*node);
  if(balance > 1){
    int left_balance = bst_balance(left_bst_node_t(*node));
    if( left_balance > 0){
      *node = bst_rotate_right(*node);
    } else if (left_balance < 0){
      *node = bst_rotate_leftright(*node);
    }
  } else if(balance < -1){
    int right_balance = bst_balance(right_bst_node_t(*node));
    if( right_balance < 0){
      *node = bst_rotate_left(*node);
    } else if (right_balance > 0){
      *node = bst_rotate_rightleft(*node);
    }
  }
}

int bst_balance(bst_node_t * node) {
  return (left_bst_node_t(node) == NULL ? 0 : height_bst_node_t(left_bst_node_t(node))) - 
    (right_bst_node_t(node) == NULL ? 0 : height_bst_node_t(right_bst_node_t(node)));
}

bst_node_t * bst_rotate_left(bst_node_t * node) {
  bst_node_t *b = right_bst_node_t(node);
  x_right_bst_node_t(node) = left_bst_node_t(b);
  x_left_bst_node_t(b) = node;
  
  BST_SET_HEIGHT(node);
  BST_SET_HEIGHT(b);
  return b;
}

bst_node_t * bst_rotate_right(bst_node_t * node) {
  bst_node_t *b = left_bst_node_t(node);
  x_left_bst_node_t(node) = right_bst_node_t(b);
  x_right_bst_node_t(b) = node;
  
  BST_SET_HEIGHT(node);
  BST_SET_HEIGHT(b);
  return b;
}

bst_node_t * bst_rotate_leftright(bst_node_t * node) {
  assert(node != NULL);
  bst_node_t *b = bst_rotate_left(left_bst_node_t(node));
  if(b == NULL) {
    return NULL;
  }
  x_left_bst_node_t(node) = b;
  return bst_rotate_right(node);
}

bst_node_t * bst_rotate_rightleft(bst_node_t * node) {
  assert(node != NULL);
  bst_node_t *b = bst_rotate_right(right_bst_node_t(node));
  if(b == NULL) {
    return NULL;
  }
  x_right_bst_node_t(node) = b;
  return bst_rotate_left(node);
}

void bst_traverse(bst_node_t * node, traverse_func func, void * arg) {
  if(node == NULL){
    return;
  }
  bst_traverse(left_bst_node_t(node), func, arg);
  (func)(node, arg);
  bst_traverse(right_bst_node_t(node), func, arg);
}

void bst_node_free(bst_node_t * node) {
  if (node != NULL){
    bst_node_free(left_bst_node_t(node));
    bst_node_free(right_bst_node_t(node));
    free(node);
    node = NULL;
  }
}
void bst_free(bst_t * tree) {
  bst_node_free(tree->root);
  free(tree);
  tree = NULL;
}
