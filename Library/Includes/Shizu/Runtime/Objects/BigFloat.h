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

#if !defined(SHIZU_OBJECTS_BIGFLOAT_H_INCLUDED)
#define SHIZU_OBJECTS_BIGFLOAT_H_INCLUDED

#if !defined(SHIZU_RUNTIME_PRIVATE) && 1 != SHIZU_RUNTIME_PRIVATE
#error("Do not include `Shizu/Runtime/Objects/BigFloat.h` directly. Include `Shizu/Runtime/Include.h` instead.")
#endif
#include "Shizu/Runtime/Object.h"
typedef struct Shizu_BigInteger Shizu_BigInteger;
typedef struct Shizu_String Shizu_String;

/// @brief A big float implementation.
/// @detail
/// The Machine Language type is
/// @code
/// class Shizu.BigFloat
/// @endcode
/// Its constructor is
/// @code
/// Shizu.BigFloat.construct()
/// @endcode
/// A big float consists of an big integer (Shizu.BigInteger) <code>x</code> and a Shizu_Integer32 scale <code>s</code>.
/// The value represented by a big float is given by <code>x 10^(-scale)</code>.
/// The same numerical values can have different representions.
Shizu_declareObjectType(Shizu_BigFloat);

struct Shizu_BigFloat {
  Shizu_Object _parent;
  Shizu_BigInteger* integer;
  Shizu_Integer32 scale;
};

struct Shizu_BigFloat_Dispatch {
  Shizu_Object_Dispatch _parent;
};

Shizu_BigFloat*
Shizu_BigFloat_create
  (
    Shizu_State2* state
  );

#endif // SHIZU_OBJECTS_BIGFLOAT_H_INCLUDED
