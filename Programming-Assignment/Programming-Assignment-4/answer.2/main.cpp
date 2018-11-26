#include <iostream>
#include <sstream>
#include <getopt.h>
#include "equity_transfer.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // First get the opcode
    bool verbose=false;
    bool midpoint=false;
    bool transfers=false;
    bool median=false;
    bool ttt=false;
    int ID=0;
    set<ttt_price *, ttt_equity> ttt_quity_set;

    // while(true) {
    //     const option long_options[] =       {{"verbose",   no_argument,       0, 'v'},
    //                                          {"median",    no_argument,       0, 'm'},
    //                                          {"midpoint",  no_argument,       0, 'p'},
    //                                          {"transfers", no_argument,       0, 't'},
    //                                          {"ttt",       required_argument, 0, 'g'},
    //                                          {0, 0,                           0, 0}};
    //     int option_index=0;
    //     int c=getopt_long(argc, argv, "vmptg:", long_options, NULL);
    //     if(c==-1) {
    //         break;
    //     }
    //     else if(c=='v') {
    //         verbose=true;
    //     }
    //     else if(c=='m') {
    //         median=true;
    //     }
    //     else if(c=='p') {
    //         midpoint=true;
    //     }
    //     else if(c=='t') {
    //         transfers=true;
    //     }
    //     else if(c=='g') {
    //         ttt=true;
    //         auto equity_temp=new ttt_price;
    //         equity_temp->ID=ID;
    //         equity_temp->equity_symbol=optarg;
    //         equity_temp->timestamp_buy=-1;
    //         equity_temp->timestamp_sell=-1;
    //         equity_temp->price_buy=0;
    //         equity_temp->price_sell=0;
    //         ttt_quity_set.insert(equity_temp);
    //         cerr<<"B: ttt_quity_set.size() = "<<ttt_quity_set.size()<<endl; 
    //         ID++;
    //         break;
    //     }
    // }
    int c;
    while (true) {
        const option long_options[] = {
                {"verbose",   no_argument,       NULL, 'v'},
                {"median",    no_argument,       NULL, 'm'},
                {"midpoint",  no_argument,       NULL, 'p'},
                {"transfers", no_argument,       NULL, 't'},
                {"ttt",       required_argument, NULL, 'g'},
                {0, 0, 0,                              0}
        };
        int option_index = 0;
        c = getopt_long(argc, argv, "vmptg:", long_options, &option_index);
        if (c == -1) break;
        switch (c) {
            case '?':
                cerr<<"???"<<endl;
                break;
            default:
                abort ();
            case 'v':
                verbose = true;
                break;
            case 'm':
                median = true;
                break;
            case 'p':
                midpoint = true;
                break;
            case 't':
                transfers = true;
                break;
            case 'g':
                ttt=true;
                auto equity_temp=new ttt_price;
                equity_temp->ID=ID;
                equity_temp->equity_symbol=optarg;
                equity_temp->timestamp_buy=-1;
                equity_temp->timestamp_sell=-1;
                equity_temp->price_buy=0;
                equity_temp->price_sell=0;
                ttt_quity_set.insert(equity_temp);
                // cerr<<"B: ttt_quity_set.size() = "<<ttt_quity_set.size()<<endl; 
                ID++;
                break;

        }
    }

    // Second, generate some data.
    int timestamp_now=0;
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

    map<string, equity_book> order_map;
    set<equity *, equity_buy> *order_buy_set=nullptr;
    set<equity *, equity_sell> *order_sell_set=nullptr;
    map<string, client_equity *> client_map;
    stringstream stream_temp;
    while(!cin.eof()) {
        string str;
        getline(cin, str);
        if(str.empty()) {
            break;
        }
        stream_temp.clear();
        stream_temp.str(str);
        stream_temp>>TIMESTAMP>>CLIENT_NAME>>BUY_OR_SELL>>EQUITY_SYMBOL>>limit_price>>quantity>>DURATION;;
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

        auto client_equity_temp=new client_equity;
        client_equity_temp->name=CLIENT_NAME;
        client_equity_temp->buy_count=0;
        client_equity_temp->sell_count=0;
        client_equity_temp->net_count=0;
        client_map.insert(make_pair(CLIENT_NAME, (client_equity_temp)));


        for(auto tttEquity_equity_it=ttt_quity_set.begin();
            tttEquity_equity_it!=ttt_quity_set.end(); ++tttEquity_equity_it) {

            if((*tttEquity_equity_it)->equity_symbol==EQUITY_SYMBOL) {
                auto ttt_equity_pt=(*tttEquity_equity_it);
                // if(!buy_signal) {
                //     if(ttt_equity_pt->timestamp_buy==-1||ttt_equity_pt->price_buy>LIMIT_PRICE) {
                //         ttt_equity_pt->price_buy=LIMIT_PRICE;
                //         ttt_equity_pt->timestamp_buy=TIMESTAMP;
                //         ttt_quity_set.insert(ttt_equity_pt);
                //     }
                // }
                // else {
                //     if(ttt_equity_pt->timestamp_buy==-1) {
                //         break;
                //     }
                //     if((ttt_equity_pt->timestamp_sell==-1||ttt_equity_pt->price_sell<LIMIT_PRICE)) {
                //         ttt_equity_pt->price_sell=LIMIT_PRICE;
                //         ttt_equity_pt->timestamp_sell=TIMESTAMP;
                //         ttt_quity_set.insert(ttt_equity_pt);
                //     }
                // }
                if(buy_signal) {
                    //我卖别人买
                    if(ttt_equity_pt->timestamp_buy==-1) {
                        ttt_equity_pt->buy_flag=false;
                        break;
                    }
                    else if(ttt_equity_pt->timestamp_sell==-1||(ttt_equity_pt->price_sell<LIMIT_PRICE &&ttt_equity_pt->buy_flag==true)) {
                        ttt_equity_pt->price_sell=LIMIT_PRICE;
                        ttt_equity_pt->timestamp_sell=TIMESTAMP;
                        ttt_equity_pt->price_earn_max=ttt_equity_pt->price_sell-ttt_equity_pt->price_buy;
                        ttt_quity_set.insert(ttt_equity_pt);
                        
                    }
                    if (ttt_equity_pt->buy_flag==true && (ttt_equity_pt->price_sell-ttt_equity_pt->price_buy_temp)>ttt_equity_pt->price_earn_max)
                    {
                        ttt_equity_pt->timestamp_buy=ttt_equity_pt->timestamp_buy_temp;
                        ttt_equity_pt->price_buy=ttt_equity_pt->price_buy_temp;
                        ttt_equity_pt->price_earn_max=ttt_equity_pt->price_sell-ttt_equity_pt->price_buy;
                        ttt_equity_pt->buy_flag=false;
                    }
                }
                else {
                    //别人卖我买
                    if(ttt_equity_pt->timestamp_buy==-1) {
                        ttt_equity_pt->price_buy=LIMIT_PRICE;
                        ttt_equity_pt->timestamp_buy=TIMESTAMP;
                        ttt_equity_pt->buy_flag=false;
                        ttt_equity_pt->price_earn_max=ttt_equity_pt->price_sell-ttt_equity_pt->price_buy;
                        ttt_quity_set.insert(ttt_equity_pt);
                    }
                    else if(ttt_equity_pt->price_buy>LIMIT_PRICE){
                        ttt_equity_pt->buy_flag=true;
                        ttt_equity_pt->timestamp_buy_temp=TIMESTAMP;
                        ttt_equity_pt->price_buy_temp=LIMIT_PRICE;
                    }
                }
            }
        }

        if(TIMESTAMP!=timestamp_now) {
            if(median) {
                get_median(order_map, timestamp_now);
            }
            if(midpoint) {
                get_midpoint(order_map, timestamp_now);
            }
            timestamp_now=TIMESTAMP;

            get_expire(order_map, order_buy_set, order_sell_set, timestamp_now);

        }

        auto order_all_iterator=order_map.find(EQUITY_SYMBOL);
        if(order_all_iterator==order_map.end()) {
            equity_book equitybook_temp=equity_book();
            equitybook_temp.EQUITY_SYMBOL=EQUITY_SYMBOL;
            order_all_iterator=order_map.insert(make_pair(EQUITY_SYMBOL, (equitybook_temp))).first;
        }

        if(buy_signal) {
            deal_buy(order_map, client_map, timestamp_now, order_all_iterator, QUANTITY, LIMIT_PRICE, next_ID,
                     transfers, CLIENT_NAME, verbose, EQUITY_SYMBOL, count_amount, count, count_transfer,
                     single_commission, total_commission);
        }
        else {
            deal_sell(order_map, client_map, timestamp_now, order_all_iterator, QUANTITY, LIMIT_PRICE, next_ID,
                      transfers, CLIENT_NAME, verbose, EQUITY_SYMBOL, count_amount, count, count_transfer,
                      single_commission, total_commission);
        }
        if(QUANTITY>0&&DURATION!=0) {
            auto Order_temp=new equity;
            Order_temp->ID=next_ID++;
            Order_temp->PRICE=LIMIT_PRICE;
            Order_temp->NAME=CLIENT_NAME;
            Order_temp->AMOUNT=QUANTITY;
            Order_temp->EXPIRE_TIME=(DURATION!=-1)?(timestamp_now+DURATION):-1;
            if(buy_signal) {
                order_buy_set=&(order_all_iterator->second.orderBuy);
                order_buy_set->insert(Order_temp);
            }
            else {
                order_sell_set=&(order_all_iterator->second.orderSell);
                order_sell_set->insert(Order_temp);
            }
        }
    }

    if(median) {
        get_median(order_map, timestamp_now);
    }

    if(midpoint) {
        get_midpoint(order_map, timestamp_now);
    }

    final_print(count_amount, count, count_transfer, total_commission);

    if(transfers) {
        get_transfers(client_map);
    }
    int jik = 0;
    if(ttt) {
        for(auto tttEquity_record_it=ttt_quity_set.begin();
            tttEquity_record_it!=ttt_quity_set.end(); tttEquity_record_it++) {
            // cerr<<"ERROR1: "<<jik++ <<endl;
            if((*tttEquity_record_it)->timestamp_buy<0||(*tttEquity_record_it)->timestamp_sell<0) {
                // cerr<<"FUCK error"<<endl;
                cout<<"Time travelers would buy "<<(*tttEquity_record_it)->equity_symbol<<" at time: "
                    <<-1<<" and sell it at time: "
                    <<-1<<endl;
                continue;
            }
            else {
                cout<<"Time travelers would buy "<<(*tttEquity_record_it)->equity_symbol<<" at time: "
                    <<(*tttEquity_record_it)->timestamp_buy<<" and sell it at time: "
                    <<(*tttEquity_record_it)->timestamp_sell<<endl;
            }
            // cerr<<"ERROR2: "<<jik++ <<endl;
        }
        // auto tttEquity_record_it=ttt_quity_set.begin();
        // cerr<<"A: ttt_quity_set.size() = "<<ttt_quity_set.size()<<endl; 
        // while(tttEquity_record_it != ttt_quity_set.end()){
        //     cerr<<"ERROR1: "<<jik++ <<endl;
        //     if((*tttEquity_record_it)->timestamp_buy<0||(*tttEquity_record_it)->timestamp_sell<0) {
        //         cerr<<"FUCK error"<<endl;
        //         continue;
        //     }
        //     else {
        //         cout<<"Time travelers would buy "<<(*tttEquity_record_it)->equity_symbol<<" at time: "
        //             <<(*tttEquity_record_it)->timestamp_buy<<" and sell it at time: "
        //             <<(*tttEquity_record_it)->timestamp_sell<<endl;
        //     }
        //     cerr<<"ERROR2: "<<jik++ <<endl;
        //     tttEquity_record_it++;


        // }
    }
    return 0;
}



