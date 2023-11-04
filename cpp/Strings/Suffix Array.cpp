
#include <bits/stdc++.h>
using namespace std;

#define ln '\n'
#define all(x) x.begin(), x.end()
#define ll long long
#define vi vector<int>
#define forn(i, a, b) for (int i = a; i < b; i++)
#define sz(x) ((int) x.size())

struct SuffixArray {
    int K = 256; // alphabet size
    int n;
    vi sa, lcp, c, cnt;

    vi make_suffix_array(string& str)
    {
        string s = str;
        s += "$";
        n = s.length();
        sa = vi(n);
        c = vi(2 * n);
        cnt = vi((max(n, K)));

        forn (k, 0, n) {
            cnt[(int)(s[k])]++;
        }
        forn (k, 1, K) {
            cnt[k] += cnt[k - 1];
        }
        forn (k, 0, n) {
            sa[--cnt[(int)(s[k])]] = k;
        }
        c[sa[0]] = 0;
        int classes = 1;
        forn (k, 1, n) {
            if (s[sa[k]] != s[sa[k - 1]]) {
                classes++;
            }
            c[sa[k]] = classes - 1;
        }
        vi pn(n);
        vi cn(2 * n);

        for (int h = 0; (1 << h) < n; h++) {
            forn (k, 0, n) {
                pn[k] = sa[k] - (1 << h);
                if (pn[k] < 0) {
                    pn[k] += n;
                }
            }

            fill(all(cnt), 0);

            forn (k, 0, n) {
                cnt[c[pn[k]]]++;
            }
            forn (k, 1, classes) {
                cnt[k] += cnt[k - 1];
            }
            for (int k = n - 1; k >= 0; k--) {
                sa[--cnt[c[pn[k]]]] = pn[k];
            }
            cn[sa[0]] = 0;
            classes = 1;
            forn (k, 1, n) {
                int cur1 = c[sa[k]];
                int cur2 = c[sa[k] + (1 << h)];
                int prev1 = c[sa[k - 1]];
                int prev2 = c[sa[k - 1] + (1 << h)];

                if (cur1 != prev1 || cur2 != prev2) {
                    classes++;
                }
                cn[sa[k]] = classes - 1;
            }

            // swap c and cn
            swap(c, cn);
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
    void kasai(string& str)
    {
        string s = str;
        s += "$";
        int n = s.length();
        lcp = vi(n);
        vi inv(n);
        forn (i, 0, n)
            inv[sa[i]] = i;
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
    ll uniqueSubStrings(string& str)
    {
        string s = str;
        make_suffix_array(s);
        kasai(s);
        int n = s.length();
        ll ans = n - sa[0];
        forn (i, 1, lcp.size()) {
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
        string combined = s1;

        int leftS1 = 0;
        combined += ("#");
        int rightS1 = combined.length() - 1;

        int leftS2 = combined.length();
        combined += (s2);
        int rightS2 = combined.length();

        make_suffix_array(combined);
        kasai(combined);
        int MAX = 0;
        int start = -1;

        forn (i, 0, sa.size() - 1) {
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
            for (int i = sa[start]; i < sa[start] + MAX; i++) {
                cout << combined[i];
            }
            cout << ln;
            // string lcs = combined.substr(sa[start], sa[start] + MAX);
            return "";
        }
    }

    int match(string& s, string& w)
    {
        int n = s.length();
        int l = 1;
        int r = n;
        int ansl = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (compare(s, sa[mid], w) >= 0) {
                ansl = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        l = 1;
        r = n;
        int ansr = -1;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (compare(s, sa[mid], w) <= 0) {
                ansr = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (ansl == -1 || compare(s, sa[ansl], w) != 0) {
            return -1;
        } else {
            return ansr - ansl + 1;
        }
    }

    int compare(string& s, int x, string& qs)
    {
        int n = s.length();
        int qn = qs.length();

        int i = 0;
        while (i + x < n && i < qn && s[i + x] == qs[i])
            i++;

        if (i >= qn) {
            return 0;
        } else if (i + x >= n) {
            return -1;
        }

        return (int)s[i + x] - (int)qs[i];
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s, t;
    cin >> s >> t;
    SuffixArray sf;
    sf.longestCommonSubString(s, t);

    return 0;
}