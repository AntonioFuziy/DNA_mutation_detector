#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <omp.h>

#define MATCH 2
#define MISMATCH -1
#define GAP -1

#define SHOW_REPORT false

int match_score(std::string a, std::string b){
    // a and b must be of equal size
    int score = 0;
    int size = a.length();
    for (int i = 0; i<size; i++){
        if (a[i] == '-' || b[i] == '-'){
            score += GAP;
        } else if (a[i] == b[i]) {
            score += MATCH;
        } else {
            score += MISMATCH;
        }
    }
    return score;
}

int main(){

    // Inputs
    int len_a, len_b;
    std::cin >> len_a;
    std::cin >> len_b;
    std::string a, b;
    std::cin >> a;
    std::cin >> b;

    int size_big, size_small;
    std::string big, small;

    if(len_a > len_b){
        size_big = len_a;
        size_small = len_b;
    } else {
        size_big = len_b;
        size_small = len_a;
    }


    const int NUM_EXPERIMENTS = len_a*len_b;
    int high_score = -9999999;
    std::string best_a, best_b;

    #pragma omp parallel for shared(high_score, best_a, best_b) firstprivate(size_big, size_small, big, small)
    for(int _ = 0; _<NUM_EXPERIMENTS; _++){

        // RNG
        std::random_device generator;

        std::uniform_int_distribution<int> subseq_size_distro(4,size_small);
        std::uniform_int_distribution<int> p_distro(size_small*2,size_big*3); // Run enough times to probably try most combinations

        const int subseq_size = subseq_size_distro(generator);        
        const int p = p_distro(generator);

        // Random subsize
        // std::cout << "Subsequence size: " << subseq_size << std::endl;
        std::uniform_int_distribution<int> index_distro(0,size_small-subseq_size);

        // Assemble substring b
        int i = index_distro(generator);
        std::string base = small.substr(i, subseq_size);

        // Try p combinations
        int max_score = size_big*std::max(MISMATCH, GAP); // Pior score possível é tudo em MISMATCH/GAP, dependendo dos pesos
        
        
        std::string match;
        int ix = 0;
        int score;
        for (int i = 0; i<p; i++){
            ix = index_distro(generator);
            score = match_score(base, big.substr(ix, subseq_size));
            if (score > max_score){
                max_score = score;
                match = big.substr(ix, subseq_size);
            }
        }
        #pragma omp critical
        {
            if(max_score > high_score){
                high_score = max_score;
                best_a = base;
                best_b = match;
            }
        }
    }


    // Output
    if (SHOW_REPORT){
        std::cout << "Sequências: " << std::endl;
        std::cout << best_a << std::endl;
        std::cout << best_b << std::endl << "Score: " << high_score << std::endl;
    } else {
        std::cout << high_score << std::endl;
    }

    return 0;
}