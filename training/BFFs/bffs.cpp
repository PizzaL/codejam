#include <iostream>
#include <set>

using namespace std;

int findLargestCircle(int n)
{
	int bffs[1000+5];
	set<int> kids;
	for (size_t i=1; i<=n; ++i)
	{
		cin >> bffs[i];
		kids.insert(i);
	}
	for (size_t i=1; i<=n; ++i)
	{
		kids.erase(bffs[i]);
	}
	if (kids.empty())
		for (size_t i=1; i<=n; ++i)
			kids.insert(i);
	int result = 2;
	while ( !kids.empty() )
	{
		int currKid = *kids.begin();
		set<int> currentCircle;
		currentCircle.clear();
		while ( currentCircle.find(currKid) == currentCircle.end() )
		{
			cout <<"currKid =" << currKid << endl;
			currentCircle.insert(currKid);
			kids.erase(currKid);
			currKid = bffs[currKid];
		}
		const int circleSize = currentCircle.size();
		cout << "circleSize=" << circleSize << endl;
		if ( circleSize > result)
			result = circleSize;
	}
	return result;
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		int n;
		cin >> n;
		cout << "Case #" << (i+1) << ": " << findLargestCircle(n) << endl;
	}
	return 0;
}