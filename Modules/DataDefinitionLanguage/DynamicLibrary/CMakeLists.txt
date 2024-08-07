#
# Shizu
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

set(name ${moduleName})
Shizu_beginDynamicLibrary()

list(APPEND ${name}.source_files Sources/Main.c)

list(APPEND ${name}.source_files Sources/DataDefinitionLanguage/Ast.c)
list(APPEND ${name}.header_files Includes/DataDefinitionLanguage/Ast.h)
list(APPEND ${name}.source_files Sources/DataDefinitionLanguage/Token.c)
list(APPEND ${name}.header_files Includes/DataDefinitionLanguage/Token.h)
list(APPEND ${name}.source_files Sources/DataDefinitionLanguage/Scanner.c)
list(APPEND ${name}.header_files Includes/DataDefinitionLanguage/Scanner.h)
list(APPEND ${name}.source_files Sources/DataDefinitionLanguage/Parser.c)
list(APPEND ${name}.header_files Includes/DataDefinitionLanguage/Parser.h)
list(APPEND ${name}.source_files Sources/DataDefinitionLanguage/Atoms.c)
list(APPEND ${name}.header_files Includes/DataDefinitionLanguage/Atoms.h)

Shizu_endDynamicLibrary()

target_link_libraries(${name} Shizu)

# Add the `Shizu.Runntime.Module.FileSystem` module to the prerequisite modules of this module.
get_target_property(prerequisiteModules ${name} prerequisiteModules)
list(APPEND prerequisiteModules Shizu.Modules.FileSystem)
set_target_properties(${name} PROPERTIES prerequisiteModules "${prerequisiteModules}")

on_executable(${name})
