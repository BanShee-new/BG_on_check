CC = gcc -g -Wall -Wextra -Werror

BACK = brick_game/
FRONT = gui/
MAIN = brick_game/tetris.c
TARGET = tetris

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN = xdg-open
else
	CHECK_FLAGS = -lcheck
	OPEN = open
endif

BACK_SOURCES = $(filter-out $(MAIN), $(wildcard $(BACK)*.c))
BACK_OBJECTS = $(BACK_SOURCES:.c=.o)

FRONT_SOURCES = $(wildcard $(FRONT)*.c)
FRONT_OBJECTS = $(FRONT_SOURCES:.c=.o)

all: clean install

$(TARGET): backend.o gui.o main.o
	@$(CC) $^ -lncurses -o $@

install: $(TARGET) 
	@rm -rf *.o
	@echo " - - - - - - - - - - - - - - - - - - - - - "
	@echo "        Установка прошла успешно.          "
	@echo "  Введите 'make run' чтоб запустить игру   "
	@echo " - - - - - - - - - - - - - - - - - - - - - "

run: 
	@./tetris

uninstall: clean
	@rm -f $(TARGET)

dvi: 
	@cd dvi && doxygen
	@$(OPEN) dvi/html/index.html

test: backend.o
	@checkmk clean_mode=1 tests/*.check > tests/test.c 
	@$(CC) tests/test.c backend.o $(CHECK_FLAGS) -o test
	@./test

gcov_report: clean test 
	@$(CC) -coverage $(BACK_SOURCES) tests/test.c -o gcovreport $(CHECK_FLAGS)
	@./gcovreport
	@lcov -t "gcovreport" -o gcovreport.info -c -d .
	@genhtml -o report gcovreport.info
	@$(OPEN) report/./index.html

main.o: $(MAIN)
	@$(CC) -c $< -o $@


backend.o: $(BACK_OBJECTS)
	@ld -r $^ -o $@

gui.o: $(FRONT_OBJECTS)
	@ld -r $^ -o $@

%.o: %.c
	@$(CC) -c $< -o $@

valgrind_test: test
	valgrind --tool=memcheck --leak-check=full ./test

valgrind_tetris: all
	valgrind --tool=memcheck --leak-check=full ./tetris

clean: clean_tetris clean_tests clean_dvi
	@echo "Программа успешно удалена"

clean_tetris:
	@rm -rf gui/*.o brick_game/*.o *.o *.a

clean_tests:
	@rm -rf  *.dSYM *.gcda *.gcno gcov* report test tests/*.c

clean_dvi:
	@rm -rf dvi/html

rebuild: clean all

.PHONY: dvi