#include "src/lib.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  uNode_t *node = node_init(0, 0, 0, 0, NULL);
  uNode_t *node1 = node_init(1, 1, 0, 0, node_copy(node));
  uNode_t *node2 = node_init(2, 2, 0, 0, node_copy(node1));
  uNode_t *node3 = node_init(3, 3, 0, 0, node_copy(node2));
  uNode_t *node4 = node_init(4, 4, 0, 0, node_copy(node3));


  uArray_t *open = NULL;
  array_push(&open, node);
  array_push(&open, node1);
  array_push(&open, node2);
  array_push(&open, node3);
  array_push(&open, node4);

  // if (array_exist(open, node4)) node4 = array_remove(&open, node4);
  // if (array_exist(open, node)) node = array_remove(&open, node);
  // if (array_exist(open, node1)) node1 = array_remove(&open, node1);
  // if (array_exist(open, node2)) node2 = array_remove(&open, node2);
  // if (array_exist(open, node3)) node3 = array_remove(&open, node3);
  
  if (open == NULL) {
    printf("ES NULL\n");
  }

  // node_print(node);
  // node_print(node1);
  // node_print(node2);
  // node_print(node3);
  // node_print(node4);
  
  // node_clean(node);
  // node_clean(node1);
  // node_clean(node2);
  // node_clean(node3);
  // node_clean(node4);
  
  array_clean(&open);

  // node_clean(node);
  // node_clean(node1);
  // node_clean(node2);
  // node_clean(node3);
  // node_clean(node4);

  return 0;
}