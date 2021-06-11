cmake_minimum_required(VERSION 3.20.3)

project(GAMEOFLIFE)

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


# look for Doxygen package
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # doxygen settings can be set here, prefixed with "DOXYGEN_"
  set(DOXYGEN_SOURCE_BROWSER YES)
  set(DOXYGEN_EXTRACT_PRIVATE YES)
  set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/api-docs")
  # this target will only be built if specifically asked to.
  # run "make api-docs" to create the doxygen documentation
  doxygen_add_docs(
    api-docs
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate API-documents for NoteSearch."
  )
endif(DOXYGEN_FOUND)
# # # check if Doxygen is installed
# find_package(Doxygen)
# if (DOXYGEN_FOUND)
#     # set input and output files
#     set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
#     set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#     # request to configure the file
#     configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#     message("Doxygen build started")

#     # note the option ALL which allows to build the docs together with the application
#     add_custom_target( doc_doxygen ALL
#         COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#         COMMENT "Generating API documentation with Doxygen"
#         VERBATIM )
# else (DOXYGEN_FOUND)
#   message("Doxygen need to be installed to generate the doxygen documentation")
# endif (DOXYGEN_FOUND)