




	const int MOD = 60;

	suma(a, b) ((a % MOD) + (b % MOD)) % MOD
	resta(a, b) ((a % MOD) - (b % MOD)) % MOD
	mult(a, b) ((a % MOD) * (b % MOD)) % MOD
	div(a, b) ((a % MOD) * (modularInverse(b, MOD))) % MOD
