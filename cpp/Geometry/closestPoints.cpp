// use Point_and_Segments.cpp
#include <bits/stdc++.h>

double closestPairRec(vector<Point> &pts, int l, int r)
{
    if (r - l <= 3)
    {
        double minD = 1e18;
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j < r; ++j)
                minD = min(minD, dist(pts[i], pts[j]));
        sort(pts.begin() + l, pts.begin() + r, [](Point a, Point b)
             { return a.y < b.y; });
        return minD;
    }

    int m = (l + r) / 2;
    double midX = pts[m].x;
    double d = min(closestPairRec(pts, l, m), closestPairRec(pts, m, r));

    vector<Point> temp;
    merge(pts.begin() + l, pts.begin() + m, pts.begin() + m, pts.begin() + r,
          back_inserter(temp), [](Point a, Point b)
          { return a.y < b.y; });
    copy(temp.begin(), temp.end(), pts.begin() + l);

    vector<Point> strip;
    for (int i = l; i < r; ++i)
        if (fabs(pts[i].x - midX) < d)
            strip.push_back(pts[i]);

    for (int i = 0; i < (int)strip.size(); ++i)
        for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) < d; ++j)
            d = min(d, dist(strip[i], strip[j]));

    return d;
}

double closestPair(vector<Point> pts)
{
    sort(pts.begin(), pts.end(), [](Point a, Point b)
         { return a.x < b.x; });
    return closestPairRec(pts, 0, pts.size());
}

int main()
{

    vector<Point> P = {{0, 0}, {3, 4}, {7, 7}, {4, 3}, {1, 1}};
    cout << "Distancia mínima: " << closestPair(P) << "\n";
    return 0;
}