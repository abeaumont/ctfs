# fHash (crypto 200)

The task provides a program, [fHash.py](fHash.py),
that creates a hash from a message and two IVs.

The challenge is to obtain a collision with a different message.

Analyzing the hashing program, the input conssts in:

* The two IVs are 2 bytes hex encoded (strings of length 4)
* The message consists in 8 bytes hex encoded (string of length 16)

The algorithm first splits the message in 4 parts of 2 bytes each
and consists in a round per part (4 rounds in total).

Each round is divided in two parts, one per IV.
Both work the same way:
* Concatenate the IV and the of the message
* Obtain the md5 of the resulting string
* Take the first 2 bytes of the digest, in hex (string of length 4)
* Replace the original IV with the resulting string

Since rounds are independant of each other,
we can focus just on getting just a valid input (2 IVs and message block)
that generate the expected output.
Doing this backward, we can find the initial IVs and message after 4 rounds.

Inside a round the 2 IVs are independant but the message is shared,
so we just look for a pair of first IV + message block
that results in the expected output (next first IV).
When we found this pair, we use the found message and
try to find a second IV that when concatenated with this found message
results in the expected output (next second IV).

Since the outputs we are searching for are rather small (2 bytes each),
it should be pretty easy to find collisions,
so we can efficiently bruteforce a solution, as done by [solver.py](solver.py).
