static class MultiSet<T> {
    HashMap<T, Integer> fre;
    TreeSet<T> set;
    int size;
     MultiSet() {
        set = new TreeSet<>();
        fre = new HashMap<>();
        size = 0;
    }
     void add(T elem) {
        if (fre.get(elem) == null || fre.get(elem) == 0) {
            fre.put(elem, 0);
            set.add(elem);
        }
        fre.put(elem, fre.get(elem) + 1);
        size++;
    }
     void remove(T elem) {
        fre.put(elem, fre.get(elem) - 1);
        if (fre.get(elem) == 0) {
            set.remove(elem);
        }
        size--;
    }
     boolean contains(T elem) {
        return set.contains(elem);
    }
}