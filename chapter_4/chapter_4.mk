TEST = test_chapter_4
OBJ  = chapter_4.o
OBJ += $(addprefix $(TEST),.o)

test_chapter_4: $(OBJ) $(DEPS)

clean:
	$(RM) $(TEST) $(OBJ)
