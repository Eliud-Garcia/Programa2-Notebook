


    static class BIT {
        long ft[];

        BIT(int n) {
            ft = new long[n + 1];
        }

        BIT(long a[]) {
            ft = new long[a.length + 1];
            for (int i = 0; i < a.length; i++) upd(i + 1, a[i]);
        }

        long qry(int i) {
            long ans = 0;
            for (; i > 0; i -= i & -i) ans += ft[i];
            return ans;
        }

        long qry(int l, int r) {
            return qry(r) - qry(l - 1);
        }

        void upd(int i, long v) {
            for (; i < ft.length; i += i & -i) ft[i] += v;
        }
    }

    public static void main(String[] args) throws IOException {
        // idx =       1  2  3  4  5  6  7  8  9
        long arr[] = { 0, 1, 1, 0, 1, 0, 0, 0, 1 };
        
        BIT ft = new BIT(arr);


    }
