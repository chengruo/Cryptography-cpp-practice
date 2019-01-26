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
	byte cipherKey[16];//ԭʼ������Կ
	word plainText[4];//���������
	word cipherText[4];//���ܺ�õ�������
	word deCipherText[4];//�����Ľ��ܺ������
	int Nb;//���ݷ��鳤��/32
	int Nk;//��Կ���鳤��/32
	int Nr;//����
	word Rcon[11];//������Կ��չ�ĳ���
	word wordKey[44];//������ʽ��ʾ����չ�����Կ
	static const byte SBox[16][16];//S������
	static const byte invSBox[16][16];//S�е���
	static const byte mixColumnMatrix[4][4];//�л�����������
	static const byte invMixColumnMatrix[4][4];//�л����泣������
};