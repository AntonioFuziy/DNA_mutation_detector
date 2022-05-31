#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

struct comp_seqs {
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

// int calculate_score(string a, string b){
//   int score = 0;
//   for(int i = 0; i < int(a.size()); i++){
//     score += match(a[i], b[i]);
//   }
//   return score;
// }
int return_index(int a, int b, int c){
  if(a >= b and a >= c and a >= 0){
    return 1;
  } else if(b >= c and b >= 0){
    return 2;
  } else if(c >= 0){
    return 3;
  }
  return 0;
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

int calculate_score(string a, string b, int n, int m, vector<vector<int>> H){
  int max_H = 0;
  int w;
  int diagonal, delecao, insercao, current_index;
  
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      w = match(a[i-1], b[j-1]);
      diagonal = H[i-1][j-1] + w;
      delecao = H[i-1][j] - 1;
      insercao = H[i][j-1] - 1;
      current_index = return_index(diagonal, delecao, insercao);

      if(current_index == 1){
        H[i][j] = diagonal;
      } else if(current_index == 2){
        H[i][j] = delecao;
      } else if(current_index == 3){
        H[i][j] = insercao;
      } 
      else {
        H[i][j] = 0;
      }

      if(H[i][j] > max_H){
        max_H = H[i][j];
      }
    }
  }
  return max_H;
}

int main(){
  int n;
  int m;
  string a; 
  string b;
  int score = 0;
  vector<vector<int>> H;

  cin >> n >> m;
  cin >> a >> b;

  cout << "A size: " << n << endl;
  cout << "B size: " << m << endl;
  cout << "" << endl;
  cout << "A: " << a << endl;
  cout << "B: " << b << endl;
  cout << "" << endl;

  H.resize(n+1);
  for(int i = 0; i < n+1; i++){
    H[i].resize(m+1);
  }
  
  vector<string> subsequences_a = generate_subsequences(a);
  vector<string> subsequences_b = generate_subsequences(b);

  string subsequence_a;
  string subsequence_b;

  string greater_sequence;
  string minor_sequence;

  vector<comp_seqs> sequences_result;

  for(int i = 0; i < int(subsequences_a.size()); i++){
    for(int j = 0; j < int(subsequences_b.size()); j++){
      if(int(subsequences_a[i].size()) == int(subsequences_b[j].size())){
        subsequence_a = subsequences_a[i];
        subsequence_b = subsequences_b[j];

        comp_seqs sequence_result;
        sequence_result.a = subsequence_a;
        sequence_result.b = subsequence_b;
        sequences_result.push_back(sequence_result);
      }
    }
  }

  comp_seqs best_sequences;
  best_sequences.score = 0;
  for (int i = 0; i < int(sequences_result.size()); i++){
    score = calculate_score(sequences_result[i].a, sequences_result[i].b, n, m, H);
    sequences_result[i].score = score;
    if(sequences_result[i].score > best_sequences.score){
      best_sequences = sequences_result[i];
    }
  }

  cout << "Score: " << best_sequences.score << endl;

  return 0;
}