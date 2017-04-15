#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
	int start; 
	int end;
	Node()
		: start(0)
		, end(0)
	{}
	Node(int start, int end)
	: start(start)
	, end(end)
	{}
	bool operator<(const Node& node) const
	{
		return start < node.start 
		    || end < node.end;
	}
};

ostream& operator<<(ostream& out, const Node& node)
{
	out << "(" << node.start << ", " << node.end << ")";
	return out;
}

int packages[50+5][50+5];

int findKits(int n, int ingredient[], int p)
{
	vector<vector<Node> > nodes;
	for (size_t i=0; i<n; ++i)
	{
		vector<Node> newNodes;
		newNodes.clear();
		for (size_t j=0; j<p; ++j)
		{
			int maxValue = ingredient[i]*11/10;
			int minValue = ingredient[i]*9/10;
			newNodes.push_back(Node( (packages[i][j]+maxValue-1)*10/11/ingredient[i]
								   , packages[i][j]*10/9/ingredient[i]) );
		}
		sort(newNodes.begin(), newNodes.end());
		nodes.push_back(newNodes);
	}
	int result = 0;
	for (size_t i=0; i<p; i++)
	{
		Node& currNode = nodes[0][i];
		if (nodes[0][i].start > nodes[0][i].end)
			continue ;
		int found = true;
		for (size_t j=1; j<n; ++j)
		{
			int index =0;
			while ( index < nodes[j].size()
				 && (nodes[j][index].start > currNode.end
				 || nodes[j][index].end < currNode.start 
				 || nodes[j][index].start > nodes[j][index].end) ) 
				++index;
			if (index == nodes[j].size() )
			{
				found =false;
				break;
			}
			currNode.start = max(currNode.start, nodes[j][index].start);
			currNode.end = min(currNode.end, nodes[j][index].end);
			nodes[j].erase(nodes[j].begin()+index);
		}
		if (found)
			++result;
	}
	return result;
}
int main() {
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		int n, p;
		int ingredient[50+5];
		cin >> n >> p;
		for (size_t j=0; j<n; ++j)
			cin >> ingredient[j];
		for (size_t j=0; j<n; ++j)
			for (size_t k=0; k<p; ++k)
			{
				cin >> packages[j][k];
			}
		cout << "Case #" << i+1 << ": " << findKits(n, ingredient, p) << endl;
	}
	return 0;
}