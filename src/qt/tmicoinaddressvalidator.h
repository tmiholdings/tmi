// Copyright (c) 2011-2014 The TMIcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TMICOIN_QT_TMICOINADDRESSVALIDATOR_H
#define TMICOIN_QT_TMICOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class TMIcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit TMIcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** TMIcoin address widget validator, checks for a valid tmicoin address.
 */
class TMIcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit TMIcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // TMICOIN_QT_TMICOINADDRESSVALIDATOR_H
