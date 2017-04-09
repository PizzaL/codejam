#include <iostream>
#include <string>

using namespace std;

void outputArr(ostream& out, int arr[], int n, string str)
{
	for (size_t i=0; i<n-1; ++i)
		out << arr[i] << str;
	out << arr[n-1];
}

long long calFloor(int n, int base)
{
	long long result=1;
	for (size_t i=0; i<n/2-1; ++i)
	{
		result=result*base+1;
	}
	return result;
}

bool isDividor(int arr[], int n, int base, int dividor)
{
	int pos = 0;
	int reminder = arr[pos];
	while (pos<n-1)
	{
		if (reminder >= dividor)
		{
			reminder %= dividor;
		}
		++pos;
		reminder = reminder*base+arr[pos]; 
	}
	return (reminder%dividor) == 0;
}

bool isPrime( int arr[], int n, int base, int dividor[] )
{
	long long floor = calFloor(n, base);
	for (size_t i=2; i<=floor; ++i)
		if ( isDividor(arr, n, base, i) )
		{
			dividor[base-2] = i;
			return false;
		}
	return true;
}

bool isCoinJam( int arr[], int n)
{
	int dividor[9];
	for (size_t i=2; i < 11; ++i)
	{
		if ( isPrime(arr, n, i, dividor) )
		{
			return false;
		}
	}
	outputArr(cout, arr, n, string("") ) ;
	cout << " ";
	outputArr(cout, dividor, 9, string(" ") );
	cout << endl;
	return true;
}

bool generateCoinJam(int arr[], int n)
{
	int pos = n-2;
	while (pos > 0)
	{
		if (arr[pos] == 0)
		{
			arr[pos]=1;
			return true;
		} else
		{
			arr[pos] = 0;
			--pos;
		}
	}
	return false;
}

void findCoinJam( int n, int j)
{
	int arr[32];
	for (size_t i=0; i<n ; ++i)
		arr[i] = 0;
	arr[0]=arr[n-1]=1;
	while (j > 0)
	{
		if ( isCoinJam(arr, n) )
			--j;
		if (!generateCoinJam(arr, n))
		{
			cout << "ERROR!";				
			return;
		}
	}
}

int main()
{
	int t, n, j;
	cin >> t; 
	for (size_t i=0; i<t; ++i)
	{
		cout << "Case #" << (i+1) << ":" << endl;
		cin >> n >> j;
		findCoinJam(n, j); 
	}
	return 0;
}