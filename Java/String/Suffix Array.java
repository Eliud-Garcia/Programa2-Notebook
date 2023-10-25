
    // primero llamar a init(texto largo)
    // luego match(texto corto)

    static class suffixArray {

        int K = 26; // alphabet size
        int sa[];
        int occ[][];
        int count[];
        int lcp[];
        int n;


        // build suffix array
        void init(String s) {
            s += "$";
            n = s.length();
            sa = computeSuffixArray(s);
            occ = new int[n + 1][K];
            count = new int[K + 1];
            for (int i = 0; i < n; i++) {
                int t = s.charAt(sa[i] == 0 ? n - 1 : sa[i] - 1) - 'a';
                if (t >= 0) {
                    occ[i][t]++;
                    count[t + 1]++;
                }
                System.arraycopy(occ[i], 0, occ[i + 1], 0, K);
            }
            for (int i = 1; i < count.length; i++) {
                count[i] += count[i - 1];
            }
        }

        // Returns indices (start, end) -> of each occurrence of w in s
        // If a minimum number of occurrences is not needed, set minOcc = 0

        int[] match(String w, int minOcc) {
            int begin = 0, end = n - 1;
            // List<pair<Integer, Integer>> matches = new ArrayList<>();

            for (int j = w.length() - 1; end - begin + 1 >= minOcc && j >= 0; j--) {
                char c = w.charAt(j);
                int let = c - 'a';
                int nbegin = count[let] + (begin == 0 ? 0 : occ[begin - 1][let]) + 1;
                int nend = count[let] + occ[end][let];
                begin = nbegin;
                end = nend;
            }
            if (end - begin + 1 < minOcc) {
                return new int[] { -1 };
            }

            int t[] = new int[end - begin + 1];
            // indices in which w appears in s
            for (int j = begin; j <= end; j++) {
                // int start = SA[j];
                // int end = SA[j] + w.length() - 1;
                // matches.add(new pair<>(star, end));
                t[j - begin] = sa[j];
            }

            Arrays.sort(t);
            return t;

        }

        int[] computeSuffixArray(String str) {
            int n = str.length();

            int[] sa = IntStream.range(0, n).mapToObj(i -> n - 1 - i)
                    .sorted((a, b) -> Character.compare(str.charAt(a), str.charAt(b)))
                    .mapToInt(Integer::intValue)
                    .toArray();

            int[] classes = new int[n];
            for (int j = 0; j < classes.length; j++) {
                classes[j] = str.charAt(j);
            }
            for (int len = 1; len < n; len *= 2) {
                int[] c = classes.clone();

                for (int i = 0; i < n; i++) {
                    classes[sa[i]] = i > 0 && c[sa[i - 1]] == c[sa[i]] && sa[i - 1] + len < n
                            && c[sa[i - 1] + len / 2] == c[sa[i] + len / 2] ? classes[sa[i - 1]] : i;
                }

                int[] cnt = new int[n];
                for (int i = 0; i < cnt.length; i++) {
                    cnt[i] = i;
                }

                int[] s = sa.clone();
                for (int i = 0; i < n; i++) {
                    int s1 = s[i] - len;
                    if (s1 >= 0)
                        sa[cnt[classes[s1]]++] = s1;
                }
            }
            return sa;
        }

        /*
         * Longest Common Preffix
         * Use Kasai algorithm to build LCP array
         * LCP is an array in which every index
         * tracks how many characters two sorted
         * adjacent suffixes have in common.
         */
        void kasai(String s) {
            s += "$";
            int n = s.length();
            lcp = new int[n];
            int[] inv = new int[n];
            for (int i = 0; i < n; i++)
                inv[sa[i]] = i;
            for (int i = 0, k = 0; i < n; i++) {
                if (inv[i] == n - 1) {
                    k = 0;
                    continue;
                }
                int j = sa[inv[i] + 1];
                while ((i + k < n) && (j + k < n) && s.charAt(i + k) == s.charAt(j + k))
                    k++;
                lcp[inv[i]] = k;
                if (k > 0)
                    k--;
            }
        }

        /*
         * n = s.length();
         * unique subStrings of s = (n*(n + 1)/2) - (Σ lcp[i]);
         */
        long uniqueSubStrings(String s) {
            init(s);
            kasai(s);
            int n = s.length();
            long ans = n - sa[0];
            for (int i = 1; i < lcp.length; i++) {
                ans += (n - sa[i]) - lcp[i - 1];
            }
            return ans;
        }

        /*
         * To find the LCS of two Strings
         * Let's combine two strings into one through the symbol "sharp" s1#s2
         * identify the suffixes which start in positions wich are inside the s1
         * identify the suffixes which start in positions wich are inside the s2
         * then let's build SA and LCP of combined string
         * 
         * then we need to find two suffixes,
         * one should be inside s1 and other should be inside s2
         * 
         * such that the length of their common prefix is a big as possible
         * 
         */
        String longestCommonSubString(String s1, String s2) {
            StringBuilder combined = new StringBuilder();

            int leftS1 = 0;
            combined.append(s1).append("#");
            int rightS1 = combined.length() - 1;

            int leftS2 = combined.length();
            combined.append(s2);
            int rightS2 = combined.length();

            init(combined + "");
            kasai(combined + "");
            int MAX = 0;
            int start = -1;

            for (int i = 0; i < sa.length - 1; i++) {
                // if sa[i] inside s1 && sa[i + 1] inside s2
                if (sa[i] >= leftS1 && sa[i] < rightS1 && sa[i + 1] >= leftS2 && sa[i + 1] < rightS2) {
                    if (lcp[i] > MAX) {
                        MAX = lcp[i];
                        start = i;
                    }
                    // else sa[i] inside s2 && sa[i + 1] inside s1
                } else if (sa[i + 1] >= leftS1 && sa[i + 1] < rightS1 && sa[i] >= leftS2 && sa[i] < rightS2) {
                    if (lcp[i] > MAX) {
                        MAX = lcp[i];
                        start = i;
                    }
                }
            }
            if (start == -1) {
                return "";
            } else {
                String lcs = combined.substring(sa[start], sa[start] + MAX);
                return lcs;
            }

        }
    }