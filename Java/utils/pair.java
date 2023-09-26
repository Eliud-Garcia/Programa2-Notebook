    
    
    
    
    
    
    static class pair<F extends Comparable<F>, S extends Comparable<S>> implements Comparable<pair<F, S>> {
        F first;
        S second;
        
        pair(F f, S s) {
            first = f;
            second = s;
        }

        @Override
        public int compareTo(pair<F, S> other) {
            if (first == other.first) {
                return second.compareTo(other.second);
            } else {
                return first.compareTo(other.first);
            }
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            pair<?, ?> p = (pair<?, ?>) o;
            return Objects.equals(first, p.first) && Objects.equals(second, p.second);
        }

        @Override
        public int hashCode() {
            int h;
            return (first == null || second == null) ? 0 : (h = first.hashCode() + second.hashCode()) ^ (h >>> 16);
        }

        @Override
        public String toString() {
            return "(" + first + ", " + second + ")";
        }
    }










    