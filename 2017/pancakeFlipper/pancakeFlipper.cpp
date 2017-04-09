#include <iostream>
#include <string>

using namespace std;

void flip(string s, int k)
{
	int pos = 0; 
	int step = 0;
	while (pos < s.size() )
	{
		while (pos < s.size() && s[pos] == '+')
			++pos;
		if (pos == s.size())
			break;
		if (pos+k > s.size() )
		{
			cout << "IMPOSSIBLE" << endl;
			return ;
		}
		// flip
		for (size_t i=0; i<k; ++i)
			if (s[pos+i]=='-')
				s[pos+i]='+';
			else	// '+'
				s[pos+i]='-';
		++step;
	}
	cout << step << endl;
}

int main()
{
	int t,k;
	string s;
	cin >> t;
	for (size_t i=0;i<t; ++i)
	{
		cin >> s >> k;
		cout << "Case #"<<(i+1)<<": ";
		flip(s, k);
	}
	return 0;
}