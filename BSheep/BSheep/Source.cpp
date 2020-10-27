#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class point
{
	public :
		int x;
		int y;
		int id;
		point() {};
		point(int a, int b, int c) { x = a, y = b, id = c;}
		double distance(point a)
		{
			int changeX = a.x - x;
			int changeY = a.y - y;
			return sqrt(pow(changeX, 2) + pow(changeY, 2));
		}

		// operator overload to compare previous vector locations to next locations
		bool operator != (point a)
		{
			if (a.x != x || a.y != y)
			{
				return true;
			} else {
				return false;
			}
		}
};

bool similar(point a, point b)
{
	//checks point 1 and 2 to see if they are the same location 
	if (a.y == b.y) 
	{
		if (a.x == b.x)
		{
			return a.id < b.id;
		} else {
			return a.x < b.x;
		}
	} else {
		return a.y < b.y;
	}
}

int sub(point w, point s, point d)
{
	// finds distance of x and y to point 1, from  point 2 and point 3
	return (s.x - w.x) * (d.y - w.y) - (d.x - w.x) * (s.y - w.y);
}

void hull(vector<point> w, vector<point> upper, vector<point> lower)
{
	sort(w.begin(), w.end(), similar);
	//make upper and lower vector for subsets
	int k = 1;
	for (int i = 1; i < w.size(); i++)
	{
		if (w[i-1] != w[i])
		{
			w[k++] = w[i];
		}
		w.resize(k);
		int length = 2 * k;
		upper.resize(length);
		lower.resize(length);
		int j = 0;
		k = 0;
		for (int i = 0; i < w.size(); i++) 
		{
			while (j >= 2 && sub(lower[j - 2], lower[j - 1], w[i]) <= 0)
			{
				j--;
			}
			while (k >= 2 && sub(upper[k - 2], upper[k - 1], w[i]) >= 0)
			{
				k--;
			}
			lower[j++] = w[i];
			upper[k++] = w[i];
		}
		lower.resize(j);
		upper.resize(k);
	}
}

int main()
{
	int test;
	//find number of tests to be run
	cin >> test;
	//decrement through tests
	while (test--) 
	{
		int numSheep;
		//take in number of sheep
		cin >> numSheep;
		vector<point> yard;
		int x = 0;
		int y = 0;
		//get x, y coords of sheep as well as id and push back into the vector
		for (int i = 0; i < numSheep; i++) 
		{
			cin >> (x, y);
			yard.push_back(point(x, y, i + 1));
		}
		vector<point> upper;
		vector<point> lower;
		double distance = 0;
		hull(yard, upper, lower);
		//reverses upper and pushes into lower
		for (int i = upper.size() - 2; i > 0; i--)
		{
			lower.push_back(upper[i]);
		}
		// finds distance among lower vector
		for (int i = 1; i < lower.size(); i++)
		{
			distance += lower[i - 1].distance(lower[i]);
		}
		distance += lower[lower.size() - 1].distance(lower[0]);
		cout << distance;
		for (int i = 0; i < lower.size(); i++)
		{
			cout << lower[i].id;
		}
		cout << "\n";
	}

	return 0;
}