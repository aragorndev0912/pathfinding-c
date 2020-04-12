#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------------*
 * Static methods
*----------------------------------------------------------------*/
static uint16_t get_h(uint16_t px, uint16_t py, uint16_t ex, uint16_t ey);

static uNode_t *evaluate(const uMap_t *const map, uArray_t **open, uArray_t **close, uint16_t diff);

/*---------------------------------------------------------------*
 * Struct uMap_t
*----------------------------------------------------------------*/
uMap_t map_init(uint16_t width, uint16_t height) {
  uMap_t map = (uMap_t){.width=width, .height=height};
  map.vector = (uint16_t *)calloc(width * height, sizeof(uint16_t));
  for (uint16_t i = 0; i < (width * height); ++i) map.vector[i] = FLOOR;
  return map;
}

void map_print(const uMap_t *map) {
  if (map->vector != NULL) {
    const uint16_t size = (map->width * map->height);
    const uint16_t *vec = map->vector;
    for (uint16_t i = 0; i < size; ++i) {
      printf("%c ", (*vec));
      if (i > 0 && (i+1) % map->width == 0) printf("\n");
      ++vec;      
    }
  }
  printf("\n");
}

void map_state_0(uMap_t *map) {
  // begin
  map->b_x = 1; 
  map->b_y = 2;
  // end
  map->e_x = 5; 
  map->e_y = 2;

  map->vector[(2 * map->width) + 1] = BEGIN;
  map->vector[(2 * map->width) + 5] = END;

  map->vector[(0 * map->width) + 3] = WALL;
  // map->vector[(1 * map->width) + 3] = WALL;
  // map->vector[(2 * map->width) + 3] = WALL;
  map->vector[(3 * map->width) + 3] = WALL;
  map->vector[(4 * map->width) + 3] = WALL;
}

uNode_t *map_path(uMap_t *map) {
  uNode_t * res = NULL;

  uArray_t *open = NULL;
  uArray_t *close = NULL;

  const uint16_t h = get_h(map->b_x, map->b_y, map->e_x, map->e_y);
  uNode_t *begin = node_init(map->b_x, map->b_y, 0, h, NULL);
  array_push(&open, begin);
  res = evaluate(map, &open, &close, 10);

  array_clean(&open);
  array_clean(&close);

  return res;
}

void map_clean(uMap_t *map) {
  if (map != NULL) {
    free(map->vector);
    map->vector = NULL;
  }
}

void map_paint_path(uMap_t *map, const uNode_t *node) {
  for (; node != NULL; node = node->prev) {
    map->vector[(node->y * map->width) + node->x] = PATH;
  }
}


/*---------------------------------------------------------------*
 * Static methods
*----------------------------------------------------------------*/
static uint16_t get_h(uint16_t px, uint16_t py, uint16_t ex, uint16_t ey) {
  return abs(px - ex) + abs(py - ey);
}

static uNode_t *evaluate(const uMap_t *const map, uArray_t **open, uArray_t **close, uint16_t diff) {
  if ((*open) == NULL) return NULL;
  uNode_t *node = array_remove_small(open);
  if (node == NULL) return NULL;
  else if (node->x == map->e_x && node->y == map->e_y) return node;
  array_push(close, node);
  // top
  uNode_t *aux_node = NULL;
  if ((node->y - 1) >= 0 && (map->vector[((node->y - 1) * map->width) + node->x] == FLOOR || map->vector[((node->y - 1) * map->width) + node->x] == END)) {
    aux_node = node_init(node->x, (node->y - 1), diff, get_h(node->x, (node->y - 1), map->e_x, map->e_y), node_copy(node));
    if (array_exist((*close), aux_node)) {
      node_clean(aux_node);
    } else {
      if (array_exist((*open), aux_node)) {
        array_set_node((*open), aux_node);
        node_clean(aux_node);
      } else {
        array_push(open, aux_node);
      }
    }
  }
  // right
  if ((node->x + 1) < map->width && (map->vector[(node->y * map->width) + (node->x + 1)] == FLOOR || map->vector[(node->y * map->width) + (node->x + 1)] == END)) {
    aux_node = node_init((node->x + 1), node->y, diff, get_h((node->x + 1), node->y, map->e_x, map->e_y), node_copy(node));
    if (array_exist((*close), aux_node)) {
      node_clean(aux_node);
    } else {
      if (array_exist((*open), aux_node)) {
        array_set_node((*open), aux_node);
        node_clean(aux_node);
      } else {
        array_push(open, aux_node);
      }
    }
  }
  // down
  if ((node->y + 1) < map->height && (map->vector[((node->y + 1) * map->width) + node->x] == FLOOR || map->vector[((node->y + 1) * map->width) + node->x] == END)) {
    aux_node = node_init(node->x, (node->y + 1), diff, get_h(node->x, (node->y + 1), map->e_x, map->e_y), node_copy(node));
    if (array_exist((*close), aux_node)) {
      node_clean(aux_node);
    } else {
      if (array_exist((*open), aux_node)) {
        array_set_node((*open), aux_node);
        node_clean(aux_node);
      } else {
        array_push(open, aux_node);
      }
    }
  }
  // left
  if ((node->x - 1) >= 0 && (map->vector[(node->y * map->width) + (node->x - 1)] == FLOOR || map->vector[(node->y * map->width) + (node->x - 1)] == END)) {
    aux_node = node_init((node->x - 1), node->y, diff, get_h((node->x - 1), node->y, map->e_x, map->e_y), node_copy(node));
    if (array_exist((*close), aux_node)) {
      node_clean(aux_node);
    } else {
      if (array_exist((*open), aux_node)) {
        array_set_node((*open), aux_node);
        node_clean(aux_node);
      } else {
        array_push(open, aux_node);
      }
    }
  }
  return evaluate(map, open, close, (diff + 10));
}