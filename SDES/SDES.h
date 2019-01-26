#include<string>
using namespace std;
class SDES {
public:
	SDES() {
		plaintext = 0x10110111;
	};
	void setKey(string s);
	void setPlaintext(string s);
	void fk(int key, int &left, int right);
	void getKey();
	void encryption();
	void decryption();
	int permutations(int num, const int p[], int pmax, int n);
	int shiftLS(int num);
	void showResult();
private:
	int key;
	int key1;
	int key2;
	int stringToInt(string s);
	int plaintext;
	int ciphertext;
	int deciphertext;

	static const int P10[10];
	static const int P8[8];
	static const int IP[8];
	static const int IPI[8];
	static const int EP1[4];
	static const int EP2[4];
	static const int P4[4];
	static const int S0[4][4];
	static const int S1[4][4];
};
