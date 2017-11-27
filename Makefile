CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = a4q5
OBJECTS = main.o cell.o grid.o graphicsdisplay.o window.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
