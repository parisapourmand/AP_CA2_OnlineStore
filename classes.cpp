#include "classes.hpp"
#include <iostream>

using namespace std;

User::User(const vector<string>& vars)
{	
		firstName = vars[1];
		lastName = vars[2];
		userName = vars[3];
		phoneNum = vars[4];
		money = stoi(vars[5]);
		if(vars[USER_INPUTS_NUM] == "buyer")
			buyer = true;
		else
			seller =true;
}

bool User::operator==(User& u) const
{
	if(firstName == u.firstName && lastName == u.lastName && userName == u.userName &&
		phoneNum == u.phoneNum && money == u.money)
    	return true;
    else
    	return false;
}

Goods::Goods(const vector<string>& vars, Store& store)
{	
	sellerPtr = store.findSeller(vars[1]);
	name = vars[2];
	price = stoi(vars[3]);
	count = stoi(vars[4]);
}

bool Goods::operator==(const Goods& g) 
{
	if( name == g.name && sellerPtr==g.sellerPtr && price == g.price )
    	return true;
    else
    	return false;
}

void Goods::increaseSoldTimes(){
	soldTimes++;
}

Store::Store()
{
	vector<User*> theBuyers;
	vector<User*> theSellers;
	buyerList = theBuyers;
	sellerList = theSellers;
}

void Store::addUser(User* userPtr)
{
	if( userPtr->getBuyer() )
		buyerList.push_back(userPtr);
	if( userPtr->getSeller() )
		sellerList.push_back(userPtr);
}

bool Store::isSeller(const string& userName)
{	
	for (int i = 0; i < sellerList.size(); i++){	
		if(sellerList[i]->getUserName() == userName){
			return true;
		}
	}
	return false;
}

bool Store::isBuyer(const std::string& userName)
{
	for (int i = 0; i < buyerList.size(); i++){	
		if(buyerList[i]->getUserName() == userName){
			return true;
		}
	}
	return false;	
}

User* Store::findSeller(const string& userName)
{
	for (int i = 0; i < sellerList.size(); i++){
		if(sellerList[i]->getUserName() == userName){
			return sellerList[i];
		}
	}
}

User* Store::findBuyer(const string& userName)
{
	for (int i = 0; i < sellerList.size(); i++){
		if(buyerList[i]->getUserName() == userName){
			return buyerList[i];
		}
	}
}

void Store::setMoney(int amount){
			if (amount >= 0)
				money = amount;
};

bool Store::validUserName(User& theUser)
{	
	for (int i = 0; i < sellerList.size(); i++){	
		if( (theUser == *sellerList[i]) && theUser.getSeller())
			return false;
		if((theUser == *sellerList[i]) && theUser.getBuyer())
			break;
		if( theUser.getUserName() == sellerList[i]->getUserName())
			return false;
	}

	for (int i = 0; i < buyerList.size(); i++){	
		if(theUser == (*(buyerList[i])) && theUser.getBuyer())
			return false;
		if(theUser == (*(buyerList[i])) && theUser.getSeller())
			break;
		if( theUser.getUserName() == buyerList[i]->getUserName())
			return false;
	}
	return true;
}

bool Store::isValidUser(const vector<string>& vars)
{ 
	if( (vars.size() != USER_INPUTS_NUM + 1) ||
		( (vars[USER_INPUTS_NUM] != "buyer") && (vars[USER_INPUTS_NUM] != "seller") ) ||
		( !isNonNegativeInt(vars[4]) || !isNonNegativeInt(vars[5]) )
	   )
		return false;
	User dummyUser(vars);
	if( !this->validUserName(dummyUser) )
		return false;
	else
		return true;
}

Stock::Stock(Store& store)
{
	vector<Goods*> theGoods;
	storePtr = &store;
	goodsList = theGoods;
}

bool Stock::validGoods(const vector<string>& vars)
{	
	if( (vars.size() != GOODS_INPUTS_NUM + 1) ||
		( !storePtr->isSeller(vars[1]) ) ||
		( !isNonNegativeInt(vars[3]) || !isNonNegativeInt(vars[4]) )
	   )
		return false;
	else
		return true;
}

void Stock::addGoods(Goods* goods)
{
	for(int i=0; i < goodsList.size(); i++)
		if((*(goodsList[i])) == (*goods)){
			goodsList[i]->setCount(goodsList[i]->getCount() + goods->getCount());
			return;
		}
	goodsList.push_back(goods);
}

vector<Goods*> Stock::searchGoods(const string& name, const int& num)
{
	vector<Goods*> result;
	for (int i = 0; i < goodsList.size(); i++){
		if( (goodsList[i]->getName() == name) && (goodsList[i]->getCount() >= num) )
			result.push_back(goodsList[i]);
	}
	return result;
}

vector<Goods*> Stock::sortGoods(vector<Goods*> theGoods)
{
	//nothing
	return theGoods;
}

bool Stock::isGoodInList(const std::vector<Goods*>& theGoods, const std::string& sellerUserName)
{
	bool result=false;
	for (int i = 0; i < theGoods.size(); i++){
		if(goodsList[i]->getSellerPtr()->getUserName() == sellerUserName)
			result=true;
	}
	return result;
}

Goods* Stock::findGoodFromList(const std::vector<Goods*>& theGoods, const std::string& sellerUserName)
{
	for (int i = 0; i < theGoods.size(); i++){
		if((theGoods[i]->getSellerPtr())->getUserName() == sellerUserName)
			return theGoods[i];
	}
}

int Stock::findGoodNum(const Goods& item)
{
	for (int i = 0; i < goodsList.size(); i++){
		if(((*goodsList[i])) == item)
			return i;
	}
	return -1;
}


bool Stock::validShopping(vector<string>& vars,vector<vector<string> >& shoppingList)
{
	string items;
	string lastString = vars[vars.size()-1];
	char lastChar = lastString[lastString.size()-1];
	vars[vars.size()-1].erase(vars[vars.size()-1].size()-1);
	if( (vars.size() != BUY_INPUTS_NUM + 1) ||
		( !storePtr->isBuyer(vars[1]) )||
		( !isNonNegativeInt(vars[3]) ) 
	   )
		return false;
	if(!isGoodInList(this->searchGoods(vars[2], stoi(vars[3])), vars[vars.size()-1]))
		return false;
	int cost = ( this->findGoodFromList(
			this->searchGoods(vars[2], stoi(vars[3])), vars[vars.size()-1]) )->getPrice() * stoi(vars[3]);
	if(storePtr->findBuyer(vars[1])->getMoney() < 1.05*cost)
		return false;
	if(lastChar == ';'){
		shoppingList.push_back(vars);
		return true;
	}
	if(lastChar == ','){
		shoppingList.push_back(vars);
	}
	else{
		return false;
	}
	while(getline(cin, items))
	{
		if(items[items.size()-1] == ';'){
			items.erase(items.size()-1);
			shoppingList.push_back(extractWords(items));
			break;
		}
		if(items[items.size()-1] == ','){
			items.erase(items.size()-1);
			shoppingList.push_back(extractWords(items));
			continue;
		}
		else
			return false;
	}
	for(int i=1; i<shoppingList.size(); i++){
		if( (shoppingList[i].size() != BUY_INPUTS_NUM-1) ||	!isNonNegativeInt(shoppingList[i][1]) )
			return false;
		if(!isGoodInList(this->searchGoods(shoppingList[i][0], stoi(shoppingList[i][1])), shoppingList[i][2]))
			return false;
		cost = ( this->findGoodFromList(
			this->searchGoods(shoppingList[i][0], stoi(shoppingList[i][1])), shoppingList[i][2]) )->getPrice() *stoi(vars[3]);
		if(storePtr->findBuyer(vars[1])->getMoney() < 1.05*cost)
			return false;
	}
	return true;
}

void Stock::setGoodsCount(int number, Goods& item)
{
	if(number > 0)
		item.setCount(number);
	else if(number == 0)
		goodsList.erase(goodsList.begin() + this->findGoodNum(item));
	else
		abort();
}

void Stock::buyGoods(const vector<vector<string> >& shoppingList)
{
	User* theBuyerPtr = storePtr->findBuyer(shoppingList[0][1]);
	User* theSellerPtr = storePtr->findSeller(shoppingList[0][BUY_INPUTS_NUM]);
	int number = stoi(shoppingList[0][3]);
	Goods* foundGoodPtr =  this->findGoodFromList(searchGoods(shoppingList[0][2], number ), theSellerPtr->getUserName() );
	int cost = (foundGoodPtr->getPrice()) * number;
	if( foundGoodPtr->getSellerPtr() == theSellerPtr ){
		theBuyerPtr->setMoney(theBuyerPtr->getMoney() - 1.05 * cost);
		theSellerPtr->setMoney(theSellerPtr->getMoney() + cost);
		storePtr->setMoney(storePtr->getMoney() + 0.05 * cost);
		this->setGoodsCount(foundGoodPtr->getCount() - number, *foundGoodPtr);
		foundGoodPtr->increaseSoldTimes();
	}
	for(int i=1; i<shoppingList.size(); i++){
		theSellerPtr = storePtr->findSeller(shoppingList[i][2]);
		number = stoi(shoppingList[i][1]);
		foundGoodPtr = this->findGoodFromList(searchGoods(shoppingList[i][0], number ), theSellerPtr->getUserName() );
		cost = (foundGoodPtr->getPrice()) * number;
		if( foundGoodPtr->getSellerPtr() == theSellerPtr ){ 
			theBuyerPtr->setMoney(theBuyerPtr->getMoney() - 1.05 * cost);
			theSellerPtr->setMoney(theSellerPtr->getMoney() + cost);
			storePtr->setMoney(storePtr->getMoney() + 0.05 * cost);
			this->setGoodsCount(foundGoodPtr->getCount() - number, *foundGoodPtr);
			foundGoodPtr->increaseSoldTimes();
		}
	}
}

void Stock::printBestSeller()
{
	for (int i = 0; i < goodsList.size(); i++)
		if(goodsList[i]->getSoldTimes() >= 10)
			cout << i+1 << ". " << goodsList[i]->getName() << ' ' << goodsList[i]->getCount() << ' '
			 << goodsList[i]->getPrice() << ' ' << goodsList[i]->getSellerUserName() << endl;
}

vector<string> extractWords( const string &str )
{
	vector<string> result;
    string::size_type start = 0;
    string::size_type found = str.find(' ', start);

    while (found != string::npos){
        if (found > start)
        	result.push_back(str.substr(start, found - start));
        start = found + 1;
        found = str.find(' ', start);
    }

    result.push_back(str.substr(start));
    return result;
}

bool isNonNegativeInt(const string& str)
{
	for(int i=0; i < str.size(); i++){
		if( str[i] < '0' || str[i] > '9' )
			return false;
	}
	return true;
}