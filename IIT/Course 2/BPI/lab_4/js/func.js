function binaryNod(m, n) {
    m = parseInt(m, 10);
    n = parseInt(n, 10);
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
    n = parseInt(n, 10);
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

function getKs(k0, eiler) {
    eiler = parseInt(eiler, 10);
    k0 = parseInt(k0, 10);
    return fastEx(k0, eulerFunction(eiler)-1, eiler);
}

function fastEx(multiplier, power, mod) {
    multiplier = parseInt(multiplier, 10);
    power = parseInt(power, 10);
    mod = parseInt(mod, 10);
    var output = 1;

    while (power) {
        while (power % 2 == 0) {
            power /= 2;
            multiplier = (multiplier * multiplier) % mod;
        }
        power -= 1;
        output = (output * multiplier) % mod;
    }

    return output;
}


function  mgetR(p, q) {
    return p * q;
}

function getEiler(p, q) {
    return (p - 1) * (q - 1);
}

function euclideX(a, b) {

    var d0 = a,
        d1 = b;

    if (a < b) {
        d0 = b;
        d1 = a;
    }

    var x0 = 1,
        x1 = 0,
        y0 = 0,
        y1 = 1;

    while (d1 > 1) {
        var q = Math.floor(d0 / d1),
            d2 = d0 % d1,
            x2 = x0 - q * x1,
            y2 = y0 - q * y1;
        d0 = d1;
        d1 = d2;
        x0 = x1;
        x1 = x2;
        y0 = y1;
        y1 = y2;
    }

    return [x1, y1, d1];
}

function getAlphabet() {
    return 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя';
}

function hashString(string, prevH, n) {
    var length = string.length,
        alphabet = getAlphabet();

    string = string.toLowerCase();

    for (var i = 0; i < length; i++) {
        var charPos = alphabet.indexOf(string[i])+1; // +1 - !!!
        prevH = hashChar(prevH, charPos, n);
    }

    return prevH;
}

function hashChar(prevH, m, n) {
    return Math.pow(prevH+m, 2) % n;
}

function generateS(hashM, kC, r) {
    return fastEx(hashM, kC, r);
}