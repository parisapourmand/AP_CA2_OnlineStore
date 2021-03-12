#include "classes.hpp"
#include <string>
#include <vector>

bool addUser(const std::vector<std::string>& command, Store& store);
bool addGoods(const std::vector<std::string>& command, Stock& stock);
bool search(const std::vector<std::string>& command, Stock& stock);
bool buy(std::vector<std::string>& command, Stock& stock);
bool searchBestseller(Stock& stock);
bool addMoney(const std::vector<std::string>& command, Store& store);
bool executeCommand(const std::string& line, Stock& stock);