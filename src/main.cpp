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
    //threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/1"));
    //threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/2"));
    //threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/3"));
    //threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/4"));
       
    //* SIR
    //threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/1"));
    //threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/2"));
    //threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/3"));
    //threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/lowCompatibility/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/lowCompatibility/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/lowCompatibility/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/lowCompatibility/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/lowCompatibility/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/lowCompatibility/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/lowCompatibility/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/lowCompatibility/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/4"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/4"));
    
    
    for (auto &t : threads)
    {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Le temps total est de : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}