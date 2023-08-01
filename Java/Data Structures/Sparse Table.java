

 // llenar sparse table O(n long n)


    static class Sparse_Table {
        int n, K;

        int st[][];

        int oper(int a, int b) {
            return a + b;
        }

        public Sparse_Table(List<Integer> a) {
            this.n = a.size();
            this.K = (int) (log(n) / log(2) + 1);
            st = new int[n + 1][K];

            for (int i = 0; i < n; i++)
                st[i][0] = a.get(i);

            for (int j = 0; j < K - 1; j++) {
                for (int i = 0; i + (1 << (j + 1)) <= n; ++i) {
                    st[i][j + 1] = oper(st[i][j], st[i + (1 << j)][j]);
                }

            }
        }

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