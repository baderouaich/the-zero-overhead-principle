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
