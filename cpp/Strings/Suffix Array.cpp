typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;

struct SuffixArray {
  int K = 256; // alphabet size
  int n;
  vi sa, lcp, c, cnt;

  vi build(string& str) {
    string s = str;
    s += "$";
    n = sz(s);
    sa = vi(n);
    c = vi(2 * n);
    cnt = vi((max(n, K)));
    forab (k, 0, n) {
      cnt[(int)(s[k])]++;
    }
    forab (k, 1, K) {
      cnt[k] += cnt[k - 1];
    }
    forab (k, 0, n) {
      sa[--cnt[(int)(s[k])]] = k;
    }
    c[sa[0]] = 0;
    int classes = 1;
    forab (k, 1, n) {
      if (s[sa[k]] != s[sa[k - 1]]) {
        classes++;
      }
      c[sa[k]] = classes - 1;
    }
    vi pn(n);
    vi cn(2 * n);

    for (int h = 0; (1 << h) < n; h++) {
      forab (k, 0, n) {
        pn[k] = sa[k] - (1 << h);
        if (pn[k] < 0) {
          pn[k] += n;
        }
      }
      fill(all(cnt), 0);
      forab (k, 0, n) {
        cnt[c[pn[k]]]++;
      }
      forab (k, 1, classes) {
        cnt[k] += cnt[k - 1];
      }
      for (int k = n - 1; k >= 0; k--) {
        sa[--cnt[c[pn[k]]]] = pn[k];
      }
      cn[sa[0]] = 0;
      classes = 1;
      forab (k, 1, n) {
        int cur1 = c[sa[k]];
        int cur2 = c[sa[k] + (1 << h)];
        int prev1 = c[sa[k - 1]];
        int prev2 = c[sa[k - 1] + (1 << h)];
        if (cur1 != prev1 || cur2 != prev2) {
          classes++;
        }
        cn[sa[k]] = classes - 1;
      }
      swap(c, cn);// swap c and cn
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
  void kasai(string& str) {
    string s = str;
    s += "$";
    int n = sz(s);
    lcp = vi(n);
    vi inv(n);
    forab (i, 0, n)
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
  ll uniqueSubStrings(string& str) {
    string s = str;
    build(s);
    kasai(s);
    int n = s.length();
    ll ans = n - sa[0];
    forab (i, 1, lcp.size()) {
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
  	*/
  //longest common substring
  string lcs(string& s1, string& s2) {
    string combined = s1;

    int leftS1 = 0;
    combined += ("#");
    int rightS1 = combined.length() - 1;

    int leftS2 = combined.length();
    combined += (s2);
    int rightS2 = combined.length();

    build(combined);
    kasai(combined);
    int MAX = 0;
    int start = -1;

    forab (i, 0, sa.size() - 1) {
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

  int match(string& s, string& w) {
    int n = sz(s);
    int l = 1;
    int r = n;
    int lower = -1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (compare(s, sa[mid], w) >= 0) {
        lower = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    l = 1;
    r = n;
    int upper = -1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (compare(s, sa[mid], w) <= 0) {
        upper = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    upper++;
    if (lower == -1 || compare(s, sa[lower], w) != 0) {
      return -1; // no aparece
    } else {
      //cantidad de veces que aparece
      return upper - lower + 1;
    }
  }

  int compare(string& s, int x, string& w) {
    int n = sz(s);
    int qn = sz(w);

    int i = 0;
    while (i + x < n && i < qn && s[i + x] == w[i])
      i++;
    if (i >= qn) {
      return 0;
    } else if (i + x >= n) {
      return -1;
    }
    return (int)s[i + x] - (int)w[i];
  }
};

int main() {
  string s, t;
  cin >> s >> t;
  SuffixArray sf;
  sf.lcs(s, t);
  return 0;
}
