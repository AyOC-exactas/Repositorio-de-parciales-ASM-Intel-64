#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WITH_ABI_MESSAGE
#include "../ejs.h"
#include "../utils.h"

TEST(test_ej2_empty_itinerary) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_single_destination_empty_requirements) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itineraryAddDestination(itinerary, createDestination("Cerro Campanario"));
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_single_destination_empty_backpack) {
  backpack_t *backpack = createBackpack(5);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_single_destination) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_CRAMPONS);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_multiple_valid_destinations) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  itineraryAddDestinationEx(itinerary, "Cerro Lopez", ITEM_KIND_SLEEPING_BAG);
  itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_SLEEPING_BAG);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_multiple_destinations) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  itineraryAddDestinationEx(itinerary, "Cerro Lopez", ITEM_KIND_SLEEPING_BAG);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_CRAMPONS);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_single_invalid_destination) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_SLEEPING_BAG);
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_CRAMPONS);
  itineraryAddDestinationEx(itinerary, "Cerro Lopez", ITEM_KIND_SLEEPING_BAG);
  itineraryAddDestinationEx(itinerary_clon, "Cerro Lopez", ITEM_KIND_SLEEPING_BAG);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

TEST(test_ej2_itinerary_multiple_invalid_destinations) {
  backpack_t *backpack = createBackpack(5);
  backpackAddItemEx(backpack, ITEM_KIND_SLEEPING_BAG, 1);
  backpack_t *backpack_clon = backpack_clone(backpack);
  itinerary_t *itinerary = createItinerary();
  itinerary_t *itinerary_clon = itinerary_clone(itinerary);
  itineraryAddDestinationEx(itinerary, "Cerro Catedral", ITEM_KIND_TENT);
  itineraryAddDestinationEx(itinerary, "Cerro Lopez", ITEM_KIND_TENT);
  itineraryAddDestinationEx(itinerary, "Cerro Tronador", ITEM_KIND_TENT);

  TEST_CALL_V(filterPossibleDestinations, itinerary, backpack);
  TEST_ASSERT_EQUALS(bool, true, itinerary_equals(itinerary, itinerary_clon));
  TEST_ASSERT_EQUALS(bool, true, backpack_equals(backpack, backpack_clon));

  if (itinerary) free_itinerary(itinerary);
  if (itinerary_clon) free_itinerary(itinerary_clon);
  if (backpack) free_backpack(backpack);
  if (backpack_clon) free_backpack(backpack_clon);
}

int main(int argc, char *argv[]) {
  printf("Corriendo los tests del ejercicio 2...\n");

  test_ej2_empty_itinerary();
  test_ej2_itinerary_single_destination_empty_requirements();
  test_ej2_itinerary_single_destination_empty_backpack();
  test_ej2_itinerary_single_destination();
  test_ej2_itinerary_multiple_valid_destinations();
  test_ej2_itinerary_multiple_destinations();
  test_ej2_itinerary_single_invalid_destination();
  test_ej2_itinerary_multiple_invalid_destinations();

  tests_end("Ejercicio 2");
}
