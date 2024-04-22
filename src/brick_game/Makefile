#---== STATIC_VARIABLES ==---#
project_name = tetris
target_dir = 
bin_dir	= $(target_dir)/bin
bin_sub_dir = realese
build_dir = $(target_dir)/build
func_dir = $(target_dir)/functions
test_dir = $(target_dir)/tests
report_dir = $(target_dir)/gcovr-report

lib_name := $(project_name).a
report_name := $(report_dir)/$(project_name).html
test_lib_name := $(test_dir)/$(project_name)_test.a
import := $(test_lib_name) $(lib_name)

#---== COMPILER ==---#
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I.. -I./$(target_dir) -pedantic -g
LDFLAGS = -lcheck -lsubunit -lpthread
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

#---= GCOVR + OPEN =---#
GCOVR := $(shell command -v gcovr 2> /dev/null)
GCOVR ?= ~/.local/bin/gcovr
REPORTFLAGS = --coverage -lgcov --html-nested --output
OS := $(shell uname -s)
OPEN_CMD := $(if $(filter Linux, $(OS)), xdg-open, open)

#---= DYNAMIC_VARIABLES =---#
find_command = find $(1) -iname "*.c"
depenc_command = $(addprefix $(build_dir)/, $(filter $(1)/%.o, $(obj_list)))

func_source := $(shell $(call find_command, $(func_dir)))
test_source = $(shell $(call find_command, $(test_dir)))
obj_list := $(patsubst %.c, %.o, $(func_source) $(test_source))
dir_list := $(addprefix $(build_dir)/, $(sort $(dir $(func_source) $(test_source))))

#---== COMPILE_RULES ==---#
# SUPPORT
.PHONY: test 
all: $(lib_name)

debug: DEBUG = -g
debug: bin_sub_dir = debug
debug: clean_obj test

build:
	@mkdir -p $(build_dir) $(dir_list)

bin:
	@mkdir -p $(bin_dir) $(bin_dir)/$(bin_sub_dir)

# MAIN
test: bin $(import)
	$(CC) -o $(bin_dir)/$(bin_sub_dir)/$@ -pipe -L. $(addprefix -l:, $(import)) $(LDFLAGS)
	@$(if $(filter valgrind, $(val)), CK_FORK=no $(val) $(VALFLAGS)) $(bin_dir)/$(bin_sub_dir)/$@

$(lib_name): $(call depenc_command, $(func_dir))
$(test_lib_name): $(call depenc_command, $(test_dir))
%.a: build
	ar crs $@ $(filter %.o, $?)

$(build_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(if $(filter $(func_dir)/%.c, $^), $(GCOVFLAGS)) $(DEBUG) -c $^ -o $@

#-----=== CHECK_RULES ===------#
.PHONY: clang-n clang-i
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../../materials/linters/.clang-format

clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../../materials/linters/.clang-format

val: val = valgrind
val: test

#---== REPORT ==---#
gcov_report: GCOVFLAGS = -fprofile-arcs -ftest-coverage
gcov_report: LDFLAGS += -lgcov
gcov_report: clean_gcov test
	@mkdir $(report_dir)
	$(GCOV) $(REPORTFLAGS) $(report_name)

gcov_open:
	$(OPEN_CMD) $(report_name)

doc:
	doxygen doc/doc_config
	$(OPEN_CMD) doc/html/index.html

#---== CLEAN ==---#
.PHONY: clean clean_gcov clean_obj clean_doc
clean: clean_doc
	@rm -rf $(obj_list) 
	@rm -rf $(lib_name) $(test_lib_name) test
	@rm -rf $(report_dir) $(build_dir) $(bin_dir)

clean_obj:
	@rm -rf $(addprefix $(build_dir)/, $(filter $(func_dir)/%.o, $(obj_list)))

clean_gcov: clean_obj
	@rm -rf $(report_dir)

clean_doc:
	@rm -rf doc/html doc/latex