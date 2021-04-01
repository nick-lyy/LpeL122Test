CC = gcc
OBJ = LpeL122Test.o
CFLAGS = -Wall -D_DEBUG -DVERBOSE

LpeL122Test: $(OBJ)
	$(CC) -o $@ $(OBJ) -lLPE_L122 -lMNet
%.o: %.cpp
	$(CC) $< -c $(CFLAGS)

.PHONY: clean
clean:
	rm -f LpeL122Test $(OBJ)

