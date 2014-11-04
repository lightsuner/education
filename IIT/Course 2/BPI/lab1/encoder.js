var Encoder = function(stringsLengths) {
    this.stringsLengths = stringsLengths;
    this.figure = [];
    this.maxRowLength = 0;
};

Encoder.prototype.setText = function(text, key = null) {
    if (key != null && isFinite(key)) {
        text = this.cesarEncode(text, key);
    }

    this.writeTextToFigure(text);
    return this;
};

Encoder.prototype.readText = function() {
    return this.readTextFromFigure();
};

Encoder.prototype.writeTextToFigure = function(text) {
    var size = this.stringsLengths.length;

    this.figure = [];
    this.maxRowLength = 0;

    for (var i = 0; text.length; i++) {
        var currentLength = this.stringsLengths[i % size];
        var substring = '';

        substring = text.substr(0, currentLength);
        text = text.substring(currentLength);

        var substringLength = substring.length;

        if (!substringLength) {
            continue;
        }

        if (this.maxRowLength < substringLength) {
            this.maxRowLength = substringLength;
        }

        this.figure[i] = substring.split('');
    }
};

Encoder.prototype.readTextFromFigure = function() {
    var outputString = '';

    for (var c = 0; c < this.maxRowLength; c++) {
        for (var r = this.figure.length; r; r--) {
            if (this.figure[r-1].length <= c) {
                continue;
            }
            outputString += this.figure[r-1][c];
        }
    }

    return outputString;
};

Encoder.prototype.cesarEncode = function(text, key){
    var alphabet = "abcdefghijklmnopqrstuvwxyz",
        base = alphabet.length,
        newText = '';

    key = key % base;

    for (var i = 0; i < text.length; i++) {
        var char = text[i],
            pos = alphabet.indexOf(char.toLowerCase());
        if (pos < 0) {
            newText += char;
            continue;
        }
        var newChar = alphabet[(pos+key)%base];
        if (char == char.toUpperCase()) {
            newChar = newChar.toUpperCase();
        }

        newText += newChar;
    }

    return newText;
};
