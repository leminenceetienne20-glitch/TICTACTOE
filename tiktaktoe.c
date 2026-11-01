#include<stdio.h>
#include<stdbool.h>
#define EMPTY ' '
#define MAX 10
#define MIN 3
void initial_board(int n, int size, char a[n][size]){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<size; j++){
			a[i][j] = EMPTY;
		}
	}
}

void display_board(int n, int size, char a[n][size]){
	int i, j;
	printf("\n");
	for(j=0; j<size; j++){
		printf("+");
		printf("---");
	}
	printf("+\n");
	
	for(i=0; i<n; i++){
		for(j=0; j<size; j++){
			printf("| %c ", a[i][j]);
		}
	printf("|\n");
	for(j=0; j<size; j++){
		printf("+");
		printf("---");
	}
		printf("+");
		printf("\n");
	}
}

char choose_symbol(char *symbol1, char *symbol2){
	char answer;
	printf("Player_1 should choose a symbol(X or O): "); 
	do{
		scanf(" %c", &answer);
		if(answer!='X' && answer!='O'){
			printf("Invalid input. Try again: ");
		}
	}
	while(answer!='X' && answer!='O');
	*symbol1=answer;
	if(*symbol1=='X'){
		*symbol2='O';
	}
	else{ 
		*symbol2='X';
	}
	printf("Player_1's symbol is <%c>\n", *symbol1);
    printf("Player_2's symbol is <%c>\n", *symbol2);
}

void read_move(int n, int size, char a[n][size], char current, char *player){
	int s=n*size-1;
	int c, i, j;
	printf("%s, choose a box (0 to %d): ",player, s);
	do{
		scanf("%d", &c);
		i=c/n;
		j=c%size;
		if(c<0 || c>s){
			printf("Invalid input. Enter a value in the given range: ");
		}
		else if(a[i][j]!=EMPTY){
			printf("The cell you chose is already occupied. Try another one: ");
		}
	}
	while(c<0 || c>s || a[i][j]!=EMPTY);
	a[i][j]=current;
}

void switch_player(char *current, char symbol1, char symbol2, char *player[10], char player1[10], char player2[10]){
	if(*current==symbol1){
		*current=symbol2;
		*player=player2;
	}
	else{
		*current=symbol1;
		*player=player1;
	}
}

bool check_win(int n, int size, char a[n][size], char current){
	int i, j;
	bool win;
	for(i=0; i<n; i++){
		win=true;
		for(j=0; j<size; j++){
			if(a[i][j]!=current){
				win=false;
			}
		}
		if(win==true){
			return win;	
		}
	}
	for(j=0; j<size; j++){
		win=true;
		for(i=0; i<n; i++){
			if(a[i][j]!=current){
				win=false;
			}
		}	
		if(win==true){
				return true;
		}	
	}
	win=true;
	for(i=0; i<n; i++){
		if(a[i][i]!=current){
			win=false;
		}
	}
	if(win){
		return true;
	}
	win=true;
	for(i=0; i<n; i++){
		if(a[i][n-1-i]!=current){
			win=false;
		}
	}
	if(win){
		return true;
	}
	return false;
}

bool check_draw(int n, int size, char a[n][size]){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<size; j++){
			if(a[i][j]==EMPTY){
				return false;
			}
		}
	}
	return true;
}

int main(){
	char choice;
	do{
		printf("\n");
		char player1[10];
		char player2[10];
		printf("Player_1 should enter a name: ");
		scanf("%s", &player1);
		printf("Player_2 should enter a name: ");
		scanf("%s", &player2);
		printf("\n");
		
		int n, i;
		printf("Enter an odd number for your match (from 3 to 10): ");
		do{
			scanf("%d", &n);
			printf("\n");
			if(n<3 || n>10 || n%2==0){
				printf("Invalid value. Enter an odd value in the range given above: ");
			}
		}
		while(n<3 || n>10 || n%2==0);
		
		char a[n][n];
		initial_board(n, n, a);
		display_board(n, n, a);
		char symbol1;
		char symbol2;
		choose_symbol(&symbol1, &symbol2);
		char *player=player1;
		char current=symbol1;
		int s=n*n-1;
		for(i=0; i<=s; i++){
			read_move(n, n, a, current, player);
			display_board(n, n, a);
			if(check_win(n, n, a, current)==true){
				printf("End of match. %s won the match.\n", player);
				break;
			}
			if(check_draw(n, n, a)==true){
				printf("Draw match.\n");
				break;
			}
			switch_player(&current, symbol1, symbol2, &player, player1, player2);
		}
		printf("Do you want to have another match?(Y/N): ");
		do{
			scanf(" %c", &choice);
			printf("\n");
			if(choice!='Y' && choice!='N'){
				printf("Invalid entry. Try again: ");
			}
		}
		while(choice!='Y' && choice!='N');
		if(choice=='Y'){
			printf("Set new match.\n\n");
		}
		else{
			printf("Thanks for playing.");
			break;
		}
	}
	while(choice=='Y');
	
	return 0;
}
