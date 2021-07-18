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

    threads.push_back(std::thread(thread_function, "./Simulations/Mutation/ImmunisationGroupe/zero"));
    threads.push_back(std::thread(thread_function, "./Simulations/Mutation/ImmunisationGroupe/moins1"));
    threads.push_back(std::thread(thread_function, "./Simulations/Mutation/ImmunisationGroupe/moins2"));
    threads.push_back(std::thread(thread_function, "./Simulations/Mutation/ImmunisationGroupe/moins3"));
    threads.push_back(std::thread(thread_function, "./Simulations/Mutation/ImmunisationGroupe/moins4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Mutation/ImmunisationGroupe/moins5"));

    

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite32"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite4"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite8"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite16"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite32"));
    
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite20"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite24"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite28"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite20"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite24"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite28"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite20"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite24"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite28"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite20"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite24"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite28"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite36"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite40"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale1/diversite1000"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite20"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite24"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite28"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite36"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite40"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale075/diversite1000"));

    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite20"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite24"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite28"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite36"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite40"));
    threads.push_back(std::thread(thread_function, "./Simulations/Diversite/PandemiePartielle/perfect_mix/charge_virale05/diversite1000"));

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