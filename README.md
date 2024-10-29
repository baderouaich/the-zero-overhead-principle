## What is the zero overhead principle ?

> "If you have an abstraction, it should not cost anything compared to writing the equivalent code at a lower level. So, if I have a matrix multiplier, it should be written in such a way that you could not drop to C level of abstraction and use arrays and pointers and such and run faster."
> [Bjarne Stroustrup from the Lex Fridman podcast](https://youtu.be/uTxRF5ag27A?t=2655)


The zero-overhead principle is a C++ design principle that states:
- You don't pay for what you don't use.
- What you do use is just as efficient as what you could reasonably write by hand.

In general, this means that no feature should be added to C++ that would impose any overhead, whether in time or space, greater than a programmer would introduce without using the feature.
The only two features in the language that do not follow the zero-overhead principle are runtime type identification and exceptions, and are why most compilers include a switch to turn them off.
[cppreference](https://en.cppreference.com/w/cpp/language/Zero-overhead_principle)

<img src="https://github.com/user-attachments/assets/554f7aa8-b1ea-4dfe-ae61-2316223e1333" width="500"/>

## Demonstration
This project includes a demonstration that contrasts equivalent code written in C and C++. Both versions are compiled to assembly language, allowing for a direct comparison of the generated instructions.

## Objective
To illustrate the Zero Overhead Principle, the C++ code should generate assembly instructions that are fewer than or equal to those produced by the C code.

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

int main(void) {
    Player p1 = {55, 47}, p2 = {9, 74}, p3 = {10, 25};
    player_move_right(&p2, 5);
    player_move_down(&p3, 5);
    player_setX(&p1, player_getX(&p2) * player_getX(&p3));
    player_setY(&p1, player_getY(&p2) / player_getY(&p3));
    player_move_left(&p1, player_getX(&p2) / 2);
    player_move_up(&p1, player_getY(&p2) / 2);
    player_setX(&p1, player_getX(&p1) + 1);
    player_setX(&p2, player_getX(&p2) + 2);
    player_setX(&p3, player_getX(&p3) + 3);
    return player_getX(&p1) * player_getX(&p2) * player_getX(&p3);
}
```

Here’s a comparable implementation using C++ features such as classes, templates, and operator overloading:
```C++
template <typename T>
class Entity {
protected:
    T x{};
    T y{};

public:
    Entity(T x, T y) : x(x), y(y) {}
    virtual ~Entity() = default;

    void setX(T x) noexcept { this->x = x; }
    T getX() const noexcept { return x; }
    void setY(T y) noexcept { this->y = y; }
    T getY() const noexcept { return y; }

    virtual void move_left(T amount) = 0;
    virtual void move_right(T amount) = 0;
    virtual void move_up(T amount) = 0;
    virtual void move_down(T amount) = 0;
    virtual Entity& operator+=(T amount) = 0;
};

class Player : public Entity<int> {
public:
    Player(int x, int y) noexcept : Entity(x, y) {}

    void move_left(int amount) override { this->x -= amount; }
    void move_right(int amount) override { this->x += amount; }
    void move_up(int amount) override { this->y -= amount; }
    void move_down(int amount) override { this->y += amount; }

    Player& operator+=(int amount) override {
        this->x += amount;
        this->y += amount;
        return *this;
    }
};

int main() {
    Player p1(55, 47), p2(9, 74), p3(10, 25);
    p2.move_right(5);
    p3.move_down(5);
    p1.setX(p2.getX() * p3.getX());
    p1.setY(p2.getY() * p3.getY());
    p1.move_left(p2.getX() / 2);
    p1.move_up(p2.getY() / 2);
    p1 += 1;
    p2 += 2;
    p3 += 3;
    return p1.getX() * p2.getX() * p3.getX();
}
```
> Note: The use of interfaces and pure virtual functions here serves to demonstrate the capabilities of C++ and is not strictly necessary for this particular example. The goal is to showcase how C++ can use features not available in C while still adhering to the Zero Overhead Principle.

C++ compiled assembly code
```shell
clang++ -S program.cpp -o program.asm --std=c++20 -Os -Wall -Wextra -Wpedantic
```
```asm
main:                                 
	movl	$27872, %eax               
	retq
```
> The C++ compiler has optimized away our Player class and the abstractions we had, all methods were inlined and
> everything was narrowed down and calculated by the compiler at compile time to the `movl $27872` instruction which is the result value that was returned by the main function.

C compiled assembly code
```shell
clang -S program.c -o program.asm --std=c17 -Os -Wall -Wextra -Wpedantic
```
```asm
main:
	movl	$27872, %eax 
	retq
```
> We can see that the C compiler optimized our program by inlining function calls and objects construction to end up with the final value calculated at compile time.

## Analysis
Both the C and C++ compilers performed optimizations such as inlining function calls and calculating values at compile time. Remarkably, despite the additional features employed in C++, the final assembly code generated was equivalent to that of the C code, demonstrating the Zero Overhead Principle in action.

## Conclusion
This demonstration illustrates that the C++ and C compilers achieved similar optimizations, such as inlining and compile-time calculations. By utilizing templates and object-oriented programming (OOP) in C++, we can write abstractions without sacrificing performance. This empowers developers to leverage advanced features like classes, methods, and templates while still achieving the efficiency of C-level code and sometimes even [better](https://youtu.be/uTxRF5ag27A?t=2678), of course if we respect the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

## References
- [Bjarne Stroustrup explaining the zero overhead principle](https://www.youtube.com/watch?v=G5zCGY0tkq8)
- [C++ guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

### Corrections
If you think there is a mistake, misconception or misinformation, feel free to open an issue at the [issue tracker][tracker].

[tracker]: https://github.com/baderouaich//the-zero-overhead-principle/issues
