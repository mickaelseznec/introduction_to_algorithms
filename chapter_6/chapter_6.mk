TEST = test_chapter_6
OBJ  = chapter_6.o
OBJ += $(addprefix $(TEST),.o)

test_chapter_6: $(OBJ) $(DEPS)

clean:
	$(RM) $(TEST) $(OBJ)

