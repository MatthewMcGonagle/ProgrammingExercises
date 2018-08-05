/**
    LeetCode 149 Maximum Number of Points on a Line

    Given a list of 2-dimensional points (with integer coordinates), find the 
    maximum number of points that occur on a single line.

    Solution Idea: Lines passing through two integer valued points can
    be represented by a 3-tuple of integers (A, B, C) such that the line is
    Ax + By + C = 0. To make such a representation unique, we may divide out 
    by the greatest common divisor of all three numbers A, B, and C. We also 
    need to enforce a sign, i.e. the first non-zero coefficient is positive. 

    Passes: Benchmark is faster than 29.5% of all cpp submissions.
**/

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

// LeetCode uses the namespace std.
using namespace std;

/** 
    Two-dimensional point structure specified by LeetCode. Note that the xy-coordinates
    are integers.
**/

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

/**
    The constructor for a line is based on two integer coordinates the line passes through. The constructor
    handles the unique representation of the line.
**/

struct Line {

    /** 
        The line is represented as {coeff[0] * x + coeff[1] * y + coeff[2] = 0}.
    **/
    int coeff[3];

    bool isDegenerate; // Whether the line is degenerate.
    /**
        Empty constructor just makes a degenerate line.
    **/

    Line() {
        for(int i = 0; i < 3; i++)
            coeff[i] = 0;
        isDegenerate = true;
    }
    /**
        Constructor ensures the representation of the line is unique. We divide out by the
        greatest common divisor of the line, and we make sure that the first non-zero coefficient
        is non-negative.
    **/
    Line(Point& a, Point& b);

    /**
        Use a dictionary ordering on the coefficients where coeff[0] is the most significant.
    **/
    //bool operator<(const Line& rhs);
    friend bool operator<(const Line& lhs, const Line& rhs);

    private:

    /**
        Ensure that the coefficients for our line obey our sign rule. The first non-zero coefficient
        is positive. This is part of ensuring unique representation of the line. This function
        should only by run if the line is non-degenerate.
    **/
    void forceSignRule();

    /**
        Flip the sign of all of the coefficients.
    **/
    void invertCoeff();
};

// inline bool operator<(const Line& lhs, const Line& rhs) {
// 
//     return (lhs < rhs);
// }

/**
    Function for printing out the contents of a line to a stream.
**/

ostream& operator<<(ostream& os, const Line& l);
ostream& operator<<(ostream& os, const Point& p);

/**
    Compute the greatest common divisor of a list of integers. Used for the unique representation of a line.
**/

int gcd( int num[], int size);

/**
    Function to construct a vector of Points using a double array of int xy-coordinates.
**/

vector<Point> makePoints(int xys[][2], int npoints) {

    Point newPoint;
    vector<Point> points;
    int x, y;

    for(int i = 0; i < npoints; i++) {

       x = xys[i][0];
       y = xys[i][1];
       newPoint = Point(x, y); 

       points.push_back(newPoint); 
    }

    return points;
}

/**
    Solution of problem. The format of member function maxPoints is specified by LeetCode.
**/

class Solution {

    public :
    int maxPoints(vector<Point>& points);
    friend ostream& operator<<(ostream &os, const Solution& solution);

    private:

    void updateCount(Line& line, map<Line, int>& counts);

    int maxCount;
    map<Line, int> lineCounts;
};

/** 
    The main executable.
**/

int main() {
    // Failed for [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    //int xys[][2] = {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    //int xys[][2] = {{1,1}, {2,2}, {3,3}};
    //int xys[][2] = {{0,0}, {0,0}};
    //int xys[][2] = {{0,0}, {1,1}, {0,0}};
    // Last failed [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    // Output 2. Expected 4.
    int xys[][2] = {{1,1}, {3,2}, {5,3}, {4,1}, {2,3},{1,4}};
    int npoints = sizeof(xys) / sizeof(int) / 2;
    vector<Point> points;
    vector<Line> lines;
    Line newLine;
    Solution solution;
    int maxCount;
    
    cout << "Number of points = " << npoints << endl;
    points = makePoints(xys, npoints);

    for(int i = 0; i < points.size() - 1; i++) {
       for(int j = i + 1; j < points.size(); j++) {
           newLine = Line(points[i], points[j]);
           cout << newLine << endl;
           lines.push_back(newLine);
        } 
    }   

    cout << "Running the solution" << endl;
    maxCount = solution.maxPoints(points);
    cout << "maxCount = " << maxCount << endl; 

    cout << solution << endl; 
    return 0;

}

Line::Line(Point& a, Point& b) {

   int gcdCoeff;

   // The xy-terms have coefficients that come from the normal to the line.
   // A non-normalized normal direction is provided by
   // (-(change y), change x). 

    coeff[0] = a.y - b.y;
    coeff[1] = b.x - a.x;

    // Check for a degenerate line (all coefficents vanishing).

    if (coeff[0] == 0 && coeff[1] == 0) {

        coeff[2] = 0;
        isDegenerate = true;
        return;
    } 
    isDegenerate = false;

    // The constant may be computed by just plugging in one of the points.

    coeff[2] = -coeff[0] * a.x - coeff[1] * a.y; 
    
    // Now remove the greatest common divisor.

    gcdCoeff = gcd(coeff, 3);
    for (int i = 0; i< 3; i++)
        coeff[i] /= gcdCoeff;

    // Now ensure our rule for the sign of the coefficents;

    forceSignRule();
}

ostream& operator<<(ostream &os, const Solution& solution) {

    map<Line, int>::const_iterator key;

    os << "SOLUTION INFO" << endl
       << "max Count = " << solution.maxCount << endl
       << "line count information" << endl;
    for(key = solution.lineCounts.begin(); key != solution.lineCounts.end(); key++) {

        os << key -> first << " has count " << key -> second << endl;
    }

    return os;
}

bool operator<(const Line& lhs, const Line& rhs) {

    bool coeffEqual;

    // Look for the first non-equal coefficients to make a comparison.

    for(int i = 0; i < 3; i++) {

        if(lhs.coeff[i] == rhs.coeff[i])
            continue;
        else
            return lhs.coeff[i] < rhs.coeff[i];
    }

    // All coefficients are same so we have equality. So we don't
    // have that less than is true.

    return false;
}

ostream& operator<<(ostream& os, const Line &l) {

    os << l.coeff[0] << " * x + "
       << l.coeff[1] << " * y + "
       << l.coeff[2] << " = 0";

    return os;
}

ostream& operator<<(ostream& os, const Point& p) {

    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

void Line::forceSignRule() {

    // Look for the first non-zero coefficient. If it is positive
    // then we are done. If it is negative, then we invert all of
    // the coefficients, and then we are done.

    for (int i = 0; i < 2; i++) {

        if (coeff[i] > 0)
            return;
        else if(coeff[i] < 0) {
           invertCoeff();
           return; 
        }
    }

}

void Line::invertCoeff() {

    for(int i = 0; i < 3; i++)
        coeff[i] *= -1; 
}

int gcd(int num[], int size) {

    int pairwiseGcd = num[0];

    for (int i = 1; i < size - 1; i++) 
       pairwiseGcd = __gcd(pairwiseGcd, num[i]); 

    return pairwiseGcd;
}

int Solution::maxPoints(vector<Point>& points) {

    Line line;
    vector<Point>::iterator endpoint[2];
    map<Line, int>::iterator key;
    map<Line, int> sweepCount;
    int repetition, newcount;

    // First look at the degenerate case where there are no lines.

    if(points.size() == 0)
        return 0;
    else if (points.size() == 1)
        return 1;

    lineCounts.clear();
    maxCount = 0;

    // Iterate over all pairs.

    for(endpoint[0] = points.begin(); endpoint[0] != points.end() - 1; endpoint[0]++) {
   
        sweepCount.clear(); 
        repetition = 0;

        for(endpoint[1] = endpoint[0] + 1; endpoint[1] != points.end(); endpoint[1]++) {

            line = Line(*endpoint[0], *endpoint[1]);

            // We only process a line if it is non-degenerate and if it
            // hasn't been counted in the master record of line counts. 
            // If it is degenerate, update the repetition count for the sweep.

            if(line.isDegenerate) 
                repetition++;

            else if (lineCounts.find(line) == lineCounts.end())
                updateCount(line, sweepCount);
        }

        for (key = sweepCount.begin(); key != sweepCount.end(); key++) {
           
            newcount = key -> second + repetition; 
            lineCounts.insert(pair<Line, int>(key -> first, newcount));
            if (newcount > maxCount)
                maxCount = newcount; 
        }
    } 

    // If there are no lines, then all points are the same, and we just return the
    // size of points. 

    if(lineCounts.empty())
        return points.size();
    else
        return maxCount;
}

void Solution::updateCount(Line& line, map<Line, int>& counts) {

    map<Line, int>::iterator key;
    key = counts.find(line);
    if(key == counts.end())
        counts.insert(pair<Line, int>(line, 2));

    else 
        (key -> second)++;
}
