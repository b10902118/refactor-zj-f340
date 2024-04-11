#include <iostream>
#include <string>
#include <cstring>
#include <utility>
using namespace std;

enum Command { MoveRight = 1, MoveLeft = 2, FallGround = 3, RotateRight = 4 };
enum Direction { Down, Left, Up, Right };
const int DirN = 4;

struct Pos {
    int x, y;
};

struct Tetris {
    // constructor is constexpr
    // error: ‘constexpr’ needed for in-class initialization of static data member ‘const Pos
    // Tetris::flatsides [4]’ of non-integral type [-fpermissive]
    static constexpr Pos flatsides[DirN] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    const int X, Y;
    Direction flatDir;
    int x, y;

    Tetris(int X, int Y) : X(X), Y(Y), flatDir(Up), x(X / 2 + X % 2), y(Y) {}
};

void right(Tetris &t) {
    int xright = t.flatDir == Right ? t.x : t.x + 1;
    if (xright < t.X) ++t.x;
}
void left(Tetris &t) {
    int xleft = t.flatDir == Left ? t.x : t.x - 1;
    if (xleft < t.X) --t.x;
}

bool stuckBoundry(const Tetris &t) { return t.x == 1 || t.x == t.X || t.y == 1; }

void rotate(Tetris &t) {
    if (!stuckBoundry(t)) t.flatDir = static_cast<Direction>((t.flatDir + 1) % 4);
}
void ground(Tetris &t) { t.y = t.flatDir == Down ? 1 : 2; }

bool onGround(Tetris &t) { return t.y == 1 || (t.y == 2 && t.flatDir != Down); }

int y2r(Tetris &t, int shift = 0) { return t.Y - (t.y + shift); }
int x2c(Tetris &t, int shift = 0) { return t.x + shift - 1; }

void print(Tetris &t) {
    char c[t.Y][t.X + 1];
    memset(c, '0', t.Y * (t.X + 1));
    for (int i = 0; i < t.Y; ++i) c[i][t.X] = '\n';

    c[y2r(t)][x2c(t)] = '1';
    for (int d = 0; d < DirN; ++d)
        if (d != t.flatDir) c[y2r(t, t.flatsides[d].y)][x2c(t, t.flatsides[d].x)] = '1';

    fwrite(c, sizeof(char), t.Y * (t.X + 1), stdout);
}

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
    print(t);

    return 0;
}
