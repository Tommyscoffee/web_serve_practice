#include <sys/types.h>
#include "../mylib/mylib.h"

// constans definitions
#define PORT (in_port_t)5511
#define HOSTNAME_LENGTH 64

//public functions

extern void goban_init(int soc, char my_stone, char peer_stone);
extern void goban_show();
extern int goban_peer_turn();
extern int goban_my_turn();
extern void goban_destroy();