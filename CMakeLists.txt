cmake_minimum_required(VERSION 3.13)

project(ft_ls C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -og -g3")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")
#-fsanitize=memory-fsanitize-memory-track-origins=2 -fsanitize=address

#include_directories(PRIVATE includes)
add_subdirectory(compact-libft)

add_library(ft_ls_lib STATIC
        src/ft_ls_handle_stat.c
        src/ft_ls_main.c
        src/ft_ls_print.c
        src/ft_ls_print_stat.c
        src/ft_ls_sorting.c
        src/utils.c
        )

target_include_directories(ft_ls_lib PUBLIC includes)

add_executable(
        ft_ls
        src/main.c
        test/main.test_2.c
)



#*------------------------------------*\
#    --  LINKING --
#*------------------------------------*/
target_link_libraries(ft_ls_lib libft)

target_link_libraries(ft_ls libft)
target_link_libraries(ft_ls ft_ls_lib)
