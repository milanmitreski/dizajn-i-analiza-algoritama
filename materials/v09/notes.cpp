#include<iostream>
#include<vector>

using namespace std;

// vraca NZD(a,b) (najveci zajednicki delilac)
// NZD(a, b) = NZD(b, a % b)
// NZD(a, 0) = a
int euclid(int a, int b) {
    int tmp;
    while(b != 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// vraca NZD(a,b)
// pri cemu x i y nakon izvrsavanja funkcije imaju takve vrednosti da vazi: a*x + b*y = NZD(a,b)
int euclid_ext(int a, int b, int& x, int& y) {
    int x1 = 1, y1 = 0; // a = 1 * a + 0 * b
    int x2 = 0, y2 = 1; // b = 0 * a + 1 * b

    int q, r, tmp;
    while(b != 0) {
        q = a / b;
        r = a - q * b; // a % b
        a = b;
        b = r;

        // a = b * q + r
        // (xr, yr) = (x1 - q * x2, y1 - q * y2)
        tmp = x1 - q * x2;
        x1 = x2;
        x2 = tmp;

        tmp = y1 - q * y2;
        y1 = y2;
        y2 = tmp;
    }

    x = x1, y = y1;
    return a;
}

// vraca niz svih prostih cinilaca broja n
// ukoliko je n = 3 * 3 * 2 * 2 * 2 potrebno je vratiti {2, 2, 2, 3, 3}
vector<int> prime_factors(int n) {
    vector<int> prime_factors;

    while(n % 2 == 0) {
        prime_factors.push_back(2);
        n /= 2;
    }

    for(int d = 3; d * d <= n; d += 2) {
        while(n % d == 0) {
            prime_factors.push_back(d);
            n /= d;
        }
    }

    if(n > 1)
        prime_factors.push_back(n);
    
    return prime_factors;
}

vector<int> eratosten(int n) {
    vector<int> eratosten(n + 1);

    for(int i = 1; i <= n; i++) {
        eratosten[i] = i;
    }

    for(int d = 2; d * d <= n; d++)
        if(eratosten[d] == d)
            for(int i = d * d; i <= n; i += d) 
                if(eratosten[i] == i)
                    eratosten[i] = d;

    return eratosten;
}

int phi(int n) {
    int phi = n;

    for(int p = 2; p * p <= n; p++) {
        if(n % p == 0) {
            while(n % p == 0)
                n /= p;
            phi -= phi / p; // phi = phi * (1 - 1/p) = phi - phi / p
        }
    }

    if(n > 1)
        phi -= phi / n;
    
    return phi;
}

vector<int> phi_eratosten(int n) {
    vector<int> phi(n + 1);

    for(int i = 1; i <= n; i++) {
        phi[i] = i;
    }

    for(int p = 2; p <= n; p++)
        if(phi[p] == p)
            for(int i = p; i <= n; i += p)
                phi[i] -= phi[i] / p;

    return phi;
}

// Modularna aritmetika (mod m) 

unsigned mod_plus(unsigned a, unsigned b, unsigned m) {
    return (a % m + b % m) % m;
}

unsigned mod_minus(unsigned a, unsigned b, unsigned m) {
    return (a % m - b % m + m) % m;
}

unsigned mod_mult(unsigned a, unsigned b, unsigned m) {
    return ((a % m) * (b % m)) % m;
}

unsigned mod_pow(unsigned a, unsigned n, unsigned m) {
    if(n == 0)
        return 1;
    else if(n % 2 == 0)
        return mod_pow(mod_mult(a, a, m), n / 2, m);
    else
        return mod_mult(a, mod_pow(a, n-1, m), m);
}

// vraca broj x takav da a * x = 1 mod m
// a * x + m * y = 1
unsigned mod_inv(unsigned a, unsigned m) {
    int x, y, d;
    d = euclid_ext(a, m, x, y);
    
    if(d != 1) {
        cerr << "Modularni inverz ne postoji, jer je NZD(a,m) > 1" << endl;
        return 0;
    } else {
        return (x % m + m) % m;
    }
}

int zbir_prostih_prost(int n) {
    vector<int> prime_factors = eratosten(n);
    int counter = 0;
    int p = 2, q;

    for(q = 3; p + q <= n; q++)
        if(prime_factors[q] == q && prime_factors[p+q] == p+q)
            counter++;
    
    return counter;
}

long long dopuna_do_punog_kvadrata(long long n) {
    long long m = 1;
    long long p;

    for(p = 2; p * p <= n; p++) {
        int k = 0;

        while(n % p == 0) {
            n /= p;
            k++;
        }

        if(k % 2 != 0)
            m *= p;
    }

    if(n > 1)
        m *= n;

    return m;
}

int ucenici_na_istim_sedistima(int m, int n) {
    return euclid(m-1, n-1) + 1;
}

int main() {
    int m, n;
    cin >> m >> n;
    cout << ucenici_na_istim_sedistima(m, n) << endl;
    return 0;
}