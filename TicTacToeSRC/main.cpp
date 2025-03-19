#include <bits/stdc++.h>
using namespace std;
int size=9;
int moved[2]={0,0};
bool turn=0;
int dx[8]={1,1,1,0,-1,-1,-1,0};
int dy[8]={1,0,-1,-1,-1,0,1,1};
char board[999][999];
void response1();
void response2();
void newGame1();
void newGame2();
void setBoard(){
	for(int i=0;i<=999;i++){
		for(int j=0;j<=999;j++){
			if(i<=0||i>=size+1)board[i][j]='=';
			else if(j<=0||j>=size+1)board[i][j]='|';
			else board[i][j]='.';
			
		}
	}
	newGame1();
	newGame2();
}
void printBoard(){
	for(int i=0;i<=size+1;i++){
		for(int j=0;j<=size+1;j++){
			cout<<board[i][j]<<"\t";
		}
		cout<<endl;
	}
}
int checkWin(){
	int check[8]={0};
	int cont[8];
	fill(cont,cont+8,1);
	for(int k=1;k<5;k++){
		for(int i=0;i<8;i++){
			if(
				moved[0]+dx[i]*k<1||
				moved[0]+dx[i]*k>size||
				moved[1]+dy[i]*k<1||
				moved[1]+dy[i]*k>size
			)continue;
			if((board[moved[0]+dx[i]*k][moved[1]+dy[i]*k]==board[moved[0]][moved[1]])&&cont[i])check[i]++;
			else cont[i]=0;
		}
	}
	for(int i=0;i<4;i++){
		if(check[i]+check[i+4]>=4){
			printBoard();
			if(turn==0)cout<<"X win\n";
			else cout<<"O win\n";
			cout<<"Game ends\n";
			return 1;
		}
	}
	return 0;
} 
void humanResponse(){
	cin>>(moved[0])>>(moved[1]);
}
int main(int argc, char** argv) {
	setBoard();
	printBoard();
	int availableMove=size*size;
	while(availableMove--){
		if(turn==0){
			cout<<"Player turn\n";
			//humanResponse();
			response2();
		}else{
			cout<<"Computer turn\n";
			humanResponse(); 
			//response1();
		}
		if(board[moved[0]][moved[1]]!='.'||moved[0]==0||moved[1]==0){
			cout<<"Illegal move\n";
			availableMove++;
		}else{
			if(turn==0){
				board[moved[0]][moved[1]]='x';
			}else{
				board[moved[0]][moved[1]]='o';
			}
			if(checkWin())break;
			printBoard();
			turn=1-turn;
		}
	}
	return 0;
}
