// distributed under the mit license
// https://opensource.org/licenses/mit-license.php

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "chacha20.h"

#define rotl32(x, n) \
    (x << n) | (x >> (32 - n))

int main(int argc, char *argv[]) {

    // Step 1: auqreter test
    uint32_t a = 0x11111111;
    uint32_t b = 0x01020304;
    uint32_t c = 0x9b8d6f43;
    uint32_t d = 0x01234567;

    chacha20_quarter(&a, &b, &c, &d);

    uint32_t  res_a = 0xea2a92f4;
    uint32_t  res_b = 0xcb1cf8ce;
    uint32_t  res_c = 0x4581472e;
    uint32_t  res_d = 0x5881c4bb;

    printf("Test 1\n");
    printf("%x, %x, %x, %x\n", a, b, c, d);

    assert(a==res_a);
    assert(b==res_b);
    assert(c==res_c);
    assert(d==res_d);


    // Step 2: Check state
    uint32_t state[16] = {
        0x879531e0,  0xc5ecf37d,  0x516461b1,  0xc9a62f8a,
        0x44c20ef3,  0x3390af7f,  0xd9fc690b,  0x2a5f714c,
        0x53372767,  0xb00a5631,  0x974c541a,  0x359e9963,
        0x5c971061,  0x3d631689,  0x2098d9d6,  0x91dbd320,
    };

    uint32_t res_state[16] = {
       0x879531e0,  0xc5ecf37d,  0xbdb886dc,  0xc9a62f8a,
       0x44c20ef3,  0x3390af7f,  0xd9fc690b,  0xcfacafd2,
       0xe46bea80,  0xb00a5631,  0x974c541a,  0x359e9963,
       0x5c971061,  0xccc07c79,  0x2098d9d6,  0x91dbd320,
    };

    printf("Test 2\n");
    chacha20_quarter(&state[2], &state[7], &state[8], &state[13]);
    printf("%x, %x, %x, %x\n", state[2], state[7], state[8], state[13]);

    assert(state[2] == res_state[2]);
    assert(state[7] == res_state[7]);
    assert(state[8] == res_state[8]);
    assert(state[13] == res_state[13]);


    uint32_t key[32] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,
        0x0c,0x0d,0x0e,0x0f,
        0x10,0x11,0x12,0x13,
        0x14,0x15,0x16,0x17,
        0x18,0x19,0x1a,0x1b,
        0x1c,0x1d,0x1e,0x1f
    };

    uint32_t block_counter = 0x1;

    uint32_t nonce[12]= {0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x4a,0x00,0x00,0x00,0x00};

    printf("Test 3\n");
    chacha20_block(key, &block_counter, nonce);

    return 0;
}
