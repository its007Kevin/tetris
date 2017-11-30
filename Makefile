CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -w
EXEC = a5
OBJECTS = main.o cell.o grid.o piece.o textdisplay.o subject.o levelzero.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
