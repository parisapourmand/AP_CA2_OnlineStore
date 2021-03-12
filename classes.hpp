#include <string>
#include <vector>

#define USER_INPUTS_NUM 6
#define BUYER_SELLER_NUM 7
#define GOODS_INPUTS_NUM 4
#define SEARCH_INPUTS_NUM 2
#define BUY_INPUTS_NUM 4
#define ADD_MONEY_INPUTS_NUM 2
#define SALE_INPUTS_NUM 3
#define SPECIAL_INPUTS_NUM 3
#define REQ_INPUTS_NUM 5
#define PRINT_INPUTS_NUM 1

class User
{
	public:
		User(const std::vector<std::string>& vars);
		bool operator==(User& u) const;
		
		bool getBuyer(){
			return buyer;
		};
		bool getSeller(){
			return seller;
		};
		std::string getUserName(){
			return userName;
		};
		void setMoney(int amount){
			if (amount >= 0)
				money = amount;
		};
		int getMoney(){
			return money;
		};

	private:
		std::string firstName;
		std::string lastName;
		std::string userName;
		std::string phoneNum;
		int money;
		bool buyer = false;
		bool seller = false;
};

class Store
{
	public:
		Store();
		bool validUserName(User& theUser);
		bool isValidUser(const std::vector<std::string>& vars);
		void addUser(User* user);
		bool isSeller(const std::string& userName);
		bool isBuyer(const std::string& userName);
		User* findSeller(const std::string& userName);
		User* findBuyer(const std::string& userName);
		void setMoney(int amount);
		int getMoney(){
			return money;
		};

	private:
		std::vector<User*> buyerList;
		std::vector<User*> sellerList;
		int money = 0;		
};

class Goods
{
	public:
		Goods(const std::vector<std::string>& vars, Store& store);
		bool operator==(const Goods& g); 
		void increaseSoldTimes();
		void setCount(int number){
			if (number >= 0)
				count = number;
		};
		std::string getName(){
			return name;
		};
		int getCount(){
			return count;
		};
		int getPrice(){
			return price;
		};
		int getSoldTimes(){
			return soldTimes;
		};		
		User* getSellerPtr(){
			return sellerPtr;
		};
		std::string getSellerUserName(){
			return sellerPtr->getUserName();
		};

	private:
		User* sellerPtr;
		std::string name;
		int price;
		int count;
		int soldTimes = 0;
		bool special = false;
		bool bestSeller =false;

};

class Stock
{
	public:
		Stock(Store& store);
		void addGoods(Goods* goods);
		bool validGoods(const std::vector<std::string>& vars);
		std::vector<Goods*> searchGoods(const std::string& name, const int& num);
		std::vector<Goods*> sortGoods(std::vector<Goods*> theGoods);
		bool isGoodInList(const std::vector<Goods*>& theGoods, const std::string& sellerUserName);
		Goods* findGoodFromList(const std::vector<Goods*>& theGoods, const std::string& sellerUserName);
		int findGoodNum(const Goods& item);
		bool validShopping(std::vector<std::string>& vars, std::vector<std::vector<std::string> >& shoppingList);
		void setGoodsCount(int number, Goods& item);
		void buyGoods(const std::vector<std::vector<std::string> >&);
		void printBestSeller();
		Store* getStorePtr(){
			return storePtr;
		};

	private:
		std::vector<Goods*> goodsList;
		Store* storePtr;
};

std::vector<std::string> extractWords(const std::string& str);
bool isNonNegativeInt(const std::string& input);