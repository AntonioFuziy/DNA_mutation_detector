#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<fstream>
#include<omp.h>

using namespace std;

int match(char a, char b){
  if(a == b){
    return 2;
  }
  return -1;
}

string generate_subsequence(string seq, int k, int n_m){
  string sequence_generated;
  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(0, n_m-k);

  int index = distribution(generator);
  if(index > int(seq.size())){
    index = seq.size();
  }

  while(int(sequence_generated.size()) < k){
    sequence_generated += seq[index];
    index++;
  }

  return sequence_generated;
}

int calculate_score(string a, string b){
  int score = 0;
  for (int i = 0; i < int(a.size()); i++){
    score += match(a[i], b[i]);
  }

  return score;
}

int main(){
  int n, m;
  string a, b;

  cin >> n;
  cin >> m;

  cin >> a;
  cin >> b;

  int current_score;
  int max_score = 0;
  int p, k;
  string subsequence_a, subsequence_b;
  string best_subsequence_a, best_subsequence_b;

  omp_set_num_threads(4);

  if(n > m){
    string change_a = a;
    a = b;
    b = change_a;
    int change_n = n;
    n = m;
    m = change_n; 
  }

  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution_n(1, n);
  uniform_int_distribution<int> distribution_m(1, m);
  uniform_int_distribution<int> distribution;
  int all_episodes = n*m;

  for(int episode = 0; episode < 100; episode++){
    if(n > m){
      distribution = distribution_n;
    } else {
      distribution = distribution_m;
    }

    k = distribution(generator);

    #pragma omp parallel for shared(max_score, best_subsequence_a, best_subsequence_b) firstprivate(a, b, subsequence_a, subsequence_b)
    for (int episode = 0; episode < all_episodes; episode++){
      subsequence_a = generate_subsequence(a, k, n);
      cout << "subsequence_a: " << subsequence_a << endl;
      p = distribution(generator);
      cout << "p: " << p << endl;

      for(int i = 0; i < p; i++){
        subsequence_b = generate_subsequence(b, k, m);
        // subsequences_b.push_back(subsequence_b);
        cout << "subsequence_b: " << subsequence_b << endl;
        current_score = calculate_score(subsequence_a, subsequence_b);

        for(int j = 0; j < k; j++){
          #pragma omp critical
          {
            if(current_score > max_score){
              cout << "New max: " << current_score << endl;
              max_score = current_score;
              best_subsequence_a = subsequence_a;
              best_subsequence_b = subsequence_b;
            }
          }
        }
      }
    }
  }

  cout << "" << endl;
  cout << "Score: " << max_score << endl;

  cout << "" << endl;
  cout << "Sequence A: " << best_subsequence_a << endl;
  cout << "Sequence B: " << best_subsequence_b << endl;

  return 0;
}