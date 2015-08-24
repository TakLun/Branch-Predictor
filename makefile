GXX=g++ -g -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__

all: predictor

predictor: predictor.o
	$(GXX) predictor.o -o predictor
	
predictor.o: predictor.cpp
	$(GXX) -c predictor.cpp
	
clean:
	rm -f *.o *.txt predictor
