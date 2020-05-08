#include "../src/ship.c"

int main(){

    Ship* ship = shipCreate(1);
    ship->bitmap[0][0] = '?';

    Ship* new_ship = shipCreate(1);

    shipPrint(ship);
    shipPrint(new_ship);
}
