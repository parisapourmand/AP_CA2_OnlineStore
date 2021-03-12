#include "functions.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Store myStore;
	Stock myStock(myStore);
	string commandLine;
	while(getline(cin, commandLine))
	{
		if( !executeCommand(commandLine, myStock) )
			cout << "Command Failed" << endl;
		else
			cout << "Command OK" << endl;
	}
	return 0;
}