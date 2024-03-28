/* Guarda en primes los numeros primos menores o iguales a MAX */
static final int MAX = 10000000;
static ArrayList<Integer> primes = new ArrayList<>();
static boolean sieve[] = new boolean[MAX + 5];
static void calculatePrimes() {
    sieve[0] = sieve[1] = true;
    int i;
    for (i = 2; i * i <= MAX; i++) {
        if (!sieve[i]) {
            primes.add(i);
            for (int j = i * i; j <= MAX; j += i)
                sieve[j] = true;
        }
    }
    for (; i <= MAX; i++) {
        if (!sieve[i]) {
            primes.add(i);
        }
    }
}