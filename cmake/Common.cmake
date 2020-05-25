# Generate compile_commands.json to make it easier to work with clang based
# tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()

# ccache
find_program(CCACHE ccache)
if(CCACHE)
  message("Using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
  message("Not using ccache - not found")
endif()

# IPO
option(ENABLE_IPO "Enable Interprocedural Optimization" OFF)
if(ENABLE_IPO)

  cmake_policy(SET CMP0069 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)

  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()

endif()

# Conan Set up some extra Conan dependencies based on our needs before loading
# Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} ms-gsl/[>=3.0.1])
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} cppitertools/[>=2.0])

include(${CMAKE_CURRENT_LIST_DIR}/Conan.cmake)
run_conan()

# Standard compiler warnings
include(${CMAKE_CURRENT_LIST_DIR}/Warnings.cmake)
set_project_warnings(${WARNINGS_TARGET})

# Sanitizer options if supported by compiler
include(${CMAKE_CURRENT_LIST_DIR}/Sanitizers.cmake)
enable_sanitizers(${OPTIONS_TARGET})

# Static analysis
include(${CMAKE_CURRENT_LIST_DIR}/StaticAnalyzers.cmake)

# Conan aggregated header's folders
target_include_directories(${OPTIONS_TARGET} INTERFACE ${CONAN_INCLUDE_DIRS})

# Conan aggregated library names to link
target_link_libraries(${OPTIONS_TARGET} INTERFACE ${CONAN_LIBS})

# C++20
target_compile_features(${OPTIONS_TARGET} INTERFACE cxx_std_20)
