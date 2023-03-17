#include <stdio.h>
#include <stdlib.h>
#include <stack>

// Matriz representnado o labirinto
char** maze;
// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Posição a ser explorada
struct pos_t
{
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions{

/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: valid_positions.size();
//Retornar o primeiro elemento do vetor: valid_positions.pop();
// Remover o elemento no topo: valid_positions.front(); 

};


pos_t load_maze(const char* file_name)
{
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)
	FILE *arq;
    arq = fopen(file_name, "r"); 
	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
	fscanf(arq,"%d %d",&num_rows,&num_cols);
	// Aloca a matriz maze (malloc)
	maze = (char **)malloc(num_rows * sizeof(char *));
	for (int i = 0; i < num_rows; ++i){
		// Aloca cada linha da matriz
		 maze[i] = (char *)malloc(num_cols* sizeof(char)); }
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			 fscanf(arq, " %c", &maze[i][j]);
			// Se o valor for 'e' salvar o valor em initial_pos
			if(maze[i][j] == 'e'){
				//printf("%c",maze[i][j]);
				initial_pos.i = i;
   				initial_pos.j = j;
			}
		}
	}
	return initial_pos;
}

void print_maze()
{
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool walk(pos_t pos)
{
	// Marcar a posição atual com o símbolo '.'
	if(maze[pos.i][pos.j] != 'e'){
	maze[pos.i][pos.j] = '.';}
	/* Dado a posição atual, verifica quais sao as próximas posições válidas
		Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 cada uma delas no vetor valid_positions
		 - pos.i, pos.j+1
		 - pos.i, pos.j-1
		 - pos.i+1, pos.j
		 - pos.i-1, pos.j
		 Caso alguma das posiçÕes validas seja igual a 's', terminar o programa
	 */
	pos_t up,down,right,left;
	bool verifica = false;
	
	up.i = pos.i - 1; up.j = pos.j;
	down.i = pos.i + 1; down.j = pos.j;
	left.i = pos.i; left.j= pos.j+1;
	right.i = pos.i; right.j = pos.j-1;

	if(0<=up.i && up.i<num_rows && 0<=up.j && up.j<num_cols){
		if(maze[up.i][up.j] == 'x'){
			valid_positions.push(up);}
		if(maze[up.i][up.j] == 's'){
			print_maze();
			return true;
		}
	}
	if(0<=down.i && down.i<num_rows && 0<=down.j && down.j <num_cols){
		if(maze[down.i][down.j] == 'x'){
			valid_positions.push(down);}
		if(maze[down.i][down.j] == 's'){
			print_maze();
			return true;
		}
	}
	if(0<=left.i && left.i<num_rows && 0<=left.j && left.j<num_cols){
		if(maze[left.i][left.j] == 'x'){
			valid_positions.push(left);}
		if(maze[left.i][left.j] == 's'){
			print_maze();
			return true;
		}
	}
	if(0<=right.i && right.i<num_rows && 0<=right.j&& right.j<num_cols){
		if(maze[right.i][right.j] == 'x'){
			valid_positions.push(right);}
		if(maze[right.i][right.j]  == 's'){
			print_maze();
			return true;
		}
	}

	system("cls");
	// Imprime o labirinto
	print_maze();
	// Verifica se o vetor nao esta vazio. 
	// Caso não esteja, pegar o primeiro valor de 
	// valid_positions, remove-lo e chamar a funçao walk com esse valor
	if(valid_positions.size() != 0){
	pos_t next_position = valid_positions.top();
	valid_positions.pop();
	verifica = walk(next_position);
	}
	if(verifica){
		return true;
	}
	else{
	return false;}
}

int main(int argc, char* argv[])
{
	// carregar o labirinto com o nome do arquivo recebido como argumento (argv[])
	pos_t initial_pos = load_maze(argv[]);
	bool exit_found = walk(initial_pos);
	if(exit_found){
		printf("Labirinto completo, Saida achada!!");
	}
	else{
		printf("Saida n\x0c6o achada!!");
	}
	free(maze);
	return 0;
}
