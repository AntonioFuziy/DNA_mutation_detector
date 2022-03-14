#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct alignment{
  int row;
  int column;
  string direction;
};

//funcao que identifica match da base nitrogenada
int match(char a, char b){
  if(a == b){
    return 2;
  };
  return -1;
}

int get_vector_length(vector<alignment> vec){
  int length = 0;
  for(alignment element: vec){
    length++;
  }
  return length;
}

void show_matrix(vector<vector<int>> H, int n, int m){
  cout << "" << endl;
  for(int i = 0; i < n; i++){
    cout << " " << endl;
    for(int j = 0; j < m; j++){
      cout << H[i][j] << " ";
    }
  }
  cout << "" << endl;
  cout << "" << endl;
}

//funcao para calcular smith waterman
vector<vector<int>> smith_waterman(vector<vector<int>> H, int n, int m, string a, string b, int w){
  int diagonal, delecao, insercao;
  // calculando diagonal, delecao e insercao
  for (int i = 1; i < n; i++){
    for (int j = 1; j < m; j++){
      w = match(a[i], b[j]);
      diagonal = H[i-1][j-1] + w;
      delecao = H[i-1][j] - 1;
      insercao = H[i][j-1] - 1;
      H[i][j] = max(diagonal, max(delecao, max(insercao, 0)));
    }
  }
  return H;
};

int main(){
  int n, m, w;
  w = 0;
  string a, b;
  vector<vector<int>> H;

  // leitura dos tamanhos das duas sequencias
  cin >> n;
  cin >> m;

  // leitura das sequencias
  cin >> a;
  cin >> b;

  a = a.insert(0, " ");
  b = b.insert(0, " ");

  //inicializando matriz H com zeros
  H.resize(n);
  for(int i = 0 ; i < n ; i++){
    H[i].resize(m);
  }

  //printando as entradas do arquivo
  cout << "n: " << n << " m: " << m << endl;
  cout << "a: " << a << " b: " << b << endl;

  //chamando a funcao que monta a matriz H e retorna o valor maximo dela
  H = smith_waterman(H, n, m, a, b, w);
  
  show_matrix(H, n, m);

  //pegando maior valor da matriz
  int max_H = 0;
  int max_j = 0;
  int max_i = 0;
  for(int i = 1; i < n; i++){
    for(int j = 1; j < m; j++){
      if(H[i][j] > max_H){
        max_H = H[i][j];
        max_i = i;
        max_j = j;
      }
    }
  }
  cout << "max " << max_H << endl;

  // aplicando o alinhamento
  alignment actual_term;
  vector<alignment> matrix_term;
  
  int actual_max = max_H;
  actual_term.row = max_i;
  actual_term.column = max_j;
  actual_term.direction = "";

  string first_sequence = "";
  string second_sequence = "";

  matrix_term.push_back(actual_term);

  int diagonal, delecao, insercao;

  while(actual_term.row > 0 and actual_term.column > 0 and actual_max > 0){
    diagonal = H[actual_term.row-1][actual_term.column-1];
    delecao = H[actual_term.row-1][actual_term.column];
    insercao = H[actual_term.row][actual_term.column-1];

    // diagonal -> vai para diagonal
    if(diagonal >= delecao and diagonal >= insercao){
      actual_term.row -= 1;
      actual_term.column -= 1;
      actual_term.direction = "diagonal";
      actual_max = diagonal;
    }

    // delecao -> vai para a esquerda
    else if(delecao >= insercao){
      actual_term.row -= 1;
      actual_term.direction = "delecao";
      actual_max = delecao;
    }

    // insercao -> vai para cima
    else {
      actual_term.column -= 1;
      actual_term.direction = "insercao";
      actual_max = insercao;
    }
    
    matrix_term.push_back(actual_term);
  };

  reverse(matrix_term.begin(), matrix_term.end());

  for (int i = 0; i < get_vector_length(matrix_term); i++){
    if(matrix_term[i].direction == "diagonal"){
      first_sequence += a[matrix_term[i].row+1];
      second_sequence += b[matrix_term[i].column+1];
    }
    else if(matrix_term[i].direction == "delecao"){
      first_sequence += a[matrix_term[i].row+1];
      second_sequence += "-";
    }
    else if(matrix_term[i].direction == "insercao"){
      first_sequence += "-";
      second_sequence += b[matrix_term[i].column+1];
    }
  }

  cout << "first_sequence: " << first_sequence << endl;
  cout << "second_sequence: " << second_sequence << endl;

  return 0;
}