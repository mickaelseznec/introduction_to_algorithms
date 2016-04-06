TEST = test_chapter_8
OBJ  = chapter_8.o
OBJ += $(addprefix $(TEST),.o)

test_chapter_8: $(OBJ) $(DEPS)

clean:
	$(RM) $(TEST) $(OBJ)
