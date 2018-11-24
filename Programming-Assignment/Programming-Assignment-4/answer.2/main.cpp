#include <iostream>
#include <sstream>
#include <string>
#include <getopt.h>
#include <map>
#include <set>
#include "equity_transfer.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // First get the opcode
    bool verbose=false;
    bool median=false;
    bool midpoint=false;
    bool transfers=false;
    bool ttt=false;
    int ID=0;
    set<ttt_equity *, comp_ttt_equity> tttEquity_record;

    while(true) {
        static struct option long_options[]={{"verbose",   no_argument,       0, 'v'},
                                             {"median",    no_argument,       0, 'm'},
                                             {"midpoint",  no_argument,       0, 'p'},
                                             {"transfers", no_argument,       0, 't'},
                                             {"ttt",       required_argument, 0, 'c'},
                                             {0, 0,                           0, 0}};
        int option_index=0;
        int c=getopt_long(argc, argv, "g:vmpt", long_options, &option_index);
        if(c==-1) {
            break;
        }
        if(c=='v') {
            verbose=true;
        }
        if(c=='m') {
            median=true;
        }
        if(c=='p') {
            midpoint=true;
        }
        if(c=='t') {
            transfers=true;
        }
        if(c=='c') {
            ttt=true;
            auto temp_equity=new ttt_equity;
            temp_equity->ID=ID;
            temp_equity->equity_symbol=optarg;
            temp_equity->timestamp_buy=-1;
            temp_equity->timestamp_sell=-1;
            temp_equity->price_buy=0;
            temp_equity->price_sell=0;
            tttEquity_record.insert(temp_equity);
            ID++;
            break;
        }
    }

    // Second, generate some data.

    int current_timestamp=0;
    int next_ID=0;

    int TIMESTAMP=0;
    string CLIENT_NAME;
    string BUY_OR_SELL;
    bool buy_signal=false;
    string EQUITY_SYMBOL;
    string limit_price;
    int LIMIT_PRICE=0;
    string quantity;
    int QUANTITY=0;
    int DURATION=0;

    int count_amount=0;
    int count=0;
    int count_transfer=0;
    int single_commission=0;
    int total_commission=0;

    map<string, equitybook> orderAll;

    set<Order *, comp_buy> *orderBuy_ptr=nullptr;
    set<Order *, comp_sell> *orderSell_ptr=nullptr;

    map<string, client_record *> clientAll;
    stringstream ss;

    while(!cin.eof()) {
        string str;
        getline(cin, str);
        if(str.empty()) {
            break;
        }
        ss.clear();
        ss.str(str);
        ss>>TIMESTAMP>>CLIENT_NAME>>BUY_OR_SELL>>EQUITY_SYMBOL>>limit_price>>quantity>>DURATION;;
        LIMIT_PRICE=atoi(limit_price.substr(1, limit_price.length()).c_str());
        QUANTITY=atoi(quantity.substr(1, quantity.length()).c_str());

        if(BUY_OR_SELL=="BUY") {
            buy_signal=true;
        }
        else if(BUY_OR_SELL=="SELL") {
            buy_signal=false;
        }
        else {
            exit(0);
        }

        auto client_record_temp=new client_record;
        client_record_temp->name=CLIENT_NAME;
        client_record_temp->buy_count=0;
        client_record_temp->sell_count=0;
        client_record_temp->net_count=0;
        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));


        for(auto tttEquity_record_it=tttEquity_record.begin();
            tttEquity_record_it!=tttEquity_record.end(); ++tttEquity_record_it) {
            if((*tttEquity_record_it)->equity_symbol==EQUITY_SYMBOL) {
                auto tttEquity_ptr=(*tttEquity_record_it);
                if(!buy_signal) {
                    if(tttEquity_ptr->timestamp_buy==-1||tttEquity_ptr->price_buy>LIMIT_PRICE) {
                        tttEquity_ptr->price_buy=LIMIT_PRICE;
                        tttEquity_ptr->timestamp_buy=TIMESTAMP;
                        tttEquity_record.insert(tttEquity_ptr);
                    }
                }
                else {
                    if(tttEquity_ptr->timestamp_buy==-1) {
                        break;
                    }
                    if(tttEquity_ptr->timestamp_sell==-1||tttEquity_ptr->price_sell<LIMIT_PRICE) {
                        tttEquity_ptr->price_sell=LIMIT_PRICE;
                        tttEquity_ptr->timestamp_sell=TIMESTAMP;
                        tttEquity_record.insert(tttEquity_ptr);
                    }
                }
            }
        }

        if(TIMESTAMP!=current_timestamp) {
            if(median) {
                do_median(orderAll, current_timestamp);
            }
            if(midpoint) {
                do_midpoint(orderAll, current_timestamp);
            }
            current_timestamp=TIMESTAMP;

            do_expire(orderAll, orderBuy_ptr, orderSell_ptr, current_timestamp);

        }

        auto orderAll_it=orderAll.find(EQUITY_SYMBOL);
        if(orderAll_it==orderAll.end()) {
            equitybook equitybook_temp=equitybook();
            equitybook_temp.EQUITY_SYMBOL=EQUITY_SYMBOL;
            orderAll_it=orderAll.insert(make_pair(EQUITY_SYMBOL, (equitybook_temp))).first;
        }

        if(buy_signal) {
            do_transact_buy(orderAll, clientAll, current_timestamp, orderAll_it, QUANTITY, LIMIT_PRICE, next_ID,
                            transfers, CLIENT_NAME, verbose, EQUITY_SYMBOL, count_amount, count, count_transfer,
                            single_commission, total_commission);
        }
        else {
            deal_sell(orderAll, clientAll, current_timestamp, orderAll_it, QUANTITY, LIMIT_PRICE, next_ID,
                      transfers, CLIENT_NAME, verbose, EQUITY_SYMBOL, count_amount, count, count_transfer,
                      single_commission, total_commission);
        }
        if(QUANTITY>0&&DURATION!=0) {
            auto Order_temp=new Order;
            Order_temp->ID=next_ID++;
            Order_temp->PRICE=LIMIT_PRICE;
            Order_temp->NAME=CLIENT_NAME;
            Order_temp->AMOUNT=QUANTITY;
            Order_temp->EXPIRE_TIME=(DURATION!=-1)?(current_timestamp+DURATION):-1;
            if(buy_signal) {
                orderBuy_ptr=&(orderAll_it->second.orderBuy);
                orderBuy_ptr->insert(Order_temp);
            }
            else {
                orderSell_ptr=&(orderAll_it->second.orderSell);
                orderSell_ptr->insert(Order_temp);
            }
        }
    }

    if(median) {
        do_median(orderAll, current_timestamp);
    }

    if(midpoint) {
        do_midpoint(orderAll, current_timestamp);
    }

    final_print(count_amount, count, count_transfer, single_commission, total_commission);

    if(transfers) {
        do_transfers(clientAll);
    }

    if(ttt) {
        for(auto tttEquity_record_it=tttEquity_record.begin();
            tttEquity_record_it!=tttEquity_record.end(); ++tttEquity_record_it) {
            if((*tttEquity_record_it)->timestamp_buy<0||(*tttEquity_record_it)->timestamp_sell<0) {
                continue;
            }
            else {
                cout<<"Time travelers would buy "<<(*tttEquity_record_it)->equity_symbol<<" at time: "
                    <<(*tttEquity_record_it)->timestamp_buy<<" and sell it at time: "
                    <<(*tttEquity_record_it)->timestamp_sell<<endl;
            }
        }
    }
    return 0;
}



