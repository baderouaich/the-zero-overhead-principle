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