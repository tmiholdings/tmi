#make clean && HOST=i686-w64-mingw32 && ./autogen.sh && CONFIG_SITE=$PWD/depends/i686-w64-mingw32/share/config.site ./configure --prefix=/ && make -j14 && make install DESTDIR=/home/tmi/_work/git/tmi32/bin && echo $?

make clean && HOST=i686-w64-mingw32 && ./autogen.sh && CONFIG_SITE=$PWD/depends/i686-w64-mingw32/share/config.site ./configure --prefix=/ && make -j8 && echo $?

