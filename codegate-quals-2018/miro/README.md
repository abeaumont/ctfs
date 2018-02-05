# Miro (crypto 404)

The task consists of two files, [client.py](client.py) and [miro.pcap](miro.pcap).

The python code is a TLS client that connects to a server
and plays a simple maze-like game, with for actions (up, down, left, right).

The problem is that the actions are encoded, and only 2 of them are available:

```python
    if user_input == "u":
        print "Sorry.. Not support function.."
        exit()
    elif user_input == "d":
        tls_client.send("6423e47152f145ee5bd1c014fc916e1746d66e8f5796606fd85b9b22ad333101\n")
    elif user_input == "r":
        tls_client.send("34660cfdd38bb91960d799d90e89abe49c1978bad73c16c6ce239bc6e3714796\n")
    elif user_input == "l":
        print "Sorry.. Not support function.."
        exit()
```

We don't know how to go up or left and we need those actions to solve the maze.

On the other hand, we have a pcap file with another maze solving session,
so we can check there what the encodings for up and left actions are.
The problem is that, of course, that session is encrypted
and we need to decipher it first.

To do so, we first get the server certificate, either by looking at the pcap file
or connecting to the server (i. e. `openssl s_client -connect ch41l3ng3s.codegate.kr:443`)

From the certificate, we extract both the RSA exponent (e = 65537) and modulus (n = 0x01c20bdc017e3caa3c579b40d439e2ecd70f12c4d7f2764784c95a3fddba00981ba9ce5b227ade47b0a7a0a8acaba4541ab95c52f6b6de3df9ec090c6c356445b21be437abe10214d0b4a398a96743bbf70c864687fb2ec929f01d6edab2d987fe09799ad2204a2704f33061dbf9c2e03b332f0ba1a446644c864a06cd586d480b)

Using [yafu](https://sourceforge.net/projects/yafu/), we factorize it to get `p` and `q`:

```
> yafu factor\(0x01c20bdc017e3caa3c579b40d439e2ecd70f12c4d7f2764784c95a3fddba00981ba9ce5b227ade47b0a7a0a8acaba4541ab95c52f6b6de3df9ec090c6c356445b21be437abe10214d0b4a398a96743bbf70c864687fb2ec929f01d6edab2d987fe09799ad2204a2704f33061dbf9c2e03b332f0ba1a446644c864a06cd586d480b\)


fac: factoring 316033277426326097045474758505704980910037958719395560565571239100878192955228495343184968305477308460190076404967552110644822298179716669689426595435572597197633507818204621591917460417859294285475630901332588545477552125047019022149746524843545923758425353103063134585375275638257720039414711534847429265419
fac: using pretesting plan: normal
fac: no tune info: using qs/gnfs crossover of 95 digits
div: primes less than 10000
fmt: 1000000 iterations
Total factoring time = 1.2601 seconds


***factors found***

P155 = 17777324810733646969488445787976391269105128850805128551409042425916175469483806303918279424710789334026260880628723893508382860291986009694703181381742497
P155 = 17777324810733646969488445787976391269105128850805128551409042425916175469168770593916088768472336728042727873643069063316671869732507795155086000807594027

ans = 1

```

With this, we generate the private key:

```python
from Crypto.PublicKey import RSA

n = 0x01c20bdc017e3caa3c579b40d439e2ecd70f12c4d7f2764784c95a3fddba00981ba9ce5b227ade47b0a7a0a8acaba4541ab95c52f6b6de3df9ec090c6c356445b21be437abe10214d0b4a398a96743bbf70c864687fb2ec929f01d6edab2d987fe09799ad2204a2704f33061dbf9c2e03b332f0ba1a446644c864a06cd586d480bL
e = 65537L
p = 17777324810733646969488445787976391269105128850805128551409042425916175469483806303918279424710789334026260880628723893508382860291986009694703181381742497L
q = 17777324810733646969488445787976391269105128850805128551409042425916175469168770593916088768472336728042727873643069063316671869732507795155086000807594027L

phi = (p - 1) * (q - 1)
d = pow(e, phi - 2, phi)
key = RSA.construct((n, e, d, p, q))
open('priv.key', 'w').write(key.exportKey('PEM'))
```

Adding the generated [private key](priv.key) to Wireshark we can now decipher the session and update the client:

```
from socket import *
from ssl import *
import time

def recv_until(s, string):
    result = ''
    while string not in result:
        result += s.recv(1)
    return result

client_socket=socket(AF_INET, SOCK_STREAM)
tls_client = wrap_socket(client_socket, ssl_version=PROTOCOL_TLSv1_2, cert_reqs=CERT_NONE)
print tls_client
print tls_client.context.cert_store_stats()

print "[+] Connecting with server.."

tls_client.connect(('ch41l3ng3s.codegate.kr',443))

print "[+] Connect OK"

while 1:
    data = recv_until(tls_client, "Input : ")
    print data
    user_input = raw_input()

    if user_input == "u":
        tls_client.send("9de133535f4a9fe7de66372047d49865d7cdea654909f63a193842f36038d362\n")
    elif user_input == "d":
        tls_client.send("6423e47152f145ee5bd1c014fc916e1746d66e8f5796606fd85b9b22ad333101\n")
    elif user_input == "r":
        tls_client.send("34660cfdd38bb91960d799d90e89abe49c1978bad73c16c6ce239bc6e3714796\n")
    elif user_input == "l":
        tls_client.send("27692894751dba96ab78121842b9c74b6191fd8c838669a395f65f3db45c03e2\n")
    else:
        print "Invalid input!"
        exit()

client_socket.shutdown(SHUT_RDWR)
client_socket.close()
```

That's it, now we can run the [solver.py](solver.py), escape the maze, and get the flag.
