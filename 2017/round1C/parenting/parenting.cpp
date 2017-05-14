#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Schedule
{
public:
	int start, end;
	Schedule(int start, int end)
	: start(start)
	, end(end)
	{
	}
	bool operator<(const Schedule& s) const
	{
		return start<s.start || (start == s.start && end < s.end);
	}
};

int parenting()
{
	int ac, aj;
	cin >> ac >> aj;
	if (ac == 0 && aj == 0)
	{
		return 2;
	}
	vector<Schedule> acSchedule, ajSchedule;
	for (size_t i=0; i<ac; ++i)
	{
		int s, e;
		cin >> s >> e;
		acSchedule.push_back(Schedule(s, e));
	}
	sort(acSchedule.begin(), acSchedule.end());
	for (size_t j=0; j<aj; ++j)
	{
		int s, e;
		cin >> s >> e;
		ajSchedule.push_back(Schedule(s, e));
	}
	sort(ajSchedule.begin(), ajSchedule.end());
	int res = 0;
	int ajIdx = 0, acIdx = 0;
	while ( acIdx < acSchedule.size() || ajIdx < ajSchedule.size() )
	{
		int startTime = acSchedule[acIdx].start;
		while ( acIdx+1 < acSchedule.size() && ajIdx < ajSchedule.size()
			 && acSchedule[acIdx].end < ajSchedule[ajIdx].start
			 && acSchedule[acIdx+1].end-startTime<= 720)
			++acIdx;
		res += 2;
		++ajIdx;
	}

	}
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		cout << "Case #" << (i+1) << ": ";
		cout << parenting();
		cout << endl;
	}
	return 0;
}