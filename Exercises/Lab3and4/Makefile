# Compiler and flags
CC = g++
FLAGS = -std=c++20 -w -I ../../GNUplot/ -I /opt/homebrew/include $(shell root-config --cflags)
LIBS = -L /opt/homebrew/lib -lboost_iostreams $(shell root-config --libs)

# Default target builds all executables
all: TestFiniteFunctions CustomFunctions CalculatePi

# TestFiniteFunctions executable
TestFiniteFunctions: TestFiniteFunctions.o FiniteFunctions.o
	@echo "Linking TestFiniteFunctions..."
	${CC} ${FLAGS} TestFiniteFunctions.o FiniteFunctions.o ${LIBS} -o TestFiniteFunctions

TestFiniteFunctions.o: TestFiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} -c TestFiniteFunctions.cxx

# CustomFunctions executable
CustomFunctions: CustomFunctions.o FiniteFunctions.o
	@echo "Linking CustomFunctions..."
	${CC} ${FLAGS} CustomFunctions.o FiniteFunctions.o ${LIBS} -o CustomFunctions

CustomFunctions.o: CustomFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} -c CustomFunctions.cxx

# Common object
FiniteFunctions.o: FiniteFunctions.cxx FiniteFunctions.h
	${CC} ${FLAGS} -c FiniteFunctions.cxx

# CalculatePi executable
CalculatePi: CalculatePi.o FiniteFunctions.o
	@echo "Linking CalculatePi..."
	${CC} ${FLAGS} CalculatePi.o FiniteFunctions.o ${LIBS} -o CalculatePi

CalculatePi.o: CalculatePi.cxx FiniteFunctions.h
	${CC} ${FLAGS} -c CalculatePi.cxx

# Clean object files and backups
clean:
	@rm -f *.o *~

# Delete executables
cleantarget:
	@rm -f TestFiniteFunctions CustomFunctions CalculatePi

