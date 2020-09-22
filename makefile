all: enc dec
enc: Encrypt.c 
	gcc -o enc Encrypt.c

dec: Decrypt.c
	gcc -o dec Decrypt.c
