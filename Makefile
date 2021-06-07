CC=g++

STD=-std=c++14

main: main.cpp
	$(CC) $(STD) main.cpp MachineLearning.cpp -o main

clean:
	rm main.o