#include <iostream>
#include <string>
using namespace std;

enum Command { MoveRight = 1, MoveLeft = 2, FallGround = 3, RotateRight = 4 };
enum Direction { Down, Left, Up, Right };
const int DirN = 4;

void printLine(int X, string brick = "", int loc = 1) {
    cout << string("0", loc - 1) + brick + string("0", X - (loc - 1) - brick.length()) + '\n';
}

void blankLines(int n, int X) {
    for (int i = 0; i < n; ++i) printLine(X);
}

bool rightClean(int X, int x, int d) {
    xright = d == Left ? x : x + 1;
    return xright < X;
}
bool leftClean(int X, int x, int d) {
    xleft = d == Right ? x : x - 1;
    return xleft > 1;
}
bool rotateClean(int X, int x, int y, int d) { return !(x == 1 || x == X || y == 1) }
bool touchGround(int X, int x, int y, int d) { return (d != Up && y == 2) || y == 1; }
int toGround(int d) { return d == Up ? 1 : 2; }

int main() {
    int X, Y;
    cin >> X >> Y;
    int n;
    cin >> n;

    int x = X / 2 + X % 2, y = Y, d = 0;
    bool grounded = false;

    for (int i = 0; i < n && !grounded; ++i) {
        int op;
        cin >> op;

        --y;

        switch (op) {
        case MoveRight:
            if (rightClean(X, x, d)) ++x;
            break;
        case MoveLeft:
            if (leftClean(X, x, d)) --x;
            break;
        case FallGround:
            y = toGround(d);
            grounded = true;
        case RotateRight:
            if (rotateClean(X, x, y, d)) {
                d = (d + 1) % DirN;
            }
            break;
        }
        if (touchGround(X, x, y, d)) break;
    }

    if (d != Down) {
        blankLines(Y - (y + 1), X);

        printLine(X, "1", x);
    }
    else {
        blankLines(Y - y, X);
    }

    if (d == Down || d == Up) {
        printLine(X, "111", x - 1);
    }
    else {
        if (d == Left) {
            printLine(X, "11", x - 1);
        }
        else {
            printLine(X, "11", x);
        }
    }

    if (d != Up) {
        printLine(X, "1", x);
        blankLines(y - 2, X);
    }
    else {
        blankLines(y - 1, X);
    }

    return 0;
}
