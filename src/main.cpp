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
    // 5000 mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur2/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur2/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur2/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur2/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur4/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur4/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur4/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur4/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur8/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur8/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur8/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur8/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur16/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur16/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur16/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/5000mouvements/densite1sur16/population100000"));

    // Mélange parfait
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur2/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur2/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur2/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur2/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur4/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur4/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur4/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur4/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur8/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur8/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur8/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur8/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur16/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur16/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur16/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/perfect_mix/densite1sur16/population100000"));
       
    //* SIR
    // 5000 mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur2/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur2/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur2/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur2/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur4/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur4/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur4/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur4/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur8/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur8/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur8/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur8/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur16/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur16/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur16/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/5000mouvements/densite1sur16/population100000"));

    // Mélange parfait
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur2/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur2/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur2/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur2/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur4/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur4/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur4/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur4/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur8/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur8/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur8/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur8/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur16/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur16/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur16/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/perfect_mix/densite1sur16/population100000"));

    // Diversité
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/diversite5"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/diversite10"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/diversite15"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/mediumCompatibility/diversite20"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/diversite5"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/diversite10"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/diversite15"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/perfect_mix/highCompatibility/diversite20"));

    // Mutation
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/mutation3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/mutation4"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/mutation5"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/mediumCompatibility/mutation6"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/mutation3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/mutation4"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/mutation5"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/perfect_mix/highCompatibility/mutation6"));
    
    
    for (auto &t : threads)
    {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Le temps total est de : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}