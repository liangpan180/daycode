make uninstall
make clean

automake -a
./configure --prefix=/usr
make -j
