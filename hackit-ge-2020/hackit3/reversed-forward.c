#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

void print(u8 *q) {
  for (int i = 0; i < 0x10; i++) printf("%x ", q[i]);
  printf("\n");
}

int main() {
  u8 q0[0x10], q1[0x10], q2[0x10], q16[0x10];
  u8 q3[0x10] = {0x69, 0x30, 0xfc, 0x30, 0x93, 0x30, 0x68, 0x30, 0xb3, 0x30, 0xa4, 0x30, 0xc3, 0x30, 0x06, 0x26};
  u8 q4[0x10] = {0x4f, 0x7a, 0x84, 0x30, 0x4b, 0x30, 0x58, 0x30, 0x83, 0x30, 0x6a, 0x30, 0x44, 0x30, 0x01, 0xff};
  u8 q5[0x10] = {0xd9, 0x68, 0x1e, 0x88, 0xbe, 0xcf, 0xb6, 0xcf, 0xbc, 0xcf, 0x11, 0xac, 0xe5, 0x9e, 0xbc, 0xcf};
  u8 q6[0x10] = {0xb3, 0xba, 0xfe, 0xca, 0xef, 0xbe, 0xad, 0xde, 0xed, 0xa5, 0x53, 0xd1, 0x37, 0x13, 0xde, 0xc0};
  u8 q7[0x10] = "r4m4nd1mUt3at3!!";
  u32 w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13;
  u8 expected[0x10] = {0x81, 0x0c, 0xff, 0xdf, 0xbf, 0xb9, 0x07, 0xa8, 0xbf, 0x5b, 0xc2, 0x37, 0x7f, 0xcc, 0x6a, 0xbf};
  u8 flag[0x11];
  printf("Password: ");
  fgets(flag, 0x11, stdin);
  for (int i = 0; i < 0x10; i++) q0[i] = flag[i];
  for (int i = 0; i <= 0xc0b1c; i++) {
    // dup    v1.4h,  w14    
    for (int j = 0; j < 4; j++) *((u16 *)q1+j) = i;
    for (int j = 8; j < 0x10; j++) q1[j] = 0;
    // add    v0.16b,  v0.16b,  v7.16b
    for (int j = 0; j < 0x10; j++) q0[j] += q7[j];
    // mul    v1.8h,  v3.8h,  v1.h[0]
    u16 x = *(u16 *)q1;
    for (int j = 0; j < 8; j++) *((u16 *)q1+j) = *((u16 *)q3+j) * x;
    // mul    v0.4s,  v0.4s,  v6.4s
    for (int j = 0; j < 4; j++) *((u32 *)q0+j) *= *((u32 *)q6+j);
    // neg    v0.4s,  v0.4s
    for (int j = 0; j < 4; j++) *((u32 *)q0+j) = ~*((u32 *)q0+j)+1;
    // add    v0.8h,  v0.8h,  v5.8h
    for (int j = 0; j < 8; j++) *((u16 *)q0+j) += *((u16 *)q5+j);
    // mla    v0.8h,  v4.8h,  v1.8h
    for (int j = 0; j < 8; j++) *((u16 *)q0+j) += *((u16 *)q4+j) * *((u16 *)q1+j); 
    // mvn    v0.16b,  v0.16b
    for (int j = 0; j < 16; j++) q0[j] ^= 0xff;
    // mov    d1,  v0.d[0]
    *(u64 *)q1 = *(u64 *)q0, *((u64 *)q1+1) = 0;
    // mov    d0,  v0.d[1]
    *(u64 *)q0 = *((u64 *)q0+1), *((u64 *)q0+1) = 0;
    // trn1   v2.8b,  v1.8b,  v0.8b
    for (int j = 0; j < 16; j += 2) q2[j] = q1[j], q2[j+1] = q0[j];
    // trn2   v0.8b,  v1.8b,  v0.8b
    for (int j = 0; j < 16; j += 2) q0[j] = q1[j+1], q0[j+1] = q0[j+1];
    // stp    d2,  d0,  [sp,  #32]
    // ldr    q0,  [sp,  #32]
    *((u64 *)q0+1) = *(u64 *)q0;
    *(u64 *)q0 = *(u64 *)q2;
    // rev64  v1.4s,  v0.4s
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        *((u32 *)q1+j*2+1-k) = *((u32 *)q0+j*2+k);
    // b2,  v1.b[1]
    q2[0] = q1[1];
    for (int j = 1; j < 0x10; j++) q2[j] = 0;
    // mov    b16,  v1.b[0]
    q16[0] = q1[0];
    for (int j = 1; j < 0x10; j++) q16[j] = 0;
    // mov    b0,  v1.b[2]
    q0[0] = q1[2];
    for (int j = 1; j < 0x10; j++) q0[j] = 0;
    // umov   w12,  v1.b[3]
    w12 = q1[3];
    // umov   w11,  v1.b[4]
    w11 = q1[4];
    // umov   w10,  v1.b[5]
    w10 = q1[5];
    // umov   w9,  v1.b[6]
    w9 = q1[6];
    // add    v2.2s,  v2.2s,  v16.2s
    for (int j = 0; j < 2; j++) *((u32 *)q2+j) += *((u32 *)q16+j);
    // umov   w8,  v1.b[7]
    w8 = q1[7];
    // umov   w7,  v1.b[8]
    w7 = q1[8];
    // umov   w6,  v1.b[9]
    w6 = q1[9];
    // umov   w5,  v1.b[10]
    w5 = q1[10];
    // umov   w4,  v1.b[11]
    w4 = q1[11];
    // umov   w3,  v1.b[12]
    w3 = q1[12];
    // umov   w2,  v1.b[13]
    w2 = q1[13];
    // eor    v0.8b,  v2.8b,  v0.8b
    for (int j = 0; j < 0x10; j++) q0[j] ^= q2[j];
    // umov   w1,  v1.b[14]
    w1 = q1[14];
    // umov   w0,  v1.b[15]
    w0 = q1[15];
    // fmov   w13,  s0
    w13 = *(u32 *)q0;
    // mov    v0.16b,  v1.16b
    for (int j = 0; j < 0x10; j++) q0[j] = q1[j];
    // sub    w12,  w12,  w13,  uxtb
    w12 -= w13 & 0xff;
    // mov    v0.b[1],  v2.b[0]
    q0[1] = q2[0];
    // eor    w11,  w12,  w11
    w11 ^= w12;
    // add    w10,  w10,  w11,  uxtb
    w10 += w11 & 0xff;
    // eor    w9,  w10,  w9
    w9 ^= w10;
    // mov    v0.b[2],  w13
    q0[2] = w13;
    // sub    w8,  w8,  w9,  uxtb
    w8 -= w9 & 0xff;
    // eor    w7,  w8,  w7
    w7 ^= w8;
    // mov    v0.b[3],  w12
    q0[3] = w12;
    // add    w6,  w6,  w7,  uxtb
    w6 += w7 & 0xff;
    // eor    w5,  w6,  w5
    w5 ^= w6;
    // sub    w4,  w4,  w5,  uxtb
    w4 -= w5 & 0xff;
    // mov    v0.b[4],  w11
    q0[4] = w11;
    // eor    w3,  w4,  w3
    w3 ^= w4;
    // add    w2,  w2,  w3,  uxtb
    w2 += w3 & 0xff;
    // eor    w1,  w2,  w1
    w1 ^= w2;
    // mov    v0.b[5],  w10
    q0[5] = w10;
    // sub    w0,  w0,  w1,  uxtb
    w0 = (w0 & 0xff) - (w1 & 0xff);
    // mov    v0.b[6],  w9
    q0[6] = w9;
    // mov    v0.b[7],  w8
    q0[7] = w8;
    // mov    v0.b[8],  w7
    q0[8] = w7;
    // mov    v0.b[9],  w6
    q0[9] = w6;
    // mov    v0.b[10],  w5
    q0[10] = w5;
    // mov    v0.b[11],  w4
    q0[11] = w4;
    // mov    v0.b[12],  w3
    q0[12] = w3;
    // mov    v0.b[13],  w2
    q0[13] = w2;
    // mov    v0.b[14],  w1
    q0[14] = w1;
    // mov    v0.b[15],  w0
    q0[15] = w0;
  }
  print(q0);

  for (int i = 0; i < 0x10; i++)
    if (flag[i] != expected[i]) {
      puts("FAIL!");
      return 0;
    }
  puts("SUCCESS!");
}
