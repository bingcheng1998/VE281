#include <iostream>
#include "equity_transfer.h"
using namespace std;



//////////////////////////////////////////////////////////////

void do_median(map<string, equitybook> &orderAll, int current_timestamp) {

    //cout<<"we are doing median!"<<endl;

    int median_price=0;
    for(auto orderAll_it=orderAll.begin(); orderAll_it!=orderAll.end(); ++orderAll_it) {
        ssize_t size=orderAll_it->second.history.size();

        //cout<<"current records: "<<orderAll_it->second.EQUITY_SYMBOL<<endl;
        //cout<<"current trade number = "<<size<<endl;

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
            cout<<"Median match price of "<<orderAll_it->second.EQUITY_SYMBOL<<" at time "<<current_timestamp<<" is $"
                <<median_price<<endl;
        }
        else {
            continue;
        }
    }
}

void do_midpoint(map<string, equitybook> &orderAll, int current_timestamp) {

    //cout<<"we are doing midpoint!"<<endl;

    //cout<<"current time = "<<current_timestamp<<endl;

    //string equity_symbol_temp=orderAll.begin()->second.EQUITY_SYMBOL;

    for(auto orderAll_it=orderAll.begin(); orderAll_it!=orderAll.end(); ++orderAll_it) {

        /*
        cout<<orderAll_it->second.EQUITY_SYMBOL<<endl;

        if(orderAll_it->second.orderBuy.empty()) {
            cout<<"no buy record!"<<endl;
        }
        else {
            cout<<"buy price = "<<(*orderAll_it->second.orderBuy.begin()).PRICE<<endl;
        }

        if(orderAll_it->second.orderSell.empty()) {
            cout<<"no sell record!"<<endl;
        }
        else {
            cout<<"sell price = "<<(*orderAll_it->second.orderSell.begin()).PRICE<<endl;
        }
         */

        if(orderAll_it->second.orderBuy.empty()||orderAll_it->second.orderSell.empty()) {
            cout<<"Midpoint of "<<orderAll_it->second.EQUITY_SYMBOL<<" at time "<<current_timestamp<<" is undefined"
                <<endl;
            continue;
        }

        auto midpoint_price=
                ((*orderAll_it->second.orderBuy.begin())->PRICE+(*orderAll_it->second.orderSell.begin())->PRICE)/2;
        cout<<"Midpoint of "<<orderAll_it->second.EQUITY_SYMBOL<<" at time "<<current_timestamp<<" is $"<<midpoint_price
            <<endl;
    }
}

void do_transfers(map<string, client_record *> &clientAll) {
    for(auto clientAll_it=clientAll.begin(); clientAll_it!=clientAll.end(); ++clientAll_it) {
        cout<<clientAll_it->second->name<<" bought "<<clientAll_it->second->buy_count<<" and sold "
            <<clientAll_it->second->sell_count<<" for a net transfer of $"<<clientAll_it->second->net_count<<endl;
    }
}

void do_expire(map<string, equitybook> &orderAll, set<Order *, comp_buy> *orderBuy_ptr,
               set<Order *, comp_sell> *orderSell_ptr, int current_timestamp) {
    set<Order *, comp_sell>::iterator orderSell_it;
    set<Order *, comp_sell>::iterator orderSell_it_temp;
    set<Order *, comp_buy>::iterator orderBuy_it;
    set<Order *, comp_sell>::iterator orderBuy_it_temp;

    //int loop=0;

    for(auto orderAll_it=orderAll.begin(); orderAll_it!=orderAll.end(); ++orderAll_it) {

        orderSell_ptr=&(orderAll_it->second.orderSell);

        for(orderSell_it=orderSell_ptr->begin(); orderSell_it!=orderSell_ptr->end();) {

            //cout<<"loop number = "<<loop<<endl;

            if((*orderSell_it)->EXPIRE_TIME!=-1&&(*orderSell_it)->EXPIRE_TIME<=current_timestamp) {
                orderSell_it_temp=orderSell_it;
                //cout<<"point to "<<(*orderSell_ptr->begin()).NAME<<endl;
                orderSell_it=orderSell_ptr->erase(orderSell_it_temp);
                //loop++;
                //cout<<"do I come here 1?"<<endl;
            }
            else {
                ++orderSell_it;
            }

        }

        orderBuy_ptr=&(orderAll_it->second.orderBuy);

        for(orderBuy_it=orderBuy_ptr->begin(); orderBuy_it!=orderBuy_ptr->end();) { // bug here

            //cout<<"loop number = "<<loop<<endl;

            if((*orderBuy_it)->EXPIRE_TIME!=-1&&(*orderBuy_it)->EXPIRE_TIME<=current_timestamp) {
                orderBuy_it_temp=orderBuy_it;
                //cout<<"point to "<<(*orderBuy_ptr->begin()).NAME<<endl;
                orderBuy_it=orderBuy_ptr->erase(orderBuy_it_temp);
                //loop++;
                //cout<<"do I come here 1?"<<endl;
            }
            else {
                ++orderBuy_it;
            }
        }
    }
}

void do_transact_buy(map<string, equitybook> &orderAll, map<string, client_record *> &clientAll, int current_timestamp,
                     map<string, equitybook>::iterator orderAll_it, int &QUANTITY, int LIMIT_PRICE, int next_ID,
                     bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &count_amount,
                     int &count, int &count_transfer, int &single_commission, int &total_commission) {
    auto transact_price=0;

    auto orderSell_ptr=&(orderAll_it->second.orderSell);

    while(QUANTITY>0&&!orderSell_ptr->empty()) {

        //cout<<"others willing to sell "<<(*orderSell_ptr->begin()).NAME<<" at "<<(*orderSell_ptr->begin()).PRICE<<endl;
        //cout<<"I am willing to pay "<<LIMIT_PRICE<<endl;

        if((*orderSell_ptr->begin())->PRICE<=LIMIT_PRICE) {
            auto Order_ptr=*orderSell_ptr->begin();
            if(Order_ptr->ID>=next_ID) {
                transact_price=LIMIT_PRICE;
            }
            else {
                transact_price=Order_ptr->PRICE;
            }

            auto equitybook_ptr=&(orderAll_it->second);
            equitybook_ptr->history.insert(transact_price);

            if(Order_ptr->AMOUNT>QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=clientAll.find(CLIENT_NAME);
                    bool find_buyer=!(clientAll_it_1==clientAll.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_1=(clientAll_it_1->second);
                        clientAll_ptr_1->buy_count+=QUANTITY;
                        clientAll_ptr_1->net_count+=QUANTITY*transact_price*(-1);
                    }

                    auto clientAll_it_2=clientAll.find(Order_ptr->NAME);
                    bool find_seller=!(clientAll_it_2==clientAll.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=Order_ptr->NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price;
                        clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(clientAll_it_2->second);
                        clientAll_ptr_2->sell_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price;
                    }
                    //find_buyer=false;
                    //find_seller=false;
                }
                if(verbose) {
                    cout<<CLIENT_NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<Order_ptr->NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                ++count;
                count_amount+=QUANTITY;
                count_transfer+=transact_price*QUANTITY;
                single_commission=(transact_price*QUANTITY)/100;
                total_commission+=single_commission*2;
                Order_ptr->AMOUNT-=QUANTITY;
                QUANTITY=0;
            }
            else if(Order_ptr->AMOUNT==QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=clientAll.find(CLIENT_NAME);
                    bool find_buyer=!(clientAll_it_1==clientAll.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_1=(clientAll_it_1->second);
                        clientAll_ptr_1->buy_count+=QUANTITY;
                        clientAll_ptr_1->net_count+=QUANTITY*transact_price*(-1);
                    }

                    auto clientAll_it_2=clientAll.find(Order_ptr->NAME);
                    bool find_seller=!(clientAll_it_2==clientAll.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=Order_ptr->NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price;
                        clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(clientAll_it_2->second);
                        clientAll_ptr_2->sell_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price;
                    }
                    //find_buyer=false;
                    //find_seller=false;
                }
                if(verbose) {
                    cout<<CLIENT_NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<Order_ptr->NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                ++count;
                count_amount+=QUANTITY;
                count_transfer+=transact_price*QUANTITY;
                single_commission=(transact_price*QUANTITY)/100;
                total_commission+=single_commission*2;
                QUANTITY=0;
                orderSell_ptr->erase(orderSell_ptr->begin());
            }
            else {
                if(transfers) {
                    auto clientAll_it_1=clientAll.find(CLIENT_NAME);
                    bool find_buyer=!(clientAll_it_1==clientAll.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=Order_ptr->AMOUNT;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=Order_ptr->AMOUNT*transact_price*(-1);
                        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr=(clientAll_it_1->second);
                        clientAll_ptr->buy_count+=Order_ptr->AMOUNT;
                        clientAll_ptr->net_count+=Order_ptr->AMOUNT*transact_price*(-1);
                    }

                    auto clientAll_it_2=clientAll.find(Order_ptr->NAME);
                    bool find_seller=!(clientAll_it_2==clientAll.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=Order_ptr->NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=Order_ptr->AMOUNT;
                        client_record_temp->net_count=Order_ptr->AMOUNT*transact_price;
                        clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(clientAll_it_2->second);
                        clientAll_ptr_2->sell_count+=Order_ptr->AMOUNT;
                        clientAll_ptr_2->net_count+=Order_ptr->AMOUNT*transact_price;
                    }
                    //find_buyer=false;
                    //find_seller=false;
                }
                if(verbose) {
                    cout<<CLIENT_NAME<<" purchased "<<Order_ptr->AMOUNT<<" shares of "<<EQUITY_SYMBOL<<" from "
                        <<Order_ptr->NAME<<" for $"<<transact_price<<"/share"<<endl;
                }
                count_amount+=Order_ptr->AMOUNT;
                ++count;
                count_transfer+=transact_price*Order_ptr->AMOUNT;
                single_commission=transact_price*Order_ptr->AMOUNT/100;
                total_commission+=single_commission*2;
                QUANTITY-=Order_ptr->AMOUNT;
                orderSell_ptr->erase(orderSell_ptr->begin());
            }
        }
        else {

            //cout<<"trade failed!"<<endl;

            break;
        }
    }

}

void deal_sell(map<string, equitybook> &orderAll, map<string, client_record *> &clientAll, int current_timestamp,
               map<string, equitybook>::iterator orderAll_it, int &QUANTITY, int LIMIT_PRICE, int next_ID,
               bool transfers, string &CLIENT_NAME, bool verbose, string &EQUITY_SYMBOL, int &count_amount,
               int &count, int &count_transfer, int &single_commission, int &total_commission) {
    auto transact_price=0;

    auto orderBuy_ptr=&(orderAll_it->second.orderBuy);

    /*
    auto orderSell_ptr=&(orderAll_it->second.orderSell);

    cout<<(*orderSell_ptr->begin())->NAME<<endl;
     */


    /*
     if(orderBuy_ptr->empty()) {
        auto it_temp=orderSell_ptr->begin();
        auto Order_ptr=*it_temp;
        while(it_temp!=orderSell_ptr->end()) {
            auto client_record_temp=new client_record;
            client_record_temp->name=Order_ptr->NAME;
            client_record_temp->buy_count=0;
            client_record_temp->sell_count=Order_ptr->AMOUNT;
            client_record_temp->net_count=QUANTITY*transact_price*(1);
            clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
            it_temp++;
        }
    }
     */

    while(QUANTITY>0&&!orderBuy_ptr->empty()) {

        //cout<<"others willing to buy "<<(*orderBuy_ptr->begin()).NAME<<" at "<<(*orderBuy_ptr->begin()).PRICE<<endl;
        //cout<<"I am willing to sell "<<LIMIT_PRICE<<endl;

        if((*orderBuy_ptr->begin())->PRICE>=LIMIT_PRICE) {
            auto Order_ptr=*orderBuy_ptr->begin();
            if(Order_ptr->ID>=next_ID) {
                transact_price=LIMIT_PRICE;
            }
            else {
                transact_price=Order_ptr->PRICE;
            }
            auto equitybook_ptr=&(orderAll_it->second);
            equitybook_ptr->history.insert(transact_price);
            if(Order_ptr->AMOUNT>QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=clientAll.find(CLIENT_NAME);
                    bool find_seller=!(clientAll_it_1==clientAll.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price*(1);
                        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_1=(clientAll_it_1->second);
                        clientAll_ptr_1->sell_count+=QUANTITY;
                        clientAll_ptr_1->net_count+=QUANTITY*transact_price*(1);
                    }

                    auto clientAll_it_2=clientAll.find(Order_ptr->NAME);
                    bool find_buyer=!(clientAll_it_2==clientAll.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=Order_ptr->NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(clientAll_it_2->second);
                        clientAll_ptr_2->buy_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price*(-1);
                    }
                    //find_buyer=false;
                    //find_seller=false;

                    //Order_ptr->AMOUNT-=QUANTITY;

                }
                if(verbose) {
                    //do_verbose_sell(Order_ptr, EQUITY_SYMBOL, CLIENT_NAME, transact_price);
                    cout<<Order_ptr->NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<CLIENT_NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                count_amount+=QUANTITY;
                ++count;
                count_transfer+=transact_price*QUANTITY;
                single_commission=transact_price*QUANTITY/100;
                total_commission+=single_commission*2;
                Order_ptr->AMOUNT-=QUANTITY;
                QUANTITY=0;
            }
            else if(Order_ptr->AMOUNT==QUANTITY) {
                if(transfers) {
                    auto clientAll_it_1=clientAll.find(CLIENT_NAME);
                    bool find_seller=!(clientAll_it_1==clientAll.end());


                    if(!find_seller) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=QUANTITY;
                        client_record_temp->net_count=QUANTITY*transact_price*(1);
                        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_1=(clientAll_it_1->second);
                        clientAll_ptr_1->sell_count+=QUANTITY;
                        clientAll_ptr_1->net_count+=QUANTITY*transact_price*(1);
                    }

                    auto clientAll_it_2=clientAll.find(Order_ptr->NAME);
                    bool find_buyer=!(clientAll_it_2==clientAll.end());


                    if(!find_buyer) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=Order_ptr->NAME;
                        client_record_temp->buy_count=QUANTITY;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=QUANTITY*transact_price*(-1);
                        clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(clientAll_it_2->second);
                        clientAll_ptr_2->buy_count+=QUANTITY;
                        clientAll_ptr_2->net_count+=QUANTITY*transact_price*(-1);
                    }
                    //find_buyer=false;
                    //find_seller=false;
                }
                if(verbose) {

                    cout<<Order_ptr->NAME<<" purchased "<<QUANTITY<<" shares of "<<EQUITY_SYMBOL<<" from "<<CLIENT_NAME
                        <<" for $"<<transact_price<<"/share"<<endl;
                }
                count_amount+=QUANTITY;
                ++count;
                count_transfer+=transact_price*QUANTITY;
                single_commission=transact_price*QUANTITY/100;
                total_commission+=single_commission*2;
                QUANTITY=0;
                orderBuy_ptr->erase(orderBuy_ptr->begin());
            }
            else {
                if(transfers) {
                    auto clientAll_it_1=clientAll.find(CLIENT_NAME);
                    bool find_seller=!(clientAll_it_1==clientAll.end());

                    if(!find_seller) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=CLIENT_NAME;
                        client_record_temp->buy_count=0;
                        client_record_temp->sell_count=Order_ptr->AMOUNT;
                        client_record_temp->net_count=Order_ptr->AMOUNT*transact_price*(1);
                        clientAll.insert(make_pair(CLIENT_NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_1=(clientAll_it_1->second);
                        clientAll_ptr_1->sell_count+=Order_ptr->AMOUNT;
                        clientAll_ptr_1->net_count+=Order_ptr->AMOUNT*transact_price*(1);
                    }

                    auto clientAll_it_2=clientAll.find(Order_ptr->NAME);
                    bool find_buyer=!(clientAll_it_2==clientAll.end());

                    if(!find_buyer) {
                        auto client_record_temp=new client_record;
                        client_record_temp->name=Order_ptr->NAME;
                        client_record_temp->buy_count=Order_ptr->AMOUNT;
                        client_record_temp->sell_count=0;
                        client_record_temp->net_count=Order_ptr->AMOUNT*transact_price*(-1);
                        clientAll.insert(make_pair(Order_ptr->NAME, (client_record_temp)));
                    }
                    else {
                        auto clientAll_ptr_2=(clientAll_it_2->second);
                        clientAll_ptr_2->buy_count+=Order_ptr->AMOUNT;
                        clientAll_ptr_2->net_count+=Order_ptr->AMOUNT*transact_price*(-1);
                    }
                    //find_buyer=false;
                    //find_seller=false;
                }
                if(verbose) {
                    cout<<Order_ptr->NAME<<" purchased "<<Order_ptr->AMOUNT<<" shares of "<<EQUITY_SYMBOL<<" from "
                        <<CLIENT_NAME<<" for $"<<transact_price<<"/share"<<endl;
                }
                count_amount+=Order_ptr->AMOUNT;
                ++count;
                count_transfer+=transact_price*Order_ptr->AMOUNT;
                single_commission=transact_price*Order_ptr->AMOUNT/100;
                total_commission+=single_commission*2;
                QUANTITY-=Order_ptr->AMOUNT;
                orderBuy_ptr->erase(orderBuy_ptr->begin());
            }
        }
        else {

            //cout<<"trade failed!"<<endl;

            break;
        }
    }

}

void final_print(int count_num, int count, int count_transfer, int single_commission, int total_commission) {
    cout<<"---End of Day---"<<endl;
    cout<<"Commission Earnings: $"<<total_commission<<endl;
    cout<<"Total Amount of Money Transferred: $"<<count_transfer<<endl;
    cout<<"Number of Completed Trades: "<<count<<endl;
    cout<<"Number of Shares Traded: "<<count_num<<endl;
}