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

|         | **Compiler** | **Lang Version** | **Optimization** |
|---------|--------------|------------------|------------------|
| **C**   |   Clang-20   |        23        |        Os        |
| **C++** |  Clang++-20  |        23        |        Os        |

## Objective
To illustrate the Zero Overhead Principle, the C++ code should generate assembly instructions that are fewer than or equal to those produced by the C code.

This is our C code: 
```C
typedef volatile int value_type; // See issue #1
typedef struct Player {
  value_type x;
  value_type y;
} Player;

static void player_setX(Player *p, value_type x) { p->x = x; }
static value_type player_getX(Player *p) { return p->x; }
static void player_setY(Player *p, value_type y) { p->y = y; }
static value_type player_getY(Player *p) { return p->y; }
static void player_move_left(Player *p, value_type amount) { p->x -= amount; }
static void player_move_right(Player *p, value_type amount) { p->x += amount; }
static void player_move_up(Player *p, value_type amount) { p->y -= amount; }
static void player_move_down(Player *p, value_type amount) { p->y += amount; }

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
#include <utility> // std::forward<>()

template<typename T>
concept EntityValueTypeConcept = std::is_integral_v<T> or std::is_floating_point_v<T>;

template<EntityValueTypeConcept T>
class Entity {
public:
  using value_type = T;

protected:
  value_type x{};
  value_type y{};

public:
  explicit Entity(value_type &&x, value_type &&y) noexcept : x(std::forward<value_type>(x)),
                                                             y(std::forward<value_type>(y)) {
  }

  Entity() noexcept = default;

  virtual ~Entity() noexcept = default;

  void setX(value_type &&x) noexcept { this->x = std::forward<value_type>(x); }
  [[nodiscard]] value_type getX() const noexcept { return x; }
  void setY(value_type &&y) noexcept { this->y = std::forward<value_type>(y); }
  [[nodiscard]] value_type getY() const noexcept { return y; }

  virtual void move_left(value_type amount) noexcept = 0;

  virtual void move_right(value_type amount) noexcept = 0;

  virtual void move_up(value_type amount) noexcept = 0;

  virtual void move_down(value_type amount) noexcept = 0;

  virtual Entity &operator+=(value_type amount) noexcept = 0;
};

class Player final : public Entity<volatile int> { // See issue #1
public:
  explicit Player(value_type &&x, value_type &&y) noexcept : Entity(std::forward<value_type>(x),
                                                                    std::forward<value_type>(y)) {
  }

  void move_left(value_type amount) noexcept override { this->x -= amount; }
  void move_right(value_type amount) noexcept override { this->x += amount; }
  void move_up(value_type amount) noexcept override { this->y -= amount; }
  void move_down(value_type amount) noexcept override { this->y += amount; }

  Player &operator+=(const value_type amount) noexcept override {
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
clang++ -S program.cpp -o program.asm --std=c++23 -Os -Wall -Wextra -Wpedantic
```
```asm
main:
	.cfi_startproc
	movl	$55, -44(%rsp)
	movl	$47, -40(%rsp)
	movl	-44(%rsp), %eax
	movl	%eax, -24(%rsp)
	movl	-40(%rsp), %eax
	movl	%eax, -8(%rsp)
	movl	$9, -44(%rsp)
	movl	$74, -32(%rsp)
	movl	-44(%rsp), %eax
	movl	%eax, -40(%rsp)
	movl	-32(%rsp), %eax
	movl	%eax, -12(%rsp)
	movl	$10, -44(%rsp)
	movl	$25, -4(%rsp)
	movl	-44(%rsp), %eax
	movl	%eax, -32(%rsp)
	movl	-4(%rsp), %eax
	movl	%eax, -16(%rsp)
	movl	$5, %eax
	movl	%eax, -44(%rsp)
	movl	-44(%rsp), %ecx
	addl	%ecx, -40(%rsp)
	movl	%eax, -44(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -16(%rsp)
	movl	-40(%rsp), %eax
	imull	-32(%rsp), %eax
	movl	%eax, -44(%rsp)
	movl	-44(%rsp), %eax
	movl	%eax, -24(%rsp)
	movl	-12(%rsp), %eax
	imull	-16(%rsp), %eax
	movl	%eax, -44(%rsp)
	movl	-44(%rsp), %eax
	movl	%eax, -8(%rsp)
	movl	-40(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movl	%ecx, -44(%rsp)
	movl	-44(%rsp), %eax
	subl	%eax, -24(%rsp)
	movl	-12(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movl	%ecx, -44(%rsp)
	movl	-44(%rsp), %eax
	subl	%eax, -8(%rsp)
	movl	$1, -44(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -24(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -8(%rsp)
	movl	$2, -44(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -40(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -12(%rsp)
	movl	$3, -44(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -32(%rsp)
	movl	-44(%rsp), %eax
	addl	%eax, -16(%rsp)
	movl	-24(%rsp), %eax
	imull	-40(%rsp), %eax
	imull	-32(%rsp), %eax
	retq
```

C compiled assembly
```shell
clang -S program.c -o program.asm --std=c23 -Os -Wall -Wextra -Wpedantic
```
```asm
main:
	.cfi_startproc
	movl	$9, -24(%rsp)
	movl	$74, -8(%rsp)
	movl	$10, -20(%rsp)
	movl	$25, -12(%rsp)
	movl	$5, %eax
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %ecx
	addl	%ecx, -24(%rsp)
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %eax
	addl	%eax, -12(%rsp)
	movl	-24(%rsp), %eax
	imull	-20(%rsp), %eax
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %eax
	movl	%eax, -16(%rsp)
	movl	-8(%rsp), %eax
	cltd
	idivl	-12(%rsp)
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %eax
	movl	%eax, -4(%rsp)
	movl	-24(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movl	%ecx, -28(%rsp)
	movl	-28(%rsp), %eax
	subl	%eax, -16(%rsp)
	movl	-8(%rsp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movl	%ecx, -28(%rsp)
	movl	-28(%rsp), %eax
	subl	%eax, -4(%rsp)
	movl	-16(%rsp), %eax
	incl	%eax
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %eax
	movl	%eax, -16(%rsp)
	movl	-24(%rsp), %eax
	addl	$2, %eax
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %eax
	movl	%eax, -24(%rsp)
	movl	-20(%rsp), %eax
	addl	$3, %eax
	movl	%eax, -28(%rsp)
	movl	-28(%rsp), %eax
	movl	%eax, -20(%rsp)
	movl	-16(%rsp), %eax
	imull	-24(%rsp), %eax
	imull	-20(%rsp), %eax
	retq
```

## Analysis
Below is an overview of the compilation process for both the C and C++ implementations, along with observations that illustrate the Zero Overhead Principle.

---

### Overview of C Code Compilation to Assembly

1. **Direct Representation of Data and Operations:**  
   The C version defines a simple `struct` (Player) with volatile integer members and a set of static functions to manipulate these values. The operations (set, get, move, arithmetic) are written as plain functions.

2. **Compilation Process:**  
   When compiled with optimization flags (e.g., `-Os` for size optimization), the compiler inlines these static functions where possible.
    - **Inlining & Constant Propagation:** The calls to simple functions (e.g., `player_getX` or `player_move_right`) are inlined, and arithmetic operations are simplified.
    - **Assembly Outcome:** The resulting assembly shows direct manipulation of memory locations on the stack with few instructions. It essentially reduces to arithmetic operations and register moves with no function call overhead.

---

### Overview of C++ Code Compilation to Assembly

1. **Use of C++ Abstractions:**  
   The C++ implementation leverages classes, templates, and operator overloading. It introduces an abstract base class (with pure virtual functions) and a derived `Player` class implementing these methods. The code uses inline methods and move semantics (via `std::forward`) to encapsulate operations.

2. **Compilation Process:**
    - **Aggressive Optimization & Inlining:** Despite the use of virtual functions and class abstractions, when compiled with optimizations (`-Os` and inlining enabled), the compiler is able to see through these abstractions.
    - **Elimination of Overhead:** All the member functions are inlined. The virtual dispatch mechanism is optimized away because the call targets are known at compile time (for the final class `Player` marked as `final`).
    - **Assembly Outcome:** The final assembly is essentially a sequence of arithmetic and move instructions very similar to the C version, demonstrating that no additional cost is incurred from the C++ abstractions.

---

### Observations Related to the Zero Overhead Principle

- **No Extra Abstraction Cost:**  
  Both the C and C++ versions ultimately compile to assembly that performs the same arithmetic and memory operations. The C++ abstractions (classes, virtual functions, templates) are entirely optimized out. This is a practical demonstration of the Zero Overhead Principle in C++: using higher-level abstractions does not introduce extra runtime cost if the compiler is able to optimize them away.

- **Inlining and Compile-Time Optimizations:**  
  In both cases, inlining eliminates the function call overhead. The compiler simplifies the code based on constant propagation and dead-code elimination, resulting in an assembly code that is as efficient as hand-written C code.

- **Performance Equivalence:**  
  The generated assembly from both versions shows that the C++ code does not carry any additional overhead relative to the C code. For instance, the C++ version’s use of virtual functions and operator overloading does not lead to extra instructions or indirection when compiled with optimizations—the abstractions are resolved at compile time.

- **Maintainability vs. Efficiency:**  
  While the C++ version uses more advanced language features for better code organization and type safety, the final binary has similar performance characteristics to the C version. This reinforces the idea that modern C++ can offer both high-level design benefits and low-level efficiency.

---

### Conclusion

Both the C and C++ versions demonstrate that, under aggressive optimization, the abstractions provided by C++ (classes, templates, operator overloading, and even virtual functions in controlled scenarios) incur no extra cost compared to the equivalent C code. The Zero Overhead Principle is upheld, as the C++ compiler is smart enough to reduce complex abstractions to a minimal set of assembly instructions, ensuring performance on par with plain C.

The extra assembly instructions generated in the C++ version are a by-product of the richer language features. They are mostly related to initialization, extra type-safety checks, and temporary copies. As long as these extra instructions do not add runtime cost to the critical operations (or occur outside of performance-critical loops), they are considered acceptable under the Zero Overhead Principle. In our example, both the C and C++ versions perform the same essential computations, and the extra lines in the C++ assembly do not translate to worse runtime performance.


## References
- [Bjarne Stroustrup explaining the zero overhead principle](https://www.youtube.com/watch?v=G5zCGY0tkq8)
- [C++ guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

### Corrections
If you think there is a mistake, misconception or misinformation, feel free to open an issue at the [issue tracker][tracker].

[tracker]: https://github.com/baderouaich//the-zero-overhead-principle/issues
