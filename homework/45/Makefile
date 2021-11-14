all: check-xor check-fletcher measure-time crc16 create-csum check-csum

check-xor: check-xor.c
	gcc -o check-xor check-xor.c

check-fletcher: check-fletcher.c
	gcc -o check-fletcher check-fletcher.c

measure-time: measure-time.c
	gcc -o measure-time measure-time.c

crc16: crc16.c
	gcc -o crc16 crc16.c

create-csum: create-csum.c
	gcc -o create-csum create-csum.c

check-csum: check-csum.c
	gcc -o check-csum check-csum.c
