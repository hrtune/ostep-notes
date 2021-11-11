# Homework

In this homework, you’ll use checksum.py to investigate various aspects
of checksums.

### Questions

First just run `checksum.py` with no arguments. Compute the additive,
XOR-based, and Fletcher checksums. Use -c to check your
answers.

```
$ python3 checksum.py
OPTIONS seed 0
OPTIONS data_size 4
OPTIONS data

Decimal:          216        194        107         66
Hex:             0xd8       0xc2       0x6b       0x42
Bin:       0b11011000 0b11000010 0b01101011 0b01000010

Add:      01000111
Xor:      00110011
Fletcher: 73,196
```

Now do the same, but vary the seed (-s) to different values.

```
$ python3 checksum.py -s 1

OPTIONS seed 1
OPTIONS data_size 4
OPTIONS data

Decimal:           34        216        195         65
Hex:             0x22       0xd8       0xc3       0x41
Bin:       0b00100010 0b11011000 0b11000011 0b01000001

(computed by ./fletcher.py)
Add: 254
Xor: 120
Fletcher: 0,219
```

Sometimes the additive and XOR-based checksums produce the
same checksum (e.g., if the data value is all zeroes). Can you pass
in a 4-byte data value (using the -D flag, e.g., -D a,b,c,d) that
does not contain only zeroes and leads the additive and XOR-based
checksum having the same value? In general, when does this occur?
Check that you are correct with the -c flag.

```
a: 10100000 (128+32 = 160)
b: 01010000 (64+16 = 80)
c: 00001010 (2 + 8 = 10)
d: 00000101 (1 + 4 = 5)

Add:            255       (0b11111111)
Xor:            255       (0b11111111)

If all of each sum of each column bits are less than 10 (0 or 1) in binary, then the add value is equal to the xor value. 
```

Now pass in a 4-byte value that you know will produce a different
checksum values for additive and XOR. In general, when does this
occur?

```
$ python3 checksum.py -D 160,80,10,6 -c

OPTIONS seed 0
OPTIONS data_size 4
OPTIONS data 160,80,10,6

Decimal:          160         80         10          6
Hex:             0xa0       0x50       0x0a       0x06
Bin:       0b10100000 0b01010000 0b00001010 0b00000110

Add:              0       (0b00000000)
Xor:            252       (0b11111100)
Fletcher(a,b):    1,141   (0b00000001,0b10001101)
```

> If the 4 values don't satisfy the condition above, then they will be different each other.

Use the simulator to compute checksums twice (once each for a different
set of numbers). The two number strings should be different
(e.g., -D a1,b1,c1,d1 the first time and -D a2,b2,c2,d2 the
second) but should produce the same additive checksum. In general,
when will the additive checksum be the same, even though the
data values are different? Check your specific answer with the -c
flag.

```
for example,
a1,,,d1 : 100,101,50,6
a2,,,d2 : 200,210,100,3
```

> If (a1 + b1 + c1 + d1) modulo 256 = (a2 + b2 + c2 + d2) modulo 256 then the add value is the same.

Now do the same for the XOR checksum.

```
for example,
a1,,,d1 : 175,48,204,6
a2,,,d2 : 51,85,240,195
```

Now let’s look at a specific set of data values. The first is: -D
1,2,3,4. 

```
$ python3 checksum.py -D 1,2,3,4 -c

OPTIONS seed 0
OPTIONS data_size 4
OPTIONS data 1,2,3,4

Decimal:            1          2          3          4
Hex:             0x01       0x02       0x03       0x04
Bin:       0b00000001 0b00000010 0b00000011 0b00000100

Add:             10       (0b00001010)
Xor:              4       (0b00000100)
Fletcher(a,b):   10, 20   (0b00001010,0b00010100)
```

What will the different checksums (additive, XOR, Fletcher)
be for this data? 

Now compare it to computing these checksums
over -D 4,3,2,1.

```
$ python3 checksum.py -D 4,3,2,1 -c

OPTIONS seed 0
OPTIONS data_size 4
OPTIONS data 4,3,2,1

Decimal:            4          3          2          1
Hex:             0x04       0x03       0x02       0x01
Bin:       0b00000100 0b00000011 0b00000010 0b00000001

Add:             10       (0b00001010)
Xor:              4       (0b00000100)
Fletcher(a,b):   10, 30   (0b00001010,0b00011110)
```

What do you notice about these three checksums?
How does Fletcher compare to the other two? 

> One of the fletcher value is different from "-D 1,2,3,4".

How is Fletcher generally “better” than something like the simple additive checksum?

> If a set of values are same but in different order then only the Fletcher works.

No checksum is perfect. Given a particular input of your choosing,
can you find other data values that lead to the same Fletcher checksum?
When, in general, does this occur? Start with a simple data
string (e.g., -D 0,1,2,3) and see if you can replace one of those
numbers but end up with the same Fletcher checksum. As always,
use -c to check your answers.

```
"-D 255,1,2,3" has the same fletcher value as "-D 0,1,2,3"
```

> If the set of values a1,a2,a3,a4 and another is (a1 + 255 * n1), (a2 + 255 * n2), (a3 + 255 * n3), (a4 + 255 * n4) then both of the fletcher values are the same.