#include <iostream>
#include <string>

using namespace std;

string findLastWord(string s)
{
	string result;
	for (size_t i=0; i<s.size(); ++i)
	{
		string head = string(1, s[i]) + result;
		string tail = result + string(1, s[i]);
		if (head < tail)
		{
			result = tail;
		} else
			result = head;
	}
	return result;
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		string s;
		cin >> s;
		cout << "Case #" << (i+1) << ": " << findLastWord(s) << endl;
	}
	return 0;
}