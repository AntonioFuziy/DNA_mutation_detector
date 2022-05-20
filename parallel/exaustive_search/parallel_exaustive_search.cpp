#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <omp.h>

using namespace std;

struct result {
  string a;
  string b;
  int score;
};

// void reportTime(const char* msg, steady_clock::duration span) {
//   auto ms = duration_cast<milliseconds>(span);
//   cout << msg << " - levou - " <<
//   ms.count() << " milisegundos" << endl;
// }

int match(char a, char b){
  if(a == b){
    return 2;
  }
  return -1;
}

int calculate_score(string a, string b){
  int score = 0;
  for(int i = 0; i < int(a.size()); i++){
    score += match(a[i], b[i]);
  }
  return score;
}

vector<string> generate_subsequences(string sequence){
  vector<string> subsequences;

  for(int i = 0; i <= int(sequence.size()); i++){
    for(int j = 1; j <= int(sequence.size()); j++){
      subsequences.push_back(sequence.substr(i, j));
    }
  }

  return subsequences;
}

int main(){
  int n;
  int m;
  string a; 
  string b;
  int score = 0;

  cin >> n >> m;
  cin >> a >> b;

  cout << "A size: " << n << endl;
  cout << "B size: " << m << endl;
  cout << "" << endl;
  cout << "A: " << a << endl;
  cout << "B: " << b << endl;
  cout << "" << endl;

  vector<string> subsequences_a = generate_subsequences(a);
  vector<string> subsequences_b = generate_subsequences(b);

  string subsequence_a;
  string subsequence_b;

  string greater_sequence;
  string minor_sequence;

  vector<result> sequences_result;

  for(int i = 0; i < int(subsequences_a.size()); i++){
    for(int j = 0; j < int(subsequences_b.size()); j++){
      if(int(subsequences_a[i].size()) == int(subsequences_b[j].size())){
        subsequence_a = subsequences_a[i];
        subsequence_b = subsequences_b[j];

        result sequence_result;
        sequence_result.a = subsequence_a;
        sequence_result.b = subsequence_b;
        sequences_result.push_back(sequence_result);
      }
    }
  }

  #pragma omp parallel for
  for (int i = 0; i < int(sequences_result.size()); i++){
    score = calculate_score(sequences_result[i].a, sequences_result[i].b);
    sequences_result[i].score = score;
  }

  result best_sequences;
  best_sequences.score = 0;

  for(int i = 0; i < int(sequences_result.size()); i++){
    if(sequences_result[i].score > best_sequences.score){
      best_sequences = sequences_result[i];
    }
  }

  cout << "Score: " << best_sequences.score << endl;
  
  cout << "Subsequence A: ";
  for (int i = 0; i < int(best_sequences.a.size()); i++){
    cout <<  best_sequences.a[i];
  }
  cout << endl;

  cout << "Subsequence B: ";
  for (int i = 0; i < int(best_sequences.b.size()); i++){
    cout <<  best_sequences.b[i];
  }
  cout << endl;

  return 0;
}