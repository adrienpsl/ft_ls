project(ft_ls__lib)

file(GLOB SOURCES_FILES_1 "*.c")
file(GLOB SOURCES_FILES_2 "./**/*.c")
file(GLOB SOURCES_FILES_3 "./**/**/*.c")
file(GLOB SOURCES_FILES_4 "./**/**/**/*.c")

file(GLOB includes "./**/*.h")


add_library(ft_ls__lib STATIC
        ${SOURCES_FILES_1}
        ${SOURCES_FILES_2}
        ${SOURCES_FILES_3}
        ${SOURCES_FILES_4}
        ${includes} src/ft_ls_lstat_extracting.c src/ft_ls_array.c src/ft_ls_main.c src/ft_ls_sorting.c src/ft_ls_print.c src/src_2/ft_ls_build_array.c src/src_2/ft_ls_main_2.c src/src_2/utils.c src/src_2/ft_ls_handle_stat.c src/src_2/ft_ls_print_2.c)

#*------------------------------------*\
#    link avec les lib
#*------------------------------------*/
target_link_libraries(ft_ls__lib libft)
target_include_directories(ft_ls__lib PUBLIC includes)
