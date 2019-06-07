.PHONY: all, $(NAME), clean, fclean, re

#*------------------------------------*\
#    color
#*------------------------------------*/
__TEXT_1__ = @echo "\033[1;34m
__TEXT_2__ = \t\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"


#*------------------------------------*\
#    path all src
#*------------------------------------*/
__PATH__ = ./src

#*------------------------------------*\
#    name
#*------------------------------------*/
__NAME__ = ft_ls


#*------------------------------------*\
#    compilateur
#*------------------------------------*/
__CC__ = gcc
__CFLAGS__ = -Wall -Werror -Wextra


#*------------------------------------*\
#    lib sources
#*------------------------------------*/

#lib ft :
__LIB_FT_PATH__ = compact-libft
__LIB_FT_INC__ = ${__LIB_FT_PATH__}includes/


#*------------------------------------*\
#    sources project push
#*------------------------------------*/
__SOURCES_PATH__ = ${__PATH__}src/

# COMMANDE find . -type f -name '*.c' | sed 's/^..//'  |  tr '\n' ' ' | pbcopy)
__TMP__ := $(shell cd ${__SOURCES_PATH__} ; find . -type f -name '*.c' | sed 's/^..//'  |  tr '\n' ' ')
#__TMP__ = data/best_path.c data/finder_finder_link.c data/lem.c data/map.c data/move.c data/room.c data/tunnel.c debug/debug_set.c debug/src/debug_map.c debug/src/debug_parseur.c debug/src/debug_path.c main.c main_2.c parseur/get_room.c parseur/get_room_utils.c parseur/get_tunnel.c parseur/getter.c solver/algo/algo.c solver/algo/find_best_path.c solver/algo/shorty_baby.c solver/move_f.c solver/move_f_main.c solver/sort_path/generate_map_path.c solver/split_path/clean_working_dll.c solver/split_path/split_path.c

__SRC__ = $(addprefix $(__SOURCES_PATH__), $(__TMP__))

__OBJ__ = $(__SRC__:.c=.o)

__HEADER_DIR__ = ${__PATH__}/includes/

#*------------------------------------*\
#    make rule
#*------------------------------------*/
all: push_push


push_push: $(__NAME__)

#*------------------------------------*\
#    buld and push
#*------------------------------------*/
$(__NAME__): $(__OBJ__)

#	build other lib 	################################
	@make -C $(__LIB_FT_PATH__)

#	compile project 	################################
	@$(__CC__) $(__CFLAGS__) -o $(__NAME__) $(__OBJ__) -L${__LIB_FT_PATH__} -lft

	$(shell mv lem_in ./test)
	$(__TEXT_1__) $(__NAME__) $(__TEXT_2__)

#*------------------------------------*\
#    if change into .c
#*------------------------------------*/
%.o: %.c $(__HEADER_DIR__) $(__LIB_FT_INC__)
	@$(__CC__) $(__CFLAG__) -I $(__HEADER_DIR__) -I $(__LIB_FT_INC__) -o $@ -c $<


clean:
	@make clean -C $(__LIB_FT_PATH__)
	@rm -rf $(__OBJ__)
#	@echo "\033[1;34mlem-in\t\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"


fclean: clean
	@make fclean -C $(__LIB_FT_PATH__)
	@rm -rf $(__NAME__)
	@echo "\033[1;34mlem-in \t\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all