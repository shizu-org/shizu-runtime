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

#include "MachineLanguage/Token.h"

Shizu_defineEnumerationType("MachineLanguage.TokenType", TokenType);

static void
Token_visit
  (
    Shizu_State2* state,
    Token* self
  );

static void
Token_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  );

static Shizu_ObjectTypeDescriptor const Token_Type = {
  .postCreateType = (Shizu_PostCreateTypeCallback*)NULL,
  .preDestroyType = (Shizu_PreDestroyTypeCallback*)NULL,
  .visitType = NULL,
  .size = sizeof(Token),
  .construct = &Token_constructImpl,
  .visit = (Shizu_OnVisitCallback*)&Token_visit,
  .finalize = (Shizu_OnFinalizeCallback*)NULL,
  .dispatchSize = sizeof(Token_Dispatch),
  .dispatchInitialize = NULL,
  .dispatchUninitialize = NULL,
};

Shizu_defineObjectType("MachineLanguage.Token", Token, Shizu_Object);

static void
Token_visit
  (
    Shizu_State2* state,
    Token* self
  )
{
  if (self->text) {
    Shizu_Gc_visitObject(Shizu_State2_getState1(state), Shizu_State2_getGc(state), (Shizu_Object*)self->text);
  }
}

static void
Token_constructImpl
  (
    Shizu_State2* state,
    Shizu_Value* returnValue,
    Shizu_Integer32 numberOfArgumentValues,
    Shizu_Value* argumentValues
  )
{
  Shizu_Type* TYPE = Token_getType(state);
  Token* self = (Token*)Shizu_Value_getObject(&argumentValues[0]);
  Shizu_Object_construct(state, (Shizu_Object*)self);
  self->type = Shizu_Value_getInteger32(&argumentValues[1]);
  self->text = (Shizu_String*)Shizu_Value_getObject(&argumentValues[2]);
  ((Shizu_Object*)self)->type = TYPE;
}

Token*
Token_create
  (
    Shizu_State2* state,
    TokenType type,
    Shizu_String* text
  )
{
  Shizu_Value returnValue = Shizu_Value_InitializerVoid(Shizu_Void_Void);
  Shizu_Value argumentValues[] = { Shizu_Value_InitializerVoid(Shizu_Void_Void),
                                   Shizu_Value_InitializerVoid(Shizu_Void_Void),
                                   Shizu_Value_InitializerVoid(Shizu_Void_Void), };
  Shizu_Value_setType(&argumentValues[0], Token_getType(state));
  Shizu_Value_setInteger32(&argumentValues[1], type);
  if (text) {
    Shizu_Value_setObject(&argumentValues[2], (Shizu_Object*)text);
  } else {
    Shizu_Value_setVoid(&argumentValues[2], Shizu_Void_Void);
  }
  Shizu_Operations_create(state, &returnValue, 3, &argumentValues[0]);
  return (Token*)Shizu_Value_getObject(&returnValue);
}
