# CXX = g++
# CXXFLAGS = -std=c++14 -Wall -MMD
# EXEC = chess
# OBJECTS = chess.o
# DEPENDS = ${OBJECTS:.o=.d} 

# ${EXEC}: ${OBJECTS}
# 	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

# -include ${DEPENDS}

# .PHONY: clean

# clean:
# 	rm ${OBJECTS} ${EXEC} ${DEPENDS}

CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -MMD
EXEC=chess
CCFILES=$(wildcard *.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

# Extra recipe that allows us to delete temporary files by saying
# make clean

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
