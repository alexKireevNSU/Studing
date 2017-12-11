#include <iostream>
#include <string>
#include <vector>
using namespace std;

int hashFunction(string str, const unsigned int firstElement, const unsigned int lastElement) {
	const unsigned char konst = 3;
	unsigned int result = 0;
	for (int i = firstElement; i < lastElement-1; ++i) {
		result += (str[i] % konst)*(pow(konst, i));
	}
	return result;
}

void main() {
	string temp;
	string str;
	vector<int> result;
	cin >> temp >> str;
	int tempLen = temp.length();
	int strLen = str.length();
	int hashTemp = hashFunction(temp , 0 , tempLen - 1);
	int firstEl = 0, lastEl = tempLen - 1;
	int hashStr = hashFunction(str, 0, tempLen - 1);
	/*cout << tempLen << " " << strLen;
	cout << hashStr << " " << hashTemp;*/
	for (int i = 0; i < strLen - tempLen; ++i) { //(i < strLen - tempLen)&&(lastEl == strLen-1)
		if(hashTemp == hashStr){
			result.push_back(i);
		}
		++firstEl;
		++lastEl;
		cout << str;
		cin >> str;
		hashStr = hashFunction(str, firstEl, lastEl);
	}
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i];
	}
	system("pause");

}