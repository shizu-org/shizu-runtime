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

#if !defined(SHIZU_OBJECTS_MAP_PRIVATE_H_INCLUDED)
#define SHIZU_RUNTIME_MAP_PRIVATE_H_INCLUDED

#if !defined(SHIZU_RUNTIME_PRIVATE) && 1 != SHIZU_RUNTIME_PRIVATE
  #error("Do not include `Shizu/Runtime/Objects/Map.private.h` directly. Include `Shizu/Runtime/Include.h` instead.")
#endif
#include "Shizu/Runtime/Objects/Map.h"

/**
 * @since 0.1
 * @brief A node of a map.
 * @unmanaged
 */
typedef struct Shizu_Map_Node Shizu_Map_Node;

struct Shizu_Map_Node {
  Shizu_Map_Node* next;
  Shizu_Value key;
  Shizu_Value value;
  Shizu_Integer32 hashValue;
};

struct Shizu_Map_Dispatch {
  Shizu_Object_Dispatch _parent;
};

struct Shizu_Map {
  Shizu_Object _parent;
  Shizu_Map_Node** buckets;
  size_t size;
  size_t capacity;
};

#endif // SHIZU_OBJECTS_MAP_PRIVATE_H_INCLUDED
