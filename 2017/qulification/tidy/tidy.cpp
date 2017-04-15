#include <iostream>
#include <algorithm>

using namespace std;

string findTidy(string n)
{
	string res;
	if (n.size() == 1)
		return n;
	int pos = 0;
	while ( pos < n.size()-1 && n[pos] <= n[pos+1])
		++pos;
	if (pos == n.size()-1)
		return n;
	if (n[pos] > '1')
	{
		for (size_t i=pos+1; i< n.size(); ++i)
			res +='9';
		while (pos > 0 && n[pos]==n[pos-1])
		{
			res +='9';
			--pos;
		}
		res=char(n[pos]-1)+res;
		for (int i=pos-1; i>=0; --i)
		{
			res =  char('0'+ min(n[i]-'0', res[0]-'0') ) + res;
		}
	} else 
	{
		for (size_t i=0;i<n.size()-1; ++i)
			res +='9';
	}
	return res;
}

int main()
{
	int t;
	string n;
	cin >> t;
	for (size_t i=0;i<t; ++i)
	{
		cin >> n;
		cout << "Case #" << (i+1) << ": " << findTidy(n) << endl;
	}
	return 0;
}