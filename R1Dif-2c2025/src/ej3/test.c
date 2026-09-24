#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#define WITH_ABI_MESSAGE
#include "../ejs.h"
#include "../utils.h"

TEST(test_ej3_empty_itinerary) {
  itinerary_t *itinerary = createItinerary();
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  backpack_t *backpack = createBackpack(255);

  backpack_t *result = TEST_CALL_S(prepareBackpack, itinerary, getItemWeight);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals_unordered(backpack, result));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (result) free_backpack(result);
}

TEST(test_ej3_itinerary_single_destination_empty_requirements) {
  itinerary_t *itinerary = createItinerary();
  itineraryAddDestination(itinerary, createDestination("Cerro Campanario"));
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  backpack_t *backpack = createBackpack(255);

  backpack_t *result = TEST_CALL_S(prepareBackpack, itinerary, getItemWeight);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals_unordered(backpack, result));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (result) free_backpack(result);
}

TEST(test_ej3_itinerary_single_destination_single_requirement) {
  itinerary_t *itinerary = createItinerary();
  itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  backpack_t *backpack = createBackpack(255);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, getItemWeight(ITEM_KIND_SLEEPING_BAG));

  backpack_t *result = TEST_CALL_S(prepareBackpack, itinerary, getItemWeight);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals_unordered(backpack, result));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (result) free_backpack(result);
}

TEST(test_ej3_itinerary_single_destination_multiple_requirements) {
  itinerary_t *itinerary = createItinerary();
  destination_t *destination = itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  destinationAddRequirement(destination, ITEM_KIND_TENT);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  backpack_t *backpack = createBackpack(255);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, getItemWeight(ITEM_KIND_SLEEPING_BAG));
  backpackAddItemEx(backpack, ITEM_KIND_TENT, getItemWeight(ITEM_KIND_TENT));

  backpack_t *result = TEST_CALL_S(prepareBackpack, itinerary, getItemWeight);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals_unordered(backpack, result));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (result) free_backpack(result);
}

TEST(test_ej3_itinerary_multiple_destination_multiple_requirements) {
  itinerary_t *itinerary = createItinerary();
  destination_t *destination = itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  destinationAddRequirement(destination, ITEM_KIND_TENT);
  destination = itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_CRAMPONS);
  destinationAddRequirement(destination, ITEM_KIND_ICE_AXE);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  backpack_t *backpack = createBackpack(255);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, getItemWeight(ITEM_KIND_SLEEPING_BAG));
  backpackAddItemEx(backpack, ITEM_KIND_TENT, getItemWeight(ITEM_KIND_TENT));
  backpackAddItemEx(backpack, ITEM_KIND_CRAMPONS, getItemWeight(ITEM_KIND_CRAMPONS));
  backpackAddItemEx(backpack, ITEM_KIND_ICE_AXE, getItemWeight(ITEM_KIND_ICE_AXE));

  backpack_t *result = TEST_CALL_S(prepareBackpack, itinerary, getItemWeight);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals_unordered(backpack, result));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (result) free_backpack(result);
}

TEST(test_ej3_itinerary_multiple_destination_overlapped_requirements) {
  itinerary_t *itinerary = createItinerary();
  destination_t *destination = itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  destinationAddRequirement(destination, ITEM_KIND_TENT);
  destination = itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_SLEEPING_BAG);
  destinationAddRequirement(destination, ITEM_KIND_CRAMPONS);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  backpack_t *backpack = createBackpack(255);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, getItemWeight(ITEM_KIND_SLEEPING_BAG));
  backpackAddItemEx(backpack, ITEM_KIND_TENT, getItemWeight(ITEM_KIND_TENT));
  backpackAddItemEx(backpack, ITEM_KIND_CRAMPONS, getItemWeight(ITEM_KIND_CRAMPONS));

  backpack_t *result = TEST_CALL_S(prepareBackpack, itinerary, getItemWeight);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals_unordered(backpack, result));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (result) free_backpack(result);
}

int main(int argc, char *argv[]) {
  printf("Corriendo los tests del ejercicio 3...\n");

  test_ej3_empty_itinerary();
  test_ej3_itinerary_single_destination_empty_requirements();
  test_ej3_itinerary_single_destination_single_requirement();
  test_ej3_itinerary_single_destination_multiple_requirements();
  test_ej3_itinerary_multiple_destination_multiple_requirements();
  test_ej3_itinerary_multiple_destination_overlapped_requirements();

  tests_end("Ejercicio 3");
}
