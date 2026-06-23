#--------------------------------------------------------------------------------
# CMake version
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#--------------------------------------------------------------------------------
# Project directories
#--------------------------------------------------------------------------------

set(MODULE_WEBUI_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_WEBUI_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_WEBUI_LIB_DIR "${MODULE_WEBUI_ROOT_DIR}/lib")
set(MODULE_WEBUI_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
set(MODULE_WEBUI_CMAKE_DIR "${MODULE_WEBUI_ROOT_DIR}/submodules/sway.module_core/cmake_modules")

#--------------------------------------------------------------------------------
# Include CMake modules
#--------------------------------------------------------------------------------

include("${MODULE_WEBUI_CMAKE_DIR}/options.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/add_submodule.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/set_compile_definitions.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/enable_coverage.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/create_object_library.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/create_interface.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/logger.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/clang/create_library.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/setup.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/create_library.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/gen_target_name.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/set_optimization.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/set_environment.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/set_compilation.cmake")
include("${MODULE_WEBUI_CMAKE_DIR}/modules/compiler/emscripten/set_modularize.cmake")

#--------------------------------------------------------------------------------
# Options
#--------------------------------------------------------------------------------

set_glob_options()

option(MODULE_WEBUI_ENVIRONMENT "Environment variable" OFF)
option(MODULE_WEBUI_COMPILATION "Compilation variable" OFF)

#--------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#--------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#--------------------------------------------------------------------------------
# Project
#--------------------------------------------------------------------------------

project_metadata("webui" 0.2.0)
project(${MODULE_WEBUI_PROJ_NAME} VERSION ${MODULE_WEBUI_VERSION} LANGUAGES CXX)

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

add_submodule("module_core" submodules/sway.module_core)
add_submodule("module_webcore" submodules/sway.module_webcore)
add_submodule("module_webcore.mvc" submodules/sway.module_webcore.mvc)

#--------------------------------------------------------------------------------
# Executable output path
#--------------------------------------------------------------------------------

set_output_dir(${MODULE_WEBUI_BIN_DIR})

#--------------------------------------------------------------------------------
# Include directories
#--------------------------------------------------------------------------------

include_directories("${MODULE_WEBUI_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_WEBUI_LIST_DIR}/submodules/sway.module_webcore/lib/cxx/include")
include_directories("${MODULE_WEBUI_LIST_DIR}/submodules/sway.module_webcore.mvc/lib/cxx/include")

#--------------------------------------------------------------------------------
# Library
#--------------------------------------------------------------------------------

add_subdirectory(lib/cxx)
