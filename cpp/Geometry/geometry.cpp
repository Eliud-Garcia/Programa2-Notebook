

//cordenada (x, y) de cada punto
vi X;
vi Y;
//valida si los 3 puntos estan en la misma linea
bool sameLine(int p1, int p2, int p3) {
  ll v1 = X[p1] * Y[p2] + X[p2] * Y[p3] + X[p3] * Y[p1];
  ll v2 =  X[p2] * Y[p1] + X[p3] * Y[p2] + X[p1] * Y[p3];
  return v1 == v2;
}



/*
razones trigonometricas

CO = cateto opuesto
CA = cateto adyacente
H = hipotenusa

sin(angulo) = CO / H
cos(angulo) = CA / H
tan(angulo) = CO / CA

sosecante(angulo) = H / CO
secante(angulo) = H / CA
cotangente(angulo) = CA / CO 
*/
