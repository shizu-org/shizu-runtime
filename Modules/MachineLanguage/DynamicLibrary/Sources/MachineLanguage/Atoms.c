#include "MachineLanguage/Atoms.h"

// memcpy
#include <string.h>

static void
Atom_finalize
  (
    Shizu_State2* state,
    Atom* self
  );

static void
Atom_visit
  (
    Shizu_State2* state,
    Atom* self
  );

static void
Atom_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  );

static Shizu_ObjectTypeDescriptor const Atom_Type = {
  .postCreateType = (Shizu_PostCreateTypeCallback*)NULL,
  .preDestroyType = (Shizu_PreDestroyTypeCallback*)NULL,
  .visitType = NULL,
  .size = sizeof(Atom),
  .construct = &Atom_constructImpl,
  .visit = (Shizu_OnVisitCallback*)&Atom_visit,
  .finalize = (Shizu_OnFinalizeCallback*)&Atom_finalize,
  .dispatchSize = sizeof(Atom_Dispatch),
  .dispatchInitialize = (Shizu_OnDispatchInitializeCallback*)NULL,
  .dispatchUninitialize = NULL,
};

Shizu_defineObjectType("MachineLanguage.Atom", Atom, Shizu_Object);

static void
Atom_finalize
  (
    Shizu_State2* state,
    Atom* self
  )
{
  if (self->bytes) {
    Shizu_State1_deallocate(Shizu_State2_getState1(state), self->bytes);
    self->bytes = NULL;
  }
}

static void
Atom_visit
  (
    Shizu_State2* state,
    Atom* self
  )
{
  if (self->next) {
    Shizu_Gc_visitObject(Shizu_State2_getState1(state), Shizu_State2_getGc(state), (Shizu_Object*)self->next);
  }
}

static void
Atom_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  )
{
  Shizu_Type* TYPE = Atom_getType(state);
  Atom* self = (Atom*)Shizu_Value_getObject(&argumentValues[0]);
  Shizu_Object_construct(state, (Shizu_Object*)self);
  Shizu_ByteArray* bytes = (Shizu_ByteArray*)Shizu_Value_getObject(&argumentValues[1]);
  size_t numberOfRawBytes = Shizu_ByteArray_getNumberOfRawBytes(state, bytes);
  uint8_t const* rawBytes = Shizu_ByteArray_getRawBytes(state, bytes);
  size_t hashValue = numberOfRawBytes;
  for (size_t i = 0, n = numberOfRawBytes; i < n; ++i) {
    hashValue = (hashValue << 5)^(hashValue >> 3) | (size_t)rawBytes[i];
  }
  self->bytes = Shizu_State1_allocate(Shizu_State2_getState1(state), numberOfRawBytes);
  if (!self->bytes) {
    Shizu_State1_setStatus(Shizu_State2_getState1(state), Shizu_Status_AllocationFailed);
    Shizu_State1_jump(Shizu_State2_getState1(state));
  }
  memcpy(self->bytes, rawBytes, numberOfRawBytes);
  self->numberOfBytes = numberOfRawBytes;
  self->hashValue = hashValue;
  self->next = NULL;
  ((Shizu_Object*)self)->type = TYPE;
}

void
Atom_construct
  (
    Shizu_State2* state,
    Atom* self,
    Shizu_ByteArray* bytes
  )
{
  Shizu_Type* TYPE = Atom_getType(state);
  Shizu_Object_construct(state, (Shizu_Object*)self);
  size_t numberOfRawBytes = Shizu_ByteArray_getNumberOfRawBytes(state, bytes);
  uint8_t const* rawBytes = Shizu_ByteArray_getRawBytes(state, bytes);
  size_t hashValue = numberOfRawBytes;
  for (size_t i = 0, n = numberOfRawBytes; i < n; ++i) {
    hashValue = (hashValue << 5)^(hashValue >> 3) | (size_t)rawBytes[i];
  }
  self->bytes = Shizu_State1_allocate(Shizu_State2_getState1(state), numberOfRawBytes);
  if (!self->bytes) {
    Shizu_State1_setStatus(Shizu_State2_getState1(state), Shizu_Status_AllocationFailed);
    Shizu_State1_jump(Shizu_State2_getState1(state));
  }
  memcpy(self->bytes, rawBytes, numberOfRawBytes);
  self->numberOfBytes = numberOfRawBytes;
  self->hashValue = hashValue;
  self->next = NULL;
  ((Shizu_Object*)self)->type = TYPE;
}

Atom*
Atom_create
  (
    Shizu_State2* state,
    Shizu_ByteArray* bytes
  )
{
  Shizu_Type* TYPE = Atom_getType(state);
  Atom* self = (Atom*)Shizu_Gc_allocateObject(state, sizeof(Atom));
  Atom_construct(state, self, bytes);
  return self;
}

static void
Atoms_finalize
  (
    Shizu_State2* state,
    Atoms* self
  );

static void
Atoms_visit
  (
    Shizu_State2* state,
    Atoms* self
  );

static void
Atoms_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  );

static Shizu_ObjectTypeDescriptor const Atoms_Type = {
  .postCreateType = (Shizu_PostCreateTypeCallback*)NULL,
  .preDestroyType = (Shizu_PreDestroyTypeCallback*)NULL,
  .visitType = NULL,
  .size = sizeof(Atoms),
  .construct = &Atoms_constructImpl,
  .visit = (Shizu_OnVisitCallback*)&Atoms_visit,
  .finalize = (Shizu_OnFinalizeCallback*)&Atoms_finalize,
  .dispatchSize = sizeof(Atoms_Dispatch),
  .dispatchInitialize = (Shizu_OnDispatchInitializeCallback*)NULL,
  .dispatchUninitialize = NULL,
};

Shizu_defineObjectType("MachineLanguage.Atoms", Atoms, Shizu_Object);

static void
Atoms_finalize
  (
    Shizu_State2* state,
    Atoms* self
  )
{
  if (self->buckets) {
    Shizu_State1_deallocate(Shizu_State2_getState1(state), self->buckets);
    self->buckets = NULL;
  }
}

static void
Atoms_visit
  (
    Shizu_State2* state,
    Atoms* self
  )
{
  for (size_t i = 0, n = self->capacity; i < n; ++i) {
    Atom* node  = self->buckets[i];
    while (node) {
      Shizu_Gc_visitObject(Shizu_State2_getState1(state), Shizu_State2_getGc(state), (Shizu_Object*)node);
      node = node->next;
    }
  }
}

static void
Atoms_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  )
{
  Shizu_Type* TYPE = Atoms_getType(state);
  Atoms* self = (Atoms*)Shizu_Value_getObject(&argumentValues[0]);
  Shizu_Object_construct(state, (Shizu_Object*)self);
  self->buckets = Shizu_State1_allocate(Shizu_State2_getState1(state), sizeof(Atom*) * 8);
  if (!self->buckets) {
    Shizu_State2_setStatus(state, Shizu_Status_AllocationFailed);
    Shizu_State2_jump(state);
  }
  for (size_t i = 0, n = 8; i < n; ++i) {
    self->buckets[i] = NULL;
  }
  self->size = 0;
  self->capacity = 8;
  ((Shizu_Object*)self)->type = TYPE;
}

void
Atoms_construct
  (
    Shizu_State2* state,
    Atoms* self
  )
{
  Shizu_Type* TYPE = Atoms_getType(state);
  Shizu_Object_construct(state, (Shizu_Object*)self);
  self->buckets = Shizu_State1_allocate(Shizu_State2_getState1(state), sizeof(Atom*) * 8);
  if (!self->buckets) {
    Shizu_State2_setStatus(state, Shizu_Status_AllocationFailed);
    Shizu_State2_jump(state);
  }
  for (size_t i = 0, n = 8; i < n; ++i) {
    self->buckets[i] = NULL;
  }
  self->size = 0;
  self->capacity = 8;
  ((Shizu_Object*)self)->type = TYPE;
}

Atoms*
Atoms_create
  (
    Shizu_State2* state
  )
{
  Shizu_Type* TYPE = Atoms_getType(state);
  Shizu_ObjectTypeDescriptor const* DESCRIPTOR = Shizu_Type_getObjectTypeDescriptor(Shizu_State2_getState1(state), Shizu_State2_getTypes(state), TYPE);
  Atoms* SELF = (Atoms*)Shizu_Gc_allocateObject(state, sizeof(Atoms));
  Atoms_construct(state, SELF);
  return SELF;
}