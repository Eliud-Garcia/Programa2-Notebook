    
    
    
    
    static long gcd(long a, long b) {
        return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
    }
 
    static long lcm(long a, long b) {
        long lcm = (a / gcd(a, b)) * b;
        return lcm > 0 ? lcm : -lcm;
    }
    