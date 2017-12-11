#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <conio.h>
#include <iostream>
//#include <vector>
using namespace std;

struct charsMass {
	char mass[35];
	int length = 0;
};

FILE *openInputStream() {//особая магия
	FILE *stream;
	return stream = fopen("in.txt", "r");
}
charsMass readTempFromStream(FILE *stream) {
	charsMass str;
	int i = 0;
	while (true) {
		char tmpCh;
		tmpCh = getc(stream);
		if (tmpCh == '\n') {
			++i;
			str.length = i+1;
			break;
		}
		str.mass[i] += tmpCh;
		++i;
	}
	return str;
}
charsMass readStrFromStream(FILE *stream, const int length) {
	charsMass str;
	int i = 0;
	while (i < length) {
		char tmpCh;
		tmpCh = getc(stream);
		str.mass[i] += tmpCh;
		++i;
	}
	str.length = length;
	return str;
}
char readNextCh(FILE *stream) {
	char tmpCh;
	tmpCh = getc(stream);
	return tmpCh;
}

charsMass changeStr(const charsMass &str, const char nextChar) {
	charsMass substr;
	substr.length = str.length;
	for (int i = 0; i < substr.length; ++i) {
		substr.mass[i] = str.mass[i + 1];
	}
	substr.mass[substr.length - 1] = nextChar;
	return substr;
}

int hashStr(const charsMass &str, const int pows[]) {
	int result = 0;
	for (int i = 0; i < str.length; ++i) {
		if (str.mass[i] >= 0) {
			result += (str.mass[i] % 3)*pows[i];
		}
		if (str.mass[i] < 0) {
			result += ((str.mass[i] + 127) % 3)*pows[i];
		}
	}
	return result;
}

int hashNextStr(const charsMass &str, const int prevHash, const char nextChar, const int pows[]) {
	if (str.mass[0] >= 0 && nextChar >=0) {
		return (prevHash - (str.mass[0] % 3)*pows[0]) / 3 + (nextChar % 3)*pows[str.length - 1];
	}
	if (str.mass[0] < 0 && nextChar >= 0) {
		return (prevHash - ((str.mass[0]+127) % 3)*pows[0]) / 3 + (nextChar % 3)*pows[str.length - 1];
	}
	if (str.mass[0] >= 0 && nextChar < 0) {
		return (prevHash - (str.mass[0] % 3)*pows[0]) / 3 + ((nextChar + 127) % 3)*pows[str.length - 1];
	}
	if (str.mass[0] < 0 && nextChar < 0) {
		return (prevHash - ((str.mass[0] + 127) % 3)*pows[0]) / 3 + ((nextChar+127) % 3)*pows[str.length - 1];
	}
}

void writeResult(const unsigned int firstChar, const unsigned int lastChar, const charsMass &str, const charsMass &temp) {
	unsigned int tmp = firstChar;
	printf_s("%i ", tmp + 1);
	int i = 0;
	while (tmp != lastChar)
	{
		if (temp.mass[i] != str.mass[i]) {
			break;
		}
		printf_s("%i ", tmp + 2);
		++tmp;
		++i;
	}
}

void RabinKarp(FILE* stream, charsMass str, const charsMass &temp) {


	int firstChar = 0, lastChar = temp.length - 1;

	int pows[17];

	for (int i = 0; i < temp.length; ++i) {
		pows[i] = pow(3, i);
	}
	int tempHash = hashStr(temp, pows);
	printf_s("%i ", tempHash);
	int strHash = hashStr(str, pows);
	while (!feof(stream))
	{
		if (tempHash == strHash) {
			writeResult(firstChar, lastChar, str, temp);
		}
		char nextChar = readNextCh(stream);
		strHash = hashNextStr(str, strHash, nextChar, pows);
		str = changeStr(str, nextChar);
		//cout << strHash << ";";
		/*strHash = hashStr(str, pows);*/
		++firstChar;
		++lastChar;
	}
}
void main() {
	FILE *stream = openInputStream();
	charsMass temp = readTempFromStream(stream);
	charsMass str = readStrFromStream(stream, temp.length);
	RabinKarp(stream, str, temp);
	system("pause");
}