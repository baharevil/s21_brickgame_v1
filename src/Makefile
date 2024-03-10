# TODO: all, install, uninstall, clean, dvi, dist
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


#---== INSTALL ==---#
install: install_backend install_frontend game.o
	mkdir -p $(install_dir)
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

#---== CHECK_RULES ==---#
.PHONY: clang-n clang-i
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../materials/linters/.clang-format

clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../materials/linters/.clang-format

valgrind: val = valgrind
valgrind: test

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

#---== CLEAN ==---#
.PHONY: clean clean_gcov clean_obj clean_doc
clean: clean_doc
	@rm -rf $(obj_list) $(gcov_list)
	@rm -rf $(lib_name) $(test_lib_name) test
	@rm -rf $(report_dir) $(build_dir) $(bin_dir)

clean_obj:
	@rm -rf $(addprefix $(build_dir)/, $(filter $(func_dir)/%.o, $(obj_list)))

clean_gcov: clean_obj
	@rm -rf $(report_dir) $(gcov_list)

clean_doc:
	@rm -rf doc/html doc/latex