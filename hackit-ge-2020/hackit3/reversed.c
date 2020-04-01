#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

u64 modinv(u64 a, u64 b) {
  u64 b0 = b, t, q;
  u64 x0 = 0, x1 = 1;
  if (b == 1) return 1;
  while (a > 1) {
    q = a / b;
    t = b, b = a % b, a = t;
    t = x0, x0 = x1 - q * x0, x1 = t;
  }
  return x1;
}

int main() {
  u8 q1[0x10], q2[0x10];
  u8 q0[0x11] = {0x81, 0x0c, 0xff, 0xdf, 0xbf, 0xb9, 0x07, 0xa8, 0xbf, 0x5b, 0xc2, 0x37, 0x7f, 0xcc, 0x6a, 0xbf, 0x00};
  u8 q3[0x10] = {0x69, 0x30, 0xfc, 0x30, 0x93, 0x30, 0x68, 0x30, 0xb3, 0x30, 0xa4, 0x30, 0xc3, 0x30, 0x06, 0x26};
  u8 q4[0x10] = {0x4f, 0x7a, 0x84, 0x30, 0x4b, 0x30, 0x58, 0x30, 0x83, 0x30, 0x6a, 0x30, 0x44, 0x30, 0x01, 0xff};
  u8 q5[0x10] = {0xd9, 0x68, 0x1e, 0x88, 0xbe, 0xcf, 0xb6, 0xcf, 0xbc, 0xcf, 0x11, 0xac, 0xe5, 0x9e, 0xbc, 0xcf};
  u8 q6[0x10] = {0xb3, 0xba, 0xfe, 0xca, 0xef, 0xbe, 0xad, 0xde, 0xed, 0xa5, 0x53, 0xd1, 0x37, 0x13, 0xde, 0xc0};
  u8 q7[0x10] = "r4m4nd1mUt3at3!!";
  for (int i = 0xc0b1c; i >= 0; i--) {
    q0[15] += q0[14];
    q0[14] ^= q0[13];
    q0[13] -= q0[12];
    q0[12] ^= q0[11];
    q0[11] += q0[10];
    q0[10] ^= q0[9];
    q0[9] -= q0[8];
    q0[8] ^= q0[7];
    q0[7] += q0[6];
    q0[6] ^= q0[5];
    q0[5] -= q0[4];
    q0[4] ^= q0[3];
    u8 a = q0[0], b = q0[1], c = q0[2];
    q0[3] += c;
    for (int j = 0; j < 0x10; j++) q1[j] = q0[j];
    c ^= b;
    b -= a;
    q1[1] = b;
    q1[2] = c;
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        *((u32 *)q0+j*2+1-k) = *((u32 *)q1+j*2+k);
    *(u64 *)q2 = *(u64 *)q0, *(u64 *)q0 = *((u64 *)q0+1);
    for (int j = 0; j < 16; j += 2) q1[j+1] = q0[j], q0[j+1] = q0[j+1];
    for (int j = 0; j < 16; j += 2) q1[j] = q2[j], q0[j] = q2[j+1];
    *((u64 *)q0+1) = *(u64 *)q0, *(u64 *)q0 = *(u64 *)q1;
    for (int j = 0; j < 16; j++) q0[j] ^= 0xff;
    for (int j = 0; j < 4; j++) *((u16 *)q1+j) = i;
    for (int j = 8; j < 0x10; j++) q1[j] = 0;
    u16 x = *(u16 *)q1;
    for (int j = 0; j < 8; j++) *((u16 *)q1+j) = *((u16 *)q3+j) * x;
    for (int j = 0; j < 8; j++) *((u16 *)q0+j) -= *((u16 *)q4+j) * *((u16 *)q1+j);
    for (int j = 0; j < 8; j++) *((u16 *)q0+j) -= *((u16 *)q5+j);
    for (int j = 0; j < 4; j++) *((u32 *)q0+j) = ~*((u32 *)q0+j)+1;
    for (int j = 0; j < 4; j++) *((u32 *)q0+j) *= modinv(*((u32 *)q6+j), 0x100000000);
    for (int j = 0; j < 0x10; j++) q0[j] -= q7[j];
  }
  printf("%s\n", q0);
}
