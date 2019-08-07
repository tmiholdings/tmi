// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The TMIcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TMICOIN_TMICOINCONSENSUS_H
#define TMICOIN_TMICOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_TMICOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/tmicoin-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBTMICOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define TMICOINCONSENSUS_API_VER 1

typedef enum tmicoinconsensus_error_t
{
    tmicoinconsensus_ERR_OK = 0,
    tmicoinconsensus_ERR_TX_INDEX,
    tmicoinconsensus_ERR_TX_SIZE_MISMATCH,
    tmicoinconsensus_ERR_TX_DESERIALIZE,
    tmicoinconsensus_ERR_AMOUNT_REQUIRED,
    tmicoinconsensus_ERR_INVALID_FLAGS,
} tmicoinconsensus_error;

/** Script verification flags */
enum
{
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    tmicoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = tmicoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | tmicoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               tmicoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | tmicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               tmicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | tmicoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int tmicoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, tmicoinconsensus_error* err);

EXPORT_SYMBOL int tmicoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, tmicoinconsensus_error* err);

EXPORT_SYMBOL unsigned int tmicoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // TMICOIN_TMICOINCONSENSUS_H
