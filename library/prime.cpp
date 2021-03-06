struct Prime {
  long long n = 0;
  vector<bool> ch;
  vector<long long> ary;
  Prime(long long N = 2000000) {
    ch.resize(N + 1);
    ch[0] = ch[1] = 1;
    for (int i = 2; i <= N; ++i)
      if (!ch[i]) {
        ary.push_back(i);
        for (int j = i; 1LL * i * j <= N; ++j) ch[i * j] = 1;
      }
    n = ary.size();
  }
  inline const bool isprime(int n) { return !ch[n]; }
};