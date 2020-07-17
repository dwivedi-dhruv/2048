#include<bits/stdc++.h>
using namespace std;


int board[4][4];                               // the board
int dirLine[] = { 1, 0,-1,0};                  // mapping it with the values (i.e.) the change in the line/column at the value '0' (s--down) && 
int dirColumn[] = { 0,1,0,-1};                 // '1' (d--right) && '2' (w--up) && '3' (a--left)



pair<int,int> generateUnoccupiedPosition()     // to generate unoccupied cells
{
	int occupied=1,line,column;
	
	while(occupied)
	{
		line=rand() % 4;
		column=rand() % 4	;
		
		if(board[line][column]==0)
		occupied=0;
		else 
		continue;
	}
	
	return make_pair( line,column );
}



void addPiece()                              //  to add the value to the board
{
	pair<int,int> pos =generateUnoccupiedPosition();
	board[pos.first][pos.second]=2;
}




void newGame()                               // after the user selects New Game option
{
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
	board[i][j]=0;
	
	addPiece();
}





bool canDoMove(int line ,int column, int nextLine , int nextColumn)
{
	if(nextLine<0 || nextColumn<0 || nextLine>=4 || nextColumn>=4 || 
	(board[line][column]!=board[nextLine][nextColumn] && board[nextLine][nextColumn]!=0))
	return false;
	return true;
}




void printGUI()                                             // to give values of the cells after the valid move
{
	system("cls");
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(board[i][j]==0)
	    	cout <<setw(4)<<"*";
	    	else
    		cout <<setw(4) <<board[i][j] ;
		}
    	cout << endl;
	}
	
	
	cout << "n:New Game || s:Down || d:Right || w:Up || a:Left || q:Quit \n";
}




void applyMove(int direction)
{
	int startLine=0,startColumn=0,lineStep=1,columnStep=1;
	
	if(direction==0)
	{
		startLine=3;
		lineStep=-1;
	}
	
	if(direction==1)
	{
		startColumn=3;
		columnStep=-1;
		
	}
	
	int movePossible=0,canAddPiece=0;
	
	do{
		
	movePossible=0;
	for(int i=startLine;i>=0 && i<4 ; i+=lineStep)
    	for(int j=startColumn ;j>=0&& j<4;j+=columnStep)
    	{
     		int nextI=i+dirLine[direction] , nextJ=j+dirColumn[direction];
    		 if(canDoMove(i,j,nextI,nextJ) && board[i][j])
    		 {
    		 	board[nextI][nextJ]+= board[i][j];
    		 	board[i][j]=0;
    		 	movePossible=canAddPiece=1;
			 }
			 
		}
		printGUI();               // to show the changing values
	}
	while(movePossible);
		
	if(canAddPiece)
	{
		addPiece();
	}
}




int main()
{
	char commandToDir[128];
	//   Controllers
	//   s--> to move the cells downward
	//   d--> to ove the cells right
    //   w--> to move the cells upward
    //   a--> to ove the cells left  
	commandToDir['s']=0;      
	commandToDir['d']=1;      
	commandToDir['w']=2;        
	commandToDir['a']=3;     
	newGame();
	
	while(true)
	{
		printGUI();
    	char command;
        cin >> command;
        
        if(command=='q')
        break;
        else if(command=='n')
        newGame();
        else if(command=='s'||command=='d'||command=='w'||command=='a')
        {
        	int currentDirection=commandToDir[command];
        	applyMove(currentDirection);
		}
		else
			cout<<"Invalid command";
	}
	
	
	
}
