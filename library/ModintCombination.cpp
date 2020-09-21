template <int mod = (int)(1e9 + 7)>
struct ModInt {
  int x;
  ModInt() : x(0) {}
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
  ModInt &operator+=(const ModInt &p) {
    if ((x += p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator-=(const ModInt &p) {
    if ((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
  ModInt &operator*=(const ModInt &p) {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
  ModInt operator-() const { return ModInt(-x); }
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
  bool operator==(const ModInt &p) const { return x == p.x; }
  bool operator!=(const ModInt &p) const { return x != p.x; }
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
  ModInt pow(int64_t n) const {
    ModInt res(1), mul(x);
    while (n) {
      if (n & 1) res *= mul;
      mul *= mul;
      n >>= 1;
    }
    return res;
  }
  friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt<mod>(t);
    return (is);
  }
  static int get_mod() { return mod; }
};

struct Combination {
  vector<ModInt<>> _fact, _rfact, _inv;
  Combination(long long nsize = 5000000)
      : _fact(nsize + 1), _rfact(nsize + 1), _inv(nsize + 1) {
    _fact[0] = _rfact[nsize] = _inv[0] = 1;
    for (int i = 1; i <= nsize; i++) _fact[i] = _fact[i - 1] * i;
    _rfact[nsize] /= _fact[nsize];
    for (int i = nsize - 1; i >= 0; i--) _rfact[i] = _rfact[i + 1] * (i + 1);
    for (int i = 1; i <= nsize; i++) _inv[i] = _rfact[i] * _fact[i - 1];
  }
  inline ModInt<> fact(int k) const { return _fact[k]; }

  inline ModInt<> rfact(int k) const { return _rfact[k]; }

  inline ModInt<> inv(int k) const { return _inv[k]; }

  ModInt<> P(int n, int r) const {
    if (r < 0 || n < r) return 0;
    return fact(n) * rfact(n - r);
  }

  ModInt<> C(int p, int q) const {
    if (q < 0 || p < q) return 0;
    return fact(p) * rfact(q) * rfact(p - q);
  }

  ModInt<> largeC(long long p, long long q) const {
    if (q < 0 || p < q) return 0;
    ModInt<> res = rfact(q);
    for (int i = 0; i < q; ++i) res *= p - i;
    return res;
  }

  // n types,choose r
  ModInt<> H(int n, int r) const {
    if (n < 0 || r < 0) return (0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};
