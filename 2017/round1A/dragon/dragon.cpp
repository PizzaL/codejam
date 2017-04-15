#include <iostream>
#include <vector>

using namespace std;

class Knight
{
public:
	int health;
	int attackPower;
	Knight(int h, int a)
	: health(h)
	, attackPower(a)
	{}
};

class Dragon 
{
public:
	int health;
	int attackPower;
	int buff;
	int cure;
	int debuff;
	Knight knight;
	int round;
	void move(int i)
	{
		if (i == 0)	// attack
			knight.health -= attackPower;
		else if (i == 1) // buff
			attackPower += buff;
		else if (i == 2) // cure
			health = cure;
		else if (i == 3) // defuff
		{
			knight.attackPower -= debuff;
			if (knight.attackPower <= 0)
				knight.attackPower = 0;
		}
		++round;
		health -= knight.attackPower;
	}
	Dragon( int h, int a, int b, int d, int hk, int ak)
	: health(h)
	, cure(health)
	, attackPower(a)
	, buff(b)
	, debuff(d)
	, round(0)
	, knight(hk, ak)
	{}
	bool operator==(const Dragon& dragon) const
	{
		return dragon.health == health
		    && dragon.attackPower == attackPower
		    && dragon.knight.health == knight.health
		    && dragon.knight.attackPower == knight.attackPower;
	}
	bool operator!=(const Dragon& dragon) const
	{
		return !(*this == dragon);
	}
};

ostream& operator<<(ostream& out, const Dragon& dragon)
{
	out << "health=" << dragon.health 
		<< " attackPower=" << dragon.attackPower
		<< " knight.health="<< dragon.knight.health
		<< " knight.attackPower=" << dragon.knight.attackPower;
	return out;
}

void fightResult(Dragon dragon)
{
	vector<Dragon> queue;
	queue.push_back(dragon);
	int index = 0;
	while (index < queue.size() )
	{
		Dragon currDragon = queue[index++];
		cout <<"currDragon=" << currDragon << endl;
		for (size_t i=0; i<4; ++i)
		{
			Dragon newDragon = currDragon;
			newDragon.move(i);
			cout << "newDragon=" << newDragon << endl;
			if (newDragon.knight.health <=0)
			{
				cout << newDragon.round;
				return;
			}
			if ( newDragon.health > 0 
			  && find(queue.begin(), queue.end(), newDragon) == queue.end() )
				queue.push_back(newDragon);
		}
	}
	cout << "IMPOSSIBLE";
}

int main()
{
	int t;
	cin >> t;
	for (size_t i=0; i<t; ++i)
	{
		int hd, ad, hk, ak, b, d;
		cin >> hd >> ad >> hk >> ak >> b >> d;
		Dragon dragon(hd, ad, b, d, hk, ak);
		cout << "Case: #" << (i+1) << ": ";
		fightResult(dragon);
		cout << endl;
	}
	return 0;
}