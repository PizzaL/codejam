#include <iostream>

using namespace std;

void findMissingLine(int n)
{
	int arr[2500+5];
	for (size_t i=0; i<=2500; ++i)
		arr[i] =0;
	for (size_t i=0; i<n*n*2-n; ++i)
	{
		int num;
		cin >> num;
		arr[num]++;
	}
	for (size_t i=0; i<=2500; ++i)
	{
		if (arr[i]%2 ==1)
			cout << " " << i;
	}
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		int n;
		cin >> n;
		cout << "Case #"<<(i+1)<< ":";
		findMissingLine(n);
		cout << endl;
	}
	return 0;
}
