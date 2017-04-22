#include <iostream>
#include <string>

using namespace std;

int findDigit(string& digits, const char key, const string& number)
{
	int res = 0;
	while (digits.find(key) != string::npos )
	{
		for (size_t i=0; i<number.size(); ++i)
		{
			int pos = digits.find(number[i]);
			digits.erase(digits.begin() + pos);
		}
		++res;
	}
	return res;
}

string getDigits(string& digits)
{
	int digit[10];
	digit[0] = findDigit(digits, 'Z', "ZERO");	// Z
	digit[4] = findDigit(digits, 'U', "FOUR" );	// U
	digit[6] = findDigit(digits, 'X', "SIX");		// X
	digit[8] = findDigit(digits, 'G', "EIGHT");	// G
	digit[7] = findDigit(digits, 'S', "SEVEN");	// S
	digit[3] = findDigit(digits, 'H', "THREE");	// H
	digit[2] = findDigit(digits, 'T', "TWO");		// T
	digit[5] = findDigit(digits, 'V', "FIVE");	// V
	digit[1] = findDigit(digits, 'O', "ONE");		// O
	digit[9] = digits.size() / 4;
	string res;
	for (size_t i=0; i<10; ++i)
		for (size_t j=0; j<digit[i]; ++j)
			res += string(1, char('0'+i));
	return res;
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		string digits;
		cin >>digits;
		cout << "Case #" << (i+1) << ": " << getDigits(digits) << endl;
	}
	return 0;
}