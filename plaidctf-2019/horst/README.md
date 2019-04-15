# Horst (crypto 200)

The challenge provides two files:

- [horst.py](horst.py), containing a permutation based cryptosystem.
- [data.txt](data.txt), containing a couple of _plaintext_ / _ciphertext_ pairs.

As we can see in the python code, the _plaintext_ consists in a pair of permutations.  
Additionally, there's another permutation that acts as a _key_.
The encryption consists in a series repeated operations on the _plaintext_ using the key.
Finally, the _ciphertext_ consists in the resulting permutations,
from which the plaintext can be recovered with the _key_ permutation.

We are provided two _plaintext_ / _ciphertext_ pairs, encrypted with the same _key_,
which is a randomly generated permutation, and not provided.  
We are expected to recover the key, to generate the flag.

Looking at the encryption process we can see that encryption process consists only in three operation rounds,
so it may be feasible to solve it using a solver,
so we create the model and extract the _plaintext_ and _ciphertext_ from the `data.txt` file and add it as the input and constraints.
The final code is available at [horst.pi](horst.pi).

We run it to obtain the key:

```sh
$ picat horst.pi
[59,2,50,29,55,15,43,30,27,6,57,22,7,26,3,35,24,40,53,46,49,10,16,12,41,47,60,11,51,58,4,1,56,28,52,19,39,9,33,36,37,63,14,0,61,13,25,17,8,54,44,34,18,23,48,62,32,42,20,45,31,5,38,21]
```

Once we have the key, we just need to construct the key as specified in the python code:

```sh
$ python2 -c "from horst import Permutation;from hashlib import sha1;print 'The flag is: PCTF{%s}' % sha1(str(Permutation([59,2,50,29,55,15,43,30,27,6,57,22,7,26,3,35,24,40,53,46,49,10,16,12,41,47,60,11,51,58,4,1,56,28,52,19,39,9,33,36,37,63,14,0,61,13,25,17,8,54,44,34,18,23,48,62,32,42,20,45,31,5,38,21]))).hexdigest()";
The flag is: PCTF{69f4153d282560cdaab05e14c9f1b7e0a5cc74d1}
```
