#include "src/map.h"

int main(int argc, char *argv[]) {

  uMap_t map = map_init(7, 5);
  map_state_0(&map);
  map_print(&map);
  uNode_t *node = map_path(&map);
  map_paint_path(&map, node);
  map_print(&map);
  node_clean(node);
  map_clean(&map);

  return 0;
}