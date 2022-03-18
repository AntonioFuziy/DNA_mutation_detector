# Projeto de Supercomputação - Alinhamento de Sequências de DNA

### Aluno: Antonio Fuziy


**Relatório sobre o funionamento do algoritmo**

___

### Smith-Waterman

Foi utilizado um `struct` para armazenar os valores e posições da matriz H além das direções que os termos da matriz seguem, esse struct foi representado abaixo:

```c++
struct alignment{
  int row; //linha do termo da matriz
  int column; //coluna do termo da matriz
  int direction; //direcao da dos termos da matriz
  int value; //valor armazenado no termo da matriz
};
```

Para a construição da matriz H implementou-se um loop sobre a uma matriz de zeros (n X m) em que:

- n -> tamamho da primeira fita do DNA 

- m -> tamamho da segunda fita do DNA

Dessa forma, o cálculo da diagonal, deleção e inserção são calculados para cada termo da matriz, após isso, esses três valores são comparados com zero e o maior valor entre eles é extraído e armazenado na matriz, esses passos foram representados no código abaixo:

**Obs: Os índices dos valores máximos entre diagonal, inserção, deleção e zero são retirados através da função `w`, esses valores representam a direção seguida ao preencher a matriz e à partir deles armazena-se os valores máximos entre diagonal, inserção, deleção e zero**

**Função `w`:**
```c++
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
```

**Função de cálculo da matriz H e armazenamento dos seus valores máximos:**

```c++
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
    
    //calculo da diagonal, deleção e inserção
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
```

### Alinhamento

Após o preenchimento da matriz H, é necessário calcular o alinhamento e montar as sequências A e B geradas pelo algoritmo de Smith-Waterman. Para o cálculo do alinhamento, primeiramente foi armazenado em um struct `alignment` os valores máximos de H, assim seria possível localizar a posição desse valor máximo e calcular o alinhamento à partir deste. Portanto, obtendo a localização do máximo de H é necessário apenas checar as direções armazenadas na matriz de struct e montando as sequências A e B geradas. Essa lógica pode ser traduzida pelo algoritmo abaixo:

```c++
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
```

Por fim, o output gerado pelo algoritmo deve ser como representado abaixo:

**OBS: O output da solução está no arquivo `output.txt`**

```bash
n: 8 m: 8
a: AGCACACA
b: ACACACTA

H Matrix:

0 0 0 0 0 0 0 0 0
0 2 1 2 1 2 1 0 2
0 1 1 1 1 1 1 0 1
0 0 3 2 3 2 3 2 1
0 2 2 5 4 5 4 3 4
0 1 4 4 7 6 7 6 5
0 2 3 6 6 9 8 7 8
0 1 4 5 8 8 11 10 9
0 2 3 6 7 10 10 10 12

Score: 12

First Sequence Generation: AGCACAC-A
Second Sequence Generation: A-CACACTA
```