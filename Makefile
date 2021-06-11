CC=g++

STD=-std=c++11

main: main.cpp
	$(CC) $(STD) main.cpp MachineLearning.cpp -o main

clean:
	rm main.o