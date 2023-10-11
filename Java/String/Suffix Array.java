 

//primero llamar a init(texto largo)
//luego match(texto corto)
 
    static class suffixArray {

        int K = 26; //alphabet size
        int sa[];
        int occ[][];
        int count[];
        int lcp[];
        int n;

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
            //indices in which w appears in s
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
         * Use Kasai algorithm to build LCP array
         * LCP is an array in which every index
         * tracks how many characters two sorted
         * adjacent suffixes have in common.
         */
        void kasai(String s) {
            s += "$";
            int n = s.length();
            lcp = new int[n - 1];
            int[] inv = new int[n];
            for (int i = 0; i < n; i++)
                inv[sa[i]] = i;
            for (int i = 0, k = 0; i < n; i++) {
                if (inv[i] > 0) {
                    int j = sa[inv[i] - 1];
                    while ((i + k < n) && (j + k < n) && s.charAt(i + k) == s.charAt(j + k))
                        k++;
                    lcp[inv[i] - 1] = k;
                    if (k > 0)
                        k--;
                }
            }
        }
    }
    // int matches[]  = suffix.match(w, k);
    // if (matches.length==1 && matches[0] == -1) {
    //    sa.println(-1);
    //  }