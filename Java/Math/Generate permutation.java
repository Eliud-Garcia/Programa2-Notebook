// O(n!) 
static void generatePermutation(ArrayList<Integer> arr, int n) {
    if (n == 1) {
        printArr(arr);
    } else {
        for (int i = 0; i < n; i++) {
            generatePermutation(arr, n - 1);
            if (n % 2 == 0) {
                swap(arr, i, n - 1);
            } else {
                swap(arr, 0, n - 1);
            }
        }
    }
}
static void swap(ArrayList<Integer> arr, int i, int j) {
    int temp = arr.get(i);
    arr.set(i, arr.get(j));
    arr.set(j, temp);
}
static void printArr(ArrayList<Integer> arr) {
    for (int num : arr) {
        sa.print(num + " ");
    }
    sa.println();
}