include common.mk

CHAPTER_NUMBERS := 2 4 6 7 8 10
CHAPTERS_DIR    := $(addprefix chapter_, $(CHAPTER_NUMBERS))

.PHONY: all clean $(UNITY_DIR) $(CHAPTERS_DIR)

all: $(CHAPTERS_DIR)

$(CHAPTERS_DIR):
	@$(MAKE) -C $@

test clean:
	@for chapter in $(CHAPTERS_DIR); \
	    do                           \
	    $(MAKE) -C $$chapter $@;     \
	    echo;                        \
	    done
