#include <bits/stdc++.h>
using namespace std;
extern int size;
extern int moved[2];
extern bool turn;
extern int dx[8];
extern int dy[8];
static int check[8];
static int cont[8];
extern char board[999][999];
static float heuristic[999][999];
static int potentialMove[999][999];
void newGame2(){
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			heuristic[i][j]=0;
		}
	}
}
static int plan[2]={0,0};
static float evaluateMove(char evaluateSign){
	fill(check,check+8,1);
	fill(cont,cont+8,1);
	for(int k=1;k<5;k++){
		for(int i=0;i<8;i++){
			if(
				plan[0]+dx[i]*k<1||
				plan[0]+dx[i]*k>size||
				plan[1]+dy[i]*k<1||
				plan[1]+dy[i]*k>size||
				cont[i]!=1
			){
				if(cont[i]==1)cont[i]=-1;
				continue;
			}
			if(board[plan[0]+dx[i]*k][plan[1]+dy[i]*k]==evaluateSign)check[i]*=10;
			else if(board[plan[0]+dx[i]*k][plan[1]+dy[i]*k]=='.')cont[i]=0;
			else cont[i]=-1;
		}
	}
	float maxVal=0;
	for(int i=0;i<4;i++){
		int curMax=1.0*(check[i]*check[i+4])+(check[i]*check[i+4])*(cont[i]+cont[i+4])/2;
		if(curMax>maxVal)maxVal=curMax;
	} 
	return maxVal;
} 
static void evaluateBoard(){
	for(int i=1;i<=size;i++){
		for(int j=0;j<=size;j++){
			if(potentialMove[i][j]==2){
				plan[0]=i;
				plan[1]=j;
				heuristic[i][j]=evaluateMove('x')+evaluateMove('o');
				potentialMove[i][j]=1;
			}
		}
	}
}
void response2(){
	if(moved[0]==0&&moved[1]==0){
		moved[0]=size/2+1;
		moved[1]=size/2+1;
		plan[0]=moved[0];
		plan[1]=moved[1];
		return;
	}else{
		
		if(plan[0]==0&&plan[1]==0){
			plan[0]=moved[0];
			plan[1]=moved[1];
		}
		potentialMove[moved[0]][moved[1]]=0;
		potentialMove[plan[0]][plan[1]]=0;
		heuristic[moved[0]][moved[1]]=0;
		heuristic[plan[0]][plan[1]]=0;
		for(int k=1;k<5;k++){
			for(int i=0;i<8;i++){
				if(
					board[moved[0]+dx[i]*k][moved[1]+dy[i]*k]=='.'&&
					board[moved[0]+dx[i]*(k-1)][moved[1]+dy[i]*(k-1)]!='.'
				)potentialMove[moved[0]+dx[i]*k][moved[1]+dy[i]*k]=2;
				if(
					board[plan[0]+dx[i]*k][plan[1]+dy[i]*k]=='.'&&
					board[plan[0]+dx[i]*(k-1)][plan[1]+dy[i]*(k-1)]!='.'
				)potentialMove[plan[0]+dx[i]*k][plan[1]+dy[i]*k]=2;
			}
		}
		evaluateBoard();
		int maxHeur=0;
		for(int i=1;i<=size;i++){
			for(int j=1;j<=size;j++){
				if(heuristic[i][j]>maxHeur){
					maxHeur=heuristic[i][j];
					plan[0]=i;
					plan[1]=j;
				}
			}
		}
		moved[0]=plan[0];
		moved[1]=plan[1];
		cout<<moved[0]<<" "<<moved[1]<<endl;
	}
}
