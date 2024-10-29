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
