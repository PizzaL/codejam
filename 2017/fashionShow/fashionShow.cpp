#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// #define TEST

class Model
{
public:
	char type;
	int point;
	int x;
	int y;
	static const string ModelType;
	Model( char type, int x, int y)
		: type(type)
		, x(x)
		, y(y)
	{
		if (type == '+')
			point = 1;
		else if (type == 'x')
			point = 1;
		else if (type == 'o')
			point = 2;
	}
	bool operator<(const Model& model) const
	{
		return x < model.x || (x == model.x && y < model.y);
	}	
	bool operator==(const Model& model) const
	{
		return x == model.x
			&& y == model.y
			&& type == model.type; 
	}
};	// Model

const string Model::ModelType="o+x";

ostream& operator<<(ostream& out, const Model& model)
{
	out << model.type << " " << model.x << " " << model.y;
	return out;
}

typedef set<Model>::iterator SMI;
typedef set<int>::iterator SII;

#ifdef TEST
void outputModel( ostream& out, const set<Model>& vec)
{
	for (SMI i=vec.begin(); i != vec.end(); ++i)
	{
			out << *i << endl;
	}
}
#endif

class Show
{
public:
	int n;
	set<Model> models;
	char map[100+5][100+5];
	string possibleModelMap[100+5][100+5];
	set<int> possiblePosition;
	set<Model> newModels;

	int calPoints() const
	{
		int point = 0;
		for (SMI it = models.begin(); it != models.end(); ++it )
		{
			point += it->point;
		}
		return point;
	}

	void calPosModel(int x, int y, const string limit)
	{
		if (possibleModelMap[x][y].find(limit) != string::npos)
		{
			possibleModelMap[x][y] = limit;
			if ( possibleModelMap[x][y].size() == 1 && possibleModelMap[x][y][0] == map[x][y] )
			{
				possiblePosition.erase( (x-1)*n + y);
			}
		}
		else
		{
			possibleModelMap[x][y] = "";
			possiblePosition.erase( (x-1)*n + y);
		}
	}

	void updatePossibleMap(const Model& model)
	{
		for (size_t i=1; i<=n; ++i)
		{
			// row = model->x or col = model->y
			if (model.type != '+') 
			{
				calPosModel(model.x , i, "+");
				calPosModel(i, model.y, "+");
			}
			if (model.type != 'x')
			{
				if (model.x>i && model.y>i)
					calPosModel(model.x-i, model.y-i, "x");
				if (model.x+i <=n && model.y+i <=n)
					calPosModel(model.x+i, model.y+i, "x");
				if (model.x+i <=n && model.y > i)
					calPosModel(model.x+i, model.y-i, "x");
				if (model.x > i && model.y+i <=n)
					calPosModel(model.x-i, model.y+i, "x");
			}	
		}
	}

	Show(int n, const set<Model>& models)
		: n(n)
		, models(models)
	{
		for (size_t i=1; i<=n; ++i)
			for (size_t j=1; j<=n; ++j)
			{
				map[i][j]='.';
				possibleModelMap[i][j]="o+x"; 
				possiblePosition.insert( (i-1)*n+j );
			}
		for (SMI it = models.begin(); it != models.end(); ++it)
		{
			map[it->x][it->y]=it->type;
			if ( it->type != 'o'
			  && possibleModelMap[it->x][it->y].find('o') != string::npos)
			{
				possibleModelMap[it->x][it->y] = "o"+string(1, it->type);	
			} else 
			{
				possibleModelMap[it->x][it->y].clear();
				possiblePosition.erase( (it->x-1)*n + it->y);
			}
			
			updatePossibleMap(*it);
		}
	}

	vector<Show> generateNextShows()
	{
		vector<Show> newShows;

		for (size_t i=0; i<Model::ModelType.size(); ++i)
		{	// search each model
			char modelType = Model::ModelType[i];
			for (SII it = possiblePosition.begin(); it != possiblePosition.end(); ++it)
			{
				int x = (*it-1)/n + 1;
				int y = (*it-1)%n+1;
				if (possibleModelMap[x][y].find(modelType) != string::npos)
				{
					Show newShow(*this);
					Model newModel(modelType, x, y);
					if (map[x][y] != '.')
					{	// upgrade
						Model oldModel(map[x][y], x, y);
						newShow.models.erase(oldModel);
					} 
					newShow.models.insert(newModel);
					newShow.newModels.insert(newModel);
					newShow.map[x][y] = modelType;
					newShow.possibleModelMap[x][y]="";
					newShow.updatePossibleMap(newModel);	// will update possiblePosition
					newShows.push_back(newShow);
#ifdef TEST
				cout << "newModel=" << newModel
				     << " added to NewShow"
				  	 << endl;
#endif
				}
			}
		}
		return newShows;
	}

	bool operator<(const Show& show)
	{
		return calPoints() < show.calPoints();
	}

	bool operator==(const Show& show)
	{
		return calPoints() == show.calPoints()
		    && models == show.models;
	}
};	// Show

typedef vector<Show>::iterator SSI;

#ifdef TEST
ostream& operator<<(ostream& out, const Show& show)
{
	out << "n=" << show.n 
		 << " models:" <<  endl;
	outputModel(out, show.models);
	out << endl << "possibleModelMap:";
	for (size_t i=1; i<=show.n ;++i)
	{
		for (size_t j=1; j<=show.n; ++j)
			out << "(" << i << " " << j << ")" << show.possibleModelMap[i][j] << " ";
		out << endl;
	}
	out << "possiblePosition=";
	for (SII it = show.possiblePosition.begin(); it != show.possiblePosition.end(); ++it)
	{
		out << *it << " ";
	}
	out << endl;
	return out;
}
#endif

void designShow(int n, const set<Model>& models)
{
	vector<Show> shows;
	Show finalShow(n, models);
#ifdef TEST
	cout << finalShow << endl;
#endif
	shows.push_back( finalShow );
	while ( !shows.empty() )
	{
		Show show = shows[0];
		shows.erase(shows.begin());
		vector<Show> newShows = show.generateNextShows();
		if (newShows.size() == 0 && finalShow < show)
			finalShow = show;
		else
		{
#ifdef TEST
			cout << newShows.size() << " newShows:" << endl;
#endif
			for (SSI it = newShows.begin(); it != newShows.end(); ++it)
			{
#ifdef TEST
				cout << *it << endl;
#endif
				if (find(shows.begin(), shows.end(), *it) != shows.end() )
					continue; 	// already in the queue
				shows.push_back(*it);
			}
		}
	}
	cout << finalShow.calPoints() << " " << finalShow.newModels.size() << endl;
	for (SMI it = finalShow.newModels.begin(); it != finalShow.newModels.end(); ++it)
	{
		cout << *it << endl;
	}
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		int n, m;
		cin >> n >> m;
		set<Model> models;
		models.clear();
		for (size_t j=0; j<m; ++j)
		{
			char type;
			int x, y;
			cin >> type >> x >> y;
			models.insert( Model(type, x, y) );
		}
		cout << "Case #" << (i+1) << ": ";
		designShow(n, models);
	}
	return 0;
}