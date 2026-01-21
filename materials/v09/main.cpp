#include<iostream>
#include<vector>

using namespace std;

int euclid(int a, int b) {
    int ost;
    while(b != 0) {
        ost = a % b;
        a = b;
        b = ost;
    }
    return a;
}

int euclid_ext(int a, int b, int& x, int& y) {
    int x1 = 1, y1 = 0;
    int x2 = 0, y2 = 1;

    int q, r, tmp;
    while(b != 0) {
        q = a / b;
        r = a - q * b;
        a = b;
        b = r;

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

vector<int> factors(int n) {
    vector<int> factors;

    while(n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    for(int d = 3; d * d <= n; d += 2) {
        while(n % d == 0) {
            factors.push_back(d);
            n /= d;
        }
    }

    if(n > 1)
        factors.push_back(n);

    return factors;
}

vector<int> eratosten(int n) {
    vector<int> eratosten(n + 1);
 
    for (int i = 1; i <= n; i++)
        eratosten[i] = i;

    for (int d = 2; d * d <= n; d++)
        if (eratosten[d] == d)
            for (int i = d * d; i <= n; i += d)
                if (eratosten[i] == i)
                    eratosten[i] = d;

    return eratosten;
}

int phi(int n) {
    int phi = n;

    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) { 
            while (n % p == 0) 
                n /= p; 
            phi -= phi / p; 
        } 
    } 

    if (n > 1) 
        phi -= phi / n; 

    return phi; 
}

vector<int> phi_eratosten(int n) {
    vector<int> phi(n + 1);

    for (int i = 1; i <= n; i++) 
        phi[i] = i;

    for (int p = 2; p <= n; p++)
        if (phi[p] == p)
            for (int i = p; i <= n; i += p)
                phi[i] -= phi[i] / p; 

    return phi;
}

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
    if (n == 0)
       return 1;
    if (n % 2 == 0)
        return mod_pow((a * a) % m, n / 2, m);
    else
        return (a * mod_pow(a, n-1, m)) % m;
}

unsigned mod_inv(unsigned a, unsigned m) {
    int x, y, d;
    d = euclid_ext(a, m, x, y);

    if(d != 1) {
        cerr << "Modularni inverz ne postoji" << endl;
        return 0;
    } else {
        return (x % m + m) % m;
    }
}
int main() {

}