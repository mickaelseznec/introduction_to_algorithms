TEST = test_chapter_2
OBJ  = chapter_2.o
OBJ += $(addprefix $(TEST),.o)

test_chapter_2: $(OBJ) $(DEPS)

clean:
	$(RM) $(TEST) $(OBJ)
