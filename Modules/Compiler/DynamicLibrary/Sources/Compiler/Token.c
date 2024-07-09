/*
  Shizu Runtime
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

#include "Compiler/Token.h"

Shizu_defineEnumerationType(Compiler_TokenType);

static void
Compiler_Token_visit
  (
    Shizu_State2* state,
    Compiler_Token* self
  );

static void
Compiler_Token_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  );

static Shizu_ObjectTypeDescriptor const Compiler_Token_Type = {
  .postCreateType = (Shizu_PostCreateTypeCallback*)NULL,
  .preDestroyType = (Shizu_PreDestroyTypeCallback*)NULL,
  .visitType = NULL,
  .size = sizeof(Compiler_Token),
  .construct = &Compiler_Token_constructImpl,
  .visit = (Shizu_OnVisitCallback*)&Compiler_Token_visit,
  .finalize = (Shizu_OnFinalizeCallback*)NULL,
  .dispatchSize = sizeof(Compiler_Token_Dispatch),
  .dispatchInitialize = NULL,
  .dispatchUninitialize = NULL,
};

Shizu_defineObjectType(Compiler_Token, Compiler_Object);

static void
Compiler_Token_visit
  (
    Shizu_State2* state,
    Compiler_Token* self
  )
{
  if (self->text) {
    Shizu_Gc_visitObject(Shizu_State2_getState1(state), Shizu_State2_getGc(state), (Shizu_Object*)self->text);
  }
}

static void
Compiler_Token_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  )
{
  Shizu_Type* TYPE = Compiler_Token_getType(state);
  Compiler_Token* self = (Compiler_Token*)Shizu_Value_getObject(&argumentValues[0]);
  Compiler_Object_construct(state, (Compiler_Object*)self);
  self->type = Shizu_Value_getInteger32(&argumentValues[1]);
  self->text = (Shizu_String*)Shizu_Value_getObject(&argumentValues[2]);
  ((Shizu_Object*)self)->type = TYPE;
}

void
Compiler_Token_construct
  (
    Shizu_State2* state,
    Compiler_Token* self,
    Compiler_TokenType type,
    Shizu_String* text
  )
{
  Shizu_Type* TYPE = Compiler_Token_getType(state);
  Compiler_Object_construct(state, (Compiler_Object*)self);
  self->type = type;
  self->text = text;
  ((Shizu_Object*)self)->type = TYPE;
}

Compiler_Token*
Compiler_Token_create
  (
    Shizu_State2* state,
    Compiler_TokenType type,
    Shizu_String* text
  )
{
  Shizu_Type* TYPE = Compiler_Token_getType(state);
  Shizu_ObjectTypeDescriptor const* DESCRIPTOR = Shizu_Type_getObjectTypeDescriptor(Shizu_State2_getState1(state), Shizu_State2_getTypes(state), TYPE);
  Compiler_Token* SELF = (Compiler_Token*)Shizu_Gc_allocateObject(state, sizeof(Compiler_Token));
  Compiler_Token_construct(state, SELF, type, text);
  return SELF;
}
