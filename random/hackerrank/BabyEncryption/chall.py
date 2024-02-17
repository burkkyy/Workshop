import string
# from secret import MSG
import binascii

def encryption(msg):
    ct = []
    for char in msg:
        ct.append((123 * char + 18) % 256)
    return bytes(ct)

def encrypt(char):
    return ((123 * char + 18) % 256)

def decipher_w_hashmap(msg):
    map = {encrypt(i): i for i in range(1, 129)}
    msg = [chr(map[char]) for char in msg]
    return ''.join(msg)

def decipher_w_loops(msg):
    og_msg = []
    for byte in msg:
        for i in range(1, 129):
            encrypted = encrypt(i)
            if encrypted == byte:
                og_msg.append(chr(i))
    return ''.join(og_msg)

f = open("./msg.enc", "r")

data = binascii.unhexlify(f.read())
flag = decipher_w_loops(data)
print(flag)

"""
for letter in encrypted:
    for i in range(130):
        a = encrypt(i)
        if a == letter:
            print(chr(i), end='')
            break
"""

"""
ct = encryption(MSG)
f = open('./msg.enc','w')
f.write(ct.hex())
f.close()
"""

