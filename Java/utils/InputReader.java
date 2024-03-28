    
// Muy rapido para leer numeros
static int scan()  {
    if (idx_ >= total_) {
        idx_ = 0;
        try {total_ = in.read(buf);}
        catch (IOException e) {e.printStackTrace();}
        if (total_ <= 0) return -1;
    }
    return buf[idx_++];
}

static String next() {
    int c;
    for (c = scan(); c <= 32; c = scan());
    sb_ = new StringBuilder();
    for (; c > 32; c = scan())
        sb_.append((char) c);
    return sb_.toString();
}

static int nextInt() {
    int c, val = 0;
    for (c = scan(); c <= 32; c = scan());
    boolean neg = c == '-';
    if (c == '-' || c == '+') c = scan();
    for (; c >= '0' && c <= '9'; c = scan()) 
        val = (val << 3) + (val << 1) + (c & 15);
    return neg ? -val : val;
}

static long nextLong(){
    int c;
    long val = 0;
    for (c = scan(); c <= 32; c = scan());
    boolean neg = c == '-';
    if (c == '-' || c == '+') c = scan();
    for (; c >= '0' && c <= '9'; c = scan())
        val = (val << 3) + (val << 1) + (c & 15);
    return neg ? -val : val;
}

static double nextDouble() {
    return Double.parseDouble(next());
}

static PrintWriter sa = new PrintWriter(new OutputStreamWriter(System.out));
static StringBuilder sb_;
static byte[] buf = new byte[2048];
static InputStream in = System.in;
static int idx_, total_;