TARGET = main.o cripto_api.o pass_api.o

all: $(TARGET)
	cc -o aes_test $(TARGET)  -lgcrypt -lm 
pass_api.o:pass_api.c pass_api.h cripto_api.h
	cc -c pass_api.c
cripto_api.o: cripto_api.c cripto_api.h
	cc -c cripto_api.c 
main: main.c pass_api.h
clean:
	rm aes_test *.o
