#ifndef UTILS_H
#define UTILS_H

#include "../test_utils/test-utils.h"
#include "ejs.h"

backpack_t *createBackpack(uint8_t max_weight);
item_t *createItem(item_kind_t kind, uint8_t weight);
destination_t *createDestination(const char *name);
event_t *createEvent(destination_t *destination);
itinerary_t *createItinerary(void);
uint8_t getItemWeight(item_kind_t kind);

void backpackAddItem(backpack_t *backpack, item_t *item);
void backpackAddItemEx(backpack_t *backpack, item_kind_t kind, uint8_t weight);
void destinationAddRequirement(destination_t *destination, item_kind_t kind);
void itineraryAddDestination(itinerary_t *itinerary, destination_t *destination);
destination_t *itineraryAddDestinationEx(itinerary_t *itinerary, const char *name, item_kind_t kind);

item_t *item_clone(item_t *item);
backpack_t *backpack_clone(backpack_t *backpack);
destination_t *destination_clone(destination_t *destination);
event_t *event_clone(event_t *event);
itinerary_t *itinerary_clone(itinerary_t *itinerary);

bool item_equals(item_t *a, item_t *b);
bool backpack_equals(backpack_t *a, backpack_t *b);
bool backpack_equals_unordered(backpack_t *a, backpack_t *b);
bool destination_equals(destination_t *a, destination_t *b);
bool event_equals(event_t *a, event_t *b);
bool itinerary_equals(itinerary_t *a, itinerary_t *b);

void free_backpack(backpack_t *backpack);
void free_destination(destination_t *destination);
void free_event(event_t *event);
void free_itinerary(itinerary_t *itinerary);

#endif
