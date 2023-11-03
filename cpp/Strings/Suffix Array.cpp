#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define ll long long
#define forn(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>

// primero llamar a init(texto largo)
// luego match(texto corto)

struct suffixArray {
    int K = 26; // alphabet size
    vector<vi> occ;
    vi sa;
    vi count;
    vi lcp;
    int n;

    // Build suffix array
    void init(string& s)
    {
        s += "$";
        n = s.length();
        sa = computeSuffixArray(s);
        occ = vector<vi>(n + 1, vi(K, 0));
        count = vi(K + 1, 0);

        forn(i, n)
        {
            int t = s[sa[i] == 0 ? n - 1 : sa[i] - 1] - 'a';
            if (t >= 0) {
                occ[i][t]++;
                count[t + 1]++;
            }
            copy(occ[i].begin(), occ[i].end(), occ[i + 1].begin());
        }

        for (int i = 1; i < count.size(); i++) {
            count[i] += count[i - 1];
        }
    }

    // Returns indices (start, end) of each occurrence of w in s
    // If a minimum number of occurrences is not needed, set minOcc = 0
    vi match(const string& w, int minOcc)
    {
        int begin = 0, end = n - 1;

        for (int j = w.length() - 1; end - begin + 1 >= minOcc && j >= 0; j--) {
            char c = w[j];
            int let = c - 'a';
            int nbegin = count[let] + (begin == 0 ? 0 : occ[begin - 1][let]) + 1;
            int nend = count[let] + occ[end][let];
            begin = nbegin;
            end = nend;
        }

        if (end - begin + 1 < minOcc) {
            // cout << "No" << ln;
            return { -1 };
        }

        vi matches(end - begin + 1);

        for (int j = begin; j <= end; j++) {
            // int start = SA[j];
            // int end = SA[j] + w.length() - 1;
            matches[j - begin] = sa[j];
        }
        sort(all(matches));
        // cout << "Yes" << ln;
        return matches;
    }

    vi computeSuffixArray(const string& str)
    {
        int n = str.length();
        vi sa(n);

        forn(i, n)
        {
            sa[i] = n - 1 - i;
        }

        sort(all(sa), [&str](int a, int b) {
            return str[a] < str[b];
        });

        vi classes(n);

        forn(j, n)
        {
            classes[j] = str[j];
        }

        for (int len = 1; len < n; len *= 2) {
            vi c(classes);

            forn(i, n)
            {
                classes[sa[i]] = i > 0 && c[sa[i - 1]] == c[sa[i]] && sa[i - 1] + len < n
                        && c[sa[i - 1] + len / 2] == c[sa[i] + len / 2]
                    ? classes[sa[i - 1]]
                    : i;
            }

            vi cnt(n);
            forn(i, n)
            {
                cnt[i] = i;
            }

            vi s(sa);

            forn(i, n)
            {
                int s1 = s[i] - len;
                if (s1 >= 0) {
                    sa[cnt[classes[s1]]++] = s1;
                }
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
    void kasai(string& s)
    {
        s += "$";
        int n = s.length();
        lcp.resize(n);
        vi inv(n);
        forn(i, n)
            inv[sa[i]]
            = i;
        for (int i = 0, k = 0; i < n; i++) {
            if (inv[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[inv[i] + 1];
            while ((i + k < n) && (j + k < n) && s[i + k] == s[j + k])
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
    ll uniqueSubStrings(string& s)
    {
        init(s);
        kasai(s);
        int n = s.length();
        long ans = n - sa[0];
        for (int i = 1; i < lcp.size(); i++) {
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
    string longestCommonSubString(string& s1, string& s2)
    {
        string combined;

        int leftS1 = 0;
        combined += s1;
        combined += "#";
        int rightS1 = combined.size() - 1;

        int leftS2 = combined.size();
        combined += s2;
        int rightS2 = combined.size();

        init(combined);
        kasai(combined);
        int MAX = 0;
        int start = -1;

        forn(i, sa.size() - 1)
        {
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
            string lcs = combined.substr(sa[start], sa[start] + MAX);
            return lcs;
        }
    }
};
