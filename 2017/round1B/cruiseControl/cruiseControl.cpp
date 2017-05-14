#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Horse
{
public:
	int dest;
	int speed;
	double time;
	Horse(int dest, int speed)
	: dest(dest)
	, speed(speed)
	{
		time = 1.0*dest/speed;
	}
	bool operator<(const Horse& horse) const
	{
		return time < horse.time;
	}
};

void cruiseControl()
{
	int dest, n;
	cin >> dest >> n;
	vector<Horse> horses;
	for (size_t i=0; i<n; ++i)
	{
		int toDest, speed;
		cin >> toDest >> speed;
		horses.push_back(Horse(dest-toDest, speed));
	}
	sort(horses.begin(), horses.end());
	double res = dest;
	res /= horses[horses.size() -1 ].time;
	cout << fixed << setprecision(6) << res;
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		cout << "Case #" << (i+1) << ": ";
		cruiseControl();
		cout << endl;
	}
	return 0;
}