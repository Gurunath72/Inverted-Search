OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
inverted_index.exe: $(OBJ)
	gcc -o $@ $^  
clean:
	rm *.o *.exe
