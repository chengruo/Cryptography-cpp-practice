#include "IDEA.h"

void IDEA::setKey(byte in[])
{
	for (int i = 0; i < 16; ++i) {
		key[i] = in[i];
	}
	getEncRoundKey(encRoundKey);
	getDecRoundKey(encRoundKey, decRoundKey);
}

void IDEA::setPlaintext(byte in[])
{
	for (int i = 0; i < 8; i+=2) {
		plainText[i / 2] = (in[i] << 8) + in[i + 1];
	}
}

word16 IDEA::invMul(word16 x)
{
	word16 t0, t1;
	word16 q, y;
	if (x <= 1) {
		return x;
	}
	t1 = word16(0x10001L / x);
	y = word16(0x10001L % x);
	if (y == 1) {
		return (1 - t1) % 0xFFFF;
	}
	t0 = 1;
	do {
		q = x / y;
		x = x % y;
		t0 += q * t1;
		if (x == 1) {
			return 0;
		}
		q = y / x;
		y = y % x;
		t1 += q * t0;
	} while (y != 1);

	return (1-t1)&0xFFFF;
}

word16 IDEA::mul(word16 x, word16 y)
{
	word32 p;
	p = (word32)x*y;
	if (p) {
		y = p & 0xFFFF;
		x = p >> 16;
		return (y - x) + (y < x);
	}
	else if (x) {
		return 1 - y;
	}
	else {
		return 1 - x;
	}
}

void IDEA::encryption(word16 in[], word16 out[], word16 * EK)
{
	word16 x1, x2, x3, x4, t1, t2;
	x1 = in[0];
	x2 = in[1];
	x3 = in[2];
	x4 = in[3];
	int r = 8;
	do {
		x1 = mul(x1, *EK++);
		x2 += *EK++;
		x3 += *EK++;
		x4 = mul(x4, *EK++);
		t2 = x1 ^ x3;
		t1 = x2 ^ x4;
		t2 = mul(t2, *EK++);
		t1 = t1 + t2;
		t1 = mul(t1, *EK++);
		t2 = t1 + t2;
		x1 ^= t1;
		x4 ^= t2;
		x2 ^= t1;
		x2 = x3 ^ t1;
		x3 = t2;
	} while (--r);
	x1 = mul(x1, *EK++);
	*out++ = x1;
	*out++ = x3 + *EK++;
	*out++ = x2 + *EK++;
	x4 = mul(x4, *EK++);
	*out = x4;
}

void IDEA::enc()
{
}

void IDEA::getEncRoundKey(word16 * encRoundKey)
{
	int i, j;
	for (i = 0, j = 0; j < 8; ++j) {
		encRoundKey[j] = (key[i] << 8) + key[i + 1];
		i += 2;
	}
	for (i = 0; j < 52; ++j) {
		++i;
		encRoundKey[i + 7] = encRoundKey[i & 7] << 9 | encRoundKey[(i + 1) & 7] >> 7;
		encRoundKey += i & 8;
		i &= 7;
	}
}

void IDEA::getDecRoundKey(word16 const * EK, word16 DK[])
{
	int i;
	word16 temp[52];
	word16 t1, t2, t3;
	word16 *p = temp + 52;
	t1 = invMul(*EK + 1);
	t2 = -*EK++;
	t3 = -*EK++;
	*--p = invMul(*EK++);
	*--p = t3;
	*--p = t2;
	*--p = t1;
	for (i = 0; i < 7; ++i) {
		t1 = *EK++;
		*--p = *EK++;
		*--p = t1;
		t1 = invMul(*EK++);
		t2 = -*EK++;
		t3 = -*EK++;
		*--p = invMul(*EK++);
		*--p = t3;
		*--p = t2;
		*--p = t1;
	}
	t1 = *EK++;
	*--p = *EK++;
	*--p = t1;
	t1 = invMul(*EK++);
	t2 = -*EK++;
	t3 = -*EK++;
	*--p = invMul(*EK++);
	*--p = t3;
	*--p = t2;
	*--p = t1;
	for (i = 0, p = temp; i < 52; ++i) {
		*DK++ = *p;
		*p++ = 0;
	}
}

void IDEA::checkRoundKey()
{

}

