#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
  int max_score = 0;
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

  for(int i = 0; i < int(subsequences_a.size()); i++){
    for(int j = 0; j < int(subsequences_b.size()); j++){
      if(int(subsequences_a[i].size()) == int(subsequences_b[j].size())){
        score = calculate_score(subsequences_a[i], subsequences_b[j]);
        if(score > max_score){
          max_score = score;
          subsequence_a = subsequences_a[i];
          subsequence_b = subsequences_b[j];
        }
      // } else if(int(subsequences_a[i].size()) > int(subsequences_b[j].size())) {
      //   greater_sequence = subsequence_a;
      //   minor_sequence = subsequence_b;

      //   for(int i = 0; i < (int(greater_sequence.size()) - int(minor_sequence.size())); i++){
      //     score = calculate_score(minor_sequence, greater_sequence.substr(i, int(minor_sequence.size())));
      //     if(score > max_score){
      //       max_score = score;
      //       subsequence_a = greater_sequence.substr(i, int(minor_sequence.size()));
      //       subsequence_b = minor_sequence;
      //     }
      //   }
      // } else if(int(subsequences_a[i].size()) < int(subsequences_b[j].size())) {
      //   minor_sequence = subsequence_a;
      //   greater_sequence = subsequence_b;

      //   for(int i = 0; i < (int(greater_sequence.size()) - int(minor_sequence.size())); i++){
      //     score = calculate_score(minor_sequence, greater_sequence.substr(i, int(minor_sequence.size())));
      //     if(score > max_score){
      //       max_score = score;
      //       subsequence_a = minor_sequence;
      //       subsequence_b = greater_sequence.substr(i, int(minor_sequence.size()));
      //     }
      //   }
      // }
      }
    }
  }

  cout << "Score: " << max_score << endl;
  cout << "Subsequence A: " << subsequence_a << endl;
  cout << "Subsequence B: " << subsequence_b << endl;

  return 0;
}