#---== COMPILER ==---#
CC = gcc
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s
# -lpanel -lncurses -lmenu

#---== SETTING_GAME ==---#
project_name = s21_brick_game_v1
controller_dir = controller
backend_dir = brick_game
frontend_dir = gui
sub_backend_dir = tetris
sub_frontend_dir = cli
install_dir = $(project_name)
import := $(controller_dir)/controller.a $(backend_dir)/tetris.a $(frontend_dir)/gui.a

.PHONY: all rebuild

all: $(project_name)
rebuild: uninstall $(project_name)

$(project_name): $(import)
	$(CC) -L. $(controller_dir)/controller.o $(addprefix -l:, $^) -o $(project_name)

$(backend_dir)/tetris.a:
	$(MAKE) --directory=$(backend_dir) target_dir=$(sub_backend_dir)

$(frontend_dir)/gui.a:
	$(MAKE) --directory=$(frontend_dir) target_dir=$(sub_frontend_dir)

$(controller_dir)/controller.a:
	$(MAKE) --directory=$(controller_dir)

# TODO
#---== INSTALL ==---#
# install: 

#---== UNINSTALL ==---#
uninstall: clean
	@echo "Game uninstall"

#---== TEST ==---#
test:
	$(MAKE) test --directory=$(backend_dir) target_dir=$(sub_backend_dir)
	@echo "Test complidet"

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
gcov_report: gcov_report_backend gcov_report_frontend
	$(MAKE) gcov_report --directory=$(backend_dir) target_dir=$(sub_backend_dir)
	@echo "If you want open use: make gcov_open"

gcov_open: gcov_open_backend gcov_open_frontend
	$(MAKE) gcov_open --directory=$(backend_dir) target_dir=$(sub_backend_dir)
	@echo "Open completed"

deps:
	pip install gcovr

dvi:
# TODO dvi (document) goal

#---== CLEAN ==---#
.PHONY: clean
# TODO clean_dvi goal
clean: clean_backend clean_frontend
	$(MAKE) clean --directory=$(controller_dir)
	@rm -rf s21_brick_game_v1
	
clean_backend:
	@$(MAKE) clean --directory=$(backend_dir) target_dir=$(sub_backend_dir)

clean_frontend:
	@$(MAKE) clean --directory=$(frontend_dir) target_dir=$(sub_frontend_dir)