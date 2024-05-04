#---== COMPILER ==---#
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I.. -I. -pedantic -g
LDFLAGS = -lcheck -lsubunit -lpthread
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

#---== STATIC_VARIABLES ==---#
project_name = common
target_dir = .
bin_dir	= $(target_dir)/bin
bin_sub_dir = release
build_dir = build
func_dir = functions
test_dir = tests
report_dir = $(target_dir)/gcovr-report

lib_name := $(project_name).a
test_lib_name := $(project_name)_test.a
report_name = $(report_dir)/$(project_name).html
import = $(test_lib_name) $(lib_name)

#---= GCOVR + OPEN =---#
GCOVR := $(shell command -v gcovr 2> /dev/null)
ifeq ($(GCOVR),)
    GCOVR := ~/.local/bin/gcovr
endif
REPORTFLAGS = --html-nested --output
OS := $(shell uname -s)
OPEN_CMD := $(if $(filter Linux, $(OS)), xdg-open, open)

#---= DYNAMIC_VARIABLES =---#
find_command = find $(1) -iname "*.c"
depenc_command = $(addprefix $(build_dir)/, $(filter $(1)/%.o, $(obj_list)))
find_command_gcov = find $(1) -iname "*.gcda" -o -iname '*.gcno'

func_source := $(shell $(call find_command, $(func_dir)))
test_source = $(shell $(call find_command, $(test_dir)))
obj_list := $(patsubst %.c, %.o, $(func_source) $(test_source))
gcov_list := $(shell $(call find_command_gcov, $(func_dir)))
dir_list := $(addprefix $(build_dir)/, $(sort $(dir $(func_source) $(test_source))))

#---== COMPILE_RULES ==---#
.PHONY: test 
all: $(lib_name)

test: $(import)

$(lib_name): build $(call depenc_command, $(func_dir))
$(test_lib_name): build $(call depenc_command, $(test_dir))

%.a:
	ar crs $@ $(filter %.o, $?)

$(build_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(if $(filter $(func_dir)/%.c, $^), $(GCOVFLAGS)) $(DEBUG) -c $^ -o $@

debug: DEBUG = -g
debug: bin_sub_dir = debug
debug: clean_obj test

build:
	@$(shell [ ! -w "$(build_dir)" ] && mkdir $(build_dir) )
	@$(shell [ ! -w "$(dir_list)" ] && mkdir $(dir_list) )

bin:
	@$(shell [ ! -w "$(bin_dir)" ] && mkdir $(bin_dir) )
	@$(shell [ ! -w "$(bin_dir)/$(bin_sub_dir)" ] && mkdir $(bin_dir)/$(bin_sub_dir) )

#-----=== CHECK_RULES ===------#
.PHONY: clang-n clang-i
clang-n:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -n -style=file:../../materials/linters/.clang-format

clang-i:
	find . -iname '*.h' -o -iname '*.c' | xargs clang-format -i -style=file:../../materials/linters/.clang-format

valgrind: val = valgrind
valgrind: test

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
	@rm -rf $(obj_list) $(gcov_list)
	@rm -rf $(lib_name) $(test_lib_name)
	@rm -rf $(report_dir) $(build_dir) $(bin_dir)
	@rm -rf $(project_name).o

clean_obj:
	@rm -rf $(addprefix $(build_dir)/, $(filter $(func_dir)/%.o, $(obj_list)))

clean_gcov: clean_obj
	@rm -rf $(report_dir) $(gcov_list)

clean_doc:
	@rm -rf doc/html doc/latex