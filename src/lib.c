#include "lib.h"
#include <stdlib.h>
#include <stdio.h>

/*---------------------------------------------------------------*
 * Static methods
*----------------------------------------------------------------*/
static bool cmp_node(const uNode_t *node, const uNode_t *node1);

static uint16_t get_f(const uArray_t *array);

/*---------------------------------------------------------------*
 * Struct uNode_t
*----------------------------------------------------------------*/
uNode_t *node_init(uint16_t x, uint16_t y, uint16_t g, uint16_t h, uNode_t *prev) {
  uNode_t *node = (uNode_t *)malloc(sizeof(uNode_t));
  node->x = x;
  node->y = y;
  node->g = g;
  node->h = h;
  node->prev = prev;

  return node;
}

uNode_t *node_copy(const uNode_t *const node) {
  if (node == NULL) return NULL;

  uNode_t *new_node = (uNode_t *)malloc(sizeof(uNode_t));
  new_node->x = node->x;
  new_node->y = node->y;
  new_node->h = node->h;
  new_node->g = node->g;
  new_node->prev = node_copy(node->prev);

  return new_node;
}

void node_print(const uNode_t *node) {
  const uNode_t *aux = node;
  while (aux != NULL) {
    printf("element: (%d, %d)\n", aux->x, aux->y);
    aux = aux->prev;
  }
  printf("\n");
}

void node_clean(uNode_t *node) {
  uNode_t *aux = NULL;
  while (node != NULL) {
    aux = node;
    free(aux);
    aux = NULL;
    node = node->prev;
  }
}

/*---------------------------------------------------------------*
 * Struct uArray_t
*----------------------------------------------------------------*/
void array_push(uArray_t **array, uNode_t *node) {
  if ((*array) == NULL) {
    (*array) = (uArray_t *)malloc(sizeof(uArray_t));
    (*array)->node = node;
    (*array)->next = NULL;
  } else {
    uArray_t *aux = (*array);
    while (aux->next != NULL) aux = aux->next;

    aux->next = (uArray_t *)malloc(sizeof(uArray_t));
    aux->next->node = node;
    aux->next->next = NULL;
  }
}

bool array_exist(const uArray_t *array, const uNode_t *node) {
  while (array != NULL) {
    if (cmp_node(array->node, node)) return true;
    array = array->next;
  }

  return false;
}

uNode_t *array_remove(uArray_t **array, const uNode_t * const node) {
  if ((*array) == NULL) return NULL;

  uArray_t *aux_array = (*array);
  if (cmp_node((*array)->node, node)) {
    (*array) = (*array)->next;
    aux_array->next = NULL;
    uNode_t *res_node = aux_array->node;
    free(aux_array);
    return res_node;
  } else {
    while (aux_array->next != NULL) {
      if (cmp_node(aux_array->next->node, node)) {
        uArray_t *node_array = aux_array->next;
        aux_array->next = node_array->next;
        node_array->next = NULL;
        uNode_t *res_node = node_array->node;
        free(node_array);
        return res_node;
      }
      aux_array = aux_array->next;
    }
  }
  return NULL;
}

void array_clean(uArray_t **array) {
  uArray_t *aux = NULL;
  while ((*array) != NULL) {
    aux = (*array);
    (*array) = (*array)->next;
    node_clean(aux->node);
    free(aux);
    aux = NULL;
  }
}

uNode_t *array_remove_small(uArray_t **array) {
  uint16_t f = get_f((*array));
  uArray_t *aux = (*array);
  if ((aux->node->g + aux->node->h) == f) {
    (*array) = (*array)->next;
    aux->next = NULL;
    uNode_t *res = aux->node;
    free(aux);
    return res;
  } else {
    while (aux->next != NULL) {
      if ((aux->next->node->g + aux->next->node->h) == f) {
        uArray_t *del_array = aux->next;
        aux->next = del_array->next;
        del_array->next = NULL;
        uNode_t *res = del_array->node;
        free(del_array);
        return res;
      }
      aux = aux->next;
    }
  }
  return NULL;
}

void array_set_node(uArray_t *array, uNode_t *node) {
    while (array != NULL) {
      if (cmp_node(array->node, node) && ((node->g + node->h) < (array->node->g + array->node->h))) {
        array->node->g = node->g;
        array->node->h = node->h;
        return;
      } 
      array = array->next;
    }
}


/*---------------------------------------------------------------*
 * Implement static methods
*----------------------------------------------------------------*/
static bool cmp_node(const uNode_t *node, const uNode_t *node1) {
  return (node->x == node1->x && node->y == node1->y);
}

static uint16_t get_f(const uArray_t *array) {
  uint16_t f = 255;

  while (array != NULL) {
    if (f > (array->node->g + array->node->h)) f = (array->node->g + array->node->h);
    array = array->next;
  }
  return f;
}