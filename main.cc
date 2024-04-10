#include <iostream>
#include <cstring>
using namespace std;

void printLine(int X, int loc = -1, char brick[] = (char *)"") {
    if (brick) {
        for (int i = 1; i < loc; ++i) cout << 0;
        cout << brick;
        for (int i = loc + strlen(brick); i <= X; ++i) cout << 0;
    }
    else {
        for (int i = 1; i <= X; ++i) cout << 0;
    }
    cout << endl;
}

void blankLines(int n, int X) {
    for (int i = 0; i < n; ++i) printLine(X);
}

bool rightClean(int X, int x, int d) { return (d != 1 && x < X - 1) || (d == 1 && x < X); }
bool leftClean(int X, int x, int d) { return (d != 3 && x > 2) || (d == 3 && x > 1); }
bool rotateClean(int X, int x, int y, int d) {
    return !(d == 1 && x == X) && !(d == 3 && x == 1) && !(d == 2 && y == 1);
}
bool touchGround(int X, int x, int y, int d) { return (d != 2 && y == 2) || (d == 2 && y == 1); }
int toGround(int d) { return d == 2 ? 1 : 2; }

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
        case 1:
            if (rightClean(X, x, d)) ++x;
            break;
        case 2:
            if (leftClean(X, x, d)) --x;
            break;
        case 3:
            y = toGround(d);
            grounded = true;
        case 4:
            if (rotateClean(X, x, y, d)) {
                d = (d + 1) % 4;
            }
            break;
        }
        if (touchGround(X, x, y, d)) break;
    }

    if (d != 0) {
        blankLines(Y - (y + 1), X);

        printLine(X, x, (char *)"1");
    }
    else {
        blankLines(Y - y, X);
    }

    if (d == 0 || d == 2) {
        printLine(X, x - 1, (char *)"111");
    }
    else {
        if (d == 1) {
            printLine(X, x - 1, (char *)"11");
        }
        else {
            printLine(X, x, (char *)"11");
        }
    }

    if (d != 2) {
        printLine(X, x, (char *)"1");
        blankLines(y - 2, X);
    }
    else {
        blankLines(y - 1, X);
    }

    return 0;
}
