# src/Makefile

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
AR = ar
ARFLAGS = rcs
RM = rm -f

# Имя библиотеки
LIB_NAME = s21_matrix.a

# Пути
FUNCTIONS_DIR = functions
HELPERS_DIR = functions/helpers
INCLUDES_DIR = include

# Заголовочные файлы
INCLUDES = -I$(INCLUDES_DIR) -I.

# Поиск всех .c файлов
SRCS = $(wildcard $(FUNCTIONS_DIR)/*.c) $(wildcard $(HELPERS_DIR)/*.c)

# Объектные файлы (с сохранением структуры)
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Цель по умолчанию
all: $(LIB_NAME)

# Сборка статической библиотеки
$(LIB_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Компиляция .c в .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Очистка
clean:
	$(RM) $(OBJS) $(LIB_NAME)

# Полная очистка
fclean: clean
	$(RM) -rf report *.gcda *.gcno *.info
	$(MAKE) -C tests clean

# Запуск тестов
test:
	$(MAKE) -C tests test

# Генерация отчёта о покрытии
gcov_report:
	$(MAKE) -C tests gcov_report

# Пересборка
re: fclean all

.PHONY: all clean fclean test gcov_report re valgrind valgrind-verbose valgrind-log