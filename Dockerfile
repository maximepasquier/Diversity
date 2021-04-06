FROM gcc:latest

COPY . /usr/src/cpp_automate

WORKDIR /usr/src/cpp_automate

RUN g++ -o ./bin/main ./src/main.cpp ./src/Humain.cpp ./src/Agent_Pathogene.cpp ./src/node.cpp ./src/Linked_list.cpp ./src/functions.cpp -mcmodel=medium -pthread

CMD [ "./bin/main" ]