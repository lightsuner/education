var Decoder = function(rows = 0, columns = 0) {
    this.rows = rows;
    this.columns = columns;
    this.figure = [];
    this.alphabet = "abcdefghijklmnopqrstuvwxyz";
    this.keywordAlphabet = "";
};


Decoder.prototype.setText = function(text) {
    this.text = text;

    return this;
};

Decoder.prototype.writeToFigure1 = function(){
    this.figure = [];

    var arrayOfText = this.text.split('');

    dance:
    for (var c = 0; c < this.columns; c++) {
        for (var r = this.rows; r; r--) {
            if (!arrayOfText.length) {
                break dance;
            }
            if (!this.figure[r-1]) {
                this.figure[r-1] = [];
            }
            this.figure[r-1][c] = arrayOfText.shift();
        }
    }

    return this;
};

Decoder.prototype.readFromFigure1 = function(){
    var outputText = '',
        figureSize = this.rows * this.columns,
        direction = 'down',
        stepMatrix = {},
        position = {r:0, c:0};

    while (outputText.length != this.text.length) {
        if (!isMarked(stepMatrix, position)) {
            outputText += this.figure[position.r][position.c];
            mark(stepMatrix, position);
        }

        var nextPos = {
            r: position.r,
            c: position.c
        };

        switch (direction) {
            case 'down':
                nextPos.r++;
                break;
            case 'right':
                nextPos.c++;
                break;
            case 'up':
                nextPos.r--;
                break;
            case 'left':
            default:
                nextPos.c--;
                break;
        }

        if (nextPos.c < 0 ||
            nextPos.r < 0 ||
            nextPos.c >= this.columns ||
            nextPos.r >= this.rows ||
            isMarked(stepMatrix, nextPos)) {
            direction = newDirection(direction);
            continue;
        }

        position = {
            r: nextPos.r,
            c: nextPos.c
        };

    }


    return outputText;
};

Decoder.prototype.writeToFigure2 = function(keyword){
    var lowercaseText = keyword
        .toLowerCase()
        .split("")
        .filter(function(x, n, s) { return s.indexOf(x) == n })
        .join("");

    this.keywordAlphabet = "";

    for (var i=0; i< this.alphabet.length; i++) {
        if (lowercaseText.indexOf(this.alphabet[i]) == -1) {
            this.keywordAlphabet += this.alphabet[i];
        }
    }
    this.keywordAlphabet += lowercaseText;

    return this;
};

Decoder.prototype.readFromFigure2 = function(){
    var outputText = "";

    for (var i=0; i< this.text.length; i++) {
        var char = this.text[i],
            pos = this.keywordAlphabet.indexOf(char.toLowerCase());

        if (pos === -1) {
            outputText += char;
            continue;
        }

        var view = this.alphabet[pos];

        if (char == char.toUpperCase()) {
            view = view.toUpperCase();
        }
        outputText += view;
    }

    return outputText;
};


function isMarked(stepMatrix, position) {
    return (stepMatrix[position.r] && stepMatrix[position.r][position.c]);
}

function mark(stepMatrix, position){
    if (!stepMatrix[position.r]) {
        stepMatrix[position.r] = {};
    }
    stepMatrix[position.r][position.c] = true;
}


function newDirection(direction) {
    switch (direction) {
        case 'down':
            return 'right';
        case 'right':
            return 'up';
        case 'up':
            return 'left';
        case 'left':
        default:
            return 'down';
    }
}