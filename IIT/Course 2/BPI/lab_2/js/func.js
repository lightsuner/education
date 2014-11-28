function euclidNod(m, n) {
    while (m && n) {
        if (m > n) {
            m = Math.floor(m%n);
        } else {
            n = Math.floor(n%m);
        }
    }
    return m + n;
}

function binaryNod(m, n) {
    if (!m || !n) {
        return m+n;
    }

    if (m == n) {
        return m;
    }

    if (m == 1 || n == 1) {
        return 1;
    }

    var multiplier = 1;
    while (m%2==0 && n%2==0) {
        multiplier <<= 1;
        m >>= 1;
        n >>= 1;
    }

    while (n > 0)
    {
        if (m%2==0 && m>0) {
            m >>= 1;
        }
        else if (n%2==0 && n>0) {
            n >>= 1;
        }
        else
        {
            var t = Math.abs(Math.floor((m-n)/2));
            if (m > n) {
                m = t;
            } else {
                n = t;
            }
        }
    }
    return multiplier*m;
}

function eulerFunction(n) {
    var output = n;

    for (var i=2; i*i<=n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            output -= output / i;
        }
    }

    if (n > 1) {
        output -= output / n;
    }

    return output;
}

function func4(a, b, n) {
    if (n < 0) {
        return "Число n меньше 0";
    }
    if (a !== Math.floor(a)) {
        return "Число a не является челым!"
    }
    if (binaryNod(a, n) !== 1) {
        return "Числа "+a+" и "+n+" не взаимо просты!"
    }
    if (eulerFunction(n) !== b) {
        return "Число "+b+" не является результатам функции эйлера числа "+n;
    }

    return "Равенство выполняется. Числа a("+a+") и n("+n+") взаимно просты, число b("+b+") является результатам функции ейлера n("+n+")."
}

function func5(n, r) {
    return Math.pow(n, eulerFunction(r)-1)%r;
}

function func6() {
    
}