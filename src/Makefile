# -lpanel -lncurses -lmenu

#---== SETTING_GAME ==---#
project_name = s21_tetris
frontend_dir = gui/
backend_dir = brick_game/
sub_frontend_dir = cli
sub_backend_dir = tetris
install_dir = $(project_name)

#---== COMPILER ==---#
CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lncurses
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

#---== COMPILE_RULES ==---#
all: rebuild
# TODO rebuild goal

#---== INSTALL ==---#
install: install_backend install_frontend game.o
	mkdir -p $(install_dir)
# TODO install goal
	@echo "Game install"

install_backend:
	cd $(backend_dir)
	$(MAKE) s21_backend.a target_dir=$(sub_backend_dir)
	cd ..

install_frontend:
	cd $(frontend_dir)
	$(MAKE) s21_frontend.a target_dir=$(sub_backend_dir)
	cd ..

#---== UNINSTALL ==---#
uninstall: uninstall_backend uninstall_frontend
# TODO uninstall goal
	@echo "Game uninstall"

uninstall_backend:
	cd $(backend_dir)
	$(MAKE) clear target_dir=$(sub_backend_dir)
	cd ..

uninstall_frontend:
	cd $(frontend_dir)
	$(MAKE) s21_frontend.a target_dir=$(sub_backend_dir)
	cd ..

#---== TEST ==---#
test: test_backend test_frontend
	@echo "Test complidet"

test_backend:
	@cd $(backend_dir)
	@$(MAKE) test target_dir=$(sub_backend_dir)
	@cd ../..

test_frontend:
	@cd $(frontend_dir)
	@$(MAKE) test target_dir=$(sub_backend_dir)
	@cd ../..


dist:
# TODO dist (tar) goal

#---== CHECK_RULES ==---#
.PHONY: clang-n clang-i
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../materials/linters/.clang-format

clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../materials/linters/.clang-format

# valgrind: val = valgrind
# valgrind: test

#---== REPORT ==---#
gcov_report: gcov_report_backend gcov_report_frontend
	@echo
	@echo "If you want open use: make gcov_open"
	@echo

gcov_report_backend:
	@cd $(backend_dir)
	@$(MAKE) gcov_report target_dir=$(sub_backend_dir)
	@cd ../..

gcov_report_frontend:
	@cd $(frontend_dir)
	@$(MAKE) gcov_report target_dir=$(sub_backend_dir)
	@cd ../..

gcov_open: gcov_open_backend gcov_open_frontend
	@echo
	@echo "Open complet"
	@echo

gcov_open_backend:
	@cd $(backend_dir)
	@$(MAKE) gcov_open target_dir=$(sub_backend_dir)
	@cd ../..

gcov_open_frontend:
	@cd $(frontend_dir)
	@$(MAKE) gcov_open target_dir=$(sub_backend_dir)
	@cd ../..

deps:
	pip install gcovr

dvi:
# TODO dvi (document) goal

#---== CLEAN ==---#
# TODO clean_dvi goal
.PHONY: clean
clean : clean_backend clean_frontend
	@rm -rf $(install_dir)
	
clean_backend:
	@cd $(backend_dir)
	@$(MAKE) clean target_dir=$(sub_backend_dir)
	@cd ../..

clean_frontend:
	@cd $(frontend_dir)
	@$(MAKE) gcov_open target_dir=$(sub_backend_dir)
	@cd ../..