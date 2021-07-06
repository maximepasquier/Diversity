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

    // charge virale = 1
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/1mouvement/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/1mouvement/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/1mouvement/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/1mouvement/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/10mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/10mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/10mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/10mouvements/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/50mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/50mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/50mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale1/50mouvements/diversite32"));

    // charge virale = 0.75
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/1mouvement/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/1mouvement/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/1mouvement/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/1mouvement/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/10mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/10mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/10mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/10mouvements/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/50mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/50mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/50mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale075/50mouvements/diversite32"));

    // charge virale = 0.50
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/1mouvement/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/1mouvement/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/1mouvement/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/1mouvement/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/10mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/10mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/10mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/10mouvements/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/50mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/50mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/50mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale05/50mouvements/diversite32"));

    // charge virale = 0.25
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/1mouvement/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/1mouvement/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/1mouvement/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/1mouvement/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/10mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/10mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/10mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/10mouvements/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/50mouvements/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/50mouvements/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/50mouvements/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/1sur16/charge_virale025/50mouvements/diversite32"));

    for (auto &t : threads)
    {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Le temps total est de : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}