

//se puede usar en cualquier estructura

static class pair<F extends Comparable<F>, S extends Comparable<S>> implements Comparable<pair<F, S>> {
        F first;
        S second;

        public pair(F first, S second) {
            this.first = first;
            this.second = second;
        }

        /*
         * • If object x is less than object y, return a negative number
         * • If object x is greater than object y, return a positive number
         * • If object x is equal to object y, return 0
         */
        @Override
        public int compareTo(pair<F, S> other) {
            // decresing order = return -first.compareTo(other.first);
            if (first == other.first) {
                return second.compareTo(other.second);
            } else {
                return first.compareTo(other.first);
            }
        }

        @Override
        public int hashCode() {
            return 31 * first.hashCode() + second.hashCode();
        }

        @Override
        public String toString() {
            return "(" + first + ", " + second + ")";
        }
    }