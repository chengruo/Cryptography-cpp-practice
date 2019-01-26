#include"SDES.h"
#include <iostream>
#include<string>
#include"stdio.h"
using namespace std;

const int SDES::P10[10] = { 3,5,2,7,4,10,1,9,8,6 };
const int SDES::P8[8] = { 6,3,7,4,8,5,10,9 };
const int SDES::IP[8] = { 2,6,3,1,4,8,5,7 };
const int SDES::IPI[8] = { 4,1,3,5,7,2,8,6 };
const int SDES::EP1[4] = { 4,1,2,3 };
const int SDES::EP2[4] = { 2,3,4,1 };
const int SDES::P4[4] = { 2,4,3,1 };
const int SDES::S0[4][4] = { {1,0,3,2},
										{3,2,1,0},
										{0,2,1,3},
										{3,1,3,2} };

const int SDES::S1[4][4] = { {0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3} };

void SDES::setKey(string s) {
	key = stringToInt(s);
}

int SDES::stringToInt(string s) {
	int key = 0;
	int i;
	int n = s.length();
	for (i = 0; i < n; i++) {
		key = key * 2 + s[i] - '0';
	}
	return key;
}

void SDES::getKey() {
	int tempkey;
	tempkey = permutations(key, P10, 10, 10);
	tempkey = shiftLS(tempkey);
	key1 = permutations(tempkey, P8, 10, 8);
	tempkey = shiftLS(tempkey);
	tempkey = shiftLS(tempkey);
	key2 = permutations(tempkey, P8, 10, 8);
}

int SDES::permutations(int num, const int p[], int pmax, int n) {
	int temp = 0;
	int i;
	for (int i = 0; i < n; i++) {
		temp <<= 1;
		temp |= (num >> (pmax - p[i])) & 1;
	}
	return temp;
}

int SDES::shiftLS(int num) {
	int temp;
	int L, R;
	L = (num >> 5) & 0x1F;
	R = num & 0x1F;
	L = ((L & 0xF) << 1) | ((L & 0x10) >> 4);
	R = ((R & 0xF) << 1) | ((R & 0x10) >> 4);
	temp = (L << 5) | R;
	return temp;
}

void SDES::showResult()
{
	//cout << ciphertext;
	printf("%x", ciphertext);
}

void SDES::encryption() {
	ciphertext = permutations(plaintext, IP, 8, 8);
	int R, L;
	R = ciphertext & 0xF;
	L = ((ciphertext & 0xF0) >> 4);
	fk(key1, L, R);
	int temp = L;
	L = R;
	R = temp;
	fk(key2, L, R);
	temp = (L << 4) | R;
	ciphertext = permutations(temp, IPI, 8, 8);
}

void SDES::fk(int key, int &left, int right) {
	int L = left;
	int R = right;
	int temp;
	int tempL, tempR;
	temp = ((permutations(R, EP1, 4, 4)) << 4) | (permutations(R, EP2, 4, 4));
	temp = temp ^ key;
	tempR = temp & 0xF;
	tempL = ((temp & 0xF) >> 4);
	tempL = S0[((tempL & 0x8) >> 2) | (tempL & 1)][(tempL >> 1)  &0x3];
	tempR = S1[((tempR & 0x8) >> 2) | (tempR & 1)][(tempR >> 1)  &0x3];
	temp = (tempL << 2) | tempR;
	temp = permutations(temp, P4, 4, 4);
	left = L ^ temp;
}

void SDES::decryption() {
	deciphertext = permutations(ciphertext, IP, 8, 8);
	int R, L;
	R = deciphertext & 0xF;
	L = ((deciphertext * 0xF0) >> 4);
	fk(key2, L, R);
	int temp = L;
	L = R;
	R = temp;
	fk(key1, L, R);
	temp=(L << 4) | R;
	deciphertext = permutations(temp, IPI, 8, 8);
}

int main()
{
	SDES sdes;
	sdes.setKey("abcdefg");
	sdes.encryption();
	sdes.showResult();
}