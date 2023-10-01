
    static class point implements Comparable<point> {
        double x, y;

        point(double _x, double _y) {
            x = _x;
            y = _y;
        }

        // angulo de coordenadas cartesianas a polares
        double angle() {
            double r = sqrt(x * x + y * y);
            double theta = atan2(y, x);
            return toDegrees(theta);
        }

        @Override
        public int compareTo(point p) {
            if (x == p.x)
                return Double.compare(y, p.y);
            return Double.compare(x, p.x);
        }

        @Override
        public boolean equals(Object o) {
            point p = (point) o;
            return x == p.x && y == p.y;
        }
    }
