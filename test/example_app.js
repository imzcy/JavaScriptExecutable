var w = new Window();

w.maximizeButton = false;

w.minimumWidth = 400;
w.minimumHeight = 500;
w.maximumWidth = 800;
w.maximumHeight = 1000;

var mFile = new Menu();
mFile.text = "&File";
var mFileRecent = new Menu();
mFile.addMenu(mFileRecent);
mFileRecent.text = "&Recent"
var mFileRecentLeaf = new MenuLeaf();
mFileRecentLeaf.text = "测试"
mFileRecent.addMenu(mFileRecentLeaf);
mFile.visible = true;
w.addMenu(mFile);

var m = new Menu();
m.text = "&Help";
var m1 = new MenuLeaf();
m.addMenu(m1);
m1.text = "关于(&A)..."
m1.addEventListener('click', function() {
    w.alert('About Calculator...\nCopyright (C) 2014');
});
w.addMenu(m);

w.innerWidth = 400;
w.innerHeight = 500;

w.title = "Calculator";

var gridX = w.width / 4;
var gridY = w.height / 5;

var t = new LineEdit();
t.appendTo(w);
t.left = t.top = 0;
t.disabled = true;
t.text = '0';

var register = 0;
var pendingOp = '';
var clearScreen = false;

Button.prototype.reposition = function(x, y, w, h) {
    this.left = gridX * (x);
    this.top = gridY * (y + 1);
    this.width = gridX * w;
    this.height = gridY * h;
}

w.addEventListener('resize', function() {
    gridX = this.innerWidth / 4;
    gridY = this.innerHeight / 5;
    for (var key in buttonsArray) {
        Button.prototype.reposition.apply(buttonsArray[key], buttons[key]);
    }
    t.width = this.innerWidth;
    t.height = gridY;
});

var numericButtonCallback = function() {
    if (clearScreen) {
        t.text = '0';
        clearScreen = false;
    }
    var number = t.text.split('.');
    if (number.length === 1) {
        if (number[0].length < 10) {
            number[0] += this.text;
        }
    } else {
        if (number[1].length < 10) {
            number[1] += this.text;
        }
    }
    t.text = number.join('.');
    if (t.text.charAt(0) == '0') {
        t.text = t.text.substring(1);
    }
}

var decimalPointCallback = function() {
    if (clearScreen) {
        t.text = '0.';
        clearScreen = false;
    }
    var number = t.text.split('.');
    if (number.length === 1) {
        t.text += '.'
    }
}

var exec = function(val) {
    switch (pendingOp) {
    case '+':
        register += val;
        break;
    case '-':
        register -= val;
        break;
    case '*':
        register *= val;
        break;
    case '/':
        register /= val;
        break;
    }
    
    return register;
}

var operationCallback = function() {
    t.text = exec(parseFloat(t.text));
    pendingOp = this.text;
    clearScreen = true;
}

var buttons = {
    1: [0, 0, 1, 1, numericButtonCallback],
    2: [1, 0, 1, 1, numericButtonCallback],
    3: [2, 0, 1, 1, numericButtonCallback],
    4: [0, 1, 1, 1, numericButtonCallback],
    5: [1, 1, 1, 1, numericButtonCallback],
    6: [2, 1, 1, 1, numericButtonCallback],
    7: [0, 2, 1, 1, numericButtonCallback],
    8: [1, 2, 1, 1, numericButtonCallback],
    9: [2, 2, 1, 1, numericButtonCallback],
    0: [0, 3, 2, 1, numericButtonCallback],
    '.': [2, 3, 1, 1, decimalPointCallback],
    '+': [3, 0, 1, 1, operationCallback],
    '-': [3, 1, 1, 1, operationCallback],
    '*': [3, 2, 1, 1, operationCallback], 
    '/': [3, 3, 1, 1, operationCallback]
}

var buttonsArray = {}

for (var key in buttons)
{
    var b = new Button();
    b.text = key;
    b.reposition.apply(b, buttons[key]);
    b.addEventListener('click', buttons[key][4]);
    b.appendTo(w);
    buttonsArray[key] = b;
}

w.addEventListener('mousemove', function(left, top) {
    t.text = 'Left: ' + left + ', Top: ' + top;
});

w.addEventListener('mouseout', function() {
    //w.alert('Mouse out');
    t.text = 'Mouse out';
});

w.visible = true;
