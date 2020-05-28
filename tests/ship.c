#include "../src/ship.c"

void bit_map_print(BitMap* map){

    for (int i = 0; map->bitmap[i] != '\0'; i++) {
        printf("\n|");
        for(int j = 0; map->bitmap[i][j] != '\0'; j++){
            printf("%c|", map->bitmap[i][j]);
        }
    }

    printf("\n");
}

BitMap* bitmap_create(int size){
    
    BitMap* bit_map = (BitMap*) malloc(sizeof(BitMap));
    
    bit_map->bitmap = (char**) malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        bit_map->bitmap[i] = (char*) malloc(sizeof(char) * size);
        for (int j = 0; j < 3; j++){
            bit_map->bitmap[i][j] = '#';
        }
    }

    return bit_map;
}

int main(){

    int size = 3;
    Ship2* ship = shipCreate2(2);
    ship->map = bitmap_create(size);
    
    bit_map_print(ship->map);

    // bit_map_print(&bit_map_d);
    // bit_map_print(bit_map_t);
    // bit_map_print(bit_map_tt);
    // bit_map_print(bit_map_tl);

    /******
     * |#|#|#|
     * |#|M|#| array - 3x3
     * |#|#|#|
     ******/   
    // bit_map_m.bitmap[1][1] = 'M'; 

}
