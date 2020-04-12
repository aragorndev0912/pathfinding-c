#ifndef Map_H
#define Map_H

#include <stdint.h>
#include "lib.h"

/*---------------------------------------------------------------*
 * Struct uMap_t
*----------------------------------------------------------------*/
typedef struct uMap_t {
  uint16_t *vector;
  uint16_t width;
  uint16_t height;

  uint16_t b_x;
  uint16_t b_y;
  uint16_t e_x;
  uint16_t e_y;
} uMap_t;

uMap_t map_init(uint16_t width, uint16_t height);

void map_print(const uMap_t *map);

void map_state_0(uMap_t *map);

uNode_t *map_path(uMap_t *map);

void map_clean(uMap_t *map);

void map_paint_path(uMap_t *map, const uNode_t *node);

#endif // Map_H