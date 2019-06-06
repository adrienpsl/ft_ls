cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME ft_ls)


#*------------------------------------*\
#    --  NAME PROJET  --
#*------------------------------------*/
project(${PROJECT_NAME} C)

#*------------------------------------*\
#    --  COMPILATEUR OPTION  --
#*------------------------------------*/
set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -og -g3")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")


#-fsanitize=memory-fsanitize-memory-track-origins=2 -fsanitize=address

add_executable(
        ft_ls__run
        file/main.c
        test/main.test_2.c)

#*------------------------------------*\
#    --  PATH  --
#*------------------------------------*/
set(REPO "file/")

#*------------------------------------*\
#    -- LIB FT FILE --
#*------------------------------------*/
add_subdirectory(compact-libft)

#*------------------------------------*\
#    --  PROJET FILE  --
#*------------------------------------*/
add_subdirectory(file)

#*------------------------------------*\
#    --  TEST FILE  --
#*------------------------------------*/
#file(GLOB sources06 "test/*.c")
#file(GLOB sources07 "includes/*.c")
#file(GLOB sources08 "includes/*.h")

#*------------------------------------*\
#    --  LINKING --
#*------------------------------------*/
target_link_libraries(ft_ls__run ft_ls__lib)
target_link_libraries(ft_ls__run libft)
