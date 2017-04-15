#include <iostream>

using namespace std;

void findStall( unsigned long long n, unsigned long long k)
{
	if (k > 1)
	{
		if (n%2 == 1)
			findStall( n/2, k/2 );
		else 
			if (k%2 == 1)
				findStall( (n-1)/2, k/2 );
			else 
				findStall( n/2, k/2);
	} else {
		if (n%2 == 1)
			cout << n/2 << " " << n/2 << endl;
		else 
			cout << n/2 << " " << (n-1)/2 << endl;
	}
}

int main()
{
	unsigned long long n, k;
	int t;
	cin >> t;
	for (size_t i=0; i< t; ++i)
	{
		cin >> n >> k;
		cout << "Case #" << (i+1) << ": ";
		findStall(n, k);
	}
	return 0;
}