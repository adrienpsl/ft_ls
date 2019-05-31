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
        ${includes} src/ft_ls_extract.c src/ft_ls_fill_lslink.c src/ft_ls_main.c)

#*------------------------------------*\
#    link avec les lib
#*------------------------------------*/
target_link_libraries(ft_ls__lib libft)
target_include_directories(ft_ls__lib PUBLIC includes)
