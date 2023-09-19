# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 15:01:56 by tsomchan          #+#    #+#              #
#    Updated: 2023/09/19 15:01:58 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	get_next_line.a
INC		=	get_next_line.h
SRCS 	=	get_next_line.c get_next_line_utils.c $(TEST)
# SRCS_B	=	$(SRCS:.c=_bonus.c)
OBJS	=	$(SRCS:.c=.o)
# OBJS_B	=	$(SRCS_B:.c=.o)
# AR		=	ar rc
CC		=	cc -g
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
TEST	=	main.c

OBJS_PTH	=	objs/

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
#	$(AR) $@ $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJS_PTH), $@)

clean:
	$(RM) $(OBJS) #$(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJS_B)
	$(AR) $(NAME) $^

.PHONY = all clean fclean re #bonus

#	my additional rules
clear:
	clear

NORM	= $(filter-out $(TEST), $(SRCS)) $(INC)

norm: clear
	norminette $(NORM)
	norminette --version

log: clear
	git log --name-status -2

clean_more:
	rm -f $(NAME)
	rm -f .DS_Store
	rm -f main.a

.PHONY += clear norm log clean_more

#	git
push:
	git push
	clear && git log --name-status -1

git_add:
	git add .
ifdef m
	git commit -m "$(m)"
endif

git: git_add push

.PHONY += push git_add git

#	testers
USER_PTH	=	/Users/tsomchan/
PROJECT_PTH	=	$(USER_PTH)github/libft/
TESTER_PTH	=	$(USER_PTH)testers/
TRI			=	$(TESTER_PTH)Tripouille/

tri:
ifdef v
	make $(v) -C $(TRI)
else
	make -C $(TRI)
endif

testers: tri

.PHONY += tri testers

#	clone to send for submission
# CLONE_PTH	=	$(USER_PTH)projects/libft/

# clone_all:
# 	cp $(SRCS) -c $(addprefix $(CLONE_PTH), $(SRCS))
# 	cp $(SRCS_B) -c $(addprefix $(CLONE_PTH), $(B_SRCS))
# 	cp libft.h -c $(addprefix $(CLONE_PTH), libft.h)

#	my testing rules
# T_PTH		=	testing/
# MYFT		=	$(addprefix $(T_PTH), coloring.c cosmetic.c result_compare.c \
# 			result_output.c result_text.c)
# T_HEADER	=	$(SRCS) $(SRCS_B) $(MYFT)
# T_SRCS		=	testing/main.c $(T_HEADER)
# T_SRCS		+=	$(addprefix $(T_PTH)test_, atoi.c bzero.c calloc.c isalnum.c \
# 			isalpha.c isascii.c isdigit.c isprint.c itoa.c memchr.c memcmp.c \
# 			memcpy.c memmove.c memset.c putchar_fd.c putendl_fd.c putnbr_fd.c \
# 			putstr_fd.c split.c strchr.c strdup.c striteri.c strjoin.c \
# 			strlcat.c strlcpy.c strlen.c strmapi.c strncmp.c strnstr.c \
# 			strrchr.c strtrim.c substr.c tolower.c toupper.c)
# T_SRCS		+=	$(addprefix $(T_PTH)test_, lstnew.c lstadd_front.c lstsize.c \
# 			lstlast.c lstadd_back.c lstdelone.c lstiter.c lstmap.c)
# T_NAME		=	main.a

# test:
# 	$(CC) $(CFLAGS) -g $(T_SRCS) -o $(T_NAME)
# 	clear
# ifdef v
# 	./$(T_NAME) $(v)
# 	norminette ft_$(v).c
# else
# 	./$(T_NAME)
# endif

# val:
# 	$(CC) $(CFLAGS) $(T_SRCS) -o $(T_NAME)
# 	clear
# ifdef v
# 	valgrind ./$(T_NAME) $(v)
# 	norminette ft_$(v).c
# else
# 	valgrind ./$(T_NAME)
# endif

# .PHONY += test val 
