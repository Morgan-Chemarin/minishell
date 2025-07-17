NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
HEADER      = libft.h

SRCS        = ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c split.c ft_strdup.c \
				ft_strjoin.c ft_strlen.c ft_strcmp.c ft_strchr.c ft_substr.c ft_putstr.c ft_memset.c \
				ft_itoa.c ft_strndup.c ft_isspace.c ft_strtrim.c ft_strlcpy.c ft_putstr_fd.c


OBJDIR      = obj
OBJS        = $(SRCS:%.c=$(OBJDIR)/%.o)

MAKEFLAGS   += --no-print-directory

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(OBJDIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus