# Homework 18

In this homework, you will use a simple program, which is known as paging-linear-translate.py, to see if you understand how simple virtual-to-physical address translation works with linear page tables. See the README for details. 

## Questions 

1 Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute <u>the size of linear page tables</u> as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows: 

```
$ paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0 
offset: 10 bit, VPN: 10 bit -> 1024

$ paging-linear-translate.py -P 1k -a 2m -p 512m -v -n 0
offset: 10bit, VPN: 11 bit -> 2048

$ paging-linear-translate.py -P 1k -a 4m -p 512m -v -n 0 
offset: 10bit, VPN: 12 bit -> 4096
```

Then, to understand how linear page table size changes as page size grows: 

```
$ paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0
offset: 10bit, VPN: 10bit -> 1024;

$ paging-linear-translate.py -P 2k -a 1m -p 512m -v -n 0
offset: 11bit, VPN: 9bit -> 512;

$ paging-linear-translate.py -P 4k -a 1m -p 512m -v -n 0
offset: 12bit, VPN: 8bit -> 256;
```

Before running any of these, try to think about the expected trends. 

- How should page-table size change as the address space grows? 

  > bigger

- As the page size grows?

  > smaller

- Why shouldn’t we just use really big pages in general? 

  > Because it costs time as the OS should search through the whole big pages.



2 Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example: 

```
$ paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0 
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]  0x00000000
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x00000000
  [       4]  0x00000000
  [       5]  0x00000000
  [       6]  0x00000000
  [       7]  0x00000000
  [       8]  0x00000000
  [       9]  0x00000000
  [      10]  0x00000000
  [      11]  0x00000000
  [      12]  0x00000000
  [      13]  0x00000000
  [      14]  0x00000000
  [      15]  0x00000000

Virtual Address Trace
  VA 0x00003a39 (decimal:    14905) --> invalid
  VA 0x00003ee5 (decimal:    16101) --> invalid
  VA 0x000033da (decimal:    13274) --> PA or invalid address?
  VA 0x000039bd (decimal:    14781) --> PA or invalid address?
  VA 0x000013d9 (decimal:     5081) --> PA or invalid address?

For each virtual address, write down the physical address it translates to
OR write down that it is an out-of-bounds address (e.g., segfault).

address space: 14bit
offset: 10bit
VPN: 4bit


$ paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 25
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]  0x80000018
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x00000000
  [       4]  0x00000000
  [       5]  0x80000009
  [       6]  0x00000000
  [       7]  0x00000000
  [       8]  0x80000010
  [       9]  0x00000000
  [      10]  0x80000013
  [      11]  0x00000000
  [      12]  0x8000001f
  [      13]  0x8000001c
  [      14]  0x00000000
  [      15]  0x00000000

Virtual Address Trace
  VA 0x00003986 (decimal:    14726) --> vpn: 0xe,[14], PA: invalid
  VA 0x00002bc6 (decimal:    11206) --> vpn: [10], offset: 966, PA: 4fc6
  VA 0x00001e37 (decimal:     7735) --> vpn: [7], invalid
  VA 0x00000671 (decimal:     1649) --> vpn: [1], invalid
  VA 0x00001bc9 (decimal:     7113) --> vpn: [6], invalid

paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 50 
ARG seed 0
ARG address space size 16k
ARG phys mem size 32k
ARG page size 1k
ARG verbose True
ARG addresses -1


The format of the page table is simple:
The high-order (left-most) bit is the VALID bit.
  If the bit is 1, the rest of the entry is the PFN.
  If the bit is 0, the page is not valid.
Use verbose mode (-v) if you want to print the VPN # by
each entry of the page table.

Page Table (from entry 0 down to the max size)
  [       0]  0x80000018
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x8000000c
  [       4]  0x80000009
  [       5]  0x00000000
  [       6]  0x8000001d
  [       7]  0x80000013
  [       8]  0x00000000
  [       9]  0x8000001f
  [      10]  0x8000001c
  [      11]  0x00000000
  [      12]  0x8000000f
  [      13]  0x00000000
  [      14]  0x00000000
  [      15]  0x80000008

Virtual Address Trace
address space: 14bit, offset: 10bit, VPN: 4bit
  VA 0x00003385 (decimal:    13189) --> vpn[12], offset: 901, PA: 0x3f85
  VA 0x0000231d (decimal:     8989) --> vpn[8], invalid
  VA 0x000000e6 (decimal:      230) --> vpn[0], offset: 230, PA: 0x60e6
  VA 0x00002e0f (decimal:    11791) --> vpn[11], invalid
  VA 0x00001986 (decimal:     6534) --> vpn[6], offset: 390, PA: 0x7586

For each virtual address, write down the physical address it translates to
OR write down that it is an out-of-bounds address (e.g., segfault).


paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 75 

paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 100 
```

What happens as you increase the percentage of pages that are allocated in each address space? 



3 Now let’s try some different random seeds, and some different (and sometimes quite crazy) address-space parameters, for variety: 

paging-linear-translate.py -P 8 -a 32 -p 1024 -v -s 1 

paging-linear-translate.py -P 8k -a 32k -p 1m -v -s 2 

paging-linear-translate.py -P 1m -a 256m -p 512m -v -s 3 



Which of these parameter combinations are unrealistic? Why?

> paging-linear-translate.py -P 8 -a 32 -p 1024 -v -s 1
>
> Because the page table size is too small against the address space.



4 Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?

> - Error: physical memory size must be GREATER than address space size (for this simulation)
>
> - Error in argument: address space must be a multiple of the pagesize

