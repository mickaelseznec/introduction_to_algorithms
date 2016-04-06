TEST = test_chapter_7
OBJ  = chapter_7.o
OBJ += $(addprefix $(TEST),.o)

test_chapter_7: $(OBJ) $(DEPS)

clean:
	$(RM) $(TEST) $(OBJ)
