
            //todos los divisores de un numero en O(sqrt(n))
            List<Long> div = new ArrayList<>();
            for (long i = 1; i * i <= n; i++) {
                if (n % i == 0) {
                    if (i * i == n) {
                        div.add(i);
                    } else {
                        div.add(i);
                        if (i != 1) {
                            div.add(n / i);
                        }
                    }
                }
            }
            