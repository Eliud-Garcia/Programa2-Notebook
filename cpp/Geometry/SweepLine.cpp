//use struct polygon and point from Polygon.cpp and Point_and_Segments.cpp

// Sweep Line Algorithm to detect if any segments intersect
struct Segment
{
    Point p, q;
    int id;
    Segment(Point _p, Point _q, int _id) : p(_p), q(_q), id(_id) {}
};


struct SweepCmp
{
    double x;
    bool operator()(const Segment &a, const Segment &b) const
    {
        auto getY = [&](const Segment &s, double X)
        {
            if (fabs(s.p.x - s.q.x) < EPS)
                return s.p.y;
            return s.p.y + (s.q.y - s.p.y) * (X - s.p.x) / (s.q.x - s.p.x);
        };
        double y1 = getY(a, x), y2 = getY(b, x);
        if (fabs(y1 - y2) > EPS)
            return y1 < y2;
        return a.id < b.id;
    }
};

struct Event
{
    double x;
    int type; // 0 = inicio, 1 = fin
    Segment seg;
    Event(double _x, int _t, Segment _s) : x(_x), type(_t), seg(_s) {}
    bool operator<(const Event &e) const
    {
        if (fabs(x - e.x) > EPS)
            return x < e.x;
        return type < e.type;
    }
};

bool anySegmentIntersection(vector<Segment> &segs)
{
    vector<Event> events;
    for (auto &s : segs)
    {
        if (s.q < s.p)
            swap(s.p, s.q);
        events.push_back(Event(s.p.x, 0, s));
        events.push_back(Event(s.q.x, 1, s));
    }
    sort(events.begin(), events.end());

    set<Segment, SweepCmp> active;
    SweepCmp cmp;

    auto next_it = [&](auto it)
    { return it == prev(active.end()) ? active.end() : next(it); };
    auto prev_it = [&](auto it)
    { return it == active.begin() ? active.end() : prev(it); };

    for (auto &ev : events)
    {
        cmp.x = ev.x;
        if (ev.type == 0)
        { // Insertar segmento
            auto it = active.insert(ev.seg).first;
            auto it_prev = prev_it(it), it_next = next_it(it);
            if (it_prev != active.end() && segmentsIntersect(it_prev->p, it_prev->q, it->p, it->q))
                return true;
            if (it_next != active.end() && segmentsIntersect(it_next->p, it_next->q, it->p, it->q))
                return true;
        }
        else
        { // Eliminar
            auto it = active.find(ev.seg);
            if (it == active.end())
                continue;
            auto it_prev = prev_it(it), it_next = next_it(it);
            if (it_prev != active.end() && it_next != active.end() &&
                segmentsIntersect(it_prev->p, it_prev->q, it_next->p, it_next->q))
                return true;
            active.erase(it);
        }
    }
    return false;
}

int main()
{
    vector<Segment> segs = {
        {{0, 0}, {4, 4}, 1},
        {{1, 4}, {4, 1}, 2},
        {{5, 5}, {7, 7}, 3}};
    cout << (anySegmentIntersection(segs) ? "Sí hay intersección" : "No hay intersección") << "\n";

    return 0;
}