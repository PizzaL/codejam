#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Horse
{
public:
	int speed;
	int dest;
	Horse(int speed, int dest)
	: speed(speed)
	, dest(dest)
	{}
	Horse()
	{}
};

class Route
{
public:
	Horse horse;
	double time;
	int dist;
	Route( Horse& horse, double time, int dist)
	: horse(horse)
	, time(time)
	, dist(dist)
	{}
	Route()
	: time(0)
	, dist(-1)
	{}
};

int map[100+5][100+5];

void express()
{
	int n, pair;
	cin >> n >> pair;
	vector<Horse> horses;
	for (size_t i=0; i<n; ++i)
	{
		int speed, dest;
		cin >> dest >> speed;
		horses.push_back(Horse( speed, dest) );
	}
	Route localMap[100+5][100+5];
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
		{
			cin >> map[i][j];
			if (i==j)
			{
				localMap[i][j].dist = 0;
				localMap[i][j].horse = horses[i];
				continue;
			}
			if (map[i][j] != -1 && horses[i].dest >= map[i][j])
			{
				localMap[i][j].horse = Horse(horses[i].speed, horses[i].dest - map[i][j]);
				localMap[i][j].time = 1.0*map[i][j]/horses[i].speed;
				localMap[i][j].dist = map[i][j];
			}
		}
	for (size_t k=0; k< n; ++k)
		for (size_t i=0; i<n; ++i)
			for (size_t j=0; j<n; ++j)
			{
				if (k ==i || k == j || i == j)
					continue;
				if ( localMap[i][k].dist>0 && localMap[k][j].dist>0)
				{
					double directTime = -1;
					if (localMap[i][k].dist+localMap[k][j].dist <= localMap[i][i].horse.dest)
						directTime = 1.0*(localMap[i][k].dist+localMap[k][j].dist)/localMap[i][i].horse.speed;
					if (localMap[i][j].dist < 0 && directTime > 0)
					{
						cout << i << "direct ->" << j << " time:" << directTime << endl;
						localMap[i][j].time = directTime;
						localMap[i][j].dist = localMap[i][k].dist + localMap[k][j].dist;
						localMap[i][j].horse = Horse(localMap[i][i].horse.speed, localMap[i][i].horse.dest - localMap[i][j].dist);
					}
				}
			}
	for (size_t k=0; k< n; ++k)
		for (size_t i=0; i<n; ++i)
			for (size_t j=0; j<n; ++j)
				{
					if (k ==i || k == j || i == j)
						continue;
					if ( localMap[i][j].dist < 0
					  || localMap[i][k].time + localMap[k][j].time < localMap[i][j].time )
					{
						cout << i << "->" << k << "->" << j <<endl;
						localMap[i][j].time = localMap[i][k].time + localMap[k][j].time;
						localMap[i][j].horse = localMap[k][j].horse;
						localMap[i][j].dist = localMap[i][k].dist + localMap[k][j].dist;
					}
				}
	for (size_t i=0; i<pair; ++i)
	{
		int start, end;
		cin >> start >> end;
		cout << " " << localMap[start-1][end-1].time;
	}
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		cout << "Case #" << (i+1) << ":";
		express();
		cout << endl;
	}
	return 0;
}