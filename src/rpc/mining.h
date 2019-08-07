// Copyright (c) 2017 The TMIcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TMICOIN_RPC_MINING_H
#define TMICOIN_RPC_MINING_H

#include "script/script.h"

#include <univalue.h>


/** Check bounds on a command line confirm target */
unsigned int ParseConfirmTarget(const UniValue& value);

#endif
