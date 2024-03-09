# ! TODO: CLEAN TEST 

#---== STATIC_VARIABLES ==---#
project_name = s21_backend
target_dir = 
build_dir = $(target_dir)/build
func_dir = $(target_dir)/function
test_dir = $(target_dir)/tests
report_dir = $(target_dir)/gcovr-report

#---== COMPILER ==---#
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I. -pedantic
LDFLAGS = -lcheck -lsubunit -lm
VALFLAGS = --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes -s

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
find_command_gcov = find $(1) -iname "*.gcda" -o -iname '*.gcno'
depenc_command = $(addprefix $(build_dir)/, $(filter $(1)/%.o, $(obj_list)))

report_name = $(report_dir)/$(project_name).html
lib_name := $(project_name).a
test_lib_name := $(test_dir)/$(project_name)_test.a

func_source := $(shell $(call find_command, $(func_dir)))
test_source = $(shell $(call find_command, $(test_dir)))
obj_list := $(patsubst %.c, %.o, $(func_source) $(test_source))
gcov_list := $(shell $(call find_command_gcov, $(func_dir)))
dir_list := $(addprefix $(build_dir)/, $(sort $(dir $(func_source) $(test_source))))

#---== COMPILE_RULES ==---#
.PHONY: test 
all: $(lib_name)

test:

$(lib_name): $(call depenc_command, $(func_dir))
$(test_lib_name): $(call depenc_command, $(test_dir))
%.a: build
	ar crs $@ $(filter %.o, $?)

build:
	@echo $(dir_list)
	@mkdir $(build_dir)
	@mkdir $(dir_list)

$(build_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(if $(filter $(func_dir)/%.c, $^), $(GCOVFLAGS)) $(DEBUG) -c $^ -o $@

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
	@rm -rf $(lib_name) $(test_lib_name) test
	@rm -rf $(report_dir) $(build_dir) $(bin_dir)

clean_obj:
	@rm -rf $(addprefix $(build_dir)/, $(filter $(func_dir)/%.o, $(obj_list)))

clean_gcov: clean_obj
	@rm -rf $(report_dir) $(gcov_list)

clean_doc:
	@rm -rf doc/html doc/latex