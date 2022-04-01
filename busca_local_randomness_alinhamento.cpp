#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<fstream>

using namespace std;

struct alignment{
  int row; //linha do termo da matriz
  int column; //coluna do termo da matriz
  int direction; //direcao da dos termos da matriz
  int value; //valor armazenado no termo da matriz
};

int match(char a, char b){
  if(a == b){
    return 2;
  };
  return -1;
}

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

string generate_subsequence_a(string seq_a, int k){
  string sequence_generated;
  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(0, 10);

  int index_a = distribution(generator);
  if(index_a > int(seq_a.size())){
    index_a = seq_a.size();
  }

  cout << "random index for subsequence a: " << index_a << endl;

  while(int(sequence_generated.size()) < k){
    sequence_generated += seq_a[index_a];
    index_a++;
  }

  return sequence_generated;
}

string generate_subsequence_b(string seq_b, int k){
  string sequence_generated;
  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(0, 10);

  int index_b = distribution(generator);
  if(index_b > int(seq_b.size())){
    index_b = seq_b.size();
  }

  cout << "Random index for subsequence b: " << index_b << endl;

  while(int(sequence_generated.size()) < k){
    sequence_generated += seq_b[index_b];
    index_b++;
  }

  return sequence_generated;
}

int calculate_score(string a, string b){
  vector<vector<alignment>> H;
  int n = int(a.size());
  int m = int(b.size());
  int w = 0;
  int max_H = 0;

  H.resize(n+1);
  for(int i = 0; i < n+1; i++){
    H[i].resize(m+1);
  }

  int diagonal, delecao, insercao;
  
  //montando a matriz H
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      //retornando match ou unmatch entre os termos das sequências 
      w = match(a[i-1], b[j-1]);
      //cálculo da diagonal, deleção e inserção
      diagonal = H[i-1][j-1].value + w;
      delecao = H[i-1][j].value - 1;
      insercao = H[i][j-1].value - 1;
      H[i][j].direction = return_index(diagonal, delecao, insercao);
      H[i][j].row = i;
      H[i][j].column = j;

      // diagonal
      if(H[i][j].direction == 1){
        H[i][j].value = diagonal;
      // delecao
      } else if(H[i][j].direction == 2){
        H[i][j].value = delecao;
      // insercao
      } else if(H[i][j].direction == 3){
        H[i][j].value = insercao;
      } 
      // 0
      else {
        H[i][j].value = 0;
      }

      //extraindo os valores máximos da matriz H
      if(H[i][j].value > max_H){
        max_H = H[i][j].value;
      }
    }
  }

  cout << "" << endl;
  cout << "Matrix H:" << endl;
  for (int i = 0; i <= n; i++){
    cout << " " << endl;
    for (int j = 0; j <= m; j++){
      cout << H[i][j].value << " ";
    }
  }
  cout << "" << endl;

  return max_H;
}

int main(){
  int n, m;
  string a, b;

  // ofstream output_file;
  // output_file.open("output_busca_local.txt");

  cin >> n;
  cin >> m;
  cout << "" << endl;
  cout << "n: " << n << " m: " << m << endl;

  cin >> a;
  cin >> b;
  cout << "a: " << a << endl; 
  cout << "b: " << b << endl;

  random_device rd;
  unsigned seed = rd();
  default_random_engine generator(seed);
  uniform_int_distribution<int> distribution(3, 10);
  int k = distribution(generator);
  
  cout << "" << endl;
  cout << "size k of subsequences: " << k << endl;

  string subsequence_a = generate_subsequence_a(a, k);
  cout << "subsequence_a generated: " << subsequence_a << endl;

  int p = distribution(generator);

  vector<string> subsequences_b;
  int best_sequence_index = 0;
  int max_score = 0;

  for(int i = 0; i < p; i++){
    string subsequence_b = generate_subsequence_b(b, k);
    subsequences_b.push_back(subsequence_b);
    int current_score = calculate_score(subsequence_a, subsequence_b);
    if(current_score > max_score){
      max_score = current_score;
      best_sequence_index = i;
    }
    cout << "Current Score: " << current_score << endl;
    cout << "" << endl;
  }

  for(int i = 0; i < p; i++){
    cout << "subsequence_b generated: " << subsequences_b[i] << endl;
  }

  cout << "" << endl;
  cout << "===================================================================" << endl;

  cout << "" << endl;
  cout << "BEST SCORE: " << max_score << endl;
  cout << "INDEX FROM BEST SCORE: " << best_sequence_index << endl;

  cout << "" << endl;
  cout << "Sequence A: " << subsequence_a << endl;
  cout << "Sequence B: " << subsequences_b[best_sequence_index] << endl;

  return 0;
}