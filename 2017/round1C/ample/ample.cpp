#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
const double pie = 3.14159265358979323846;
double res[1000][1000];
int lastOne[1000][1000];

class Ample {
public:
	int height;
	int r;
	Ample(int r, int height)
	: r(r)
	, height(height)
	{
	}

	double top()
	{
		return 1.0*r*r*pie;
	}
	double total()
	{
		return top() + 2.0*pie*r*height;
	}
	bool operator<(const Ample& ample) const
	{
		return r<ample.r || (r == ample.r && height < ample.height );
	}
};

double cal(vector<Ample>& amples, int k)
{
	sort(amples.begin(), amples.end());
	for (size_t i=0; i<=amples.size(); ++i)
	{
		res[i][0] = 0;
	}
	for (size_t j=1; j<=k; ++j)
		for (size_t i=j; i<=amples.size(); ++i)
		{
			res[i][j] = res[i-1][j-1] + amples[i-1].total();
			lastOne[i][j] = i;
			if (j-1 != 0)
			{
				res[i][j] -= amples[lastOne[i-1][j-1]-1].top();
			}
			if (i-1 >= j && res[i-1][j] >= res[i][j] )
			{
				res[i][j] = res[i-1][j];
				lastOne[i][j] = lastOne[i-1][j];
			}
		}
	return res[amples.size()][k];
}

void ample()
{
	int n, k;
	cin >> n >> k;
	vector<Ample> amples;
	for (size_t i=0; i<n; ++i)
	{
		int r, h;
		cin >> r >> h;
		amples.push_back(Ample(r, h));
	}
	cout << fixed << setprecision(10) << cal(amples, k);
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		cout << "Case #" << (i+1) << ": ";
		ample();
		cout << endl;
	}
	return 0;
}