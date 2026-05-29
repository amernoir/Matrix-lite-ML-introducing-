# src/tests/Makefile

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit

# Пути
SRC_DIR = ..
FUNCTIONS_DIR = $(SRC_DIR)/functions
HELPERS_DIR = $(SRC_DIR)/functions/helpers
INCLUDES_DIR = $(SRC_DIR)/include

# Заголовочные файлы
INCLUDES = -I$(INCLUDES_DIR) -I$(SRC_DIR)

# Поиск всех .c файлов библиотеки
LIB_SRCS = $(wildcard $(FUNCTIONS_DIR)/*.c) $(wildcard $(HELPERS_DIR)/*.c)

# Тестовые файлы
TEST_SRC = test_s21_matrix.c
TEST_NAME = test_s21_matrix

all: $(TEST_NAME)

$(TEST_NAME): $(TEST_SRC) $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_SRCS) $(TEST_SRC) -o $(TEST_NAME) $(CHECK_FLAGS)

test: $(TEST_NAME)
	./$(TEST_NAME)

gcov_report: CFLAGS += -fprofile-arcs -ftest-coverage
gcov_report: clean $(TEST_SRC) $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_SRCS) $(TEST_SRC) -o $(TEST_NAME) $(CHECK_FLAGS)
	./$(TEST_NAME)
	lcov -t "$(TEST_NAME)" -o $(TEST_NAME).info -c -d $(SRC_DIR)
	genhtml -o report $(TEST_NAME).info
	rm -f *.gcda *.gcno

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_s21_matrix

valgrind-verbose: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./$(TARGET)

valgrind-log: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind_$$(date +%Y%m%d_%H%M%S).log ./$(TARGET)

# Проверка только утечек (быстрая)
valgrind-quick: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: valgrind valgrind-verbose valgrind-log valgrind-quick
clean:
	rm -f $(TEST_NAME) *.gcda *.gcno *.info
	rm -rf report/

.PHONY: all test clean gcov_report