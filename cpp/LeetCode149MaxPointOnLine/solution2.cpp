/**

    Leet Cod 149 Max Points on a Line : Find the maximum number of points that occur on a line where the
    points have integer coordinates, and points are allowed to be repeated.

    Solution Idea: First get rid of multiplicity in points by using multi-points that include a count
    of their multiplicity.

    Solution Passes as being faster than 62.40% of all accepted cpp solutions (8 ms).
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

    Lines are given unique representations as triples of integers (A, B, C)
    such that the line is given by A * x + B * y + C = 0. The uniqueness
    is enforced by dividing out by the greatest common divisor of all
    three integers and also enforcing the first non-zero of A or B is
    positive.

    Note that a proper line shouldn't include A = B = 0. In the interest of
    efficiency, it is up to the user to make sure this is the case.

**/

struct Line {

    int coeff[3];

    Line(const Point& a, const Point& b);
    Line() { 
        for(int i = 0; i < 3; i++)
            coeff[i] = 0;

    }

    private:
    inline void getInitCoeffs(const Point &a, const Point &b);
    inline void removeGCD();
    inline void enforceSignRule();
    inline void inverseCoeff();

    friend bool operator<(const Line& lhs, const Line& rhs);
};

/**
    Output functions useful for printing.

**/

ostream& operator<<(ostream& os, const Point& p);
ostream& operator<<(ostream& os, const MultiPoint& mp); 

/**
    Greatest common divisor function.
**/

int gcd(int nums[], int size);

/**
    The solution class. Leetcode specifies the form of the member function maxPoints. 

**/

class Solution {

    public:

    int maxPoints(vector<Point>& points);

    private:

    vector<MultiPoint> aggregatePoints(const vector<Point>& points);
    int trivialCount(vector<MultiPoint>& mPoints);
    void doSweep(const MultiPoint& commonEndPoint, vector<MultiPoint>::const_iterator begin, 
                 vector<MultiPoint>::const_iterator end);

    void updateSweepCount(const Line& line, const MultiPoint& newPoint, map<Line, int>& sweepCount);

    map<Line, int> pointsOnLine; 
    int maxCount;
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
    cout << "The maximum number of points = " << maxPoints << endl;
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

Line::Line(const Point& a, const Point& b) {

    getInitCoeffs(a, b);
    removeGCD();
    enforceSignRule();

}

void Line::getInitCoeffs(const Point &a, const Point &b) {

    // coeff[0] and coeff[1] come from a choice of (un-normalized) normal direction to the line.
    // coeff[0] = change in y.
    coeff[0] = b.y - a.y; 

    // coeff[1] = - change in x. 
    coeff[1] = a.x - b.x;

    // coeff[2] is found by plugging in one of the points.

    coeff[2] = - coeff[0] * a.x - coeff[1] * a.y;


}

void Line::removeGCD() {

    int coeffGCD = gcd(coeff, 3);
    
    for(int i = 0; i < 3; i++)
        coeff[i] /= coeffGCD; 

}

void Line::enforceSignRule() {

    if (coeff[0] < 0)
        inverseCoeff();
    else if(coeff[0] == 0 && coeff[1] < 0)
        inverseCoeff();

}

void Line::inverseCoeff() {

    for(int i = 0; i < 3; i++)
        coeff[i] *= -1;

}

bool operator<(const Line& lhs, const Line& rhs) {

    // Use a dictionary ordering for the coefficients.

    for(int i = 0; i < 3; i++) {

        if(lhs.coeff[i] < rhs.coeff[i])
            return true;
        else if (lhs.coeff[i] > rhs.coeff[i])
            return false;
    }

    // If we made it this far then all coefficients are equal.

    return false;
}

ostream& operator<<(ostream& os, const Point& p) {

    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

ostream& operator<<(ostream& os, const MultiPoint& mp) {

   const Point* p = &mp;
   os << *p << " " << mp.count << " times"; 
   return os;
}

int gcd(int nums[], int size) {

    int pairwiseGcd = nums[0];
    for(int i = 1; i < size; i++)
        pairwiseGcd = __gcd(pairwiseGcd, nums[i]);

    return pairwiseGcd;
}

int Solution::maxPoints(vector<Point>& points) {

    // Find the multiplicities of the points.

    vector<MultiPoint> mPoints = aggregatePoints(points);
    vector<MultiPoint>::const_iterator mp[2]; 
    map<Line, int> sweepCount;
    map<Line, int>::iterator mapIt;

    // First check if we are in a trivial case.

    if (mPoints.size() < 3)
        return trivialCount(mPoints);

    // Next iterate over the pairs of multi-points.

    maxCount = 0;
    pointsOnLine.clear();

    for (mp[0] = mPoints.begin(); mp[0] != mPoints.end() - 1; mp[0]++) 

        doSweep(*mp[0], mp[0] + 1, mPoints.end());

    for(int i = 0; i<mPoints.size(); i++)
        cout << mPoints[i] << "\t";
    cout << endl;

    return maxCount;
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

int Solution::trivialCount(vector<MultiPoint>& mPoints) {

    if(mPoints.size() == 0)
        return 0;

    if(mPoints.size() == 1)
        return mPoints[0].count;

    if(mPoints.size() == 2)
        return mPoints[0].count + mPoints[1].count;
}

void Solution::doSweep(const MultiPoint& commonEndPoint, vector<MultiPoint>::const_iterator begin, vector<MultiPoint>::const_iterator end) {

    Point* p[2];
    vector<MultiPoint>::const_iterator mp;
    map<Line, int> sweepCounts;
    map<Line, int>::iterator lineCount;
    Line line;

    p[0] = (Point*) &commonEndPoint;

    for(mp = begin; mp != end; mp++) {

        p[1] = (Point*) &(*mp);
        line = Line(*p[0], *p[1]); 
        updateSweepCount(line, *mp, sweepCounts);

    }

    // For all of the lines we found during the sweep, we never counted the common end point. So we now have
    // to add this multiplicity in. Then insert into our master map of line counts. Also update the maximum
    // count if we find something larger.

    for(lineCount = sweepCounts.begin(); lineCount != sweepCounts.end(); lineCount++) {

        lineCount -> second += commonEndPoint.count; 
        pointsOnLine.insert(*lineCount);

        if(lineCount -> second > maxCount)
            maxCount = lineCount -> second;
    }
}

void Solution::updateSweepCount(const Line& line, const MultiPoint& newPoint, map<Line, int>& sweepCount) {

    map<Line, int>::iterator lineCount;
    pair<Line, int> newLineCount;

    // First check if we have already processed this line in previous sweeps.
    // Only do updates if it hasn't been seen before.

    lineCount = pointsOnLine.find(line); 
    if (lineCount != pointsOnLine.end()) 
        return;

    // Now check if the line was previously seen in this sweep.

    lineCount = sweepCount.find(line);
    if (lineCount != sweepCount.end()) 

        lineCount -> second += newPoint.count; 

    else {

        newLineCount = pair<Line, int>(line, newPoint.count); 
        sweepCount.insert(newLineCount);

    }
}

