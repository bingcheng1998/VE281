#include "equity_transfer.h"

using namespace std;

void get_median(map<string, equity_book> &order_map, int timestamp_now) {
    int median_price=0;
    for(auto orderAll_it=order_map.begin(); orderAll_it!=order_map.end(); ++orderAll_it) {
        ssize_t size=orderAll_it->second.history.size();
        if(size!=0) {
            bool even=(size%2==0);
            size/=2;
            auto median_price_it=orderAll_it->second.history.begin();
            for(auto i=0; i<size; ++i) {
                ++median_price_it;
            }
            if(!even) {
                median_price=*median_price_it;
            }
            else {
                median_price=((*median_price_it)+*(--median_price_it))/2;
            }
            cout<<"Median match price of "<<orderAll_it->second.EQUITY_SYMBOL<<" at time "<<timestamp_now<<" is $"
                <<median_price<<endl;
        }
        else {
            continue;
        }
    }
}

void get_midpoint(map<string, equity_book> &order_list, int timestamp_now) {
    for(auto orderAll_it=order_list.begin(); orderAll_it!=order_list.end(); ++orderAll_it) {
        if(orderAll_it->second.orderBuy.empty()||orderAll_it->second.orderSell.empty()) {
            cout<<"Midpoint of "<<orderAll_it->second.EQUITY_SYMBOL<<" at time "<<timestamp_now<<" is undefined"
                <<endl;
            continue;
        }
        auto midpoint_price=
                ((*orderAll_it->second.orderBuy.begin())->PRICE+(*orderAll_it->second.orderSell.begin())->PRICE)/2;
        cout<<"Midpoint of "<<orderAll_it->second.EQUITY_SYMBOL<<" at time "<<timestamp_now<<" is $"<<midpoint_price
            <<endl;
    }
}

void get_transfers(map<string, client_equity *> &client_map) {
    for(auto clientAll_it=client_map.begin(); clientAll_it!=client_map.end(); ++clientAll_it) {
        cout<<clientAll_it->second->name<<" bought "<<clientAll_it->second->buy_count<<" and sold "
            <<clientAll_it->second->sell_count<<" for a net transfer of $"<<clientAll_it->second->net_count<<endl;
    }
}

void get_expire(map<string, equity_book> &order_list, set<equity *, equity_buy> *order_buy_set,
                set<equity *, equity_sell> *order_sell_set, int timestamp_now) {
    set<equity *, equity_sell>::iterator Sell_set_it;
    set<equity *, equity_sell>::iterator Sell_set_it_temp;
    set<equity *, equity_buy>::iterator buy_set_it;
    set<equity *, equity_sell>::iterator buy_set_it_temp;
    for(auto orderAll_it=order_list.begin(); orderAll_it!=order_list.end(); ++orderAll_it) {
        order_sell_set=&(orderAll_it->second.orderSell);
        for(Sell_set_it=order_sell_set->begin(); Sell_set_it!=order_sell_set->end();) {
            if((*Sell_set_it)->EXPIRE_TIME!=-1&&(*Sell_set_it)->EXPIRE_TIME<=timestamp_now) {
                Sell_set_it_temp=Sell_set_it;
                Sell_set_it=order_sell_set->erase(Sell_set_it_temp);
            }
            else {
                ++Sell_set_it;
            }
        }
        order_buy_set=&(orderAll_it->second.orderBuy);
        for(buy_set_it=order_buy_set->begin(); buy_set_it!=order_buy_set->end();) { // bug here
            if((*buy_set_it)->EXPIRE_TIME!=-1&&(*buy_set_it)->EXPIRE_TIME<=timestamp_now) {
                buy_set_it_temp=buy_set_it;
                buy_set_it=order_buy_set->erase(buy_set_it_temp);
            }
            else {
                ++buy_set_it;
            }
        }
    }
}

void deal_buy(map<string, equity_book> &order_list, map<string, client_equity *> &client_map, int timestamp_now,
              map<string, equity_book>::iterator order_all_iterator, int &QUANTITY, int LIMIT_PRICE, int next_ID,
              bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &NUMBER_OF_COMPLETED_TRADES,
              int &count, int &NUMBER_OF_SHARES_TRADED, int &COMMISION_EARNINGS, int &MONEY_TRANSFERRED) {
    auto transact_price=0;

    auto orderSell_ptr=&(order_all_iterator->second.orderSell);

    while(QUANTITY>0&&!orderSell_ptr->empty()) {
        if((*orderSell_ptr->begin())->PRICE<=LIMIT_PRICE) {
            auto order_pt=*orderSell_ptr->begin();
            if(order_pt->ID>=next_ID) {
                transact_price=LIMIT_PRICE;
            }
            else {
                transact_price=order_pt->PRICE;
            }

            auto equitybook_ptr=&(order_all_iterator->second);
            equitybook_ptr->history.insert(transact_price);

            if(order_pt->AMOUNT>QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=client_map.find(CLIENT_NAME);
                    bool find_buyer=!(clientAll_it_1==client_map.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        client_map.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto client_map_pt_A=(clientAll_it_1->second);
                        client_map_pt_A->buy_count+=QUANTITY;
                        client_map_pt_A->net_count+=QUANTITY*transact_price*(-1);
                    }

                    auto client_map_it_B=client_map.find(order_pt->NAME);
                    bool find_seller=!(client_map_it_B==client_map.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=order_pt->NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price;
                        client_map.insert(make_pair(order_pt->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(client_map_it_B->second);
                        clientAll_ptr_2->sell_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price;
                    }
                }
                if(verbose) {
                    cout<<CLIENT_NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<order_pt->NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                ++count;
                NUMBER_OF_COMPLETED_TRADES+=QUANTITY;
                NUMBER_OF_SHARES_TRADED+=transact_price*QUANTITY;
                COMMISION_EARNINGS=(transact_price*QUANTITY)/100;
                MONEY_TRANSFERRED+=COMMISION_EARNINGS*2;
                order_pt->AMOUNT-=QUANTITY;
                QUANTITY=0;
            }
            else if(order_pt->AMOUNT==QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=client_map.find(CLIENT_NAME);
                    bool find_buyer=!(clientAll_it_1==client_map.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        client_map.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto client_map_pt_A=(clientAll_it_1->second);
                        client_map_pt_A->buy_count+=QUANTITY;
                        client_map_pt_A->net_count+=QUANTITY*transact_price*(-1);
                    }

                    auto client_map_it_B=client_map.find(order_pt->NAME);
                    bool find_seller=!(client_map_it_B==client_map.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=order_pt->NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price;
                        client_map.insert(make_pair(order_pt->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(client_map_it_B->second);
                        clientAll_ptr_2->sell_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price;
                    }
                }
                if(verbose) {
                    cout<<CLIENT_NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<order_pt->NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                ++count;
                NUMBER_OF_COMPLETED_TRADES+=QUANTITY;
                NUMBER_OF_SHARES_TRADED+=transact_price*QUANTITY;
                COMMISION_EARNINGS=(transact_price*QUANTITY)/100;
                MONEY_TRANSFERRED+=COMMISION_EARNINGS*2;
                QUANTITY=0;
                orderSell_ptr->erase(orderSell_ptr->begin());
            }
            else {
                if(transfers) {
                    auto clientAll_it_1=client_map.find(CLIENT_NAME);
                    bool find_buyer=!(clientAll_it_1==client_map.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=order_pt->AMOUNT;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=order_pt->AMOUNT*transact_price*(-1);
                        client_map.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr=(clientAll_it_1->second);
                        clientAll_ptr->buy_count+=order_pt->AMOUNT;
                        clientAll_ptr->net_count+=order_pt->AMOUNT*transact_price*(-1);
                    }

                    auto client_map_it_B=client_map.find(order_pt->NAME);
                    bool find_seller=!(client_map_it_B==client_map.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=order_pt->NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=order_pt->AMOUNT;
                        client_record_temp->net_count=order_pt->AMOUNT*transact_price;
                        client_map.insert(make_pair(order_pt->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(client_map_it_B->second);
                        clientAll_ptr_2->sell_count+=order_pt->AMOUNT;
                        clientAll_ptr_2->net_count+=order_pt->AMOUNT*transact_price;
                    }
                }
                if(verbose) {
                    cout<<CLIENT_NAME<<" purchased "<<order_pt->AMOUNT<<" shares of "<<EQUITY_SYMBOL<<" from "
                        <<order_pt->NAME<<" for $"<<transact_price<<"/share"<<endl;
                }
                NUMBER_OF_COMPLETED_TRADES+=order_pt->AMOUNT;
                ++count;
                NUMBER_OF_SHARES_TRADED+=transact_price*order_pt->AMOUNT;
                COMMISION_EARNINGS=transact_price*order_pt->AMOUNT/100;
                MONEY_TRANSFERRED+=COMMISION_EARNINGS*2;
                QUANTITY-=order_pt->AMOUNT;
                orderSell_ptr->erase(orderSell_ptr->begin());
            }
        }
        else {
            break;
        }
    }

}

void deal_sell(map<string, equity_book> &order_map, map<string, client_equity *> &client_map, int timestamp_now,
               map<string, equity_book>::iterator order_all_iterator, int &QUANTITY, int LIMIT_PRICE, int next_ID,
               bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &count_num,
               int &NUMBER_OF_COMPLETED_TRADES, int &NUMBER_OF_SHARES_TRADED, int &COMMISION_EARNINGS,
               int &MONEY_TRANSFERRED) {
    auto transact_price=0;
    auto orderBuy_ptr=&(order_all_iterator->second.orderBuy);
    while(QUANTITY>0&&!orderBuy_ptr->empty()) {
        if((*orderBuy_ptr->begin())->PRICE>=LIMIT_PRICE) {
            auto order_pt=*orderBuy_ptr->begin();
            if(order_pt->ID>=next_ID) {
                transact_price=LIMIT_PRICE;
            }
            else {
                transact_price=order_pt->PRICE;
            }
            auto equitybook_ptr=&(order_all_iterator->second);
            equitybook_ptr->history.insert(transact_price);
            if(order_pt->AMOUNT>QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=client_map.find(CLIENT_NAME);
                    bool find_seller=!(clientAll_it_1==client_map.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price*(1);
                        client_map.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto client_map_pt_A=(clientAll_it_1->second);
                        client_map_pt_A->sell_count+=QUANTITY;
                        client_map_pt_A->net_count+=QUANTITY*transact_price*(1);
                    }

                    auto client_map_it_B=client_map.find(order_pt->NAME);
                    bool find_buyer=!(client_map_it_B==client_map.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=order_pt->NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        client_map.insert(make_pair(order_pt->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(client_map_it_B->second);
                        clientAll_ptr_2->buy_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price*(-1);
                    }
                }
                if(verbose) {
                    cout<<order_pt->NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<CLIENT_NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                count_num+=QUANTITY;
                ++NUMBER_OF_COMPLETED_TRADES;
                NUMBER_OF_SHARES_TRADED+=transact_price*QUANTITY;
                COMMISION_EARNINGS=transact_price*QUANTITY/100;
                MONEY_TRANSFERRED+=COMMISION_EARNINGS*2;
                order_pt->AMOUNT-=QUANTITY;
                QUANTITY=0;
            }
            else if(order_pt->AMOUNT==QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=client_map.find(CLIENT_NAME);
                    bool find_seller=!(clientAll_it_1==client_map.end());


                    if(!find_seller) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price*(1);
                        client_map.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto client_map_pt_A=(clientAll_it_1->second);
                        client_map_pt_A->sell_count+=QUANTITY;
                        client_map_pt_A->net_count+=QUANTITY*transact_price*(1);
                    }

                    auto client_map_it_B=client_map.find(order_pt->NAME);
                    bool find_buyer=!(client_map_it_B==client_map.end());


                    if(!find_buyer) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=order_pt->NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        client_map.insert(make_pair(order_pt->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(client_map_it_B->second);
                        clientAll_ptr_2->buy_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price*(-1);
                    }
                }
                if(verbose) {

                    cout<<order_pt->NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<CLIENT_NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                count_num+=QUANTITY;
                ++NUMBER_OF_COMPLETED_TRADES;
                COMMISION_EARNINGS=transact_price*QUANTITY/100;
                MONEY_TRANSFERRED+=COMMISION_EARNINGS*2;
                NUMBER_OF_SHARES_TRADED+=transact_price*QUANTITY;
                QUANTITY=0;
                orderBuy_ptr->erase(orderBuy_ptr->begin());
            }
            else {
                if(transfers) {
                    auto clientAll_it_1=client_map.find(CLIENT_NAME);
                    bool find_seller=!(clientAll_it_1==client_map.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=order_pt->AMOUNT;
                        client_record_temp->net_count=order_pt->AMOUNT*transact_price*(1);
                        client_map.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto client_map_pt_A=(clientAll_it_1->second);
                        client_map_pt_A->sell_count+=order_pt->AMOUNT;
                        client_map_pt_A->net_count+=order_pt->AMOUNT*transact_price*(1);
                    }

                    auto client_map_it_B=client_map.find(order_pt->NAME);
                    bool find_buyer=!(client_map_it_B==client_map.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_equity;
                        client_record_temp->name=order_pt->NAME;
                        client_record_temp->buy_count=order_pt->AMOUNT;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=order_pt->AMOUNT*transact_price*(-1);
                        client_map.insert(make_pair(order_pt->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(client_map_it_B->second);
                        clientAll_ptr_2->buy_count+=order_pt->AMOUNT;
                        clientAll_ptr_2->net_count+=order_pt->AMOUNT*transact_price*(-1);
                    }
                }
                if(verbose) {
                    cout<<order_pt->NAME<<" purchased "<<order_pt->AMOUNT<<" shares of "<<EQUITY_SYMBOL<<" from "
                        <<CLIENT_NAME<<" for $"<<transact_price<<"/share"<<endl;
                }
                count_num+=order_pt->AMOUNT;
                ++NUMBER_OF_COMPLETED_TRADES;
                NUMBER_OF_SHARES_TRADED+=transact_price*order_pt->AMOUNT;
                COMMISION_EARNINGS=transact_price*order_pt->AMOUNT/100;
                MONEY_TRANSFERRED+=COMMISION_EARNINGS*2;
                QUANTITY-=order_pt->AMOUNT;
                orderBuy_ptr->erase(orderBuy_ptr->begin());
            }
        }
        else {
            break;
        }
    }

}

void final_print(int NUMBER_OF_SHARES_TRADED, int NUMBER_OF_COMPLETED_TRADES, int MONEY_TRANSFERRED,
                 int COMMISION_EARNINGS) {
    cout<<"---End of Day---\n"<<"Commission Earnings: $"<<COMMISION_EARNINGS
    <<"\nTotal Amount of Money Transferred: $"<<MONEY_TRANSFERRED
    <<"\nNumber of Completed Trades: "<<NUMBER_OF_COMPLETED_TRADES
    <<"\nNumber of Shares Traded: "<<NUMBER_OF_SHARES_TRADED<<endl;
}