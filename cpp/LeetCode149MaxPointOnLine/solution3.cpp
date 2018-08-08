/**

    Leet Cod 149 Max Points on a Line : Find the maximum number of points that occur on a line where the
    points have integer coordinates, and points are allowed to be repeated.

    Solution Idea: First get rid of multiplicity in points by using multi-points that include a count
    of their multiplicity.

    For unique identifiers of lines, instead of needing to divide out by greatest common divisors, let's
    represent them uniquely using a combination of integer, numerator, and denominator. For example, we
    represent 7/5 = 1 + 2/5. So we only need to do a single division and modulo operation. No need to find
    gcd's. Then to compare, we just use convert to long and do cross-multiplication.

    Solution Passes as being faster than 18.24% of all accepted cpp solutions (16 ms). So now real improvement
    over solution 2. Also, the use of long to keep track of cross-multiplication seems a little suspect as
    the exact size of int vs long is compiler dependent.
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
    Represent rational numbers using an integer part, a numerator, and a denominator.
    We use integer part to reduce the possibility of overflow. Then we can make
    comparisons on the fractional level using cross multiplication if needed.

    For example we represent 7/5 = 1 + 2/5. This only needs one integer division
    and one modulo operation. No need to find gcd's.
**/

struct Rational {

    int intPart, num, denom;

    Rational() : intPart(0), num(0), denom(1) {}
    Rational(int n) : intPart(n), num(0), denom(1) {}
    Rational(int num_, int denom_);

    inline bool nonZero() {return !(intPart == 0 && num == 0); }

    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend bool operator>(const Rational& lhs, const Rational& rhs){ return rhs < lhs; }
};

// /**
//     Can compute the product of two integers with precise precision. Use this for accurately
//     doing cross-multiplication.
// 
// **/
// 
// struct LargeInt {
// 
//     int mostSig, leastSig;
//     LargeInt() : mostSig(0), leastSig(0) {}
//     LargeInt(int n) : mostSig(0), leastSig(n) {}
// 
//     void product(int x, int y);
// };

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

    Rational coeff[3];

    Line(const Point& a, const Point& b);

    Line() { 
        
        for(int i = 0; i < 3; i++)
            coeff[i] = Rational(0);
    }

    private:
    inline void enforceUniqueness(const int initCoeff[3]);

    friend bool operator<(const Line& lhs, const Line& rhs);
};

/**
    Output functions useful for printing.

**/

ostream& operator<<(ostream& os, const Point& p);
ostream& operator<<(ostream& os, const MultiPoint& mp); 
ostream& operator<<(ostream& os, const Line& l);

/**
    The solution class. Leetcode specifies the form of the member function maxPoints. 

**/

class Solution {

    public:

    int maxPoints(vector<Point>& points);
    void printMap();

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

    //int coordsArray[][2] = {{1,1}, {2,2}, {3,3}, {2, 2}};

    // Input [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]] fails for division by 0.
    // int coordsArray[][2] = {{1,1}, {3,2}, {5,3}, {4,1}, {2,3}, {1,4}};
    // Input [[0,0],[65536,65536],[65536,131072]] failed with output 3, expected 2.
    //int coordsArray[][2] = {{0, 0}, {65536, 65536}, {65536, 131072}};
    // Input [[0,-12],[5,2],[2,5],[0,-5],[1,5],[2,-2],[5,-4],[3,4],[-2,4],[-1,4],[0,-5],[0,-8],[-2,-1],[0,-11],[0,-9]]
    // failes with output 3, expected 6.
    //int coordsArray[][2] = {{0,-12},{5,2},{2,5},{0,-5},{1,5},{2,-2},{5,-4},{3,4},{-2,4},{-1,4},{0,-5},{0,-8},{-2,-1},{0,-11},{0,-9}};
    // Input [[0,0],[94911151,94911150],[94911152,94911151]] fails with output 3, expected 2.
    int coordsArray[][2] = {{0,0},{94911151,94911150},{94911152,94911151}};
    vector<int[2]> coords(coordsArray, coordsArray + sizeof(coordsArray) / sizeof(int) / 2);
    vector<Point> points;
    vector<MultiPoint> mPoints;
    Solution solver;
    int maxPoints;
    Rational x, y;

    cout << "RATIONAL NUMBER TEST" << endl
        << "Rational(-10, 4) = " << Rational(-10, 4) << endl 
        << "Rational(10, -4) = " << Rational(10, -4) << endl
        << "Rational(10, 4) = " << Rational(10, 4) << endl
        << "Rational(-10, -4) = " << Rational(-10, -4) << endl;

    x = Rational(10, 4);
    y = Rational(18, 7);

    cout << "( " << x << " < " << y << " ) = " << (x < y) << endl << endl;

    x = Rational(3,2);
    y = Rational(6,4);
    cout << "( " << x << " < " << y << " ) = " << (x < y) << endl << endl;
    cout << "( " << x << " > " << y << " ) = " << (x > y) << endl << endl;

    x = Rational(3,2);
    y = Rational(-10, 3);
    cout << "( " << x << " > " << y << " ) = " << (x > y) << endl << endl;

    


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

    // Let's try constructing some lines.

    cout << "The line through " << points[0] << " and " << points[1] << " is " << Line(points[0], points[1]) << endl;

    // Now let's test the Solution.

    cout << "Finding the maximum number of points" << endl;
    maxPoints = solver.maxPoints(points);
    cout << "The maximum number of points = " << maxPoints << endl;

    solver.printMap();

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

Rational::Rational(const int num_, const int denom_) {

    if(denom_ < 0) {
        num = num_ * -1;
        denom = denom_ * -1;
    }
    else {
        num = num_;
        denom = denom_;
    } 

    intPart = num / denom;
    num = num % denom;

    if(num < 0) {
        num += denom;
        intPart -= 1;
    }

}

ostream& operator<<(ostream& os, const Rational& rhs) {

    if (rhs.intPart != 0)
        os << rhs.intPart << " + ";
    os << rhs.num << " / " << rhs.denom;
    return os;
}

bool operator<(const Rational& lhs, const Rational& rhs) {

    long check[2];

    // First check the integer part as it is most significant.

    if (lhs.intPart != rhs.intPart)
        return lhs.intPart < rhs.intPart;

    // Now we need to make the comparison at the fractional level using
    // cross multiplication.

    check[0] = lhs.num;
    check[0] *= rhs.denom;
    check[1] = rhs.num;
    check[1] *= lhs.denom;
    return check[0] < check[1];
}

Line::Line(const Point& a, const Point& b) {

    int initCoeff[3];
    initCoeff[0] = b.y - a.y;
    initCoeff[1] = a.x - b.x;
    initCoeff[2] = -initCoeff[0] * a.x - initCoeff[1] * a.y;

    enforceUniqueness(initCoeff);

}

void Line::enforceUniqueness(const int initCoeff[3]) {

    // Break into cases of whether the x coefficient is non-vanishing.

    if(initCoeff[0] != 0) {

        coeff[0] = Rational(1);
       
        for(int i = 1; i < 3; i++)
            coeff[i] = Rational(initCoeff[i], initCoeff[0]);
    }
    else {

        coeff[0] = Rational(0);
        coeff[1] = Rational(1);
        coeff[2] = Rational(initCoeff[2], initCoeff[1]);
    }
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

ostream& operator<<(ostream& os, const Line& l) {

    os << "( " << l.coeff[0] << " ) x + ( " << l.coeff[1] << " ) y + "
       << l.coeff[2] << " = 0";    

    return os;
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

    return maxCount;
}

void Solution::printMap() {

    map<Line, int>::const_iterator mapIt;
    for(mapIt = pointsOnLine.begin(); mapIt != pointsOnLine.end(); mapIt++)
        cout << mapIt -> first << " has " << mapIt -> second << " points" << endl;
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

    vector<MultiPoint>::const_iterator mp;
    map<Line, int> sweepCounts;
    map<Line, int>::iterator lineCount;
    Line line;

    for(mp = begin; mp != end; mp++) {

        line = Line(commonEndPoint, *mp);
        updateSweepCount(line, *mp, sweepCounts);

    }


    // For all of the lines we found during the sweep, we never counted the common end point. So we now have
    // to add this multiplicity in. Then insert into our master map of line counts. Also update the maximum
    // count if we find something larger.

    for(lineCount = sweepCounts.begin(); lineCount != sweepCounts.end(); lineCount++) {

        (lineCount -> second) += commonEndPoint.count; 
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

