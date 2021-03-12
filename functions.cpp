#include "functions.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool executeCommand(const string &commandLine,Stock& stock)
{
	vector<string> commandWords = extractWords(commandLine);

	if(commandWords[0] == "add_user")
		return addUser(commandWords, *(stock.getStorePtr()));
	if(commandWords[0] == "add_goods")
		return addGoods(commandWords, stock);
	if(commandWords[0] == "search")
		return search(commandWords, stock);	
	if(commandWords[0] == "buy")
		return buy(commandWords, stock);
	if(commandWords[0] == "search_bestseller")
		return searchBestseller(stock);
	if(commandWords[0] == "add_money")
		return addMoney(commandWords, *(stock.getStorePtr()));
	// else if(commandWords[0] == "add_special")
	// 	cout<<"in special";
	// else if(commandWords[0] == "remove_special")
	// 	cout<<"in remove";
	// if(commandWords[0] == "sale")
	// 	cout<<"in sale";
	// else if(commandWords[0] == "search_sale")
	// 	cout<<"ain search sale";
	// else if(commandWords[0] == "print_factor")
	// 	cout<<"print_factor";
	else
	 return false;
}

bool addUser(const vector<string>& command, Store& store)
{
	bool result = store.isValidUser(command);
	if (!result)
		return false;
	User* userPtr = new User(command);
	store.addUser(userPtr);
	return true;
}

bool addGoods(const vector<string>& command, Stock& stock)
{
	bool result = stock.validGoods(command);
	if (!result)
		return false;
	Goods* goodsPtr = new Goods(command, *(stock.getStorePtr()));
	stock.addGoods(goodsPtr);
	return true;
}

bool search(const vector<string>& command, Stock& stock)
{
	if( (command.size() != SEARCH_INPUTS_NUM + 1) || !isNonNegativeInt(command[SEARCH_INPUTS_NUM]))
		return false;
	vector<Goods*> found = stock.searchGoods(command[1],stoi(command[2]));
	stock.sortGoods(found);
	for(int i=0; i < found.size(); i++)
		cout << i+1 << ". " << found[i]->getName() << ' ' << found[i]->getCount() << ' '
			 << found[i]->getPrice() << ' ' << found[i]->getSellerUserName() << endl;
	return true;
}

bool buy(vector<string>& command, Stock& stock)
{
	vector<vector<string> > shoppingList;
	if( !stock.validShopping(command, shoppingList) )
		return false;
	stock.buyGoods(shoppingList);
	return true;
}

bool searchBestseller(Stock& stock){
	stock.printBestSeller();
	return true;
}

bool addMoney(const vector<string>& command, Store& store){
	if( (command.size() != ADD_MONEY_INPUTS_NUM + 1) || !isNonNegativeInt(command[ADD_MONEY_INPUTS_NUM]) )
		return false;
	if(store.isSeller(command[1])){
		store.findSeller(command[1])->setMoney(store.findSeller(command[1])->getMoney() + stoi(command[ADD_MONEY_INPUTS_NUM]));
		return true;	
	}
	if(store.isBuyer(command[1])){
		store.findBuyer(command[1])->setMoney(store.findBuyer(command[1])->getMoney() + stoi(command[ADD_MONEY_INPUTS_NUM]));
		return true;	
	}
	return false;
}