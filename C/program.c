typedef struct Player {
    int x;
    int y;
} Player;

inline void player_setX(Player *p, int x) { p->x = x; }

inline int player_getX(Player *p) { return p->x; }

inline void player_setY(Player *p, int y) { p->y = y; }

inline int player_getY(Player *p) { return p->y; }

inline void player_move_left(Player *p, int amount) { p->x -= amount; }

inline void player_move_right(Player *p, int amount) { p->x += amount; }

inline void player_move_up(Player *p, int amount) { p->y -= amount; }

inline void player_move_down(Player *p, int amount) { p->y += amount; }

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

