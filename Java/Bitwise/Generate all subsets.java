
//  O(n · 2^n )
static List<List<Integer>> generateSubsets(int[] nums) {
    List<List<Integer>> subsets = new ArrayList<>();
    int n = nums.length;
    // Total number of subsets = 2^n
    // Generate all subsets
    for (int i = 0; i < 1 << n; i++) {
        List<Integer> subset = new ArrayList<>();
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                subset.add(nums[j]);
            }
        }
        subsets.add(subset);
    }
    return subsets;
}

static void solve() throws IOException {
    int arr[] = { 1, 2, 3 };
    List<List<Integer>> x = generateSubsets(arr);
    for (List<Integer> i : x) {
        sa.println(i);
    }
}