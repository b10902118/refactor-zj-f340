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

class Tetris {
    // constructor is constexpr
    // error: ‘constexpr’ needed for in-class initialization of static data member ‘const Pos
    // Tetris::flatsides [4]’ of non-integral type [-fpermissive]
    static constexpr Pos flatsides[DirN] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    const int X, Y;
    Direction flatDir;
    int x, y;

    bool stuckBoundry() { return x == 1 || x == X || y == 1; }
    int y2r(int shift = 0) { return Y - (y + shift); }
    int x2c(int shift = 0) { return x + shift - 1; }

  public:
    Tetris(int X, int Y) : X(X), Y(Y), flatDir(Up), x(X / 2 + X % 2), y(Y) {}

    void down() { --y; }

    void right() {
        int xright = flatDir == Right ? x : x + 1;
        if (xright < X) ++x;
    }

    void left() {
        int xleft = flatDir == Left ? x : x - 1;
        if (xleft < X) --x;
    }

    void rotate() {
        if (!stuckBoundry()) flatDir = static_cast<Direction>((flatDir + 1) % 4);
    }

    void ground() { y = flatDir == Down ? 1 : 2; }

    bool onGround() { return y == 1 || (y == 2 && flatDir != Down); }

    void print() {
        char c[Y][X + 1];
        memset(c, '0', Y * (X + 1));
        for (int i = 0; i < Y; ++i) c[i][X] = '\n';

        c[y2r()][x2c()] = '1';
        for (int d = 0; d < DirN; ++d)
            if (d != flatDir) c[y2r(flatsides[d].y)][x2c(flatsides[d].x)] = '1';

        fwrite(c, sizeof(char), Y * (X + 1), stdout);
    }
};

int main() {
    int X, Y;
    cin >> X >> Y;
    int n;
    cin >> n;

    Tetris t(X, Y);

    for (int i = 0; i < n && !t.onGround(); ++i) {
        int op;
        cin >> op;

        t.down();

        switch (op) {
        case MoveRight:
            t.right();
            break;
        case MoveLeft:
            t.left();
            break;
        case FallGround:
            t.ground();
            break;
        case RotateRight:
            t.rotate();
            break;
        }
    }
    t.print();

    return 0;
}
