# OSS Service (Hard) (crypto 500)

The task provides a [link](http://ctf.sharif.edu:8088/) (and a [mirror](http://8088.ctf.certcc.ir/)).

As in a previous [easy](http://ctf.sharif.edu:8086/) task,
we are asked to provide a valid OSS signature on a given message.
The difference is that we don't have any plaintext/ciphertext pair here to use
(so no [known-plaintext attack](https://en.wikipedia.org/wiki/Known-plaintext_attack) in this case.)

The OSS scheme is a cryptosystem proposed by Ong, Schnorr and Shamir
in the 1984 paper _An Efficient Signature Scheme Based on Quadratic Equations_,
based on the difficulty of solving equations of the kind `x^2 + k*y^2 = m (mod n)`,
where `n = p*q`, `m` is the message and `k` is the public key.

In the 1984 paper _An Efficient Solution of the Congruence x^2 + k*y^2 = m (mod n)_,
Pollard and Schnorr describes an algorithm to efficiently forge valid signatures
in the OSS scheme.

An explanation of both the scheme and the algorithm can also be found
[here](https://webcourse.cs.technion.ac.il/236500/Spring2016/ho/WCFiles/cryptanalysis-slides-03-sig-oss.1x1.pdf).

To solve this task we need to implement this algorithm.
We do so at [solver.sage](solver.sage)
and then validate it using the provided [verifier.py](verifier.py).
