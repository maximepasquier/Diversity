.DEFAULT_GOAL := compile

compile:
	g++ -o ./bin/main ./src/main.cpp ./src/Humain.cpp ./src/Agent_Pathogene.cpp ./src/node.cpp ./src/Linked_list.cpp ./src/functions.cpp -mcmodel=medium -pthread

run:
	./bin/main

clear_bin:
	rm ./bin/*

clear_data:
	rm ./data/*