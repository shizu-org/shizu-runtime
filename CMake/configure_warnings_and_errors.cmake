#
# Shizu
# Copyright (C) 2018-2024 Michael Heilmann. All rights reserved.
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

# SUMMARY
# Configure warnings and errors for a static libraries, module libraries, and executables.
# 
# DETAIL
# Configure warnings and errors for a static libraries, module libraries, and executables.
# For GCC:  Turn several warnings into errors.
# For MSVC: Turn several warnings into errors.
#
# PARAM target The target.
macro(Shizu_configureWarningsAndErrors target)
  if (NOT DEFINED ${target}.compiler_c)
    message(FATAL_ERROR "please execute detect_compiler before Shizu_configureWarningsAndErrors")
  endif()
  if (${${target}.compiler_c} STREQUAL ${${target}.compiler_c_gcc})
    target_compile_options(${target} BEFORE PRIVATE "-Werror=implicit-function-declaration")
  endif()

  if(${${target}.compiler_c} STREQUAL ${${target}.compiler_c_msvc})
    set(${target}.compile_options "")
    # C4090:  'opertion' : different 'modifier' qualifiers
    list(APPEND ${target}.compile_options "/we4090")
    # C4133: 'function' incompatible types - from 'type1' to 'type2'
    list(APPEND ${target}.compile_options "/we4133")
    # C4020_ 'function': too many actual parameters
    list(APPEND ${target}.compile_options "/we4020")
    # C4013: 'function': undefined; assuming extern returning int
    list(APPEND ${target}.compile_options "/we4013")
    # C4024: 'function': different types for formal and actual parameter 'number'
    list(APPEND ${target}.compile_options "/we4024")
    # C4716: 'function' must return a value
    list(APPEND ${target}.compile_options "/we4716")
    # C4013: 'function' undefined; assuming extern returning int
    list(APPEND ${target}.compile_options "/we4013")
    # C4028: formal parameter 'number' different from declaration
    list(APPEND ${target}.compile_options "/we4028")

    # The quotes around "${${target}.compile_options}" concatenate the list elements to a single string separated by semicolons.
    set_source_files_properties(${${target}.source_files} PROPERTIES COMPILE_OPTIONS "${${target}.compile_options}")
    set_source_files_properties(${${target}.header_files} PROPERTIES COMPILE_OPTIONS "${${target}.compile_options}")

  endif()

endmacro()
