project(test)
include_directories(../src)
add_executable(test src/main.c)
target_link_libraries(test stk)
