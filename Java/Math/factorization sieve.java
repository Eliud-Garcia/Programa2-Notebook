


	/*
     * primero llamar a sieve() y
     * luego a factorize()
     */

    static final long MAX = 1000000; // 10^6

    static long[] primediv = new long[(int) MAX];
    static List<Long> primes = new ArrayList<>();

    static void sieve() {
        for (int i = 0; i < MAX; i++)
            primediv[i] = i;
        int root = (int) sqrt(MAX) + 1;
        for (int i = 2; i < MAX; i++) {
            if (primediv[i] != i)
                continue;
            primes.add((long) i);
            if (i > root)
                continue;
            for (int j = i * i; j < MAX; j += i)
                primediv[j] = i;
        }
    }

    static Map<Long, Integer> factorize(long n) { // n <= 10^12
        Map<Long, Integer> factors = new HashMap<>();
        for (int i = 0; i < primes.size() && n >= MAX; ++i) {
            while (n % primes.get(i) == 0) {
                factors.put(primes.get(i), factors.getOrDefault(primes.get(i), 0) + 1);
                n /= primes.get(i);
            }
        }
        if (n >= MAX) {
            factors.put(n, factors.getOrDefault(n, 0) + 1);
            return factors;
        }
        while (n > 1) {
            factors.put(primediv[(int) n], factors.getOrDefault(primediv[(int) n], 0) + 1);
            n /= primediv[(int) n];
        }
        return factors;
    }

    public static void main(String[]args) throws IOException {
		
		
        sieve();

        Map<Long, Integer> ans = factorize(2500);

        for (Map.Entry<Long, Integer> entry : ans.entrySet()) {
            long prime = entry.getKey();
            int count = entry.getValue();
            for (int j = 0; j < count; j++) {
                System.out.println(prime);
            }
        }
    }