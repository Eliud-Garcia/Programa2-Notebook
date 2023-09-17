    




    Comparator<int[]> byDistance = new Comparator<int[]>() {
        @Override
        public int compare(int[] a, int[] b) {
            return Integer.compare(a[0], b[0]);
        }
    };

    
    Collections.sort(arr, byDistance);

    //-----------------------------------------------------------------------------------------------------

    // otro ejemplo de uso
        
        Arrays.sort(m, new Comparator<Man>() {
            @Override
            public int compare(Man x, Man y) {
                return Integer.signum(x.a - y.a);
            } 
        }); 

    //-----------------------------------------------------------------------------------------------------


        Integer arr[] = new Integer[10];
        Arrays.sort(arr, (a, b) -> Integer.compare(a, b));


        List<Integer> arr = new ArrayList<>();
        Collections.sort(arr, (a, b) -> Integer.compare(a, b));


    //-----------------------------------------------------------------------------------------------------

    //en estructuras

    PriorityQueue<int[]> edge = new PriorityQueue<>((a, b)->Integer.compare(a[2], b[2]));



