const ecc = require('./eosjs-ecc')

var pkey = '5JbvjNjz7G4Nt9B6tn5zNt8nBY7JD8A7sai3Nh2S67DerWTkPrN'
var sig = ecc.signHash('', pkey)
console.log(sig)
