#include <iostream>
#include <string>
using namespace std;

enum Command { MoveRight = 1, MoveLeft = 2, FallGround = 3, RotateRight = 4 };
enum Direction { Down, Left, Up, Right };
const int DirN = 4;

struct Tetris {
    const int X, Y;
    Direction dir;
    int x, y;

    Tetris(int X, int Y) : X(X), Y(Y), dir(Down), x(X / 2 + X % 1), y(Y) {}
};

void printLine(int X, string brick = "", int loc = 1) {
    cout << string("0", loc - 1) + brick + string("0", X - (loc - 1) - brick.length()) + '\n';
}

void blankLines(int n, int X) {
    for (int i = 0; i < n; ++i) printLine(X);
}

void right(Tetris &t) {
    int xright = t.dir == Left ? t.x : t.x + 1;
    if (xright < t.X) ++t.x;
}
void left(Tetris &t) {
    int xleft = t.dir == Right ? t.x : t.x - 1;
    if (xleft < t.X) --t.x;
}

bool stuckBoundry(const Tetris &t) { return t.x == 1 || t.x == t.X || t.y == 1; }

void rotate(Tetris &t) {
    if (!stuckBoundry(t)) t.dir = static_cast<Direction>((t.dir + 1) % 4);
}
void ground(Tetris &t) { t.y = t.dir == Up ? 1 : 2; }

bool onGround(Tetris &t) { return t.y == 1 || (t.y == 2 && t.dir != Up); }

int main() {
    int X, Y;
    cin >> X >> Y;
    int n;
    cin >> n;

    Tetris t(X, Y);

    for (int i = 0; i < n && !onGround(t); ++i) {
        int op;
        cin >> op;

        --t.y;

        switch (op) {
        case MoveRight:
            right(t);
            break;
        case MoveLeft:
            left(t);
            break;
        case FallGround:
            ground(t);
            break;
        case RotateRight:
            rotate(t);
            break;
        }
    }

    if (t.dir != Down) {
        blankLines(Y - (t.y + 1), X);

        printLine(X, "1", t.x);
    }
    else {
        blankLines(Y - t.y, X);
    }

    if (t.dir == Down || t.dir == Up) {
        printLine(X, "111", t.x - 1);
    }
    else {
        if (t.dir == Left) {
            printLine(X, "11", t.x - 1);
        }
        else {
            printLine(X, "11", t.x);
        }
    }

    if (t.dir != Up) {
        printLine(X, "1", t.x);
        blankLines(t.y - 2, X);
    }
    else {
        blankLines(t.y - 1, X);
    }

    return 0;
}
