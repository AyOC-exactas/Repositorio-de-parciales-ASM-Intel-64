#include "ejs_aux.h"

bool backpackContainsItem(backpack_t *backpack, item_kind_t kind) {
  for (uint32_t i = 0; i < backpack->item_count; ++i) {
    if (backpack->items[i].kind == kind) {
      return true;
    }
  }

  return false;
}
