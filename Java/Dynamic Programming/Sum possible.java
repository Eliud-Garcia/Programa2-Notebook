
/*
 * return a boolean indicating whether or not 
 * it is possible to create the amount by summing numbers of the list.
 */

    static int MAX = (int) 1e7 + 1;
    static Boolean dp[] = new Boolean[MAX];

    public static boolean sumPossible(int amount, List<Integer> numbers) {
        if (amount == 0)
            return true;

        if (amount < 0) {
            return false;
        }

        if (dp[amount] != null) {
            return dp[amount];
        }

        for (int i : numbers) {
            int subAmount = amount - i;
            if (sumPossible(subAmount, numbers)) {
                dp[amount] = true;
                return true;
            }
        }
        return dp[amount] = false;
    }

    public static void main(String[] args) throws IOException {

        ArrayList<Integer> nums = new ArrayList<>();
        nums.add(3);
        nums.add(2);
        nums.add(1);
        System.out.println(sumPossible(4, nums));

    }