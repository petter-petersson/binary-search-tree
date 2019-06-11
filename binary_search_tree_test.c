#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#include "test.h"
#include "binary_search_tree.h"

int test_rotate_rightleft(test_context_t * ctx){

  bst_node_t mnodes[] = {
    {.key = 1},
    {.key = 3},
    {.key = 2}
  };
  bst_node_t * nodes = mnodes;

  for(int i = 0; i < 3; i++) {
    nodes[i].left = NULL;
    nodes[i].right = NULL;
  }

  nodes[0].right = &nodes[1];
  nodes[1].left = &nodes[2];
  /*
   *         1
   *          \
   *           3
   *          /
   *         2
   */ 
  check(nodes->key == 1, ctx);
  check(nodes->right->key == 3, ctx);
  check(nodes->right->left->key == 2, ctx);

  bst_node_t * result = bst_rotate_rightleft(nodes);
  assert(result != NULL);

  check(result->key == 2, ctx);
  check(result->left->key == 1, ctx);
  check(result->right->key == 3, ctx);
  return 0;
}
int test_rotate_leftright(test_context_t * ctx){

  bst_node_t mnodes[] = {
    {.key = 3},
    {.key = 1},
    {.key = 2}
  };
  bst_node_t * nodes = mnodes;

  for(int i = 0; i < 3; i++) {
    nodes[i].left = NULL;
    nodes[i].right = NULL;
  }

  nodes[0].left = &nodes[1];
  nodes[1].right = &nodes[2];
  /*
   *         3
   *        /
   *       1
   *        \
   *         2
   */ 
  check(nodes->key == 3, ctx);
  check(nodes->left->key == 1, ctx);
  check(nodes->left->right->key == 2, ctx);

  bst_node_t * result = bst_rotate_leftright(nodes);
  assert(result != NULL);

  check(result->key == 2, ctx);
  check(result->left->key == 1, ctx);
  check(result->right->key == 3, ctx);
  return 0;
}

int test_rotate_right(test_context_t * ctx){
  bst_node_t mem[5];
  bst_node_t * nodes = mem;

  for(int i = 0; i < 5; i++) {
    (nodes + i)->key = 4 - i;
    (nodes + i)->left = NULL;
    (nodes + i)->right = NULL;
  }

  nodes->left = (nodes + 1);
  (nodes + 1)->left = (nodes + 2);
  (nodes + 2)->right = (nodes + 3);
  (nodes + 2)->left = (nodes + 4);
  
  /*
   *         4
   *        /
   *       3
   *      /
   *     2
   *    / \
   *   0   1
   */ 
  check(nodes->key == 4, ctx);
  check(nodes->left->key == 3, ctx);
  check(nodes->left->left->key == 2, ctx);
  check(nodes->left->left->right->key == 1, ctx);
  check(nodes->left->left->left->key == 0, ctx);

  nodes->left = bst_rotate_right(nodes + 1);

  /*
   *         4
   *        /
   *       2
   *      / \
   *     0   3
   *        /
   *       1
   */ 
  check(nodes->key == 4, ctx);
  check(nodes->left->key == 2, ctx);
  check(nodes->left->right->key == 3, ctx);
  check(nodes->left->right->left->key == 1, ctx);
  check(nodes->left->left->key == 0, ctx);

  return 0;
}

int test_rotate_left(test_context_t * ctx){
  bst_node_t mem[5];
  bst_node_t * nodes = mem;

  for(int i = 0; i < 5; i++) {
    (nodes + i)->key = i;
    (nodes + i)->left = NULL;
    (nodes + i)->right = NULL;
  }

  nodes->right = (nodes + 1);
  (nodes + 1)->right = (nodes + 2);
  (nodes + 2)->left = (nodes + 3);
  (nodes + 2)->right = (nodes + 4);

  /*
   *   0
   *    \
   *     1
   *      \
   *       2
   *      / \
   *     3   4
   */ 
  check(nodes->key == 0, ctx);
  check(nodes->right->key == 1, ctx);
  check(nodes->right->right->key == 2, ctx);
  check(nodes->right->right->left->key == 3, ctx);
  check(nodes->right->right->right->key == 4, ctx);
  
  nodes->right = bst_rotate_left(nodes + 1);

  /*
   *   0
   *    \
   *     2
   *    / \
   *   1   4
   *    \
   *     3
   */ 
  check(nodes->key == 0, ctx);
  check(nodes->right->key == 2, ctx);
  check(nodes->right->left->key == 1, ctx);
  check(nodes->right->left->right->key == 3, ctx);
  check(nodes->right->right->key == 4, ctx);

  return 0;
}

typedef struct print_node_args_s {
  int count;
  int expected_keys[9];
} print_node_args_t;
extern void print_node(bst_node_t * node, void * arg){

  print_node_args_t * args = (print_node_args_t *) arg;

  printf("key: %d value: %s height: %d\n", 
      node->key, 
      (char *) node->value,
      node->height);
  int len = sizeof(args->expected_keys)/sizeof(int);
  assert(args->count < len);
  args->expected_keys[args->count] = node->key;
  (args->count)++;
}

int test_add_to_tree(test_context_t * ctx){

  print_node_args_t test_args;
  test_args.count = 0; //?

  bst_t * tree = bst_init();
  check(tree != NULL, ctx);

  struct test_node {
    int key;
    char * value;
  };

  const struct test_node data[] = { 
    { .key = 1, .value = "test-1"},
    { .key = 10, .value = "test-10"},
    { .key = 5, .value = "test-5"},
    { .key = 17, .value = "test-17"},
    { .key = 27, .value = "test-27"},
    { .key = 37, .value = "test-37"},
    { .key = 47, .value = "test-47"},
    { .key = 57, .value = "test-57"},
    { .key = 67, .value = "test-67"}
  };

  size_t n = sizeof(data) / sizeof(struct test_node);
  assert(n == 9);

  for(int i=0; i < n; i++) {
    bst_add(tree, data[i].key, (void *) data[i].value);
  }

  bst_traverse(tree->root, print_node, &test_args);
  
  check(test_args.expected_keys[0] == 1, ctx);
  check(test_args.expected_keys[1] == 5, ctx);
  check(test_args.expected_keys[2] == 10, ctx);
  check(test_args.expected_keys[3] == 17, ctx);

  check(test_args.expected_keys[7] == 57, ctx);
  check(test_args.expected_keys[8] == 67, ctx);

  check(tree->root->key == 27, ctx);
  check(tree->root->right->key == 47, ctx);
  check(tree->root->right->left->key == 37, ctx);
  check(tree->root->right->right->key == 57, ctx);
  check(tree->root->right->right->right->key == 67, ctx);
  //
  check(tree->root->left->key == 10, ctx);
  check(tree->root->left->left->key == 1, ctx);
  check(tree->root->left->right->key == 17, ctx);
  check(tree->root->left->left->right->key == 5, ctx);
  if(tree != NULL){
    bst_free(tree);
  }
  //need to have adress of tree as arg if we want this
  //check(tree == NULL, ctx);
  return 0;
}

//tmp weak test, remove
int test_add_to_tree_reversed(test_context_t * ctx){
  print_node_args_t test_args;
  test_args.count = 0; //?

  bst_t * tree = bst_init();
  check(tree != NULL, ctx);

  struct test_node {
    int key;
    char * value;
  };

  const struct test_node data[] = { 
    { .key = 67, .value = "test-67"},
    { .key = 57, .value = "test-57"},
    { .key = 47, .value = "test-47"},
    { .key = 1, .value = "test-1"},
    { .key = 27, .value = "test-27"},
    { .key = 5, .value = "test-5"},
    { .key = 10, .value = "test-10"},
    { .key = 17, .value = "test-17"},
    { .key = 37, .value = "test-37"},
  };

  for(int i=0; i < 9; i++) {
    bst_add(tree, data[i].key, (void *) data[i].value);
  }
  bst_traverse(tree->root, print_node, &test_args);

  if(tree != NULL){
    bst_free(tree);
  }
  return 0;
}

typedef struct print_many_args_s {
  int count;
  int max_height;
  int min_key;
  int max_key;
} print_many_args_t;

extern void init_print_many_args_t(print_many_args_t * args) {
  args->max_height = 0;
  args->min_key = INT_MAX;
  args->max_key = 0;
  args->count = 0;
}

extern void print_node_for_many(bst_node_t * node, void * arg){
  print_many_args_t * args = (print_many_args_t *) arg;

  if(node->height > args->max_height){
    args->max_height = node->height;
  }
  if(node->key < args->min_key){
    args->min_key = node->key;
  }
  if(node->key > args->max_key){
    args->max_key = node->key;
  }
  (args->count)++;
}
int test_add_many_to_tree(test_context_t * ctx){

  print_many_args_t test_args;
  init_print_many_args_t(&test_args);
  assert(test_args.min_key == INT_MAX);

  bst_t * tree = bst_init();
  check(tree != NULL, ctx);

  for(int i=0; i < 1000000; i++) {
    bst_add(tree, i, NULL);
  }
  bst_traverse(tree->root, print_node_for_many, &test_args);

  printf("max height: %d\n", test_args.max_height);
  check(test_args.max_height < 21, ctx);

  printf("count: %d\n", test_args.count);
  check(test_args.count == 1000000, ctx);
  if(tree != NULL){
    bst_free(tree);
  }
  return 0;
}

int test_add_many_to_tree_reversed(test_context_t * ctx){
  print_many_args_t test_args;
  init_print_many_args_t(&test_args);
  assert(test_args.min_key == INT_MAX);

  bst_t * tree = bst_init();
  check(tree != NULL, ctx);

  for(int i=1000000; i > 0; i--) {
    bst_add(tree, i, NULL);
  }
  bst_traverse(tree->root, print_node_for_many, &test_args);

  printf("max height: %d\n", test_args.max_height);
  check(test_args.max_height < 21, ctx);
  printf("count: %d\n", test_args.count);
  check(test_args.count == 1000000, ctx);
  if(tree != NULL){
    bst_free(tree);
  }
  return 0;
}

int test_add_many_random_to_tree(test_context_t * ctx){
  print_many_args_t test_args;
  init_print_many_args_t(&test_args);
  assert(test_args.min_key == INT_MAX);

  bst_t * tree = bst_init();
  check(tree != NULL, ctx);

  srand(time(NULL));
  int r;

  for(int i=0; i < 1000000; i++) {
    r = rand();// % 10000;
    bst_add(tree, r, NULL);
  }
  printf("done adding\n");
  bst_traverse(tree->root, print_node_for_many, &test_args);

  printf("\nmax height: %d\n", test_args.max_height);
  printf("max: %d\n", test_args.max_key);
  printf("min: %d\n", test_args.min_key);

  //usually the result is 23 but 24 has happened
  check(test_args.max_height <= 25, ctx);
  //NOTE: this would fail if rand produces a value more than once (which it seems not to
  //if we don't loop +INT_MAX times)
  printf("count: %d\n", test_args.count);
  check(test_args.count == 1000000, ctx);
  if(tree != NULL){
    bst_free(tree);
  }
  return 0;
}
int main(){
  test_context_t context;
  test_context_init(&context);

  test_ctx(test_add_to_tree, "test_add_to_tree", &context);
  test_ctx(test_add_to_tree_reversed, "test_add_to_tree_reversed", &context);
  test_ctx(test_rotate_left, "test_rotate_left", &context);
  test_ctx(test_rotate_right, "test_rotate_right", &context);
  test_ctx(test_rotate_leftright, "test_rotate_leftright", &context);
  test_ctx(test_rotate_rightleft, "test_rotate_rightleft", &context);

  test_ctx(test_add_many_to_tree, "test_add_many_to_tree", &context);
  test_ctx(test_add_many_to_tree_reversed, "test_add_many_to_tree_reversed", &context);
  test_ctx(test_add_many_random_to_tree, "test_add_many_random_to_tree", &context);
  test_context_show_result(&context);
}
