
static void ocurrencia_Multiplos(int nums[]) {
    int n = nums.length;
    int ocurrences[] = new int[n + 1];
    HashMap<Integer, Integer> mp = new HashMap<>();
    for (int i = 0; i < n; i++) {
        if (nums[i] <= n) {
            mp.put(nums[i], mp.getOrDefault(nums[i], 0) + 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (mp.getOrDefault(i, 0) == 0) {
            continue;
        }
        for (int j = i; j <= n; j += i) {
            ocurrences[j] += mp.getOrDefault(i, 0);
        }
    }
    /* multiplo mas repetido y menos repetido */
    long MAX = 0;
    long MIN = Long.MAX_VALUE;
    for (int i : ocurrences) {
        MAX = max(MAX, i);
        MIN = min(MIN, i);
    }
    sa.println(MAX);
}