cmake_minimum_required(VERSION 3.10)

project(mml-math VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect all source files for mml-math
file(GLOB_RECURSE MML_MATH_SOURCES src/*.cpp)

# Option to choose between shared or static library, default to shared
option(BUILD_SHARED_LIBS "Build shared libraries by default" ON)

# Create the shared library for mml-math
add_library(mml-math ${MML_MATH_SOURCES})

# Check if MML_PATH is set; otherwise, use default value
if(NOT DEFINED MML_LIBPATH)
    set(MML_LIBPATH "/usr/lib/" CACHE PATH "Path to the mml library")
endif()
if(NOT DEFINED MML_INCPATH)
    set(MML_INCPATH "/usr/local/include/" CACHE PATH "Path to the mml library")
endif()

# Set include and library paths for mml
set(MML_INCLUDE_DIR "${MML_INCPATH}")
set(MML_LIBRARY_DIR "${MML_LIBPATH}")

# Include directories for mml-math
target_include_directories(mml-math
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${MML_INCLUDE_DIR}
)

# Directly link to the library file
target_link_libraries(mml-math PRIVATE ${MML_LIBRARY_DIR}/libmml.so)

# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Add main.cpp as an executable
add_executable(calc.x calculator/main.cpp calculator/logging.cpp)
target_compile_options(calc.x PRIVATE -Dcalc_log=\"${CMAKE_BINARY_DIR}/calc.log\")
target_include_directories(calc.x PRIVATE -I ${MML_INCLUDE_DIR} -I calculator/)
target_link_libraries(calc.x PRIVATE mml-math ${MML_LIBRARY_DIR}/libmml.so)

# Install the executable
install(TARGETS calc.x
        DESTINATION /usr/local/bin
)

# Install the library
install(TARGETS mml-math
        EXPORT mml-mathTargets
        LIBRARY DESTINATION /usr/lib
        INCLUDES DESTINATION /usr/local/include
)

# Install the header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mml-math
        DESTINATION /usr/local/include)
install(FILES ${PROJECT_SOURCE_DIR}/include/mml-math.hpp
        DESTINATION /usr/local/include)

# Generate the mml-math-config.cmake file and install it
install(EXPORT mml-mathTargets
        FILE mml-mathTargets.cmake
        DESTINATION /usr/lib/cmake/mml-math)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/mml-math-configVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(mml-math-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/mml-math-config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/mml-math-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/mml-math-configVersion.cmake"
    DESTINATION /usr/lib/cmake/mml-math
)

# Enable testing
enable_testing()

# Set the output directory for test executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

# Find all test files and add them as executables
file(GLOB_RECURSE MML_MATH_TEST_SOURCES test/*.cpp)

foreach(TEST_FILE ${MML_MATH_TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} mml-math ${MML_LIBRARY_DIR}/libmml.so)
    # Output test executables to the 'tests' directory
    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS ${TEST_NAME})

# Add custom target to uninstall
add_custom_target(uninstall
    COMMAND sudo rm -rf /usr/local/include/mml-math
    COMMAND sudo rm -rf /usr/local/include/mml-math.hpp
    COMMAND sudo rm -rf /usr/lib/cmake/mml-math
    COMMAND sudo rm -rf /usr/lib/libmml-math.so
    COMMAND sudo rm -rf /usr/local/bin/calc.x
    COMMENT "Uninstalling files..."
)

