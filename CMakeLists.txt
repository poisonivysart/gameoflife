cmake_minimum_required(VERSION 3.20.3)
INCLUDE(FindPackageHandleStandardArgs) 
set(CMAKE_INSTALL_PREFIX "CUnit/CUnit.h")  

# set(CUnit)
# find_path(CUNIT_INCLUDE_DIR NAMES CUnit/CUnit.h)
# find_library(CUNIT_LIBRARY NAMES cunit)
# find_package_handle_standard_args(CUnit DEFAULT_MSG CUNIT_LIBRARY CUNIT_INCLUDE_DIR)
# find_package(CUnit REQUIRED)

project(GAMEOFLIFE)

# find_package(SDL2 REQUIRED)

# tell CMake to use CTest extension
# CMAKE_INSTALL_PREFIX = "SDL2"

add_executable(${PROJECT_NAME} main.c)


add_subdirectory(game)
target_link_libraries(${PROJECT_NAME} life)

add_subdirectory(console)
target_link_libraries(${PROJECT_NAME} board)

enable_testing()
# now register the executable with CTest
add_executable(my_test tests/tests.c)
target_link_libraries(my_test cunit)
# set_target_properties (my_test PROPERTIES LINK_FLAGS -Wl,-lcunit)  
add_test(NAME my_test COMMAND my_test)


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