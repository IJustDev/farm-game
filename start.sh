gcc src/*.c -o game \
    -Iinclude \
    -L/usr/lib \
    -lSDL2 -lSDL2_ttf -lSDL2_image \
    && ./game
