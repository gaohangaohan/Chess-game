CXX = g++

CXXFLAGS = -std=c++14 -Wall -MMD

OBJECTS = main.o piece.o board.o player.o human.o graphicsdisplay.o window.o computer.o LevelTT.o

DEPENDS = ${OBJECTS:.o=.d}

EXEC = chess

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
