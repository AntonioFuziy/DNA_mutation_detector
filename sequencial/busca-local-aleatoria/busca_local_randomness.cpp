#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<fstream>

using namespace std;

int match(char a, char b){
  if(a == b){
    return 2;
  };
  return -1;
}

string generate_subsequence_a(string seq_a, int k, int n){
  string sequence_generated;
  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(0, n-k);

  int index_a = distribution(generator);
  if(index_a > int(seq_a.size())){
    index_a = seq_a.size();
  }

  // cout << "Random index for subsequence A: " << index_a << endl;

  while(int(sequence_generated.size()) < k){
    sequence_generated += seq_a[index_a];
    index_a++;
  }

  return sequence_generated;
}

string generate_subsequence_b(string seq_b, int k, int m){
  string sequence_generated;
  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(0, m-k);

  int index_b = distribution(generator);
  if(index_b > int(seq_b.size())){
    index_b = seq_b.size();
  }

  // cout << "Random index for subsequence B: " << index_b << endl;

  while(int(sequence_generated.size()) < k){
    sequence_generated += seq_b[index_b];
    index_b++;
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

  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(1, n);
  int k = distribution(generator);

  string subsequence_a = generate_subsequence_a(a, k, n);

  int p = distribution(generator);

  vector<string> subsequences_b;
  int best_sequence_index = 0;
  int max_score = 0;

  for(int i = 0; i < p; i++){
    string subsequence_b = generate_subsequence_b(b, k, m);
    subsequences_b.push_back(subsequence_b);
    int current_score = calculate_score(subsequence_a, subsequence_b);
    if(current_score > max_score){
      max_score = current_score;
      best_sequence_index = i;
    }
  }

  cout << "" << endl;
  cout << "Score: " << max_score << endl;

  cout << "" << endl;
  cout << "Sequence A: " << subsequence_a << endl;
  cout << "Sequence B: " << subsequences_b[best_sequence_index] << endl;

  return 0;
}