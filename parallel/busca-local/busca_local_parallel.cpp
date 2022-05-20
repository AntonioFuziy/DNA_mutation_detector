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

  if(n > m){
    string change_a = a;
    a = b;
    b = change_a;
    int change_n = n;
    n = m;
    m = change_n; 
  }

  int current_score;
  int max_score = 0;
  int best_sequence_index = 0;
  int p;
  string subsequence_a;
  vector<string> subsequences_b;

  omp_set_num_threads(4);

  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(1, n);
  int k = distribution(generator);

  int all_episodes = n*m;

  #pragma omp parallel for shared(current_score, best_sequence_index, max_score) firstprivate(subsequence_a, subsequences_b)
  for (int episode = 0; episode < all_episodes; episode++){
    subsequence_a = generate_subsequence(a, k, n);
    // cout << episode << endl;
    p = distribution(generator);

    for(int i = 0; i < p; i++){
      string subsequence_b = generate_subsequence(b, k, m);
      subsequences_b.push_back(subsequence_b);
      current_score = calculate_score(subsequence_a, subsequence_b);

      #pragma omp critical
      {
        if(current_score > max_score){
          max_score = current_score;
          best_sequence_index = i;
        }
      }
    }
  }

  cout << "" << endl;
  cout << "Score: " << max_score << endl;

  cout << "" << endl;
  cout << "Sequence A: " << subsequence_a << endl;
  cout << "Sequence B: " << subsequences_b[best_sequence_index] << endl;

  return 0;
}