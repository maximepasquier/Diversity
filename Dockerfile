FROM gcc:latest

COPY . /usr/src/cpp_automate

WORKDIR /usr/src/cpp_automate

RUN g++ -o ./bin/main -I ./include ./src/*.cpp -std=c++11 -pthread

CMD [ "./bin/main" ]