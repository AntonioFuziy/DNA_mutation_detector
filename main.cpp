#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct alignment{
  int row;
  int column;
  int direction;
  int value;
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

void show_matrix(vector<vector<alignment>> H, int n, int m){
  cout << "" << endl;
  cout << "Matrix H:" << endl;
  for (int i = 0; i <= n; i++){
    cout << " " << endl;
    for (int j = 0; j <= m; j++){
      cout << H[i][j].value << " ";
    }
  }
  cout << "" << endl;
}

int main(){
  int n, m, w;
  string a, b;
  vector<vector<alignment>> H;

  int max_H = 0;
  int max_j = 0;
  int max_i = 0;

  cin >> n;
  cin >> m;
  cout << "" << endl;
  cout << "n: " << n << " m: " << m << endl;

  cin >> a;
  cin >> b;
  cout << "a: " << a << endl; 
  cout << "b: " << b << endl;

  //inicializando matriz H com zeros
  H.resize(n+1);
  for(int i = 0; i < n+1; i++){
    H[i].resize(m+1);
  }

  int diagonal, delecao, insercao;
  //montando a matriz H
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      w = match(a[i-1], b[j-1]);
      diagonal = H[i-1][j-1].value + w;
      delecao = H[i-1][j].value - 1;
      insercao = H[i][j-1].value - 1;
      H[i][j].direction = return_index(diagonal, delecao, insercao);
      H[i][j].row = i;
      H[i][j].column = j;
      if(H[i][j].direction == 1){
        H[i][j].value = diagonal;
      } else if(H[i][j].direction == 2){
        H[i][j].value = delecao;
      } else if(H[i][j].direction == 3){
        H[i][j].value = insercao;
      } else {
        H[i][j].value = 0;
      }

      if(H[i][j].value > max_H){
        max_H = H[i][j].value;
        max_i = i;
        max_j = j;
      }
    }
  }
  
  //exibindo a matriz H
  show_matrix(H, n, m);

  //exibindo o score
  cout << "" << endl;
  cout << "Score: " << max_H << endl;
  cout << "" << endl;

  // aplicando o alinhamento
  alignment actual_term;
  string first_sequence, second_sequence;

  actual_term.row = max_i;
  actual_term.column = max_j;
  actual_term.direction = H[max_i][max_j].direction;
  actual_term.value = max_H;

  while(actual_term.row > 0 and actual_term.column > 0 and actual_term.value > 0){
    if(actual_term.direction == 1){
      first_sequence += a[actual_term.row-1];
      second_sequence += b[actual_term.column-1];
      actual_term.row--;
      actual_term.column--;
    } else if(actual_term.direction == 2){
      first_sequence += a[actual_term.row-1];
      second_sequence += '-';
      actual_term.row--;
    } else if(actual_term.direction == 3){
      first_sequence += '-';
      second_sequence += b[actual_term.column-1];
      actual_term.column--;
    }
    actual_term.value = H[actual_term.row][actual_term.column].value;
    actual_term.direction = H[actual_term.row][actual_term.column].direction;
  }

  reverse(first_sequence.begin(), first_sequence.end());
  reverse(second_sequence.begin(), second_sequence.end());

  cout << "First Sequence Generation: " << first_sequence << endl;
  cout << "Second Sequence Generation: " << second_sequence << endl;

  return 0;
}