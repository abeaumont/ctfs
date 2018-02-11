# yasc (RE 300)

The task only provides a [binary file](yasc).

If we analyze or run it, we can see that it reads a input string
and it validates that the input string is the expected one.
If that's the case, it prints the flag.

The input string is composed of 24 blocks where
each block consists in a character and a sequence of numbers.
The length of this sequence of numbers is the index of the block
(that is, from 1 to 24).

That is, if we use `C` for any character and `D` for any digit,
the string has the following format (without spaces):

`C1 D1 C2 D2_1 D2_2 C3 D3_1 D3_2 D3_3 ... C24 D24_1 ... D24_24`

The character of every block is compared against the string `LeIa1SE#g@scn$mrhGipNtl!`,
so that determines what each character is.

For the digits, each block is processed differently.
The xor of all the digits in the sequence is calculated,
resulting in a sequence of 24 integers.

This integers must be a permutation of size 24 of the range [0, 23],
and when used the block's value as an index for the string `LeIa1SE#g@scn$mrhGipNtl!`,
the resulting character must match with the one in the string `SimplestrIngchaL1ENG!@#$`,
indexed by block's number (starting with 0).

If these validations success, both an MD5 and a SHA1 hash is calculated with this information
(for each block, the character and the block value as a 32bit integer).
If the MD5 matches with a predefined hash value,
an encrypted flag is then XORed with the obtained SHA1 to decrypt the flag and print it.

The [solver](solver.py) shows how this process is done.
