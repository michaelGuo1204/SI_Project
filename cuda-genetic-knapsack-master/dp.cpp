// Jakub 'cubix651' Cislo
#include <iostream>

namespace console {
	template <typename H>
	void read(H& h)
	{
		std::cin >> h;
	}

	template <typename H, typename... T>
	void read(H& h, T&... t)
	{
		std::cin >> h;
		read(t...);
	}

	template <typename H>
	void write(const H& h)
	{
		std::cout << h;
	}

	template <typename H, typename... T>
	void write(const H& h, const T&... t)
	{
		std::cout << h;
		write(t...);
	}

	void writeln()
	{
		std::cout << std::endl;
	}

	template <typename H>
	void writeln(const H& h)
	{
		std::cout << h << std::endl;
	}

	template <typename H, typename... T>
	void writeln(const H& h, const T&... t)
	{
		std::cout << h;
		writeln(t...);
	}

	template <typename H>
	void print(const H& h)
	{
		std::cout << h;
	}

	template <typename H, typename... T>
	void print(const H& h, const T&... t)
	{
		std::cout << h << " ";
		print(t...);
	}

	void println()
	{
		std::cout << std::endl;
	}

	template <typename H>
	void println(const H& h)
	{
		std::cout << h << std::endl;
	}

	template <typename H, typename... T>
	void println(const H& h, const T&... t)
	{
		std::cout << h << " ";
		println(t...);
	}
}

using namespace console;
using namespace std;

const int MAXN = 1e6 + 3, MAXB = 1e6 + 3;
int w[MAXN], v[MAXN], n, B, dp[MAXB][2];

void solve()
{
	read(n, B);
	for(int i = 0; i < n; ++i)
		read(w[i], v[i]);
	for(int i = 0; i <= B; ++i)
		dp[i][0] = 0;
	for(int k = 1; k <= n; ++k)
	{
		for(int i = 0; i < w[k-1]; ++i)
			dp[i][k%2] = dp[i][(k-1)%2];
		for(int i = w[k-1]; i <= B; ++i)
			dp[i][k%2] = max(dp[i][(k-1)%2], dp[i-w[k-1]][(k-1)%2] + v[k-1]);
	}
	println(dp[B][n%2]);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	solve();	
	return 0;
}
