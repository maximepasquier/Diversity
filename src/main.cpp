#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>
#include <random>
#include "Simulation.h"

//* Nombre de threads maximum dédiés aux simulations
#define NB_THREADS 8

std::vector<std::mutex> verrous(NB_THREADS);

void thread_function(std::string path)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    Simulation Reference(path, generator);
}

int main(int argc, char const *argv[])
{
    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> threads;

    /*
    //* Positions SI
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Positions/1000mouvements/10000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Positions/1000mouvements/14000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Positions/1000mouvements/17000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Positions/1000mouvements/20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Positions/perfect_mix"));

    //* Divergence
    // SI mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur8/19"));

    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/1000mouvements/densite1sur16/19"));

    // SI mix
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur8/19"));

    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SI/Reference/perfect_mix/densite1sur16/19"));

    // SIR mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur8/19"));

    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/1000mouvements/densite1sur16/19"));

    // SIR mix
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur8/19"));

    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/0"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/5"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/6"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/7"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/9"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/10"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/11"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/12"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/13"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/14"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/15"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/17"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/18"));
    threads.push_back(std::thread(thread_function, "./Simulations/Random_Divergence/SIR/Reference/perfect_mix/densite1sur16/19"));

    //* SI
    // 1000 mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur2/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur2/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur2/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur2/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur4/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur4/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur4/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur4/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur8/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur8/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur8/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur8/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur16/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur16/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur16/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SI/Reference/1000mouvements/densite1sur16/population100000"));

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
    // 1000 mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur2/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur2/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur2/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur2/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur4/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur4/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur4/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur4/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur8/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur8/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur8/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur8/population100000"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur16/population5000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur16/population20000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur16/population50000"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Reference/1000mouvements/densite1sur16/population100000"));

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
    
    //* SIR mouvements
    // perfect mix référence
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/perfect_mix"));
    // mouvements
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/1mouvement"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/10mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/50mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/100mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/200mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/400mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/600mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/800mouvements"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mouvements/1000mouvements"));
    

    // Mutation
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/zero"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/moins1"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/moins2"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/moins3"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/moins4"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Mutation/moins5"));

        

    // Référence au mélange parfait
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/SIR/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite32"));

    */

    for (auto &t : threads)
    {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Le temps total est de : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}