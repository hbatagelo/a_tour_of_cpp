# From: https://github.com/conan-io/cmake-conan

# Download Conan packages and extras specified in CONAN_EXTRA_REQUIRES
macro(run_conan)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(
      STATUS
        "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD
         "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
         "${CMAKE_BINARY_DIR}/conan.cmake")
  endif()
  include(${CMAKE_BINARY_DIR}/conan.cmake)

  # Add ayeganov remote repository
  conan_check()
  conan_add_remote(NAME ayeganov URL
                   https://api.bintray.com/conan/ayeganov/cppitertools)

  # Launch conan install
  conan_cmake_run(
    REQUIRES
    ${CONAN_EXTRA_REQUIRES}
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing
    ENV
    CC=${CMAKE_C_COMPILER}
    ENV
    CXX=${CMAKE_CXX_COMPILER}
    GENERATORS
    cmake_paths)
endmacro()
