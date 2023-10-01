

    //usar la clase point
    static class circle {

        point centro;
        double radio;

        circle(point center, double radius) {
            this.centro = center;
            this.radio = radius;
        }

        // Almacena los puntos en el arco del círculo
        List<point> construirArco(double anguloInicio, double anguloFin) {
            List<point> arco = new ArrayList<>();

            double radianIni = toRadians(anguloInicio);
            double radianEnd = toRadians(anguloFin);
            double incrementoAngular = 0.00000001;

            for (double theta = radianIni; theta <= radianEnd; theta += incrementoAngular) {
                double X = centro.x + radio * cos(theta);
                double Y = centro.y + radio * sin(theta);
                arco.add(new point(X, Y));
            }

            return arco;
        }

        // point a = inicio de la linea
        // point b = final de la linea
        boolean interseccionConLinea(point a, point b) {

            // m = (y2- y1) / (x2-x1);
            double m = (b.y - a.y) / (b.x - a.x);

            // Ax + By + C = 0

            double A = -m;
            double B = 1;
            double C = -(m * a.x) + a.y;

            double x0 = abs(-A * C / (A * A + B * B)), y0 = abs(-B * C / (A * A + B * B));

            if (C * C > radio * radio * (A * A + B * B) + 1e-6) {
                //sa.println(-1);
                return false;
            } else {
                double d = radio * radio - C * C / (A * A + B * B);
                double mult = sqrt(d / (A * A + B * B));
                double ax, ay, bx, by;
                ax = x0 + B * mult;
                bx = x0 - B * mult;
                ay = y0 - A * mult;
                by = y0 + A * mult;

                if (radio >= b.x) {
                    //sa.println(0);
                } else {
                    point ans1 = new point(ax, ay); //interseccion 1
                    point ans2 = new point(bx, by); // inteseccion 2
                    // sa.println(ans1.x + " " + ans1.y + " " + abs(ans1.angle()));
                    // sa.println(ans2.x + " " + ans2.y + " " + abs(ans2.angle()));

                }
                return true;
            }
        }

    }
