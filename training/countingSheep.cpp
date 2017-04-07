#include <iostream>
#include <set>
#include <string>

using namespace std;

int BTCount(int x)
{
	set<int> digits;
	for (size_t i=0;i<10;++i)
		digits.insert(i);
	int i=1;
	while (!digits.empty())
	{
		int temp = x*i;
		while (temp > 0)
		{
			digits.erase(temp%10);
			temp/=10;
		}
		++i;
	}

	return x*(i-1);
}

int main()
{
	int n;
	cin >> n;
	for (size_t i =0; i< n; ++i)
	{
		int x;
		
		cin >> x;
		if (x == 0)
			cout << "Case #" << (i+1) << ": INSOMNIA" << endl;
		else
			cout << "Case #" << (i+1) << ": " << BTCount(x) << endl;
	}
	return 0;
}