/**

    Leet Cod 149 Max Points on a Line : Find the maximum number of points that occur on a line where the
    points have integer coordinates, and points are allowed to be repeated.

    Solution Idea: First get rid of multiplicity in points by using multi-points that include a count
    of their multiplicity.
**/

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

// Leet code requires us to use the standard namespace.

using namespace std;

/**
    The structure to hold point information as specified by Leet Code.

**/

struct Point {

    int x, y;

    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

// Comparison function for points. We just use a dictionary ordering.

bool operator<(const Point& lhs, const Point& rhs); 

/**
    Function to make a point from a an array of size 2. We don't add this as
    a constructor to Point inorder to stay with the specifications of Point.
**/

Point makePoint(int coord[2]) {

    return Point(coord[0], coord[1]);

}

/**
    Points that include multiplicity.
**/

struct MultiPoint : Point {

    int count;

    MultiPoint() : Point(), count(1) {}
    MultiPoint(int a, int b) : Point(a, b), count(1) {}
    MultiPoint(int coord[2]) : Point(coord[0], coord[1]), count(1) {} 
    MultiPoint(Point p, int count_) : Point(p), count(count_) {}
};

/**
    Output functions useful for printing.

**/

ostream& operator<<(ostream& os, const Point& p);
ostream& operator<<(ostream& os, const MultiPoint& mp); 

/**
    The solution class. Leetcode specifies the form of the member function maxPoints. 

**/

class Solution {

    public:

    int maxPoints(vector<Point>& points);

    private:

    vector<MultiPoint> aggregatePoints(const vector<Point>& points);
    
};

/**
    The main execution.
**/

int main() {

    int coordsArray[][2] = {{1,1}, {2,2}, {3,3}, {2, 2}};
    vector<int[2]> coords(coordsArray, coordsArray + sizeof(coordsArray) / sizeof(int) / 2);
    vector<Point> points;
    vector<MultiPoint> mPoints;
    Solution solver;
    int maxPoints;

    cout << "POINTS AND MULTIPOINTS TESTS" << endl
         << "Constructing Points and MultiPoints" << endl;

    // Construct points and multi points from the coordinates vector.

    for(int i = 0; i < coords.size(); i++) {

        points.push_back(Point(coords[i][0], coords[i][1]));
        mPoints.push_back(coords[i]);
    }

    // Let's print out the points. No need to be efficient here. 
    for(int i = 0; i < points.size(); i++)
        cout << points[i] << "\t"; 
    cout << endl;

    // Let's print out the multi-points.
    for(int i = 0; i< mPoints.size(); i++)
        cout << mPoints[i] << "\t";
    cout << endl;

    // Now let's test the Solution.

    cout << "Finding the maximum number of points" << endl;
    maxPoints = solver.maxPoints(points);

    return 0;

}

bool operator<(const Point& lhs, const Point& rhs) {

    if (lhs.x < rhs.x)
        return true;
    else if (lhs.x > rhs.x)
        return false;
    else 
        return (lhs.y < rhs.y); 

}

ostream& operator<<(ostream& os, const Point& p) {

    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

ostream& operator<<(ostream& os, const MultiPoint& mp) {

   const Point* p = &mp;
   os << *p << " " << mp.count << " times"; 
}

int Solution::maxPoints(vector<Point>& points) {

    // Find the multiplicities of the points.

    vector<MultiPoint> mPoints = aggregatePoints(points);

    for(int i = 0; i<mPoints.size(); i++)
        cout << mPoints[i] << "\t";
    cout << endl;
}

vector<MultiPoint> Solution::aggregatePoints(const vector<Point>& points) {

    vector<MultiPoint> mPoints;
    vector<Point>::const_iterator p;
    map<Point, int> pointCount;
    map<Point, int>::iterator mapIt;
    pair<Point, int> newCount;
    MultiPoint mp;
  
    // Use a map to keep track of the point counts.
 
    for(p = points.begin(); p != points.end(); p++) {
        mapIt = pointCount.find(*p);
        if (mapIt != pointCount.end()) 
            (mapIt->second)++;
        else {
            newCount = pair<Point, int>(*p, 1);
            pointCount.insert(newCount); 
        }
    } 

    // Now use the point counts to create the multiPoints.

    for(mapIt = pointCount.begin(); mapIt != pointCount.end(); mapIt++) {

        mp = MultiPoint(mapIt->first, mapIt->second); 
        mPoints.push_back(mp);

    }

    return mPoints;
}
