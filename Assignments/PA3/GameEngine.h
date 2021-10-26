#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "City.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();
    void run();

    enum class StartOption {
        NEW_GAME = 1,
        LOAD_GAME = 2
    };

    enum class GameOption {
        CONSTRUCT = 1,
        DEMOLISH = 2,
        SHOW_BUILDING_SHORT_INFO = 3,
        SHOW_BUILDING_LONG_INFO = 4,
        SHOW_CITY_STATUS = 5,
        SHOW_CITY_MAP = 6,
        NEXT_TURN = 7,
        SAVE_GAME = 8,
        QUIT = 9
    };

private:
    City *const city;

    void construct() const;
    void demolish() const;
    void show_building_short_info() const;
    void show_building_long_info() const;
    void show_city_status() const;
    void show_city_map() const;
    void next_turn() const;
    void save() const;
};

#endif //GAMEENGINE_H
