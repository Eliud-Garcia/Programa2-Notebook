
    //Build O(n long n)
    //Query O(1)
    static class STable {
        int N, K;
        int st[][];

        //min, max, or, and, gcd, lcm, abs
        //ceil, floor, etc
        int oper(int a, int b) {
            return min(a, b);
        }

        STable(List<Integer> a) {
            N = a.size();
            K = (int) (log(N) / log(2)) + 1;
            st = new int[N + 1][K];
            for (int i = 0; i < N; i++)
                st[i][0] = a.get(i);
            for (int j = 0; j < K - 1; j++) {
                for (int i = 0; i + (1 << (j + 1)) <= N; ++i) {
                    st[i][j + 1] = oper(st[i][j], st[i + (1 << j)][j]);
                }
            }
        }
        
        //non-idempotent operations
        //O(log(n))
        long sum(int l, int r) {
            long sum = 0;
            for (int j = K; j >= 0; j--) {
                if ((1 << j) <= r - l + 1) {
                    sum += st[l][j];
                    l += (1 << j);
                }
            }
            return sum;
        }

        int query(int l, int r) {
            int k = 31 - Integer.numberOfLeadingZeros(r - l + 1);
            return oper(st[l][k], st[r - (1 << k) + 1][k]);
        }
    }
