#ifndef EQUITY_TRANSFER_H
#define EQUITY_TRANSFER_H

// #include <iostream>
// #include <sstream>
// #include <string>
// #include <getopt.h>
#include <map>
#include <set>

using namespace std;

class Order {
public:
    int ID;
    string NAME;
    int AMOUNT;
    int PRICE;
    int EXPIRE_TIME;
};

struct comp_buy {
    bool operator()(const Order *a, const Order *b) const {
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

struct comp_sell {
    bool operator()(const Order *a, const Order *b) const {
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

class equitybook {
public:
    string EQUITY_SYMBOL;
    set<Order *, comp_buy> orderBuy;
    set<Order *, comp_sell> orderSell;
    multiset<int> history;
};

class ttt_equity {
public:
    int ID;
    string equity_symbol;
    int timestamp_buy;
    int timestamp_sell;
    int price_buy;
    int price_sell;
};

struct comp_ttt_equity {
    bool operator()(const ttt_equity *a, const ttt_equity *b) const {
        return a->ID<b->ID;
    }
};

class client_record {
public:
    string name="";
    int buy_count=0;
    int sell_count=0;
    int net_count=0;
};

struct comp_client_record {
    bool operator()(const client_record &a, const client_record &b) const {
        return a.name<b.name;
    }
};


//////////////////////////////////////////////////////////////

void do_median(map<string, equitybook> &orderAll, int current_timestamp);

void do_midpoint(map<string, equitybook> &orderAll, int current_timestamp);

void do_transfers(map<string, client_record *> &clientAll);

void do_expire(map<string, equitybook> &orderAll, set<Order *, comp_buy> *orderBuy_ptr,
               set<Order *, comp_sell> *orderSell_ptr, int current_timestamp);

void do_transact_buy(map<string, equitybook> &orderAll, map<string, client_record *> &clientAll, int current_timestamp,
                     map<string, equitybook>::iterator orderAll_it, int &QUANTITY, int LIMIT_PRICE, int next_ID,
                     bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &count_amount,
                     int &count, int &count_transfer, int &single_commission, int &total_commission);

void deal_sell(map<string, equitybook> &orderAll, map<string, client_record *> &clientAll, int current_timestamp,
               map<string, equitybook>::iterator orderAll_it, int &QUANTITY, int LIMIT_PRICE, int next_ID,
               bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &count_amount,
               int &count, int &count_transfer, int &single_commission, int &total_commission);

void final_print(int count_num, int count, int count_transfer, int single_commission, int total_commission);

//////////////////////////////////////////////////////////////

#endif 

