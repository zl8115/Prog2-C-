// Assignment 2 v2.0 - Created by Ze Lum - Last Edit 19/11/2016 - 1455Hours

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct protein
{
	string gi;
	string ref;
	string name;
	string sequence;
};

void inamerequest(string* iname);								// Selecting the input file (abriged or complete)
void inputvector(string* iname, vector<protein>* v);			// Loads the selected input file into a vector
void onamerequest(string* oname);								// Selects the default output file or construct a new one
void mainmenu(int* input);										// Main Menu of options
void database (int totalprotein);								// Loads database
void search(vector<protein>* v, string* oname, int option);		// Search function for ID, gi ID, ref ID and keyword
void hitmenu (string* oname, protein output, int itemID);		// A further search function detailing the protein found

int main()		// Main function that runs all functions
{
	int option;
	string iname, oname = "selected_proteins.txt";
	vector<protein> v;
	inamerequest(&iname);
	inputvector(&iname, &v);
	onamerequest(&oname);
	MainMenu:
	mainmenu(&option);
	switch(option)
	{
		case 1 : database(v.size()); break;
		case 2 : case 3 : case 4 : case 5 : search(&v, &oname, option); break;
		case 6 : goto Terminate; break;
		default : goto MainMenu; break;
	}
	goto MainMenu;
	Terminate:
	return 0;
}

void inamerequest(string* iname)	// Selecting the input file name
{
	int input;
	string Option1 = "protein_a.fa";
	string Option2 = "protein_c.fa";
	EntryKey:
	cout << endl << endl;
	cout << "File Selection:" << endl;
	cout << "-----------------------------" << endl;
	cout << "Select file option:" << endl ;
	cout << "1: Abridged protein sequence" << endl;
	cout << "2: Complete protein sequence" << endl;
	cout << endl << "Input option:";
	cin >> input;
	if (cin.fail() || input > 2 || input < 1)	// Invalid Option Failure loop
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Invalid option" << endl << endl;
		goto EntryKey;
	}
	cin.ignore(10000,'\n');
	if (input == 1)
	{
		*iname = Option1;
	}
	else 
	{
		*iname = Option2;
	}
	cout << endl << endl;
	cout << "Selected file is: " << (*iname) << endl;
	
}

void inputvector(string* iname, vector<protein>* v)	// Loading the file contents into a vector
{
	protein iline;	// Temporary struct to save into 
	string junk;	// String line for junk text
	ifstream ist;
	ist.open((*iname).c_str(), ios_base::in);
	if (!ist)
	{
		cout << endl << "ERROR : " << *iname << " cannot be opened" << endl;
		cout << "WARNING: PROGRAM WILL CONTINUE WITHOUT INPUT FILE" << endl;
	}
	else 
	{
		cout << endl << "File " << *iname << " successfully opened" << endl;
		cout << endl << "Loading database..." << endl;
		while(!ist.eof())
		{
			getline(ist, junk, '|');		// Searches for word in between ">gi|" and saves as junk to be discarded
			getline(ist, iline.gi, '|');	// Saves the gi ID between the two '|' and saves gi ID under protein struct gi
			getline(ist, junk, '|');		// Removes 'ref' part
			getline(ist, iline.ref, '|');	// Saves the ref ID between the two '|' under protein struct ref
			getline(ist, junk, ' ');		// Removes a space character
			getline(ist, iline.name, '\n'); // Saves the third section of the line under protein struct name
			getline(ist, iline.sequence, '>');	// Saves the sequence after protein line until '>' marker
			(*v).push_back(iline);			// Pushback temporary struct into vector
		}
	}
	cout << endl << "Database loaded with " << (*v).size() << " number of proteins" << endl;
	ist.close();
	return;
}

void onamerequest(string* oname)		// Additional feature to alter output file easily
{
	int input;
	string newfile;
	EntryKey:
	cout << endl << endl;
	cout << "Output File:" << endl;
	cout << "-----------------------------" << endl;
	cout << "The output file will be attempted to be created or overwritten if it exists already" << endl;
	cout << "Default output file is : " << *oname << endl;
	cout << "Available options:" << endl;
	cout << "1: Use Default File" << endl;
	cout << "2: Change output file name" << endl;
	cout << endl << "Input option:";
	cin >> input;
	if (cin.fail() || input > 2 || input < 1)
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Invalid option" << endl << endl;
		goto EntryKey;
	}
	else if (input == 2)
	{
		cin.ignore(10000,'\n');
		cout << "Enter output file name:" << endl ;
		cin >> newfile;
		*oname = newfile; 				// No check function to allow different extensions and etc - Not lazy to create one but don't need one
		cout << endl << endl;
		cout << "Output file name is: " << (*oname) << endl;
	}
	cin.ignore(10000,'\n');
	ofstream ost;								// Section to check if the file can be opened
	ost.open((*oname).c_str(), ios_base::app);	// Append option is selected to allow a construction of another fa file and etc
	if (!ost)
	{
		cout << "ERROR : " << *oname << " cannot be opened" << endl;
		goto EntryKey;
	}
	else 
	{
		cout << "File " << *oname << " successfully opened" << endl;
	}
	ost.close();
}

void mainmenu(int* input)	// Seperate function to print available options and check for error before parsing the input to main function
{
	Menu:
	int in;
	cout << endl << endl;
	cout << "Main Menu" << endl;
	cout << "-----------------------------" << endl;
	cout << "Select one of the following options:" << endl;
	cout << "1: Overview of database" << endl;
	cout << "2: Search by item id" << endl;
	cout << "3: Search by gi id" << endl;
	cout << "4: Search by ref id" << endl;
	cout << "5: Search by keyword" << endl;
	cout << "6: Quit program" << endl;
	cout << endl << "Input option:";
	cin >> in;
	if (cin.fail() || in > 6 || in < 1)
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << endl << "Invalid option selection" << endl;
		goto Menu;
	}
	cin.ignore(10000,'\n');
	*input = in;
}

void database(int totalprotein)
{
	cout << endl << endl; 
	cout << "Amino Acid Codes Database:" << endl;
	cout << "-----------------------------" << endl;
	cout << "A | Alanine" << endl;
	cout << "B | Aspartic acid (D) or Asparagine (N)" << endl;
	cout << "C | Csyteine" << endl;
	cout << "D | Aspartic acid" << endl;
	cout << "E | Glutamic acid" << endl;
	cout << "F | Phenylalanine" << endl;
	cout << "G | Glycine" << endl;
	cout << "H | Histidine" << endl;
	cout << "I | Isoleucine" << endl;
	cout << "J | Leucine (L) or Isoleucine" << endl;
	cout << "K | Lysine" << endl;
	cout << "L | Leucine" << endl;
	cout << "M | Methionine" << endl;
	cout << "N | Asparagine" << endl;
	cout << "O | Pyrolysine" << endl;
	cout << "P | Arginine" << endl;
	cout << "Q | Glutamine" << endl;
	cout << "R | Arginine" << endl;
	cout << "S | Serine" << endl;
	cout << "T | Thereonine" << endl;
	cout << "U | Selenocysteine" << endl;
	cout << "V | Valine" << endl;
	cout << "W | Tryptophan" << endl;
	cout << "Y | Tyrosine" << endl;
	cout << "Z | Glutamic Acid(E) or Glutamine (Q)" << endl;
	cout << "X | Any" << endl; 
	cout << "* | translation stop" << endl;
	cout << "- | gap of indeterminate length" << endl;
	cout << endl << "Total no of proteins: " << totalprotein << endl;
	
	// Table for Nucleic Acid Code
	/*
	string desc;
	for(int i = 0; i < 17; i++)switch (abrev)
	{
		case 0 : desc = "A | Adenine"; break;
		case 1 : desc = "C | Cytosine"; break;
		case 2 : desc = "G | Guanine"; break;
		case 3 : desc = "T | Thymine"; break;
		case 4 : desc = "U | Uracil"; break;
		case 5 : desc = "R | Purine (A or G)"; break;
		case 6 : desc = "Y | Pyramidines (A, T or U)"; break;
		case 7 : desc = "K | Bases which are Ketones (G, T or U)"; break;
		case 8 : desc = "M | Bases with Amino Groups (A or C)"; break;
		case 9 : desc = "S | Strong interaction (C or G)"; break;
		case 10 : desc = "W | Weak interaction (A, T or U)"; break;
		case 11 : desc = "B | not A (C, G, T or U)"; break;
		case 12 : desc = "D | not C (A, G, T or U)"; break;
		case 13 : desc = "H | not G (A, C, T or U)"; break;
		case 14 : desc = "V | not T or U (A, G or C)"; break;
		case 15 : desc = "N | Nucleic acid (A, C, G, T or U)"; break;
		case 16 : desc = "- | gap of indeterminate length"; break;
	}
	*/
}

// Alternate function that reads file "database.txt" for the database overview
/*
void database()
{
	cout << endl << endl; 
	cout << "Amino Acid Codes Database:" << endl;
	cout << "-----------------------------" << endl;
	string iline, idata = "database.txt";
	ifstream ist;
	ist.open(idata.c_str(), ios_base::in);
	if(!ist)
	{
		cout << "File " << idata << " failed to load" << endl;
		return;
	}
	while(getline(ist, iline))
	{
		cout << iline << endl;
	}
}
*/


void search(vector<protein>* v, string* oname, int option) // Search function for all vectors for respective option selection
{
	string sinput, temp;
	int input;
	size_t find;
	vector<int> i;
	EntryKey:
	cout << endl << endl;
	switch (option)
	{
		case 2: // Search by Item ID
		{
			cout << "Search by Item ID Function:" << endl;
			cout << "-----------------------------" << endl;
			cout << "Select 0 to return to Main Menu" << endl;
			cout << (*v).size() << " Item IDs found" << endl;
			cout << endl << "Select an Item ID no :";
			cin >> input;
			if (cin.fail() || input > (*v).size() || input < 0)
			{
				cin.clear();
				cin.ignore(10000,'\n');
				cout << "Invalid option" << endl << endl;
				goto EntryKey;
			}
			cin.ignore(10000,'\n');
			if (input == 0) return;
			input--;	// Reduce input to match with vector array
			goto End;
		}
		case 3:	// Search by gi ID
		{
			cout << "Search by gi ID Function:" << endl;
			cout << "-----------------------------" << endl;
			cout << "Select 0 to return to Main Menu" << endl;
			cout << (*v).size() << " gi IDs found" << endl;
			cout << endl << "Input a gi ID no :";
			cin >> sinput;
			cin.ignore(10000, '\n');
			if (sinput == "0") return;
			for (input = 0 ; input < (*v).size(); ++input)
			{
				if ((*v)[input].gi == sinput)
				{
					goto End;
				}
			}
			cout << "gi ID is either invalid or not found" << endl;
			goto EntryKey;
		}
		case 4:	// Search by ref ID
		{
			cout << "Search by ref ID Function:" << endl;
			cout << "-----------------------------" << endl;
			cout << "Select 0 to return to Main Menu" << endl;
			cout << (*v).size() << " ref IDs found" << endl;
			cout << endl << "Input a ref ID no :";
			cin >> sinput;
			cin.ignore(10000, '\n');
			if (sinput == "0") return;
			for (input = 0 ; input < (*v).size(); ++input)
			{
				if ((*v)[input].ref == sinput)
				{
					goto End;
				}
			}
			cout << "ref ID is either invalid or not found" << endl;
			goto EntryKey;
		}
		case 5:	// Search by keyword
		{
			cout << "Search by keyword Function:" << endl;
			cout << "-----------------------------" << endl;
			cout << "Select 0 to return to Main Menu" << endl;
			cout << (*v).size() << " names found" << endl;
			cout << endl << "Input a keyword:";
			cin >> sinput;
			cin.ignore(10000, '\n');
			if (sinput == "0") return;
			for (input = 0 ; input < (*v).size(); ++input)
			{
				temp = (*v)[input].name;
				find = (temp).find(sinput);
				if (find != string::npos)
				{
					i.push_back(input);
					cout << endl << "-----------------------------" << endl;
					cout << "Option " << i.size();
					cout << endl << "-----------------------------" << endl;
					cout << "item ID:" << input+1 << " | gi ID:" << (*v)[input].gi << " | ref ID:" << (*v)[input].ref << endl;
					cout << (*v)[input].name << endl;
				}
			}
			if(i.size() == 0)
			{
				cout << "Invalid search" <<endl;
				cout << "Restarting function..." << endl;
				goto EntryKey; 
			}
			cout << endl << "-----------------------------" << endl;
			cout << "Option" << i.size() + 1 ;
			cout << endl << "-----------------------------" << endl;
			cout << "Return to Main Menu" << endl << endl;;
			ExitKey:
			cout << "Select the most suitable option from the above" << endl;
			cout << "Input option:";
			cin >> input;
			if (cin.fail() || input > i.size() + 1 || input < 1)
			{
				cin.clear();
				cin.ignore(10000,'\n');
				cout << "Invalid option" << endl << endl;
				goto ExitKey;
			}
			else if (input == i.size() + 1)
			{
				cin.ignore(10000,'\n');
				return;
			}
			cin.ignore(10000,'\n');
			input --;
			input = i[input];
			goto End;
		}		
	}
	End:
	hitmenu (oname, (*v)[input], input);	// Sends oname and the specific protein struct to hitmenu() function
}

void hitmenu (string* oname, protein output, int itemID) // output = (*v)[input], itemID = input
{
	int input, count;
	itemID ++;				// Makes itemID start from 1 not 0
	cout << endl << "Search is successful and returned header:" << endl;
	cout << "gi ID:" << output.gi << " | ref ID:" << output.ref << " | Item ID:" << itemID << endl;
	cout << "Name:" << output.name << endl << endl;
	EntryKey:
	cout << endl << endl;
	cout << "Hit Menu:" << endl;
	cout << "-----------------------------" << endl;
	cout << "Select an option:" << endl;
	cout << "1: Description" << endl;
	cout << "2: Protein sequence" << endl;
	cout << "3: Protein statistics" << endl;
	cout << "4: Record" << endl;
	cout << "5. Return to Main Menu" << endl;
	cout << endl << "Input option:";
	cin >> input;
	if (cin.fail() || input > 5 || input < 1)
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << endl << "Invalid option section" << endl;
		goto EntryKey;
	}
	cin.ignore(10000, '\n');
	switch (input)
	{
		case 1 :	// Prints out details of protein/
		{
			cout << endl << endl << "Description" << endl;
			cout << "-----------------------------" << endl; 
			cout << "Item ID : " << itemID << endl;
			cout << "gi ID : " << output.gi << endl;
			cout << "ref ID : " << output.ref << endl;
			cout << "Protein Name : " << output.name << endl;
			cout << endl << "-----------------------------" << endl;
			goto EntryKey;
			break;
		}
		case 2 :	// Prints out the selected protein sequence
		{
			cout << endl << endl << "Protein sequence" << endl;
			cout << "-----------------------------" << endl; 
			cout << "Selected Protein Sequence: " << endl;
			cout << endl << "-----------------------------" << endl;
			cout << output.sequence << endl;
			cout << endl << "-----------------------------" << endl;
			goto EntryKey;
			break;
		}
		case 3 :	// Outputs the frequency of amino acid found in selected protein
		{
			cout << endl << endl << "Protein statistics" << endl;
			cout << "-----------------------------" << endl; 
			int total = 0;
			char test = 'A';
			for(int i = 0; i < 28 ; i ++)							// Using iteration loop instead of multiple variables and switch statement to save memory
			{
				count = 0;
				for(int j = 0; j < (output.sequence).size() ; j++)
				{
					switch (i)
					{
						case 26 : if ((output.sequence).at(j) == '*') {count++;} break;
						case 27 : if ((output.sequence).at(j) == '-') {count++;} break;
						default : if ((output.sequence).at(j) == (test+i)) {count++;} break;
					}
				}
				if (count > 0)	// Only prints out A.Acid that are found in selected proteins
				{
					switch (i)
					{
						case 26 : cout << "Translation stop '&' : " << count << endl; break;
						case 27 : cout << "Indeterminate gap '-' : " << count << endl; break;
						default: cout << "Amino Acid '" << (char)(test+i) << "' : " << count << endl; break;
					}
				}
				total = total + count;
			}	
			cout << "Selected Protein Length: " << total << endl;
			goto EntryKey;
			break;
		}
		case 4 :	// Save the selected protein to designated output file in .fa file format - Also does not save itemID no
		{
			ofstream ost;
			ost.open((*oname).c_str(), ios_base::app);
			if(!ost)
			{
				cout << "File "<< *oname <<" cannot be read" << endl;
				cout << "Returning to main function" << endl;
				return;
			}
			ost << ">gi|" << output.gi << "|ref|" << output.ref << "| " << output.name << endl;
			ost << output.sequence;
			ost.close();
			cout << "File " << *oname << " successfully written" << endl;
			cout << "Returning to Main Menu" << endl;
			return;
		}
		case 5 : return;
	}
}