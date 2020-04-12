#ifndef LIB_H
#define LIB_H

#include <stdint.h>

/*---------------------------------------------------------------*
 * Enum bool
*----------------------------------------------------------------*/
typedef enum bool {
  false = 0,
  true
} bool;


/*---------------------------------------------------------------*
 * Enum Tile
*----------------------------------------------------------------*/
typedef enum Tile {
  FLOOR   = 0x2E,
  WALL    = 0x23,
  BEGIN   = 0x40,
  END     = 0x24,
  PATH    = 0x2B,
} Tile;

/*---------------------------------------------------------------*
 * Struct uNode_t
*----------------------------------------------------------------*/
typedef struct uNode_t {
  uint16_t x;
  uint16_t y;
  uint16_t g;
  uint16_t h;

  struct uNode_t *prev;
} uNode_t;

uNode_t *node_init(uint16_t x, uint16_t y, uint16_t g, uint16_t h, uNode_t *prev);

uNode_t *node_copy(const uNode_t *const node);

void node_print(const uNode_t *node);

void node_clean(uNode_t *node);

/*---------------------------------------------------------------*
 * Struct uArray_t
*----------------------------------------------------------------*/
typedef struct uArray_t {
  uNode_t *node;
  struct uArray_t *next;
} uArray_t;

void array_push(uArray_t **array, uNode_t *node);

bool array_exist(const uArray_t *array, const uNode_t *node);

uNode_t *array_remove(uArray_t **array, const uNode_t * const node);

void array_clean(uArray_t **array);

uNode_t *array_remove_small(uArray_t **array);

void array_set_node(uArray_t *array, uNode_t *node);

#endif //LIB_H