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
