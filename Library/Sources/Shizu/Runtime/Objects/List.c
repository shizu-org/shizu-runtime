/*
  Shizu
  Copyright (C) 2024 Michael Heilmann. All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#define SHIZU_RUNTIME_PRIVATE (1)
#include "Shizu/Runtime/Objects/List.private.h"

#include "Shizu/Runtime/State2.h"
#include "Shizu/Runtime/State1.h"
#include "Shizu/Runtime/Gc.h"

// memcmp, memcpy
#include <string.h>

// fprintf, stderr
#include <stdio.h>

// exit, EXIT_FAILURE
#include <stdlib.h>

// INT_MAX, SIZE_MAX
#include <limits.h>

static void
Shizu_List_postCreateType
  (
    Shizu_State1* state1
  );

static void
Shizu_List_preDestroyType
  (
    Shizu_State1* state1
  );

static void
Shizu_List_visit
  (
    Shizu_State2* state,
    Shizu_List* self
  );

static void
Shizu_List_finalize
  (
    Shizu_State2* state,
    Shizu_List* self
  );

static void
Shizu_List_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  );

static void
Shizu_List_ensureFreeCapacity
  (
    Shizu_State2* state,
    Shizu_List* self,
    size_t required
  );

static Shizu_ObjectTypeDescriptor const Shizu_List_Type = {
  .postCreateType = (Shizu_PostCreateTypeCallback*) & Shizu_List_postCreateType,
  .preDestroyType = (Shizu_PreDestroyTypeCallback*) & Shizu_List_preDestroyType,
  .visitType = NULL,
  .size = sizeof(Shizu_List),
  .construct = &Shizu_List_constructImpl,
  .visit = (Shizu_OnVisitCallback*) & Shizu_List_visit,
  .finalize = (Shizu_OnFinalizeCallback*) & Shizu_List_finalize,
  .dispatchSize = sizeof(Shizu_List_Dispatch),
  .dispatchInitialize = NULL,
  .dispatchUninitialize = NULL,
};

Shizu_defineObjectType("Shizu.List", Shizu_List, Shizu_Object);

static const char* namedMemoryName = "Shizu.Lists.NamedMemory";

typedef struct Lists {
  size_t minimumCapacity;
  size_t maximumCapacity;
} Lists;

static void
Shizu_List_postCreateType
  (
    Shizu_State1* state1
  )
{
  if (Shizu_State1_allocateNamedStorage(state1, namedMemoryName, sizeof(Lists))) {
    Shizu_State1_setStatus(state1, 1);
    Shizu_State1_jump(state1);
  }
  Lists* g = NULL;
  if (Shizu_State1_getNamedStorage(state1, namedMemoryName, (void**)&g)) {
    Shizu_State1_deallocateNamedStorage(state1, namedMemoryName);
    Shizu_State1_setStatus(state1, 1);
    Shizu_State1_jump(state1);
  }
  g->minimumCapacity = 8;
  g->maximumCapacity = SIZE_MAX / sizeof(Shizu_Value);
  if (g->maximumCapacity > Shizu_Integer32_Maximum) {
    g->maximumCapacity = Shizu_Integer32_Maximum;
  }
  if (g->maximumCapacity > INT_MAX) {
    g->maximumCapacity = INT_MAX;
  }
  if (g->maximumCapacity > SIZE_MAX) {
    g->maximumCapacity = SIZE_MAX;
  }
}

static void
Shizu_List_preDestroyType
  (
    Shizu_State1* state1
  )
{
  Shizu_State1_deallocateNamedStorage(state1, namedMemoryName);
}

static void
Shizu_List_visit
  (
    Shizu_State2* state,
    Shizu_List* self
  )
{
  for (size_t i = 0, n = self->size; i < n; ++i) {
    Shizu_Gc_visitValue(Shizu_State2_getState1(state), Shizu_State2_getGc(state), self->elements + i);
  }
}

static void
Shizu_List_finalize
  (
    Shizu_State2* state,
    Shizu_List* self
  )
{
  self->size = 0;
  Shizu_State1_deallocate(Shizu_State2_getState1(state), self->elements);
  self->elements = NULL;
  self->capacity = 0;
}

static void
Shizu_List_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  )
{
  if (1 != numberOfArgumentValues) {
    Shizu_State2_setStatus(state, Shizu_Status_NumberOfArgumentsInvalid);
    Shizu_State2_jump(state);
  }
  if (!Shizu_Value_isObject(&argumentValues[0])) {
    Shizu_State2_setStatus(state, Shizu_Status_ArgumentTypeInvalid);
    Shizu_State2_jump(state);
  }
  Shizu_List* SELF = (Shizu_List*)Shizu_Value_getObject(&argumentValues[0]);
  Shizu_Type* TYPE = Shizu_List_getType(state);
  Shizu_Object_construct(state, (Shizu_Object*)SELF);
  SELF->elements = malloc(8 * sizeof(Shizu_Value));
  if (!SELF->elements) {
    Shizu_State2_setStatus(state, Shizu_Status_AllocationFailed);
    Shizu_State2_jump(state);
  }
  SELF->size = 0;
  SELF->capacity = 8;
  ((Shizu_Object*)SELF)->type = TYPE;
}

/** @todo Do not alloc*/
static void
Shizu_List_ensureFreeCapacity
  (
    Shizu_State2* state,
    Shizu_List* self,
    size_t requiredFreeCapacity
  ) 
{
  Lists* g = NULL;
  if (Shizu_State1_getNamedStorage(Shizu_State2_getState1(state), namedMemoryName, (void**)&g)) {
    Shizu_State2_setStatus(state, Shizu_Status_AllocationFailed);
    Shizu_State2_jump(state);
  }
  size_t oldCapacity = self->capacity;
  size_t newCapacity = self->capacity;
  size_t availableFreeCapacity = self->capacity - self->size;
  while (requiredFreeCapacity > availableFreeCapacity) {
    {
      oldCapacity = self->capacity;
      newCapacity = oldCapacity;
      if (oldCapacity > g->maximumCapacity / 2) {
        // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
        // Consequently, we cannot double the capacity. Try to saturate the capacity.
        if (oldCapacity == g->maximumCapacity) {
          Shizu_State2_setStatus(state, Shizu_Status_AllocationFailed);
          Shizu_State2_jump(state);
        } else {
          newCapacity = g->maximumCapacity;
        }
      } else {
        newCapacity = oldCapacity * 2;
      }
    }
    availableFreeCapacity = newCapacity - self->size;
  }
  Shizu_Value* newElements = realloc(self->elements, newCapacity * sizeof(Shizu_Value));
  if (!newElements) {
    Shizu_State2_setStatus(state, 1);
    Shizu_State2_jump(state);
  }
  self->elements = newElements;
  self->capacity = newCapacity;
}

static Shizu_Value const IndexOutOfBounds = { .tag = Shizu_Value_Tag_Void, .voidValue = Shizu_Void_Void };

void
Shizu_List_clear
  (
    Shizu_State2* state,
    Shizu_List* self
  )
{
  self->size = 0;
}

Shizu_Value
Shizu_List_getValue
  (
    Shizu_State2* state,
    Shizu_List* self,
    Shizu_Integer32 index
  )
{
  if (index < 0 || index >= self->size) {
    return IndexOutOfBounds;
  }
  return self->elements[index];
}

Shizu_Integer32
Shizu_List_getSize
  (
    Shizu_State2* state,
    Shizu_List* self
  )
{
  Shizu_Cxx_Debug_assert(self->size >= 0);
  Shizu_Cxx_Debug_assert(self->size <= Shizu_Integer32_Maximum);
  return (Shizu_Integer32)self->size;
}

void
Shizu_List_insertValue
  (
    Shizu_State2* state,
    Shizu_List* self,
    size_t index,
    Shizu_Value const* value
  )
{
  if (Shizu_Value_isVoid(value)) {
    return;
  }
  if (self->capacity == self->size) {
    Shizu_List_ensureFreeCapacity(state, self, 1);
  }
  if (index < self->size) {
    memmove(self->elements + index,
            self->elements + index + 1,
            sizeof(Shizu_Value) * (self->size - index));
  }
  self->elements[index] = *value;
  self->size++;
}

void
Shizu_List_appendValue
  (
    Shizu_State2* state,
    Shizu_List* self,
    Shizu_Value const* value
  )
{
  Shizu_List_insertValue(state, self, self->size, value);
}

void
Shizu_List_prependValue
  (
    Shizu_State2* state,
    Shizu_List* self,
    Shizu_Value const* value
  )
{
  Shizu_List_insertValue(state, self, 0, value);
}
