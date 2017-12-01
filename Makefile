CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -w
EXEC = a5
OBJECTS = main.o cell.o grid.o piece.o textdisplay.o subject.o levelzero.o levelone.o leveltwo.o levelthree.o levelfour.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
