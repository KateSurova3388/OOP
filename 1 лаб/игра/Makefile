CC := g++-12
CFLAGS := 
TARGET := game
TAGET_TEST := test
OBJECTS := obj/field.o obj/ship.o obj/manager.o obj/cell.o obj/main.o
OBJDIR := obj

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)

.PHONY: clean
