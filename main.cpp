#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct alignment{
  int row; //linha do termo da matriz
  int column; //coluna do termo da matriz
  int direction; //direcao da dos termos da matriz
  int value; //valor armazenado no termo da matriz
};

//funcao que identifica match da base nitrogenada
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

int main(){
  int n, m, w;
  string a, b;
  vector<vector<alignment>> H;

  ofstream output_file;
  output_file.open("output.txt");

  int max_H = 0;
  int max_j = 0;
  int max_i = 0;

  cin >> n;
  cin >> m;
  output_file << "" << endl;
  output_file << "n: " << n << " m: " << m << endl;

  cin >> a;
  cin >> b;
  output_file << "a: " << a << endl; 
  output_file << "b: " << b << endl;

  //inicializando matriz H com zeros
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
        max_i = i;
        max_j = j;
      }
    }
  }
  
  //exibindo a matriz H
  output_file << "" << endl;
  output_file << "Matrix H:" << endl;
  for (int i = 0; i <= n; i++){
    output_file << " " << endl;
    for (int j = 0; j <= m; j++){
      output_file << H[i][j].value << " ";
    }
  }
  output_file << "" << endl;

  //exibindo o score
  output_file << "" << endl;
  output_file << "Score: " << max_H << endl;
  output_file << "" << endl;

  // aplicando o alinhamento
  alignment actual_term;
  string first_sequence, second_sequence;
  
  actual_term.row = max_i;
  actual_term.column = max_j;
  actual_term.direction = H[max_i][max_j].direction;
  actual_term.value = max_H;

  //realizar a subida da matriz até chegar na coluna 0, ou linha 0 ou chegar a um valor zero da matriz
  while(actual_term.row > 0 and actual_term.column > 0 and actual_term.value > 0){
    //caso a direcao seja diagonal
    if(actual_term.direction == 1){
      first_sequence += a[actual_term.row-1];
      second_sequence += b[actual_term.column-1];
      actual_term.row--;
      actual_term.column--;
    } 
    //caso a direcao seja deleção
    else if(actual_term.direction == 2){
      first_sequence += a[actual_term.row-1];
      second_sequence += '-';
      actual_term.row--;
    } 
    //caso a direção seja inserção
    else if(actual_term.direction == 3){
      first_sequence += '-';
      second_sequence += b[actual_term.column-1];
      actual_term.column--;
    }
    //atualiza o valor e a direção
    actual_term.value = H[actual_term.row][actual_term.column].value;
    actual_term.direction = H[actual_term.row][actual_term.column].direction;
  }

  //reverte as sequências, pois as sequências geradas são invertidas quando o alinhamento é calculado de baixo para cima
  reverse(first_sequence.begin(), first_sequence.end());
  reverse(second_sequence.begin(), second_sequence.end());

  output_file << "First Sequence Generation: " << first_sequence << endl;
  output_file << "Second Sequence Generation: " << second_sequence << endl;

  cout << "Go to output.txt file to see the result" << endl;
  output_file.close();

  return 0;
}