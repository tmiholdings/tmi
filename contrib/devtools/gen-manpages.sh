#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

TMICOIND=${TMICOIND:-$SRCDIR/tmicoind}
TMICOINCLI=${TMICOINCLI:-$SRCDIR/tmicoin-cli}
TMICOINTX=${TMICOINTX:-$SRCDIR/tmicoin-tx}
TMICOINQT=${TMICOINQT:-$SRCDIR/qt/tmicoin-qt}

[ ! -x $TMICOIND ] && echo "$TMICOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($TMICOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for tmicoind if --version-string is not set,
# but has different outcomes for tmicoin-qt and tmicoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$TMICOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $TMICOIND $TMICOINCLI $TMICOINTX $TMICOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
