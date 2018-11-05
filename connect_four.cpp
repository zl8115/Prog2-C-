/*Connect Four program written by Ze Lum on 17/10/2016 @ 2114hours*/
#include <iostream>

using namespace std;

int main()
{
	char board[7][6]={0}, output;
	int i, j, player, input, count, x, y, turns = 0, end = 0; //i & j variables used as x & y
	do{
		start:
		end = 0, turns = 0;
		//Print and fill array
		cout << "|1||2||3||4||5||6||7|" << endl << "---------------------" << endl;
		for (j = 0; j < 6; j++)
			{
				for (i = 0; i < 7; i++)
				{
					board[i][j] = ' ';
					cout << "|" << board[i][j] << "|";
				}
				cout << endl;
			}
			cout << endl;
		//Start of program loop
		do{
			//Player select & output marker based on turns
			if (turns%2 == 0)
				{player = 1, output = 'X';}
			else
				{player = 2, output = 'O';}
			cout << "Player " << player << " (" << output << ") Input a column to place '" << output << "' :"<< endl;
			//Loop to check for input errors and filled columns
			do
			{
				cin >> input;
				while((cin.fail())||(input<1)||(input>7))
				{
					cin.clear();
					cin.ignore(10000,'\n');
					cout<<"Input a valid number between 1 & 7"<<endl;
					cin>>input;
				}
				input--;
				for (j=5; (board[input][j] == 'X')||(board[input][j] == 'O'); j--);		//Identifies the row for use
				if(j<0)		 //Checks if column is full and prints error message
					{cout << "Column " << input+1 << " is full. Select a different column" << endl;}
			}while(j<0);
			cin.ignore(128, '\n');
			board[input][j] = output;	//Overwriting empty spot with Output Marker
			//Vertical check (Check only works when rows reach a min height of 4)
			if((j<3)&&((board[input][j])==(board[input][j+1]))&&((board[input][j])==(board[input][j+2]))&&((board[input][j])==(board[input][j+3])))
			end = 1;
			//Horizontal check (Check only works when rows and columns are within checking boundaries)
			for(x=input;((x>=0)&&(x<=7)&&(board[x][j]==output));x--);
			x++;
			if(((board[x][j])==(board[x+1][j]))&&((board[x][j])==(board[x+2][j]))&&((board[x][j])==(board[x+3][j]))&&(x<4))
				{end = 1;}
			//Diaganol Backward (/) check (Check only works when rows and columns are within checking boundaries)
			for(x=input,y=j;(((x>=0)&&(x<=7))&&((y>=0)&&(y<=6))&&(board[x][y]==output));x--, y++);
			x++, y--;
			if((x<4)&&(y>2)&&((board[x][y])==(board[x+1][y-1]))&&((board[x][y])==board[x+2][y-2])&&((board[x][y])==board[x+3][y-3]))
				{end = 1;}
			//Diaganol Forward (\) check (Check only works when rows and columns are within checking boundaries)
			for(x=input,y=j;(((x>=0)&&(x<=7))&&((y>=0)&&(y<=6))&&(board[x][y]==output));x++, y++);
			x--, y--;
			if((x>2)&&(y>2)&&((board[x][y])==(board[x-1][y-1]))&&((board[x][y])==board[x-2][y-2])&&((board[x][y])==board[x-3][y-3]))
				{end = 1;}
			//Reprint of Board after checking and implementation
			cout << endl << endl;
			cout << "|1||2||3||4||5||6||7|" << endl << "---------------------" << endl;
			for (j = 0; j < 6; j++)
			{
				for (i = 0; i < 7; i++)
					{cout << "|" << board[i][j] << "|";}
				cout<<endl;
			}
			cout<<endl;
			turns++;			//Adding no of turns
			if (turns==42)		//Check if game is tied
				{end=2;}		
		}while(end == 0);
		switch(end)				//Ending options
		{
			case 1:				//Game is Won by a Player
				cout<<"Congratulations! Player " << player <<" ("<< output << ")" <<" has won" << endl << endl;
			break;
			case 2: 			//Game is tied
				cout << "The game results in a tie, neither player has won" << endl << endl; 
		}
		do{						//Option to restart game
			cout << "Would you like to continue? [Y/N]" << endl;
			cin >> output;
			cin.ignore(128,'\n');
			if((output == 'y')||(output == 'Y'))
				{goto start;}
		}while((output != 'n')&&(output != 'N'));
	}while((end != 1)&&(end != 2));
	return 0;
} /* Oooohh... (0.0) 100 lines */