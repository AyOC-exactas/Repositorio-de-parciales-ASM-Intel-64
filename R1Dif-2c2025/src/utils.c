
#include "utils.h"

#include <stdint.h>
#include <string.h>

#include "ejs_aux.h"

backpack_t *createBackpack(uint8_t max_weight) {
  backpack_t *backpack = (backpack_t *)malloc(sizeof(backpack_t));
  backpack->items = NULL;
  backpack->max_weight = max_weight;
  backpack->item_count = 0;
  return backpack;
}

item_t *createItem(item_kind_t kind, uint8_t weight) {
  item_t *item = (item_t *)malloc(sizeof(item_t));
  item->kind = kind;
  item->weight = weight;
  return item;
}

destination_t *createDestination(const char *name) {
  destination_t *destination = (destination_t *)malloc(sizeof(destination_t));
  destination->requirements = NULL;
  destination->requirements_size = 0;
  size_t size = strlen(name);
  memset(destination->name, 0, 25);
  memcpy(destination->name, name, size > 25 ? 25 : size);
  return destination;
}

event_t *createEvent(destination_t *destination) {
  event_t *event = (event_t *)malloc(sizeof(event_t));
  event->destination = destination;
  event->next = NULL;
  return event;
}

itinerary_t *createItinerary(void) {
  itinerary_t *itinerary = (itinerary_t *)malloc(sizeof(itinerary_t));
  itinerary->first = NULL;
  return itinerary;
}

uint8_t getItemWeight(item_kind_t kind) {
  switch (kind) {
    case ITEM_KIND_TENT:
      return 15;
    case ITEM_KIND_SLEEPING_BAG:
      return 1;
    case ITEM_KIND_ROPE:
      return 3;
    case ITEM_KIND_CRAMPONS:
      return 5;
    case ITEM_KIND_HARNESS:
      return 2;
    case ITEM_KIND_OXYGEN:
      return 10;
    case ITEM_KIND_ICE_AXE:
      return 5;
    default:
      return 255;
  }
}

void backpackAddItem(backpack_t *backpack, item_t *item) {
  uint32_t index = backpack->item_count;
  backpack->item_count++;
  backpack->items = (item_t *)realloc(backpack->items, sizeof(item_t) * backpack->item_count);
  backpack->items[index] = *item;
}

void backpackAddItemEx(backpack_t *backpack, item_kind_t kind, uint8_t weight) {
  item_t *item = createItem(kind, weight);
  backpackAddItem(backpack, item);
  if (item) free(item);
}

void destinationAddRequirement(destination_t *destination, item_kind_t kind) {
  uint32_t index = destination->requirements_size;
  destination->requirements_size++;
  destination->requirements = (item_kind_t *)realloc(destination->requirements, sizeof(item_kind_t) * destination->requirements_size);
  destination->requirements[index] = kind;
}

void itineraryAddDestination(itinerary_t *itinerary, destination_t *destination) {
  if (itinerary->first == NULL) {
    itinerary->first = createEvent(destination);
  } else {
    event_t *event = itinerary->first;
    while (event->next != NULL) event = event->next;
    event->next = createEvent(destination);
  }
}

destination_t *itineraryAddDestinationEx(itinerary_t *itinerary, const char *name, item_kind_t kind) {
  destination_t *dest = createDestination(name);
  destinationAddRequirement(dest, kind);
  itineraryAddDestination(itinerary, dest);
  return dest;
}

item_t *item_clone(item_t *item) {
  return createItem(item->kind, item->weight);
}

backpack_t *backpack_clone(backpack_t *backpack) {
  backpack_t *clone = createBackpack(backpack->max_weight);
  clone->item_count = backpack->item_count;
  size_t size = sizeof(item_t) * backpack->item_count;
  clone->items = (item_t *)malloc(size);
  memcpy(clone->items, backpack->items, size);
  return clone;
}

destination_t *destination_clone(destination_t *destination) {
  destination_t *clone = createDestination(destination->name);
  clone->requirements_size = destination->requirements_size;
  size_t size = sizeof(item_kind_t) * destination->requirements_size;
  clone->requirements = (item_kind_t *)malloc(size);
  memcpy(clone->requirements, destination->requirements, size);
  return clone;
}

event_t *event_clone(event_t *event) {
  if (event == NULL) return NULL;
  destination_t *destination_clon = destination_clone(event->destination);
  event_t *clone = createEvent(destination_clon);
  return clone;
}

itinerary_t *itinerary_clone(itinerary_t *itinerary) {
  itinerary_t *clone = createItinerary();
  clone->first = event_clone(itinerary->first);
  event_t *last = clone->first;
  event_t *event = itinerary->first;

  while (event != NULL) {
    last->next = event_clone(event->next);
    last = last->next;
    event = event->next;
  }

  return clone;
}

bool item_equals(item_t *a, item_t *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;
  if (a->kind != b->kind) return false;
  if (a->weight != b->weight) return false;
  return true;
}

bool backpack_equals(backpack_t *a, backpack_t *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;
  if (a->max_weight != b->max_weight) return false;
  if (a->item_count != b->item_count) return false;

  for (uint32_t i = 0; i < a->item_count; ++i) {
    if (!item_equals(&a->items[i], &b->items[i])) return false;
  }

  return true;
}

bool backpack_equals_unordered(backpack_t *a, backpack_t *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;
  if (a->max_weight != b->max_weight) return false;
  if (a->item_count != b->item_count) return false;

  for (uint32_t i = 0; i < a->item_count; ++i) {
    item_t item = a->items[i];
    if (!backpackContainsItem(b, item.kind)) return false;
    if (item.weight != getItemWeight(item.kind)) return false;
  }

  return true;
}

bool destination_equals(destination_t *a, destination_t *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;
  if (a->requirements_size != b->requirements_size) return false;
  if (memcmp(a->name, b->name, 25) != 0) return false;

  for (uint32_t i = 0; i < a->requirements_size; ++i) {
    if (a->requirements[i] != b->requirements[i]) return false;
  }

  return true;
}

bool event_equals(event_t *a, event_t *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;
  if (!destination_equals(a->destination, b->destination)) return false;
  return true;
}

bool itinerary_equals(itinerary_t *a, itinerary_t *b) {
  if (a == b) return true;
  if (a == NULL || b == NULL) return false;
  event_t *a_event = a->first;
  event_t *b_event = b->first;

  while (a_event != NULL) {
    if (!event_equals(a_event, b_event)) return false;
    a_event = a_event->next;
    b_event = b_event->next;
  }

  if (b_event != NULL) return false;
  return true;
}

void free_backpack(backpack_t *backpack) {
  free(backpack->items);
  free(backpack);
}

void free_destination(destination_t *destination) {
  free(destination->requirements);
  free(destination);
}

void free_event(event_t *event) {
  free_destination(event->destination);
  free(event);
}

void free_itinerary(itinerary_t *itinerary) {
  event_t *event = itinerary->first;

  while (event != NULL) {
    event_t *next = event->next;
    free_event(event);
    event = next;
  }

  free(itinerary);
}
