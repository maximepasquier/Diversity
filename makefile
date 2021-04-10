.DEFAULT_GOAL := compile

compile:
	g++ -o ./bin/main ./src/*.cpp -std=c++11
run:
	./bin/main

clear_bin:
	rm ./bin/*

clear_data:
	rm ./data/*
