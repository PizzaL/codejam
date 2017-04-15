#include <iostream>

using namespace std;

bool isTidy(int n)
{
	int last = n%10;
	n/=10;
	while (n>0)
	{
		if (n%10 > last)
			return false;
		last=n%10;
		n/=10;
	}
	return true;
}

int findTidy(int n)
{
	for (int i=n; i>9; --i)
		if (isTidy(i))
			return i;
	return n;
}

int main()
{
	int t, n;
	cin >> t ;
	for (size_t i=0;i<t; ++i)
	{
		cin >> n;
		cout << "Case #" << (i+1) << ": " << findTidy(n) << endl;
	}
	return 0;
}