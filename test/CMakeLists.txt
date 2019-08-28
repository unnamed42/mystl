add_executable(test main.cpp)

target_include_directories(test PUBLIC ../include)

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
