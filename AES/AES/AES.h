#pragma once
typedef unsigned char byte;
struct word {
	byte wordKey[4];
};

class AES {
public:
	AES();
	void setCipherKey(byte key[]);
	void setPlainText(byte plain[]);
	void keyExpansion(byte key[], word w[]);
	word rotWord(word w);
	word subWord(word w);
	word wordXOR(word w1, word w2);
	void encryption(word in[], word out[], word key[]);
	void processEncryption();
	void addRoundKey(word in[], int round);
	void subByte(word in[]);
	void shiftRows(word in[]);
	void mixColumn(word in[]);
	byte GFMultiplyByte(byte L, byte R);
	void decryption(word in[], word out[], word key[]);
	void processDecryption();
	void invShiftRows(word in[]);
	void invSubByte(word in[]);
	void invMixColumn(word in[]);
	void initRcon();
private:
	byte cipherKey[16];//原始加密密钥
	word plainText[4];//输入的密文
	word cipherText[4];//加密后得到的密文
	word deCipherText[4];//对密文解密后的数据
	int Nb;//数据分组长度/32
	int Nk;//密钥分组长度/32
	int Nr;//轮数
	word Rcon[11];//用于密钥扩展的常量
	word wordKey[44];//以字形式表示的扩展后的密钥
	static const byte SBox[16][16];//S盒数据
	static const byte invSBox[16][16];//S盒的逆
	static const byte mixColumnMatrix[4][4];//列混淆常量矩阵
	static const byte invMixColumnMatrix[4][4];//列混淆逆常量矩阵
};