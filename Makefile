CC = gcc
CWARN = all extra error
INCLUDES = $(abspath unity) $(abspath utils)
CFLAGS =  $(addprefix -W, $(CWARN)) $(addprefix -I, $(INCLUDES)) -std=gnu99

CHAPTER_NUMBERS = 2 4
CHAPTERS = $(addprefix chapter_, $(CHAPTER_NUMBERS))
CLEAN_CHAPTERS = $(addprefix clean_, $(CHAPTERS))

UNITY_DIR = unity
UNITY_OBJ = $(addprefix $(abspath unity)/, unity.o)

UTILS_DIR = utils
UTILS_OBJ = $(addprefix $(abspath utils)/, utils.o)

DEPS = $(UNITY_OBJ) $(UTILS_OBJ)

export CC
export CFLAGS
export DEPS

.PHONY: all clean $(UNITY_DIR) $(CHAPTERS) $(CLEAN_CHAPTERS) chapter_2

all: unity utils $(CHAPTERS)

unity:
	@$(MAKE) -C $(UNITY_DIR) -f $@.mk

utils:
	@$(MAKE) -C $(UTILS_DIR) -f $@.mk

$(CHAPTERS):
	@$(MAKE) -C $@ -f $@.mk

$(CLEAN_CHAPTERS):
	@$(MAKE) -C $(subst clean_,,$@) -f $(subst clean_,,$@).mk clean

clean: $(CLEAN_CHAPTERS)
	@$(MAKE) -C $(UNITY_DIR) -f $(UNITY_DIR).mk clean
	@$(MAKE) -C $(UTILS_DIR) -f $(UTILS_DIR).mk clean
