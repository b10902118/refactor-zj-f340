## Report
### Problem description (f340. 俄羅斯方塊 (Tetris))
link: https://zerojudge.tw/ShowProblem?problemid=f340

Given the board size `X`, `Y`, and number of operations `n`. The goal is to simulate a falling T-shaped brick with four operations: `move right`, `move left`, `go buttom`, and `rotate clockwise`. If an operation is illegal, ignore it. Print the simulated board in the end.

### Refactor process
The order generally follows the path taught in class:
1. Function with multiple variable arguments
2. Function with a struct argument
3. Class with method

Along the way, I also tried out new stuff like `string`, `enum` and good practices like eliminate magic constants and giving variables meaningful names.

### Lessons
Choosing  right members to characterize an object is hard even in a simple problem. When I am creating class Tetris, several options are in my mind:
1. Maintaining the leftmost, rightmost, downmost coordinates to simplify checking.
2. Keeping the direction only, easy to update but involve more conditioning in checking.

Finally, I choose the latter and decide to record the direction of the flat side. This allows me to use less operations and variables. I chose this way also because the extra conditioning had been made natural with `enum Direction`.

New techniques may not be the most suitable. For example, I first rewrite my print process with `string` concatenating 0's and 1's (brick), but latter it became filling '1' into a big char buffer initialized with '0', which is a primitive but effective way. Another example is that I first use `pair<int,int>` to record coordinates, but latter found a `struct` with x, y is much clearer and shorter.

