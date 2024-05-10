
//counting tilings
const int MOD = 1e9 + 7;
int dp[1001][1<<10];
int n, m;

void fill_colum(int column, int idx, int cur_mask, int next_mask) {
   if (idx == n) { // he llenado toda la columna
      dp[column + 1][next_mask] = (dp[column + 1][next_mask] + dp[column][cur_mask]) % MOD;
      return;
   }
   if ((cur_mask) & (1 << idx)) { // si el tile actual esta full
      fill_colum(column, idx + 1, cur_mask, next_mask);
   } else {
      // horizontal
      fill_colum(column, idx + 1, cur_mask, next_mask | (1 << idx));
      // vertical
      if (idx + 1 < n && (!(cur_mask & (1 << (idx + 1))))) {
         fill_colum(column, idx + 2, cur_mask, next_mask);
      }
   }
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   cin >> n >> m;
   dp[0][0] = 1;
   forn(column, m) { // todas las coumnas
      forn(mask, (1 << n)) { // todas las posibles mask
         if (dp[column][mask] > 0) {
            // hay forma de llenar la i-esima columna
            fill_colum(column, 0, mask, 0);
         }
      }
   }
   cout << dp[m][0] << ln;

   return 0;
}
