.DEFAULT_GOAL := compile

compile:
	g++ -o ./bin/main ./src/*.cpp
run:
	./bin/main

clear_bin:
	rm ./bin/*

clear_data:
	rm ./data/*
