
    public static void main(String[] args) throws IOException {
        
        /*
        
        idx             =      1   2    3    4   5    6   7   8   9   10   11   12   13   14   15   16
        arr             =      1   0    2    1   1    3   0   4   2    5    2    2    3    1    0    2
        sumPrefixBIT    =          1    3    4   5    8   8  12  14   19   21   23   26   27   27   29

        bit.bit_search(12) = 8 porque es el idx en el sumPrefixBIT
        con la sumatoria que buscamos
        
        */

        long arr[] = { 1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3, 1, 0, 2 };
        BIT ft = new BIT(arr);
        sa.println(ft.bit_search(12)); // 8
        sa.close();
    }

    static class BIT {
        long ft[];
        int N;

        BIT(int n) {
            N = n;
            ft = new long[n + 1];
        }

        BIT(long a[]) {
            ft = new long[a.length + 1];
            N = ft.length;
            for (int i = 0; i < a.length; i++)
                upd(i + 1, a[i]);
        }

        long qry(int i) {
            long ans = 0;
            for (; i > 0; i -= i & -i)
                ans += ft[i];
            return ans;
        }

        long qry(int l, int r) {
            return qry(r) - qry(l - 1);
        }

        void upd(int i, long v) {
            for (; i < ft.length; i += i & -i)
                ft[i] += v;
        }

        // This is equivalent to calculating lower_bound on prefix sums array
        int bit_search(int v) { // O(log(N))
            int sum = 0;
            int pos = 0;
            int LOGN = (int) (log(N) / log(2));
            for (int i = LOGN; i >= 0; i--) {
                if (pos + (1 << i) < N && sum + ft[pos + (1 << i)] < v) {
                    sum += ft[pos + (1 << i)];
                    pos += (1 << i);
                }
            }
            return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
        }

    }
