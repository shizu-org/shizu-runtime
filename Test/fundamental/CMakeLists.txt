#
# Shizu Runtime
# Copyright (C) 2024 Michael Heilmann. All rights reserved.
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

cmake_minimum_required(VERSION 3.20)

set(name ${Shizu.Runtime.project-name}.Runtime.Test.Fundamental)

Shizu_beginExecutable()

list(APPEND ${name}.source_files Sources/Shizu.Runtime.Test.Fundamental/Main.c)

Shizu_endExecutable()

target_link_libraries(${name} PRIVATE ${Shizu.Runtime.project-name})

add_dependencies(${name} Shizu.Runtime.Modules.FileSystem)

add_test(NAME ${name} COMMAND ${name} WORKING_DIRECTORY $<TARGET_FILE_DIR:${name}>)

set(modules "")
get_target_property(modules Shizu.Runtime modules)
foreach (module ${modules})
  add_dependencies(${name} ${module})
endforeach()
foreach (module ${modules})
  copy_plugin(${name} ${module})
endforeach()
