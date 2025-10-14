//use struct polygon and point from Polygon.cpp and Point_and_Segments.cpp

bool inside(const Point &a, const Point &b, const Point &p)
{
    return orientation(a, b, p) >= 0;
}

Point lineIntersection(const Point &a, const Point &b, const Point &c, const Point &d)
{
    Point r = b - a, s = d - c;
    double t = (c - a).cross(s) / r.cross(s);
    return a + r * t;
}

vector<Point> convexIntersection(const vector<Point> &A, const vector<Point> &B)
{
    vector<Point> output = A;

    for (int i = 0; i < (int)B.size(); ++i)
    {
        Point a = B[i], b = B[(i + 1) % B.size()];
        vector<Point> input = output;
        output.clear();

        for (int j = 0; j < (int)input.size(); ++j)
        {
            Point p = input[j], q = input[(j + 1) % input.size()];
            bool pin = inside(a, b, p), qin = inside(a, b, q);

            if (pin && qin)
                output.push_back(q);
            else if (pin && !qin)
                output.push_back(lineIntersection(a, b, p, q));
            else if (!pin && qin)
            {
                output.push_back(lineIntersection(a, b, p, q));
                output.push_back(q);
            }
        }
    }

    if (output.size() > 1 && output.front() == output.back())
        output.pop_back();
    return output;
}

int main()
{

    vector<Point> A = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    vector<Point> B = {{2, -1}, {5, 2}, {2, 5}, {-1, 2}};
    vector<Point> inter = convexIntersection(A, B);
    Polygon interPoly(inter);
    cout << "Área de intersección: " << interPoly.area() << "\n";
}