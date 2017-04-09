#include <iostream>
#include <set>

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
#ifdef TEST
			cout << "model=" << *it << endl;
#endif
			point += it->point;
		}
		return point;
	}

	void calPosModel(int x, int y, const string limit)
	{
#ifdef TEST
		cout << "(" << x << ", " << y << ")" << possibleModelMap[x][y] << "&" << limit << endl;
#endif
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
#ifdef TEST
		cout << "n=" << n 
			 << " models:" <<  endl;
		outputModel(cout, models);
		cout << endl << "possibleModelMap:";
		for (size_t i=1; i<=n ;++i)
		{
			for (size_t j=1; j<=n; ++j)
				cout << "(" << i << " " << j << ")" << possibleModelMap[i][j] << " ";
			cout << endl;
		}
		cout << "possiblePosition=";
		for (SII it = possiblePosition.begin(); it != possiblePosition.end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
#endif
	}

	bool operator<(const Show& show) const
	{
		return calPoints() < show.calPoints();
	}

	void generateNextShows()
	{
		int index = 0;
		while ( !possiblePosition.empty() && index < Model::ModelType.size() )
		{
			char modelType = Model::ModelType[index];
			bool noMore = true;
			for (SII it = possiblePosition.begin(); it != possiblePosition.end(); ++it)
			{
				int x = (*it-1)/n + 1;
				int y = (*it-1)%n+1;
#ifdef TEST
				cout << "(" << x << ", " << y << ")" << endl;
#endif
				if (possibleModelMap[x][y].find(modelType) != string::npos)
				{
					Model newModel(modelType, x, y);
#ifdef TEST
					cout << "newModel=" << newModel << endl;	
#endif
					if (map[x][y] != '.')
					{	// upgrade
						Model oldModel(map[x][y], x, y);
						models.erase(oldModel);
#ifdef TEST
						cout << "update oldModel=" << oldModel 
							 << " to newModel=" << newModel
							 << endl;
#endif
					} 
					models.insert(newModel);
					newModels.insert(newModel);
					map[x][y] = modelType;
					possibleModelMap[x][y]="";
					updatePossibleMap(newModel);	// will update possiblePosition
#ifdef TEST
					cout << endl << "possibleModelMap:";
					for (size_t i=1; i<=n ;++i)
					{
						for (size_t j=1; j<=n; ++j)
							cout << "(" << i << " " << j << ")" << possibleModelMap[i][j] << " ";
						cout << endl;
					}
					for (SII it = possiblePosition.begin(); it != possiblePosition.end(); ++it)
					{
						cout << *it << " ";
					}
					cout << endl;
#endif
					noMore = false;
					break;							// break to reloop
				}
			} 
			if (noMore)
				++index;
		}
	}

};	// Show

void designShow(int n, const set<Model>& models)
{
	Show show(n, models);
	show.generateNextShows();
	cout << show.calPoints() << " " << show.newModels.size() << endl;
	for (SMI it = show.newModels.begin(); it != show.newModels.end(); ++it)
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