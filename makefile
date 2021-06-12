.DEFAULT_GOAL := compile

compile:
	g++ -o ./bin/main -I ./include ./src/*.cpp -std=c++11 -pthread
run:
	./bin/main

clear_bin:
	rm ./bin/*

clear_data:
	rm ./data/*
