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

#if !defined(SHIZU_OBJECTS_BYTEARRAY_PRIVATE_H_INCLUDED)
#define SHIZU_OBJECTS_BYTEARRAY_PRIVATE_H_INCLUDED

#if !defined(SHIZU_RUNTIME_PRIVATE) && 1 != SHIZU_RUNTIME_PRIVATE
  #error("Do not include `Shizu/Runtime/Objects/ByteArray.private.h` directly. Include `Shizu/Runtime/Include.h` instead.")
#endif
#include "Shizu/Runtime/Objects/ByteArray.h"

struct Shizu_ByteArray_Dispatch {
  Shizu_Object_Dispatch _parent;
};

struct Shizu_ByteArray {
  Shizu_Object _parent;
  size_t size;
  size_t capacity;
  uint8_t* elements;
};

#endif // SHIZU_OBJECTS_BYTEARRAY_PRIVATE_H_INCLUDED
