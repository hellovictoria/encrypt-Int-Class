GXX=g++
objects=ecyInt.o main.o main libsafeopts2.so

main:main.o ecyInt.o
	cd ./safeoptslib;make
	$(GXX) -o $@ $< -lsafeopts2
main.o:main.cpp
	$(GXX) -c $< -o $@
ecyInt.o:ecyInt.cpp
	$(GXX) -c $< -o $@

.PHONY:clean
clean:
	cd ./safeoptslib;make clean
	rm -rf $(objects)
 
