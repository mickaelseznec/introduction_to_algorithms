include ../common.mk

CHAPTER := $(notdir $(CURDIR))

OBJ     := $(CHAPTER).o
OBJ     += test_$(CHAPTER).o

EXE     := test_$(CHAPTER).out

$(EXE): $(OBJ) $(DEPS)
	$(CC) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(OBJ) $(DEPS) $(EXE)

test: $(EXE)
	@./$(EXE)
