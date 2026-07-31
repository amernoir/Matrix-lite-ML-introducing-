CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g -fPIC
AR = ar
ARFLAGS = rcs
RM = rm -f

LIB_NAME = s21_matrix.a
LIB_SO = s21_matrix.so

FUNCTIONS_DIR = functions
HELPERS_DIR = functions/helpers
INCLUDES_DIR = include

INCLUDES = -I$(INCLUDES_DIR) -I.

SRCS = $(wildcard $(FUNCTIONS_DIR)/*.c) $(wildcard $(HELPERS_DIR)/*.c)
SRCS_NO_MAIN = $(filter-out $(FUNCTIONS_DIR)/main.c, $(SRCS))

OBJS = $(patsubst %.c,%.o,$(SRCS_NO_MAIN))
OBJS_ALL = $(patsubst %.c,%.o,$(SRCS))

BLAS_CFLAGS = -DHAVE_BLAS
BLAS_LDFLAGS = -lcblas -lopenblas

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(LIB_SO): $(OBJS)
	$(CC) -shared -o $@ $^ $(BLAS_LDFLAGS) -lm

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_ALL) $(LIB_NAME) $(LIB_SO)

fclean: clean

re: fclean all

.PHONY: all clean fclean re blas
