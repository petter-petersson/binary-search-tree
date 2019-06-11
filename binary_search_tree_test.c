#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "test.h"
#include "binary_search_tree.h"


int test_add_to_tree(test_context_t *context){

  return 0;
}


int main(){
  test_context_t context;
  test_context_init(&context);

  test_ctx(test_add_to_tree, "test_add_to_tree", &context);

  test_context_show_result(&context);
}
