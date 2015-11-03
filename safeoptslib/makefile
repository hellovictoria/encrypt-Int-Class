GXX=g++
OBJC=$(wildcard *.cpp)
TARGET=libsafeopts2.so
objects=safeopts1.o

libsafeopts2.so:safeopts1.o
	$(GXX) $< -o $@ -shared -lcrypto
	rm -rf /usr/lib/$(TARGET)
	cp ./$(TARGET) /usr/lib/
safeopts1.o:$(OBJC)
	$(GXX) -c $< -o $@ -fPIC

.PHONY:clean
clean:
	rm -rf $(objects) $(TARGET)
