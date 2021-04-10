FROM gcc:latest

COPY . /usr/src/cpp_automate

WORKDIR /usr/src/cpp_automate

RUN g++ -o ./bin/main ./src/*.cpp -std=c++11

CMD [ "./bin/main" ]