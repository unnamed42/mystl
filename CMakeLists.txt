cmake_minimum_required(VERSION 3.10)

project(mystl_test)

add_executable(test_target test/main.cpp test/everything.hpp)

set_target_properties(test_target PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(test_target PUBLIC -Wall -Wextra)
target_include_directories(test_target PUBLIC include)

add_custom_command(
    OUTPUT test/everything.hpp
    VERBATIM COMMAND find ${CMAKE_CURRENT_LIST_DIR}/include -name "*.hpp" -printf "#include \"%P\"\\n" | sort > ${CMAKE_CURRENT_LIST_DIR}/test/everything.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "generating everything.hpp"
)
