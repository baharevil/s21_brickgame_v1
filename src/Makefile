#---== COMPILER ==---#
CC = gcc
LDFLAGS = -lncurses
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

#---== SETTING_GAME ==---#
project_name = s21_brick_game_v1
common_dir = common
controller_dir = controller
backend_dir = brick_game
frontend_dir = gui
sub_backend_dir = tetris
sub_frontend_dir = cli
install_dir = $(project_name)
import := $(controller_dir)/controller.a $(frontend_dir)/gui.a $(backend_dir)/tetris.a $(common_dir)/common.a

.PHONY: all rebuild $(import)

all: $(project_name)
rebuild: uninstall $(project_name)

$(project_name): $(import)
	$(CC) -L. $(controller_dir)/controller.o $(addprefix -l:, $^) $(LDFLAGS) -o $(project_name)

$(backend_dir)/tetris.a:
	$(MAKE) --directory=$(backend_dir) target_dir=$(sub_backend_dir)

$(frontend_dir)/gui.a:
	$(MAKE) --directory=$(frontend_dir) target_dir=$(sub_frontend_dir)

$(controller_dir)/controller.a:
	$(MAKE) --directory=$(controller_dir)

$(common_dir)/common.a:
	$(MAKE) --directory=$(common_dir)

# TODO
#---== INSTALL ==---#
# install: 

#---== UNINSTALL ==---#
uninstall: clean
	@echo "Game uninstall"

#---== TESTS ==---#
test: common_test tetris_test

common_test: LDFLAGS += -lcheck -lsubunit -lm
common_test: $(common_dir)/common.a
	$(MAKE) test --directory=$(common_dir)
	$(CC) -L. $(common_dir)/common_test.a $(addprefix -l:, $^) $(LDFLAGS) -o $@
	@echo "Common test compiled"

tetris_test: LDFLAGS += -lcheck -lsubunit -lm
tetris_test: $(backend_dir)/tetris.a $(common_dir)/common.a
	$(MAKE) test --directory=$(backend_dir) target_dir=$(sub_backend_dir)
	$(CC) -L. $(backend_dir)/tetris_test.a $(addprefix -l:, $^) $(LDFLAGS) -o $@
	@echo "Tetris test compiled"

dist:
# TODO dist (tar) goal

#---== CHECK_RULES ==---#
.PHONY: clang-n clang-i
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../materials/linters/.clang-format

clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../materials/linters/.clang-format

valgrind: $(project_name)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s $(shell pwd)/$(project_name)

#---== REPORT ==---#
gcov_report: LDFLAGS += -lgcov -lcheck -lsubunit -ldl -lm
gcov_report: gcov_report_dir
	$(MAKE) gcov_report --directory=$(backend_dir) target_dir=$(sub_backend_dir)
	$(MAKE) gcov_report --directory=$(common_dir)
	$(CC) -L. $(backend_dir)/tetris_test.a $(backend_dir)/tetris.a $(common_dir)/common.a $(LDFLAGS) -o tetris_test
	@./tetris_test
	@gcovr -r brick_game --html --html-details --html-self-contained -o gcov_report/brick_game.html

gcov_report_dir:
	$(shell [ ! -w report ] && mkdir -p gcov_report) 

deps:
	pip install gcovr

dvi:
# TODO dvi (document) goal

#---== CLEAN ==---#
.PHONY: clean
# TODO clean_dvi goal
clean: clean_backend clean_frontend clean_test clean_gcov_report
	$(MAKE) clean --directory=$(controller_dir)
	$(MAKE) clean --directory=$(common_dir)
	@rm -rf s21_brick_game_v1
# @rm -rf tetris_test
# @rm -rf common_test
# @rm -rf gcov_report
	
clean_backend:
	@$(MAKE) clean --directory=$(backend_dir) target_dir=$(sub_backend_dir)

clean_frontend:
	@$(MAKE) clean --directory=$(frontend_dir) target_dir=$(sub_frontend_dir)

clean_test: clean_common_test clean_tetris_test

clean_common_test:
	@rm -rf common_test

clean_tetris_test:
	@rm -rf tetris_test

clean_gcov_report:
	@rm -rf gcov_report