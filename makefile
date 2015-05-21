edit:main ecyInt.o safeopts1.o

safeopts1.o:safeopts1.cpp
    g++ -c $< -o $@ -fPIC
libsafeopts2.so:safeopts1.o
    g++ $< -o $@ -shared -lcrypto
ecyInt.o:ecyInt.cpp
    g++ -c $< -o $@
main:ecyInt.o main.cpp
    g++ $< -o $@ -L. libsafeopts2.so
