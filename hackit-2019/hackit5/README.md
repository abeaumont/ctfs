# Hackit 5

We are just given a [crackme](crackme) file.

```sh
$ file crackme
crackme: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, stripped
$ ls -sh crackme
19K crackme
```

So, it seems we have a binary for x86-64 architecture, nothing fancy here.  
Fortunately, it also seems pretty small, so not too much code bloat, hopefully.

If we run the binary (obviously we didn't execute it right away, but it'll serve for illustrative purposes ;),
it kindly reports the proper usage:

```sh
$ chmod a+x crackme
$ ./crackme
Usage: ./crackme <password>
$ ./crackme ifeellucky
Fail!
```

Unsurprisingly, it seems to be the usual crackme, as the name suggests.

The program takes a noticeable time to run:

```sh
$ time ./crackme ifeellucky
Fail!

real	0m0.414s
user	0m0.414s
sys	0m0.000s
```

This suggests that there's quite a bit of logic in that small size.

We also can check what `strings` can tell us:

```
$ strings -8 crackme
[...]
Usage: %s <password>
Success!
E LAKSUERETNUOCN
%tEXtdate:create
2016-03-28T16:11:02+09:00
%tEXtdate:modify
2007-05-15T07:55:53+09:00
tEXtSoftware
www.inkscape.org
[...]
```

Interestingly enough, it seems we should expect to see `Success!` when we guess the correct password,
there's some `EUSKAL ENCOUNTER` text there, and also we seem to have an embedded PNG.

Even if it's not needed to solve the level, we can extract the PNG image with binwalk:

```sh
$ binwalk -D 'png image:png' crackme
```

We can see that it's the euskal encounter logo: ![logo](logo.png).

With all this information, we're ready to reverse the binary.  

The structure in the main function is quite simple and consists in:

- check the number of CLI arguments.
- if there are less than 2 arguments, show usage and finish.
- otherwise, initialize a buffer of size 256B (0x100) with the second argument (the password).
- run a loop 31337 (0x7a69) times, for each loop iteration:
  - traverse an array of items, which consists in a function pointer and 2 arguments
  - for each of the items in the array, call the function with:
    - the buffer (with the password initially)
    - the buffer size (256B)
    - the 2 arguments in the item
    - the loop index
- once the loop is completed, compare the buffer with a hardcoded byte sequence,
  if they match, you guessed the password.

Once the general structure is clear, we need to identify the functions and arguments in the array.  
There are in total 14 elements in the array, but there are only 12 different functions,
since 2 of them are called twice.

Knowing this, it seems pretty clear that those 12 functions will be invertible
and that the task consists in just inverting the code, and using the expected output as our initial input.  
That way, we should get the password as output of our inverted program.

Checking the functions, most of them are simple arithmetic operations.  
In some cases the same function serves for both directions.  
There are some functions that deserve especial mention:

- f1380 uses a multiplication, which means that a modular inverse is needed to reverse it.
  We just bruteforce the value since it's just 8 bits.
- f1450 uses the PNG as a data table. We just extracted the data block to use it.
- f1520 is an example of a function that serves both for direct and invert directions,
  but unfortunately it uses floating point datatypes and operations.
  This means that any precision error will result in an incorrect output,
  so extra care has to be taken with casts and constants.
  In our particular case, using O2 or O3 optimization levels in GCC results in a different constant for `0.1337`,
  which yields an incorrect result. It works just fine without optimizations or using Clang though.
- f1620 has the most complex logic, with some intertwined variables that require especial care to invert.

In order to reverse the functions, the approach we followed is:
- Use a disassembler / decompiler to reverse the logic of the first function.
- Write the code in C.
- Execute both the C written code and the provided `crackme` program
  to verify that both provide the same output given the same input.
  That is, to verify that we have reversed the code correctly.
- Write such function with the logic inverted in C.
- Run the C program calling the first the function we have reversed and then the inverted function
  and validate that the output of the program matches the input.
  That is, both the direct and invert functions work and their composition is the identity function.
- Repeat the whole process for all the functions.
- Put both the direct and reverse block in a loop of 31337 and check that it works.
  This should validate that the usage of the loop index argument in the functions is correctly reversed.
  
Once everything above works, we have reversed the whole program and we have it's invert,
so we just swich the order of things:
- Use the expected output as input.
- Call the loop in reverse order.
- In every loop interation, we call all the functions in reverse order.
- The output of the program is the password.
- Additionally, we can call the direct code to validate tha the end result matches the expected output.

Once this is done, we get the password :)

```sh
$ cc crackme.c -lm
$ ./a.out
R0unD4ndr0UNdth3buff3r
```

You can check the code we built at [crackme.c](crackme.c).
