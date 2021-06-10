cmake_minimum_required(VERSION 3.20.3)

project(GAMEOFLIFE)

find_package(SDL2 REQUIRED)

# tell CMake to use CTest extension
enable_testing()
add_executable(my_test tests/tests.c)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(my_test cunit)

add_subdirectory(game)
target_link_libraries(${PROJECT_NAME} board ${SDL2_LIBRARIES})



# create an executable, which instantiates a runner from
# GoogleTest, Boost.Test, QtTest or whatever framework you use
# find_package(SDL2 REQUIRED)


# depending on the framework, you need to link to it
# target_link_libraries(my_test
#                       gtest_main)

# now register the executable with CTest
add_test(NAME my_test COMMAND my_test)


# target_include_directories(${PROJECT_NAME} PUBLIC Adder)

# target_link_directories(${PROJECT_NAME} PRIVATE Adder)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# # check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)