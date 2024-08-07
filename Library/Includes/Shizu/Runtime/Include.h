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

#if !defined(SHIZU_RUNTIME_INCLUDE_H_INCLUDED)
#define SHIZU_RUNTIME_INCLUDE_H_INCLUDED

#define SHIZU_RUNTIME_PRIVATE (1)
#include "Shizu/Runtime/Extensions.h"
#include "Shizu/Runtime/Gc.h"
#include "Shizu/Runtime/Locks.h"
#include "Shizu/Runtime/Stack.h"
#include "Shizu/Runtime/State2.h"
#include "Shizu/Runtime/Status.h"
#include "Shizu/Runtime/Value.h"

#include "Shizu/Runtime/countLeadingZeroes.h"
#include "Shizu/Runtime/countTrailingZeroes.h"
#include "Shizu/Runtime/getWorkingDirectory.h"
#include "Shizu/Runtime/isPowerOfTwo.h"
#include "Shizu/Runtime/powerOfTwoGreaterThan.h"
#include "Shizu/Runtime/powerOfTwoGreaterThanOrEqualTo.h"

#include "Shizu/Runtime/Operations/Include.h"

#include "Shizu/Runtime/Objects/ByteArray.h"
#include "Shizu/Runtime/Objects/CxxProcedure.h"
#include "Shizu/Runtime/Objects/Environment.h"
#include "Shizu/Runtime/Objects/List.h"
#include "Shizu/Runtime/Objects/Map.h"
#include "Shizu/Runtime/Objects/String.h"
#include "Shizu/Runtime/Objects/WeakReference.h"
#undef SHIZU_RUNTIME_PRIVATE

#endif // SHIZU_RUNTIME_INCLUDE_H_INCLUDED
