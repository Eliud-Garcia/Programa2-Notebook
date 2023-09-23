

    // para hacer queries en rangos eficientemente


    public static void main(String[] args) throws IOException {


        // arr indexado desde 1 hasta n + 1
        // arr[0] = 0; es ignorado

        int arr[] = { 0, 1, 6, 4, 2, 5, 3 };

        int n = arr.length;
        int prefix[] = new int[n];

        for (int i = 1; i < prefix.length; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }

        //query en rango desde a hasta b
        // a va desde 1 hasta n + 1
        // b va desde 1 hasta n + 1
        //[a, b] inclusive
        
        int a = 2;
        int b = 6;
        long query = prefix[b] - prefix[a - 1];
        sa.println(query);

        sa.close();
    }