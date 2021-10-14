Homework (Code) 

In this homework, you will gain some familiarity with memory allocation. First, you’ll write some buggy programs (fun!). Then, you’ll use some tools to help you find the bugs you inserted. Then, you will realize how awesome these tools are and use them in the future, thus making yourself more happy and productive. The first tool you’ll use is gdb, the debugger. There is a lot to learn about this debugger; here we’ll only scratch the surface. The second tool you’ll use is valgrind [SN05]. This tool helps find memory leaks and other insidious memory problems in your program. If it’s not installed on your system, go to the website and do so: http://valgrind.org/downloads/current.html 

Questions 

(1) First, write a simple program called **null.c** that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program? 

```
$ ./null
Segmentation fault (core dumped)
```

(2) Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you? 

```
(gdb) run
Starting program: /mnt/c/Users/Sakiharu/Documents/GitHub/ostep-notes/homework/14/null

Program received signal SIGSEGV, Segmentation fault.
0x0000000008001161 in main () at null.c:5
5           printf("%d\n", *p);
```

(3). Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool? 

```
==951== Memcheck, a memory error detector
==951== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==951== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==951== Command: ./null
==951==
==951== error calling PR_SET_PTRACER, vgdb might block
==951== Invalid read of size 4
==951==    at 0x109161: main (null.c:5)
==951==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==951==
==951==
==951== Process terminating with default action of signal 11 (SIGSEGV)
==951==  Access not within mapped region at address 0x0
==951==    at 0x109161: main (null.c:5)
==951==  If you believe this happened as a result of a stack
==951==  overflow in your program's main thread (unlikely but
==951==  possible), you can try to increase the size of the
==951==  main thread stack using the --main-stacksize= flag.
==951==  The main thread stack size used in this run was 8388608.
==951==
==951== HEAP SUMMARY:
==951==     in use at exit: 0 bytes in 0 blocks
==951==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==951==
==951== All heap blocks were freed -- no leaks are possible
==951==
==951== For lists of detected and suppressed errors, rerun with: -s
==951== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)
```

(4). Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)? 

```
==1009== Memcheck, a memory error detector
==1009== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1009== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1009== Command: ./forget-to-free
==1009==
==1009== error calling PR_SET_PTRACER, vgdb might block
==1009==
==1009== HEAP SUMMARY:
==1009==     in use at exit: 40 bytes in 1 blocks
==1009==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==1009==
==1009== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==1009==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1009==    by 0x10915E: main (forget-to-free.c:5)
==1009==
==1009== LEAK SUMMARY:
==1009==    definitely lost: 40 bytes in 1 blocks
==1009==    indirectly lost: 0 bytes in 0 blocks
==1009==      possibly lost: 0 bytes in 0 blocks
==1009==    still reachable: 0 bytes in 0 blocks
==1009==         suppressed: 0 bytes in 0 blocks
==1009==
==1009== For lists of detected and suppressed errors, rerun with: -s
==1009== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

(5). Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct? 

```
==1124== Memcheck, a memory error detector
==1124== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1124== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1124== Command: ./arrayof100
==1124==
==1124== error calling PR_SET_PTRACER, vgdb might block
==1124== Invalid write of size 4
==1124==    at 0x10919D: main (arrayof100.c:8)
==1124==  Address 0x4a471d0 is 0 bytes after a block of size 400 alloc'd
==1124==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1124==    by 0x10917E: main (arrayof100.c:5)
==1124==
==1124==
==1124== HEAP SUMMARY:
==1124==     in use at exit: 0 bytes in 0 blocks
==1124==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==1124==
==1124== All heap blocks were freed -- no leaks are possible
==1124==
==1124== For lists of detected and suppressed errors, rerun with: -s
==1124== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

(6). Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. 

Does the program run?

Yes. 



What happens when you use valgrind on it?

```
==1176== Memcheck, a memory error detector
==1176== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1176== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1176== Command: ./free-before
==1176==
==1176== error calling PR_SET_PTRACER, vgdb might block
==1176== Invalid read of size 4
==1176==    at 0x109207: main (free-before.c:16)
==1176==  Address 0x4a4704c is 12 bytes inside a block of size 40 free'd
==1176==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1176==    by 0x1091FE: main (free-before.c:14)
==1176==  Block was alloc'd at
==1176==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==1176==    by 0x10919E: main (free-before.c:5)
==1176==
-1
==1176==
==1176== HEAP SUMMARY:
==1176==     in use at exit: 0 bytes in 0 blocks
==1176==   total heap usage: 2 allocs, 2 frees, 552 bytes allocated
==1176==
==1176== All heap blocks were freed -- no leaks are possible
==1176==
==1176== For lists of detected and suppressed errors, rerun with: -s
==1176== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

 

(7). Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

```
$ ./funny
-1
munmap_chunk(): invalid pointer
Aborted (core dumped)
```

Maybe no