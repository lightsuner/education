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


function getR(p, q) {
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

function getOffset() {
    return 2;
}

function encodeString(string, key, r) {
    var output = [],
        length = string.length;

    string = string.toLowerCase();

    for (var i = 0; i < length; i++) {
        output.push(encodeChar(string[i], key, r));
    }

    return output.join(', ');
}

function encodeChar(char, key, r) {
    var alphabet = getAlphabet(),
        alphabetLength = alphabet.length,
        charPos = alphabet.indexOf(char);
    if (charPos === -1) {
        return char;
    }

    charPos += getOffset();

    return fastEx(charPos, key, r);
}

function decodeChar(number, key, r) {
    var charPos = fastEx(number, key, r);

    return getAlphabet()[charPos-getOffset()];
}

function decodeString(string, key, r) {
    var codes = string.split(','),
        output = '';
    for (var i in codes) {
        output += decodeChar(parseInt(codes[i], 10), key, r);
    }

    return output;
}
