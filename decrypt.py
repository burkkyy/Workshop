import hashlib
from Crypto.Hash import keccak
from Crypto.Cipher import AES
from Crypto.Util import Counter

def get_priv_key(pw, ciphertext, cipherparms, salt, mac):
    dec_key = hashlib.scrypt(
        bytes(pw, 'utf-8'), salt=bytes.fromhex(salt), 
        n=262144, r=8, p=1, maxmem=2000000000, dklen=32
    )

    validate = dec_key[16:] + bytes.fromhex(ciphertext)
    keccak_hash=keccak.new(digest_bits=256)
    keccak_hash.update(validate)

    iv_int=int(cipherparms, 16)
    ctr = Counter.new(AES.block_size * 8, initial_value=iv_int)
    dec_suite = AES.new(dec_key[0:16], AES.MODE_CTR, counter=ctr)

    if (mac == keccak_hash.hexdigest()): 
        print("mac is correct")
    else: print("mac is not correct")

    plain_key = dec_suite.decrypt(bytes.fromhex(ciphertext))
    print("priv_key: ", plain_key.hex())

def main():
    # output should be 0x000...0001
    '''
    get_priv_key(
        "a",
        "f97975cb858242372a7c910de23976be4f545ad6b4d6ddb86e54b7d9b3b1c6a1",
        "7fa01f1d0d6a7117382632028cb0c323",
        "859c5d345ee58dfca293950c540016af3a889d0dacb00b8eff2ac2b150f0b07e",
        "31ccb67e48aba5d64bf727a5c6589fd5857021540d25d12df31323f10ae2bf97"
    )
    '''
    get_priv_key(
        "PASSWORD",
        "2cbe506db002243e1f3bc005cf43c56fdc21fe9d9c746597e62de9e1e73aae74",
        "02c16cc261177d1f2e3f4b9273435851",
        "1c2af003bff7cc86b94751b9cadf236cb9c334e7d0a0fd3517ecb5c6c6b998c1",
        "9f94301c2365d01ab7fa30e1d87b28d543cc7a218694acec901025456e34587c"
    )
    
if __name__ == '__main__':
    main()
