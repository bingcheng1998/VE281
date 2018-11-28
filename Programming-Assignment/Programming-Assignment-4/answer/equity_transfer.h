#ifndef EQUITY_TRANSFER_H
#define EQUITY_TRANSFER_H

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class equity {
public:
    int ID;
    string NAME;
    int AMOUNT;
    int PRICE;
    int EXPIRE_TIME;
};

struct equity_buy {
    bool operator()(const equity *a, const equity *b) const {
        if(a->PRICE>b->PRICE) {
            return true;
        }
        else if(a->PRICE==b->PRICE) {
            return a->ID<b->ID;
        }
        else {
            return false;
        }
    }
};

struct equity_sell {
    bool operator()(const equity *a, const equity *b) const {
        if(a->PRICE>b->PRICE) {
            return false;
        }
        else if(a->PRICE==b->PRICE) {
            return a->ID<b->ID;
        }
        else {
            return true;
        }
    }
};

class equity_book {
public:
    string EQUITY_SYMBOL;
    set<equity *, equity_buy> orderBuy;
    set<equity *, equity_sell> orderSell;
    multiset<int> history;
};

class ttt_price {
public:
    int ID;
    string equity_symbol;
    int timestamp_buy;
    int timestamp_sell;
    int price_buy;
    int price_sell;
    int price_buy_temp;
    int timestamp_buy_temp;
    int price_earn_max;
    bool buy_flag;
};

struct ttt_equity {
    bool operator()(const ttt_price *a, const ttt_price *b) const {
        return a->ID<b->ID;
    }
};

class client_equity {
public:
    string name="";
    int buy_count=0;
    int sell_count=0;
    int net_count=0;
};

void get_median(map<string, equity_book> &order_map, int timestamp_now);

void get_midpoint(map<string, equity_book> &order_list, int timestamp_now);

void get_transfers(map<string, client_equity *> &client_map);

void get_expire(map<string, equity_book> &order_list, set<equity *, equity_buy> *order_buy_set,
                set<equity *, equity_sell> *order_sell_set, int timestamp_now);

void deal_buy(map<string, equity_book> &order_list, map<string, client_equity *> &client_map, int timestamp_now,
              map<string, equity_book>::iterator order_all_iterator, int &QUANTITY, int LIMIT_PRICE, int next_ID,
              bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &NUMBER_OF_COMPLETED_TRADES,
              int &count, int &NUMBER_OF_SHARES_TRADED, int &COMMISION_EARNINGS, int &MONEY_TRANSFERRED);

void deal_sell(map<string, equity_book> &order_map, map<string, client_equity *> &client_map, int timestamp_now,
               map<string, equity_book>::iterator order_all_iterator, int &QUANTITY, int LIMIT_PRICE, int next_ID,
               bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &count_num,
               int &NUMBER_OF_COMPLETED_TRADES, int &NUMBER_OF_SHARES_TRADED, int &COMMISION_EARNINGS,
               int &MONEY_TRANSFERRED);

void final_print(int NUMBER_OF_SHARES_TRADED, int NUMBER_OF_COMPLETED_TRADES, int MONEY_TRANSFERRED,
                 int COMMISION_EARNINGS);

#endif 

