#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <random>
#include <omp.h>
using namespace std;

// #define P 100

struct SubstringValue
{
    string substring;
    int score;
};

int match(char a, char b){
  if(a == b){
    return 2;
  };
  return -1;
}

int calculate_score(string a, string b){
  int score = 0;
  for (int i = 0; i < int(a.size()); i++){
    score += match(a[i], b[i]);
  }

  return score;
}

string create_substring(string seq, int index, int random_size)
{

    string substring;
    while ((substring.size() < random_size) && (index < seq.size()))
    {

        substring.push_back(seq[index]);
        index++;
    }
    return substring;
}

int main()
{
    int n;
    int m;
    cin >> n >> m;

    string a;
    string b;
    cin >> a;
    cin >> b;
    // swap para que o a sempre seje a maior sequência
    if (m > n)
    {
        a.swap(b);
        swap(n, m);
    }
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "Seq a: " << a << endl;
    cout << "Seq b: " << b << endl;
    cout << endl;
    random_device rd;
    unsigned seed = rd();
    default_random_engine generator(seed);

    vector<SubstringValue> sa_best_values_global;
    int global_score = -n; // menor valor possível
    string best_sb;
    int best_k;

#pragma omp parallel for
    for (int rep = 0; rep < 100; rep++)
    {
        uniform_int_distribution<int> distribution_k(1, m);
        int k;
        k = distribution_k(generator);
        // cout<<endl;
        // cout<<"k: "<<k<<endl;
        uniform_int_distribution<int> distribution_b(0, m - k);
        int index_b = distribution_b(generator);
        string sb = create_substring(b, index_b, k);
        // cout<<"Subsequence b: "<<sb<<endl;
        int p = n - k + 1;
        // cout<<"p "<<p<<endl;
        // salvando apenas strings para checar se já há no sa_best_values
        vector<string> all_seqs;
        all_seqs.resize(p);
        vector<SubstringValue> sa_best_values;
        int score = -n;

        for (int i = 0; i < p; i++)
        {

            SubstringValue sa_temp;
            sa_temp.substring = a.substr(i, k);
            // cout<<sa_temp.substring<<" ";

            // int index_a = distribution_a(generator);
            // sa_temp.substring = create_substring(a,index_a,k);
            all_seqs[i] = sa_temp.substring;
            sa_temp.score = calculate_score(sa_temp.substring, sb);
#pragma omp critical
            {
                if (sa_temp.score > score)
                {
                    score = sa_temp.score;
                    sa_best_values.clear();
                    sa_best_values.push_back(sa_temp);
                }
                else if (sa_temp.score == score)
                {
                  sa_best_values.push_back(sa_temp);
                }
                // cout<<sa_temp.substring<<" "<< sa_temp.score<<" | " ;

                if (score > global_score)
                {
                    global_score = score;
                    best_sb = sb;
                    sa_best_values_global = sa_best_values;
                    best_k = k;
                }
            }
        }
    }
    // cout<<"Subsequences a generated and yours scores: [ ";

    // cout<<"]"<<endl<<endl;
    cout << "Best k: " << best_k << endl;
    cout << "Best Subsequence (highers scores) [ ";
    for (int i = 0; i < sa_best_values_global.size(); i++)
    {

        cout << sa_best_values_global[i].substring << " | ";
    }
    cout << "]" << endl;
    cout << "Best Score: " << global_score << endl;
    return 0;
}