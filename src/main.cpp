#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <random>
#include "Simulation.h"

//* Initialiser globalement un générateur de nombres aléatoire
//unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
//default_random_engine generator(seed);
//std::default_random_engine generator(123456789);

void thread_function(std::string path)
{
    std::default_random_engine generator(123456789);
    Simulation Reference(path, generator);
}

int main(int argc, char const *argv[])
{
    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> threads;
      
    //* SI
    threads.push_back(std::thread(thread_function, "./Simulations/SI_Reference/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI_Reference/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI_Reference/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI_Reference/4"));
       
    //* SIR
    threads.push_back(std::thread(thread_function, "./Simulations/SIR_Reference/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR_Reference/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR_Reference/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR_Reference/4"));
    
    for (auto &t : threads)
    {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Le temps total est de : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}