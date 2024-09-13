## What is the zero overhead principle ?

> "If you have an abstraction, it should not cost anything compared to writing the equivalent code at a lower level. So, if I have a matrix multiplier, it should be written in such a way that you could not drop to C level of abstraction and use arrays and pointers and such and run faster."
> [Bjarne Stroustrup from the Lex Fridman podcast](https://youtu.be/uTxRF5ag27A?t=2655)


The zero-overhead principle is a C++ design principle that states:
- You don't pay for what you don't use.
- What you do use is just as efficient as what you could reasonably write by hand.

In general, this means that no feature should be added to C++ that would impose any overhead, whether in time or space, greater than a programmer would introduce without using the feature.
The only two features in the language that do not follow the zero-overhead principle are runtime type identification and exceptions, and are why most compilers include a switch to turn them off.
[cppreference](https://en.cppreference.com/w/cpp/language/Zero-overhead_principle)

## Demonstration
This is a small demonstration that has the same code written in C and C++ and both are compiled to assembly so you can
see the instructions difference.
<br>
In order to achieve the `zero overhead principle` in this demonstration, what we write in C++ code should be less or 
equal assembly instructions than we wrote in C.

This is our C code: 
```C
typedef struct Player {
    int x;
    int y;
} Player;

static void player_setX(Player *p, int x) { p->x = x; }

static int player_getX(Player *p) { return p->x; }

static void player_setY(Player *p, int y) { p->y = y; }

static int player_getY(Player *p) { return p->y; }

static void player_move_left(Player *p, int amount) { p->x -= amount; }

static void player_move_right(Player *p, int amount) { p->x += amount; }

static void player_move_up(Player *p, int amount) { p->y -= amount; }

static void player_move_down(Player *p, int amount) { p->y += amount; }

int main() {
    Player p1 = {55, 47}, p2 = {9, 74}, p3 = {10, 25};
    player_move_right(&p2, 5);
    player_move_down(&p3, 5);
    player_setX(&p1, player_getX(&p2) * player_getX(&p3));
    player_setY(&p1, player_getY(&p2) / player_getY(&p3));
    player_move_left(&p1, player_getX(&p2) / 2);
    player_move_up(&p1, player_getY(&p2) / 2);
    return player_getX(&p1) * player_getX(&p2) * player_getX(&p3);
}
```

This is our C++ code (equivalent: C + OOP feature):
```C++
class Entity {
protected:
    int x{};
    int y{};
public:
    Entity(int x, int y) : x(x), y(y) {}

    virtual ~Entity() = default;

    void setX(int x) noexcept { this->x = x; }

    int getX() const noexcept { return x; }

    void setY(int y) noexcept { this->y = y; }

    int getY() const noexcept { return y; }

    virtual void move_left(int amount) = 0;

    virtual void move_right(int amount) = 0;

    virtual void move_up(int amount) = 0;

    virtual void move_down(int amount) = 0;
};

class Player : public Entity {
public:
    Player(int x, int y) noexcept: Entity(x, y) {}

    void move_left(int amount) override { this->x -= amount; }

    void move_right(int amount) override { this->x += amount; }

    void move_up(int amount) override { this->y -= amount; }

    void move_down(int amount) override { this->y += amount; }
};

int main() {
    Player p1(55, 47), p2(9, 74), p3(10, 25);
    p2.move_right(5);
    p3.move_down(5);
    p1.setX(p2.getX() * p3.getX());
    p1.setY(p2.getY() * p3.getY());
    p1.move_left(p2.getX() / 2);
    p1.move_up(p2.getY() / 2);
    return p1.getX() * p2.getX() * p3.getX();
}
```
> NB: we don't really have to use interfaces and pure virtual functions here because OOP is just a feature in C++ and we can use the same C code here.
> It's just that to demonstrate the zero overhead principle, we have to use a feature that doesn't exist in C such as OOP, 
> so then we can test if the extended code will compile same as if we were using C itself with 0 overhead.

C++ compiled assembly code
```shell
clang++ -S program.cpp -o program.asm --std=c++20 -Os -Wall -Wextra -Wpedantic
```
```asm
main:                                 
	movl	$18620, %eax               
	retq
```
> The C++ compiler has optimized away our Player class and the abstractions we had, all methods were inlined and
> everything was narrowed down and calculated by the compiler at compile time to the `movl $18620` instruction which is the result value that was returned by the main function.

C compiled assembly code
```shell
clang -S program.c -o program.asm --std=c17 -Os -Wall -Wextra -Wpedantic
```
```asm
main:
	movl	$18620, %eax 
	retq
```
> We can see that the C compiler optimized our program by inlining function calls and objects construction to end up with the final value calculated at compile time.

## Conclusion
We can see that the C and C++ compilers did the same optimizations such as inlining all function calls, compile time calculations..
<br>
But by using OOP to do our abstractions with C++, we still end up with same code as we wrote in C level, and that we call `Zero Overhead`.
<br>
This is such a good thing that we can use C++ features that don't exist in C such as (classes, methods, lambdas, polymorphism, templates ...)
to write code that will compile just as if we were using C or Fortran, but with many features, of course if we respect the [C++ guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

## References
- [Bjarne Stroustrup explaining the zero overhead principle](https://www.youtube.com/watch?v=G5zCGY0tkq8)
- [C++ guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

### Corrections
If you think there is a mistake, misconception or misinformation, feel free to open an issue at the [issue tracker][tracker].

[tracker]: https://github.com/baderouaich//the-zero-overhead-principle/issues
