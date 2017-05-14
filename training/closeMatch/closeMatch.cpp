#include <iostream>
#include <string>

using namespace std;

void setZeroAndNice(string& str1, string& str2, int head, int tail)
{
	for (size_t i=head; i<=tail; ++i)
	{
		str1[i] = '0';
		str2[i] = '9';
	}
}

void closeMatch(string& c, string& j)
{
	for (int i = c.size() - 1; i >= 0; --i)
	{
		if (c[i] != '?' && j[i] !='?' )
			continue;
		else if (c[i] == '?' && j[i] == '?')
		{
			int idx=i;
			while (idx >= 0 && c[idx] == '?' && j[idx] == '?')
				--idx;
			if (idx < 0 || c[idx] == j[idx])
			{
				if ( i < c.size()-1 || c[i+1] != j[i+1])
				{
					for (int k=idx+1; k<i; ++k)
						c[k]=j[k]='0';
					if (c[i+1] > j[i+1])
					{
						c[i] = '0';
						if (c[i+1] - j[i+1] > 5)
							j[i] = '1';
						else
							j[i] = '0';
					} else 
					{
						j[i] = '0';
						if (j[i+1] - c[i+1] > 5)
							c[i] = '1';
						else
							c[i] = '0';
					}
				} else
				{
					for (int k=idx+1; k<=i; ++k)
					{
						c[k] = j[k] = '0';
					}
				}
			} else
			{
				if (c[idx] < j[idx])
				{
					setZeroAndNice(j, c, idx+1, i);
				} else
				{
					setZeroAndNice(c, j, idx+1, i);
				}
			}
		} else
		{
			if (c[i] == '?')
				c[i] = j[i];
			else
				j[i] = c[i];
		}

	}
	cout << c << " " << j;
}

int main()
{
	int t;
	cin >> t; 
	for (size_t i=0; i<t; ++i)
	{
		string c, j;
		cin >> c >> j;
		cout << "Case #" << (i+1) << ": ";
		closeMatch(c, j);
		cout << endl;
	}
	return 0;
}