/*
PI = 3.141592653589793...
RAD_TO_DEG(x) = x * 180 / PI
DEG_TO_RAD(x) = x * PI / 180
Circunferencia completa = 2 * PI * r
Área del círculo = PI * r²
*/

ld DEG_TO_RAD(ld deg) { return deg * PI / 180.0; }
ld RAD_TO_DEG(ld rad) { return rad * 180.0 / PI; }

// -------------------- CÍRCULO Y ARCO --------------------

/*
d = 2r
l = longitud de la cuerda del arco (≤ d)
θ = ángulo central en radianes
*/

ld arco_por_cuerda(ld d, ld l) {
    // longitud del arco correspondiente a una cuerda de longitud l
    // devuelve (arco / perímetro)
    return (d * acos(l/d)) / (PI * d);
}

ld longitud_arco(ld r, ld angulo_en_grados) {
    return 2 * PI * r * (angulo_en_grados / 360.0);
}

ld area_sector(ld r, ld angulo_en_grados) {
    return (PI * r * r * angulo_en_grados) / 360.0;
}

ld area_segmento(ld r, ld angulo_en_radianes) {
    // área del segmento circular (sector - triángulo)
    return 0.5 * r * r * (angulo_en_radianes - sin(angulo_en_radianes));
}
// -------------------- TRIÁNGULOS --------------------
ld area_heron(ld a, ld b, ld c) {
    ld s = (a + b + c) / 2;
    return sqrtl(s * (s - a) * (s - b) * (s - c));
}

ld area_triangulo(pt a, pt b, pt c) {
    return fabsl(cross(b - a, c - a)) / 2.0;
}

ld circunradio(ld a, ld b, ld c) {
    ld A = area_heron(a, b, c);
    return (a * b * c) / (4.0 * A);
}

ld inradio(ld a, ld b, ld c) {
    ld A = area_heron(a, b, c);
    ld s = (a + b + c) / 2;
    return A / s;
}

/*
Teorema del seno:
    a / sin(A) = b / sin(B) = c / sin(C) = 2R
    
Teorema del coseno:
    c² = a² + b² - 2ab * cos(C)

Pitágoras:
    c² = a² + b²  (si C = 90°)

Distancia punto a plano (3D):
    d = |Ax + By + Cz + D| / sqrt(A² + B² + C²)

Vector normal a un plano (3D):
    n = (p2 - p1) × (p3 - p1)

Ángulo entre dos vectores:
    θ = arccos( (u·v) / (|u| |v|) )
*/
