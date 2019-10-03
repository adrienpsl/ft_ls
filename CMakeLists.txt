cmake_minimum_required(VERSION 3.14)

project(ft_ls C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -og -g3")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(libft)

add_library(ls_lib STATIC
        src/ft_ls.build_files.c
        includes/ft_ls.build_files.h
        src/ft_ls.build_files.utils_0.c
        src/ft_ls.build_files.utils_1.c
        src/ft_ls.build_files.utils_2.c
        src/ft_ls.c
        src/ft_ls.catch_options.c
        src/ft_ls.handle_files_array.c
        src/ft_ls.parser.c
        src/ft_ls.print.c
        )

target_include_directories(ls_lib PUBLIC includes)

add_executable(ft_ls
        src/main.c)



#*------------------------------------*\
#    --  LINKING --
#*------------------------------------*/
target_link_libraries(ls_lib libft)

target_link_libraries(ft_ls libft)
target_link_libraries(ft_ls ls_lib)
