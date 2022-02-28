#include <vector>
#include <list>       
#include <string>     
#include <algorithm>  
#include <functional> 
#include <iostream>   
#include <fstream>    
#include <string.h>  
#include <unistd.h>   
#include <stdlib.h>   
#include <termios.h>
#include <unistd.h>

#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

int main()
{
	char choice;
	int capacity = 0;
	string username;
	string password;
	string newPassword;
	pair<string, string> p;
	char * filename = new char[100];
	
	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	

	
	cout << "Enter preferred hash table capacity: ";
	cin >> capacity;
	PassServer ps(capacity); 
	
	
	while(choice != 'x')
	{
		Menu();
		cin >> choice;
		
		switch(choice)
		{
			case 'l':
				cout << "Enter password file name to load from: ";
				cin >> filename;
				ps.load(filename);
				break;
			case 'a':
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				cin >> password;
				tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
					
				p.first = username;
				p.second =password;
				if(ps.addUser(p))
					cout << "\nUser " << username << " added.\n";
				else 
					cout << "\n*****Error: User already exists. Could not add user.\n";
				break;
			case 'r':
				cout << "Enter username: ";
				cin >> username;
				if(ps.removeUser(username))
					cout << "User " << username << " deleted\n";
				else 
					cout << "*****Error:User not found. Could not delete user\n";
				break;
			case 'c':
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				cin >> password;
				tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

				cout << "\nEnter new password: ";
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);
				cin >> newPassword;
				tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

				p.first = username;
				p.second =password;
				
				if(ps.changePassword(p, newPassword))
					cout << "\nPassword changed for user " << username;
				else 
					cout << "\n*****Error: Could not change user password\n";
				break;

			case 'f':
				cout << "Enter username: ";
				cin >> username;
				if(ps.find(username))
					cout << "\nUser '" << username << "' found";
				else 
					cout << "\nUser '" << username << "' not found"; 
				break;
			case 'd':
				ps.dump();

				break;
			case 's':
				cout << "Size of hashtable: " << ps.size();
				break;
			case 'w':
				cout << "Enter password file name to write to: ";
				cin >> filename;
				ps.write_to_file(filename);
				break;
			case 'x':
				return 0;
			default:
				cout << "*****Error: Invalid entry.  Try again.";
				break;
		}
			
	}
}

void Menu()
{
	cout << "\n\n";
	cout << "l - Load From File" << endl;
	cout << "a - Add User" << endl;
	cout << "r - Remove User" << endl;
	cout << "c - Change User Password" << endl;
	cout << "f - Find User" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to Password File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}