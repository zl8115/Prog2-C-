//Completed Assignment 3 v3.0 - by Ze Lum - Completed 8/12/2016 - 2141Hours

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

//-----------CELL CLASS---------------->

// Cell class acts as a boolean variable indicating if it is a live or not
class Cell
{
	public:
	bool current_state;								// Public variable indicating current state of cell (0:Dead ; 1:Alive)
	bool next_state;								// Next state before update() function
	virtual char get_state();						// Returns the character/"symbol" for current state
	virtual char get_alive_char();					// Returns the character/"symbol" for alive status
	void set_state_alive();							// Sets the current_state to 1 (Alive)
	void set_state_dead();							// Sets the current_state to 0 (Dead)
	virtual void set_next_state(int neighbours);	// Sets next_state according to the number of neighbouring ALIVE cells (Counted in Board function)
	void update();									// Updates current_state to next_state
	Cell& operator=(const Cell& cell_in);			// Equates the current_state of each Cell class variable
	Cell(){};										// Cell Constructor left empty
	~Cell(){};										// Cell Destructor left empty
};

//-----------CELL FUNCTIONS---------------->

// Returns the character/"symbol" representation of an 'alive' Cell
char Cell::get_state()
{
	if (current_state == 1)
		{return 'O';}
	else
		{return ' ';}
}

// Used by class Board to get alive_char variable
char Cell::get_alive_char()
	{return 'O';}

// Sets the next_state variable according to the conditions of no of alive neighbours
void Cell::set_next_state(int neighbours)
{
	if (neighbours >= 4 || neighbours <= 1)		// Conditions for death
		{next_state = 0;}
	else if (neighbours == 3 && current_state == 0)	//  Conditions for birth
		{next_state = 1;}
	else 
		{next_state = current_state;}	// Carry over what it was before
}

// Set the current state of cell as alive
void Cell::set_state_alive()
	{current_state = 1;}

// Set the current_state of cell as dead
void Cell::set_state_dead()
	{current_state = 0;}

// Update current_state to the next_state
void Cell::update()
	{current_state = next_state;}

//-----------CELL OPERATORS---------------->

// Saves current_state to the next cell
Cell& Cell::operator=(const Cell& cell_in)
{
	current_state = cell_in.current_state;
}

// Prints out the current_state variable, users can use get_state() to get the character association
ostream& operator<<(ostream& os, Cell cell)
{
	return os << cell.current_state;
}

//-----------CANCER CLASS---------------->

//Cancer cell inherits Cell variables
/*
Side note: Class cannot inherit and alter variables that are implemented in functions. 
I.E. 
If char alive_char = 'O' replaces all 'O' in Cell class; alive_char = 'X' does not work as var "alive_char" is a read-only variable inherited from Cell
Hence, implementation of Cancer Class used  rather than a variable 
*/
class Cancer: public Cell
{
	public:
	char get_state();						//Overide the virtual function in cell
	char get_alive_char();
	void set_next_state(int neighbours);
	Cancer(){};
	~Cancer(){};
};

char Cancer::get_state()
{
	if (current_state == 1)
	{
		return 'X';
	}
	else
	{
		return ' ';
	}
}

char Cancer::get_alive_char()
{
	return 'X';
}

void Cancer::set_next_state(int neighbours)
{
	if (neighbours >= 5 || neighbours <= 1)				// Difference in condition here (neighbours >= 5) instead of 4
	{
		next_state = 0;
	}
	else if (neighbours == 3 && current_state == 0)
	{
		next_state = 1;
	}
	else 
	{
		next_state = current_state;
	}
}

//-----------BOARD CLASS---------------->

//Board class acts as a 2D Vector capable dealing with Cell-based classes
class Board
{
	private:
		char alive_char;		// Variable used only for checking conditions (More reliable than ' ')
		int time_counter;		// Time counter for each "round"
		int confluence;			// Confluence variable
		int selection;			// Selection variable
		int row_max;			// No of Rows in Board
		int col_max;			// No of Columns in Board
		vector <vector<Cell*> > board;		// 2D Vector of Pointers acting as the board
		
	public:
		int get_num_cells();	// Gets the number of alive cells(Normal/Cancer)
		int get_time();			// Returns current time_counter
		void set_state(int sel, int con);	// Sets the 2D Vector state - Include set_vector() and seed_cells() functions
		void get_neighbours(int i, int j);	// Gets the no of neighbouring cells to send to Cell::set_next_state(neighbours)
		void next_state();		// Calls the function get_neighbours() and set_update()
		void print();			// Prints out the full board with Cell char/"symbol" states
		void seed_cells();		// Randomly sets coordinates on the Board with cell_alive
		void set_vector();		// Sets the vector according to the selection of Cell-based class
		void set_update();		// Tells the cells to update the current_state according to the next_state()
		Board();				// Initializes Board of dimension (20 * 75)
		Board(int col);			// Initializes Board of dimension (20 * col)
		Board(int col, int row);// Initializes Board of dimension (row * col)
		~Board(){};
};

//-----------BOARD INITIALIZER---------------->

// Default Board initialization
Board::Board()
{
	row_max = 20;
	col_max = 75;
}

// Board initialization with one int values
Board::Board(int col)
{
	row_max = 20;
	col_max = col;
}

// Board initialization with 2 int values
Board::Board(int col, int row)
{
	row_max = row;
	col_max = col;
}

//-----------BOARD GET FUNCTIONS---------------->

// Counts the number of alive cells and returns the count number
int Board::get_num_cells()
{
	int count = 0;
	for (int i = 0; i < row_max; ++i)
	{
		for (int j = 0; j < col_max; ++j)
		{
			if (board[i][j]->get_state() == alive_char)
			{
				count++;
			}
		}
	}
	return count;
}

// Returns the current time of the board
int Board::get_time()
{
	return time_counter;
}

// Gets the no of neighbours for Cell-based class to interpret
// Requires the coordinates of the "Cell" to initializes a 3*3 scan radius to start counting
void Board::get_neighbours(int i, int j)
{
	int count = 0;
	int x_min, x_max, y_min, y_max;
	if (board[i][j]->get_state() == alive_char)		
		{count --;}		// Creates negative offset to ignore counting the centre Cell
	
	y_min = -1, y_max = 1;
	
	if (i == 0)			// Condition for when the Cell is on the first row
		{y_min = 0;}	
	else if (i == row_max-1)	// Condition for when the Cell is on the last row
		{y_max = 0;}
		
	x_min = -1, x_max = 1;
	
	if (j == 0)			// Condition for when the Cell is on the first column
		{x_min = 0;}
	else if (j == col_max-1)	// Condition for when the Cell is on the last column
		{x_max = 0;}
		
	for(int y = y_min; y <= y_max; y++)		// Counting loop
	{
		for(int x = x_min; x <= x_max; x++)
		{
			if (board[i+y][j+x]->get_state() == alive_char)
			{
				count ++;
			}
		}
	}
	board[i][j]->set_next_state(count);		// Calls function to set the next_state of the Cell accordingly
}

//-----------BOARD MISC FUNCTIONS---------------->

// Sets the next state of the Board
void Board::next_state()
{
	for (int i = 0; i < 20; i++)			// For every vector component, the Cell-based class performs get_neighbour
	{
		for(int j = 0; j < 75 ; j++)
		{
			Board::get_neighbours(i,j);
		}
	}
	Board::set_update();					// Updates the board after the entire loop for checking is completed to complete the function
	time_counter++;							// Updates the counter as a sign of performing the next state
}

// Prints out the 2D vector Board
void Board::print()
{
	system("cls");												// Clears board to print the Board class
	cout << "Time :" << Board::get_time() << endl;				// Prints out the current Board time
	cout << "Cell Number :" << Board::get_num_cells() << endl;	// Prints out the number of alive cells on the Board
	for (int i = 0; i < row_max; ++i)							// Loop to print out the char/"symbol" of every Cell state
	{
		for (int j = 0; j < col_max; ++j)
		{
			cout << board[i][j]->get_state();
		}
		cout << endl;			// Formatting line
	}
}

// Randomly initializes Cell unto the board according to the confluence set
void Board::seed_cells()
{
	time_counter = 0;				// Initalize the counter to start from 0
	srand(time(NULL));				// The random seed is set according to the current time of the computer - Adds a more random factor
	int temp_x, temp_y;				// Temporary x-y coord to initialize cell
	int lim = int(confluence*row_max*col_max/100);	// Sets the limit of the loop iteration
	for (int i = 0; i < lim; ++i)
	{
		do
		{
			temp_x = rand()%row_max;		// Random row number
			temp_y = rand()%col_max;		// Random column number
		}while(board[temp_x][temp_y]->get_state() == alive_char);	// To ensure that a board coordinate is not used twice
		board[temp_x][temp_y] -> set_state_alive();		// Sets the current cell as alive
	}
}

//-----------BOARD SET FUNCTIONS---------------->

// Initializes the 2D vector that acts as the complete board
void Board::set_vector()
{
	vector<Cell*> row;		// Temporary vector used to initialize the board
	for(int i = 0; i < row_max; i++)
	{
		for(int j = 0; j < col_max; j++)
		{
			switch(selection)				// Dependent on the selection of Cell-type
			{
				case 1:		// Case 1 is for Normal Cells
				row.push_back(new Cell());	// Creates new pointer to the newly created Cell-class
				break;
				case 2:		// Case 2 is for Cancer
				row.push_back(new Cancer());// Creates new pointer to the newly created Cancer-class
				break;
				default:	// Should never be reached but default cell is used
				row.push_back(new Cell());
				break;
			}
		}
		board.push_back(row);	// Pushes back a vector row of pointers to vector "board"
		row.clear();	// Clears row to create new vector row of pointers
	}
	alive_char = board[0][0]->get_alive_char();		// Gets the alive_char according to the initialized Cell-type
}

// Main initializer for the board
void Board::set_state(int sel, int con)
{
	selection = sel;		// Saves the Cell-type selection for later use
	confluence = con;		// Saves the confluence percentage for later use
	set_vector();			// Initialize vector accordingly
	seed_cells();			// Seed the cells accordingly
} 

// Update all the cells' current_state to the next_state
void Board::set_update()
{
	for (int i = 0; i < row_max; i++)
	{
		for (int j = 0; j < col_max; j ++)
		{
			board[i][j]->update();
		}
	}
}

//-----------PROTOTYPE FUNCTIONS USED IN INT MAIN---------------->

void mainmenu(int* sel, int* con);		// Prototype function to query user of selection of cell-type and confluence

//-----------INT MAIN---------------->

int main()
{
	char exit;										// Initializes exiting character
	int sel, con;									// Variables for the selection and confluence
	Board trial;									// Initializes variable of class-type Board
	mainmenu(&sel, &con);							// Query for selection and confluence, and saving the selected options
	trial.set_state(sel, con);						// Uses the Board function of set_state
	trial.print();									// Prints out the board accordingly
	exit = cin.get();								// Prompts user to hit the 'Enter' key or any input to enter loop for running the program
	while((exit != 'q') && (exit != 'Q'))			// Condition is the when 'q' or 'Q' is entered to exit program
	{
		trial.next_state();							// Pushes Board to enter the next state
		trial.print();								// Prints out the newly updated Board
		exit = cin.get();							// Get next command to loop or exit
	}
	return 0;
}

//-----------FUNCTIONS USED IN INT MAIN---------------->

void mainmenu(int* sel, int* con)		// Function to query user of selection of cell-type and confluence
{
	CellKey:
	cout << "Select your cell type: (1) normal cells or (2) cancer cells" << endl;
	cin >> *sel;
	if(cin.fail() || *sel < 1 || *sel > 2)		// Failsafe for selecting an integer besides 1 & 2 or something else
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid option" << endl;
		goto CellKey;
	}
	cin.ignore(10000, '\n');		// Remove any random characters after the "Enter" key
	ConKey:
	cout << "Select the confluence percentage (%)" << endl;
	cin >> *con;
	if(cin.fail() || *con > 100 || *con < 0)	// Failsafe for selecting an integer between 0 & 100
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid option" << endl;
		goto ConKey;
	}
	cin.ignore(10000, '\n');		// Remove any random characters after the "Enter" key
}
// Also, I did not include option to choose row/col size to meet the requirements of the assignment :3
// 400 Lines with tons of comment and things... Not too bad I guess... Despite the last 2 lines kinda being fillers... But let's keep that hush hush between us...
// Since this is the last assignment, maybe I shall include a short story just for the sake of extending your attention span and try to keep you engaged for whatever bored reason you are here...
// But maybe a short story is too much, so maybe a joke instead
// I think a joke is more suitable... Now time to think of a joke... I know! Since this is programming...
// So, you're ready for a joke? That's good. This might get a little bit lengthy, but here goes... Once there was a programmer sitting on his desk reading his student's code. Line after line, he reads and comes across a hidden joke. Upon reading it, the programmer doesn't understand it. So he looks at the line count and looks back. Error 404: Joke not found;
// Hope you at least had a small chuckle from that. Also, I hope you actually had a line counter in whatever editor you're reading this in...
// Anyhow...
/* int main()
{if (date < 25/12/2016){std::cout << "Merry Christmas!!!";} 
else if (date <= 1/1/2016){std::cout << "Happy New Year";}
else{std::cout << "Hope the new term doesn't start...";}} */ // 410 Lines to end isn't too bad