# Target to run the compiled binary
run: chess
	./chess

# Build the final executable
chess: global.o setting.o options.o delay.o board_controller.o\
    bishop.o king.o knight.o pawn.o queen.o rook.o main.o
	gcc -o chess global.o setting.o options.o delay.o board_controller.o \
    bishop.o king.o knight.o pawn.o queen.o rook.o main.o -Iheaders

# Object file for the main program
main.o: main.c headers/global.h headers/pieces/pieces.h \
    headers/utilities/setting.h headers/utilities/options.h
	gcc -c main.c -Iheaders

global.o: global.c headers/global.h
	gcc -c global.c -Iheaders

# Object files for utilities
setting.o: utilities/setting.c headers/utilities/setting.h headers/global.h
	gcc -c utilities/setting.c -Iheaders

options.o: utilities/options.c headers/utilities/options.h headers/global.h
	gcc -c utilities/options.c -Iheaders

delay.o: utilities/delay.c headers/utilities/delay.h
	gcc -c utilities/delay.c

board_controller.o: utilities/board_controller.c headers/utilities/board_controller.h headers/global.h
	gcc -c utilities/board_controller.c -Iheaders

# Object files for pieces
bishop.o: pieces/bishop.c headers/pieces/bishob.h headers/global.h
	gcc -c pieces/bishop.c -Iheaders

king.o: pieces/king.c headers/pieces/king.h headers/global.h
	gcc -c pieces/king.c -Iheaders

knight.o: pieces/knight.c headers/pieces/knight.h headers/global.h
	gcc -c pieces/knight.c -Iheaders

pawn.o: pieces/pawn.c headers/pieces/pawn.h headers/global.h
	gcc -c pieces/pawn.c -Iheaders

queen.o: pieces/queen.c headers/pieces/queen.h headers/global.h
	gcc -c pieces/queen.c -Iheaders

rook.o: pieces/rook.c headers/pieces/rook.h headers/global.h
	gcc -c pieces/rook.c -Iheaders


# Clean up generated files
clean:
	rm -f main.o setting.o options.o delay.o global.o board_controller.o\
    bishop.o king.o knight.o pawn.o queen.o rook.o
