#include <iostream>
#include <string>

using namespace std;

void assignCake(int r, string map[])
{
	int topRow = 0;
	for (size_t i=0; i<r; ++i)
	{
		string newRow;
		newRow.clear();
		int index = 0;
		while (index < map[i].size() )
		{
			while (index < map[i].size() && map[i][index] == '?')
				++index;
			if (index < map[i].size())
			{
				newRow +=string(index - newRow.size()+1, map[i][index]);
				++index;
			}
		}

		if (newRow.size() == 0)
		{
			if (topRow == 0)
				continue;
			else
			{
				map[i]=map[i-1];
				cout << map[i] << endl;
				topRow = i+1;
			}
		}
		else if (newRow.size() < map[i].size() )
			newRow += string(map[i].size() - newRow.size(), newRow[newRow.size()-1]);
		if (topRow <= i)
		{
			for (size_t j=topRow; j<=i; ++j)
			{
				map[j]=newRow;
				cout << newRow << endl;
			}
			topRow = i+1;
		}	
	}
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0;i<t;++i)
	{
		int r, c;
		string map[25+5];
		cin >> r >> c;
		for (size_t j=0; j<r; ++j)
			cin >> map[j];
		cout << "Case #" << (i+1) << ": " << endl;
		assignCake(r, map);
	}
	return 0;
}