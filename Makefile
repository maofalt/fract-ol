# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motero <motero@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 18:38:23 by motero            #+#    #+#              #
#    Updated: 2022/10/26 22:55:02 by motero           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

#=============================================================================#
#                                 HEADERS                                     #
#=============================================================================#

HDR_NAME = Fractol.h #here other headers too
HDR_DIR = includes/
HDRS = $(addprefix $(HDR_DIR), $(HDR_NAME))
HDR_INC = -I includes -I libft/includes -I minilibx-linux/

#=============================================================================#
#                                 LIBRARIES                                     #
#=============================================================================#

LIBFT_HDIR = libft/includes
LIBFT_HDIR_INC = -I./libft/includes/
LIB_BINARY = -Llibft -lft
LIBFT = libft/libft.a

#=============================================================================#
#                                 MiniLIBX                                    #
#=============================================================================#

MINILIBX_HDIR = includes/minilibx-linux/
MINILIBX_HDIR_INC = -I ./minilibx-linux/
MINILIBX_BINARY = -Lmlx_linux -lmlx_Linux -L$(MINILIBX_HDIR) -Imlx_linux -lXext -lX11 -lm -lz
MINILIBX = $(MINILIBX_HDIR)libmlx.a


#=============================================================================#
#                               SOURCES                                       #
#=============================================================================#

SRCS_DIR_PS = sources/
SRCS_NAME_PS = main.c \
			ft_calculate_fractal.c \
			ft_manage_events.c \
			ft_render_images.c \
			ft_coordinates.c

SRCS_PS = $(addprefix $(SRCS_DIR_PS), $(SRCS_NAME_PS))

#=============================================================================#
#                                OBJECTS                                      #
#=============================================================================#

OBJS_PATH = objs/
OBJS_NAME = $(SRCS_NAME_PS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

#=============================================================================#
#                          COMPILATOR & FLAGS                                 #
#=============================================================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
LIBA = ar rc
LIBS = ranlib

RM = rm -Rf

#=============================================================================#
#                                 Profiler                                    #
#=============================================================================#

PROFILE = fractol_prof

OBJS_PATH_PROFILER = objs_prof/
OBJS_NAME_PROFILER = $(SRCS_NAME_PS:.c=.o)
OBJS_PROFILER = $(addprefix $(OBJS_PATH_PROFILER), $(OBJS_NAME_PROFILER))

PROFILER_FLAG = -pg

#=============================================================================#
#                                 Fsanitize                                    #
#=============================================================================#

SANITIZE = fractol_sanitize

OBJS_PATH_SANITIZE = objs_sanitize/
OBJS_NAME_SANITIZE = $(SRCS_NAME_PS:.c=.o)
OBJS_SANITIZE = $(addprefix $(OBJS_PATH_SANITIZE), $(OBJS_NAME_SANITIZE))

SANITIZE_FLAG = -g3 -fsanitize=address

#=============================================================================#
#                                 Valgrind                                    #
#=============================================================================#

VALGND = fractol_valgrind

OBJS_PATH_VALGND = objs_valgrind/
OBJS_NAME_VALGND = $(SRCS_NAME_PS:.c=.o)
OBJS_VALGND = $(addprefix $(OBJS_PATH_VALGND), $(OBJS_NAME_VALGND))

VALGND_FLAG = -g3

#=============================================================================#
#                                 Callgrind                                    #
#=============================================================================#

CALLGND = fractol_callgrind

OBJS_PATH_CALLGND = objyRatio
OBJS_PATH_GDB = objs_gdb/
OBJS_NAME_GDB = $(SRCS_NAME_PS:.c=.o)
OBJS_GDB = $(addprefix $(OBJS_PATH_GDB), $(OBJS_NAME_GDB))

GDB_FLAG = -g

#=============================================================================#
#                                COLOURS                                      #
#=============================================================================#

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NONE = \033[0m

bold := $(shell tput bold)
normal := $(shell tput sgr0)

#=============================================================================#
#                                RULES                                        #
#=============================================================================#

all: check_libft check_mlx project ${NAME} ${HDRS}
		@echo "\n $(GREEN) $(bold) \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/"
		@echo "\t \t[ $(GREEN)✔$(NONE)] $(bold)Project is ready [ $(GREEN)✔$(NONE)]"
		@echo "$(GREEN) $(bold) /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ \n"

check_libft:
		@echo "\n[ $(BLUE)$(bold)CHECKING LIBFT$(NONE)]"
		@echo "============================================="
		@make -C libft

check_mlx:
		@echo "\n[ $(BLUE)$(bold)CHECKING MINILIBX$(NONE)]"
		@echo "============================================="
		@make -C includes/minilibx-linux/ mlx

project:
		@echo "\n == $(bold)$(YELLOW)CHECKING PROJECT$(normal)=="
		@echo "==============================================="

$(OBJS_PATH):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH)%.o: $(SRCS_DIR_PS)%.c $(HDRS)
		@$(CC) $(CFLAGS) $(HDR_INC) $(LIBFT_HDIR_INC) $(MINILIBX_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet fractol"

$(NAME): $(OBJS_PATH) $(OBJS) $(HDRS)
		@$(CC) $(CFLAGS) $(OBJS) $(LIB_BINARY) $(MINILIBX_BINARY) $(HDR_INC)  -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] fractol"

malloc_test: $(OBJS_PATH) $(OBJS)
		@make -C libft
		$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} $(LIB_BINARY) -L. -lmallocator

#=============================================================================#
#                                RULES   PROFILER                             #
#=============================================================================#

#To xecute as follows :make sanitizer var="1 2 3"

prof: fclean check_libft project ${PROFILE} ${HDRS} run_prof execute_profiler

execute_profiler :
		@gprof -b ${PROFILE} gmon.out > analysis.txt
		@echo "\t[ $(GREEN) Profling done!$(NONE) ]"
		@echo "========================================"
		@cat analysis.txt

run_prof: fractol_prof
	@echo "\n[ $(BLUE)$(bold)Executing binary$(NONE) ]"
	./fractol_prof $(var)

$(OBJS_PATH_PROFILER):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_PROFILER)%.o: $(SRCS_DIR_PS)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(PROFILER_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet fractol_prof"

$(PROFILE) : $(OBJS_PATH_PROFILER) $(OBJS_PROFILER) $(LIBFT) $(HDRS)
		@echo " \n[$(bold)$(YELLOW) PROFILER COMPILATION $(NONE)]"
		$(CC) $(CFLAGS) $(PROFILER_FLAG) $(OBJS_PROFILER) $(LIB_BINARY) $(MINILIBX_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] fractol_prof"

#=============================================================================#
#                                RULES   SANITIZER                            #
#=============================================================================#

#to launch as folows  : make sanitizer var="1 2 3"
sanitizer: fclean check_libft project ${SANITIZE} ${HDRS} run_san

run_san: fractol_sanitize
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"
	./fractol_sanitize $(var)

$(OBJS_PATH_SANITIZE):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_SANITIZE)%.o: $(SRCS_DIR_PS)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(SANITIZE_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet fractol_sanitize"

$(SANITIZE) : $(OBJS_PATH_SANITIZE) $(OBJS_SANITIZE) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)FSANITIZE COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(SANITIZE_FLAG) $(OBJS_SANITIZE) $(LIB_BINARY) $(MINILIBX_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] fractol_sanitize"

#make run_sanitize with good run

#=============================================================================#
#                                RULES  VALGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
valgnd: fclean check_libft project ${VALGND} ${HDRS} run_valgnd

run_valgnd: fractol_valgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with valgrind$(NONE)]\n"
	@valgrind ./fractol_valgrind $(var)

$(OBJS_PATH_VALGND):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_VALGND)%.o: $(SRCS_DIR_PS)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet fractol_valgrind"

$(VALGND) : $(OBJS_PATH_VALGND) $(OBJS_VALGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)VALGND COMPILATION"
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(LIB_BINARY) $(OBJS_VALGND) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] fractol_valgrind"


#=============================================================================#
#                                RULES  CALLLGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
callgnd: fclean check_libft project ${VALGND} ${HDRS} run_callgnd

run_callgnd: fractol_callgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with callgrind$(NONE)]\n"
	@valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes  ./fractol_callgrind $(var)
	@kcachegrind callgrind.out.*

$(OBJS_PATH_CALLGND):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_CALLGND)%.o: $(SRCS_DIR_PS)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet fractol_callgrind"

$(CALLGND) : $(OBJS_PATH_CALLGND) $(OBJS_CALLGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)CALLGND COMPILATION]"
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(LIB_BINARY) $(OBJS_CALLGND) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] fractol_callgrind"

#=============================================================================#
#                                RULES   GDB                                  #
#=============================================================================#

#to launch as folows  : make BDG
bdg: fclean check_libft project ${BDG} ${HDRS} run_bdg

run_bdg: fractol_gdb
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"
	gdb fractol_gdb $(var)

$(OBJS_PATH_GDB):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_GDB)%.o: $(SRCS_DIR_PS)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet fractol_gdb"

$(BDG) : $(OBJS_PATH_GDB) $(OBJS_GDB) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)BDG COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(OBJS_GDB) $(LIB_BINARY)  -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] fractol_gdb"

#=============================================================================#
#                                COMMANDS                                     #
#=============================================================================#

clean:
		@echo "[ $(RED)$(bold)STARTING CLEAN$(NONE) ]"
		@echo "==================================="
		@${RM} $(OBJS_PATH) $(OBJS_PATH_PROFILER) $(OBJS_PATH_SANITIZE) $(OBJS_PATH_VALGND) $(OBJS_CALLGND) $(OBJS_PATH_GDB)
		@rm -rf analysis.txt gmon.out callgrind.out.* ${PROFILE}
		@echo "\t[ $(RED)✗$(NONE) ] $(OBJ_DIR) directory"
		@make -C ./libft/ clean

fclean: clean
		@rm -f ${NAME} ${PROFILE} ${SANITIZE} ${VALGND} ${CALLGND} ${BDG}
		@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
		@make -C ./libft/ fclean

re: fclean all

.PHONY: all clean fclean re
