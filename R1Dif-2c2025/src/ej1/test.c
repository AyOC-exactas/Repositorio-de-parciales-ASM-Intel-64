#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define WITH_ABI_MESSAGE
#include "../ejs.h"
#include "../utils.h"

TEST(test_ej1_add_small_item_to_empty_backpack) {
  backpack_t *backpack = createBackpack(5);
  backpack_t *backpack_clon = backpack_clone(backpack);
  item_t *small_item = createItem(ITEM_KIND_SLEEPING_BAG, 1);
  item_t *small_item_clon = item_clone(small_item);

  bool result = TEST_CALL_B(canItemFitInBackpack, backpack, small_item);

  TEST_ASSERT_EQUALS(bool, true, result);
  TEST_ASSERT_EQUALS(bool, true, item_equals(small_item, small_item_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (small_item) free(small_item);
  if (small_item_clon) free(small_item_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej1_add_big_item_to_empty_backpack) {
  backpack_t *backpack = createBackpack(5);
  backpack_t *backpack_clon = backpack_clone(backpack);
  item_t *big_item = createItem(ITEM_KIND_SLEEPING_BAG, 10);
  item_t *big_item_clon = item_clone(big_item);

  bool result = TEST_CALL_B(canItemFitInBackpack, backpack, big_item);

  TEST_ASSERT_EQUALS(bool, false, result);
  TEST_ASSERT_EQUALS(bool, true, item_equals(big_item, big_item_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (big_item) free(big_item);
  if (big_item_clon) free(big_item_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej1_add_medium_item_to_empty_backpack) {
  backpack_t *backpack = createBackpack(5);
  backpack_t *backpack_clon = backpack_clone(backpack);
  item_t *medium_item = createItem(ITEM_KIND_SLEEPING_BAG, 5);
  item_t *medium_item_clon = item_clone(medium_item);

  bool result = TEST_CALL_B(canItemFitInBackpack, backpack, medium_item);

  TEST_ASSERT_EQUALS(bool, true, result);
  TEST_ASSERT_EQUALS(bool, true, item_equals(medium_item, medium_item_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (medium_item) free(medium_item);
  if (medium_item_clon) free(medium_item_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej1_add_small_item_to_backpack) {
  backpack_t *backpack = createBackpack(5);
  item_t *small_item = createItem(ITEM_KIND_SLEEPING_BAG, 1);
  item_t *small_item_clon = item_clone(small_item);

  for (uint32_t i = 0; i < 4; ++i) {
    backpackAddItem(backpack, small_item);
  }

  backpack_t *backpack_clon = backpack_clone(backpack);

  bool result = TEST_CALL_B(canItemFitInBackpack, backpack, small_item);

  TEST_ASSERT_EQUALS(bool, true, result);
  TEST_ASSERT_EQUALS(bool, true, item_equals(small_item, small_item_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (small_item) free(small_item);
  if (small_item_clon) free(small_item_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej1_add_small_item_to_full_backpack) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 5);
  backpack_t *backpack_clon = backpack_clone(backpack);
  item_t *small_item = createItem(ITEM_KIND_SLEEPING_BAG, 1);
  item_t *small_item_clon = item_clone(small_item);

  bool result = TEST_CALL_B(canItemFitInBackpack, backpack, small_item);

  TEST_ASSERT_EQUALS(bool, false, result);
  TEST_ASSERT_EQUALS(bool, true, item_equals(small_item, small_item_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (small_item) free(small_item);
  if (small_item_clon) free(small_item_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

int main(int argc, char *argv[]) {
  printf("Corriendo los tests del ejercicio 1...\n");

  test_ej1_add_small_item_to_empty_backpack();
  test_ej1_add_big_item_to_empty_backpack();
  test_ej1_add_medium_item_to_empty_backpack();
  test_ej1_add_small_item_to_backpack();
  test_ej1_add_small_item_to_full_backpack();

  tests_end("Ejercicio 1");
}
