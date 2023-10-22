    
    
    //Mas rapido que el BufferedReader
    // ##############################################################
    // ##############################################################

    static int scan() throws IOException {
        if (_index >= _total) {
            _index = 0;
            _total = in.read(buf);
            if (_total <= 0) {
                return -1;
            }
        }
        return buf[_index++];
    }

    static String next() throws IOException {
        int c;
        for (c = scan(); c <= 32; c = scan())
            ;
        StringBuilder sb = new StringBuilder();
        for (; c > 32; c = scan()) {
            sb.append((char) c);
        }
        return sb.toString();
    }

    static int nextInt() throws IOException {
        int c, val = 0;
        for (c = scan(); c <= 32; c = scan())
            ;
        boolean neg = c == '-';
        if (c == '-' || c == '+') {
            c = scan();
        }
        for (; c >= '0' && c <= '9'; c = scan()) {
            val = (val << 3) + (val << 1) + (c & 15);
        }
        return neg ? -val : val;
    }

    static long nextLong() throws IOException {
        int c;
        long val = 0;
        for (c = scan(); c <= 32; c = scan())
            ;
        boolean neg = c == '-';
        if (c == '-' || c == '+') {
            c = scan();
        }
        for (; c >= '0' && c <= '9'; c = scan()) {
            val = (val << 3) + (val << 1) + (c & 15);
        }
        return neg ? -val : val;
    }

    static double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    // para input/output con files
    // in = new FileInputStream("input.txt");
    // sa = new BufferedWriter(new BufferedWriter(new FileWriter("output.txt")));

    static PrintWriter sa = new PrintWriter(new OutputStreamWriter(System.out));
    static byte[] buf = new byte[2048];
    static InputStream in = System.in;
    static int _index, _total;