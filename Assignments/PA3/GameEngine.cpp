#include "GameEngine.h"

#include <iostream>

using namespace std;

GameEngine::StartOption prompt_for_start_option();
GameEngine::GameOption prompt_for_game_option();
Building::Type prompt_for_building_type();
City::Coordinates prompt_for_coordinates(int grid_size);
int prompt_for_grid_size();
std::string prompt_for_filename();
City *prompt_for_city();

GameEngine::GameEngine(): city(prompt_for_city()) { }

GameEngine::~GameEngine() {
    delete city;
}

void GameEngine::construct() const {
    Building::Type building_type = prompt_for_building_type();

    if (!city->can_construct(building_type)) {
        cout << "Not enough budget" << endl;
        return;
    }

    City::Coordinates coordinates = prompt_for_coordinates(city->get_grid_size());

    if (!city->construct_at(building_type, coordinates)) {
        cout << "Cannot construct at " << coordinates << endl;
    }
}

void GameEngine::demolish() const {
    City::Coordinates coordinates = prompt_for_coordinates(city->get_grid_size());

    if (!city->demolish_at(coordinates)) {
        cout << "Cannot demolish at " << coordinates << endl;
    }
}

void GameEngine::show_building_short_info() const {
    City::Coordinates coordinates = prompt_for_coordinates(city->get_grid_size());

    Building *building = city->get_at(coordinates);
    if (building) {
        cout << building->get_short_information() << endl;
    }
    else {
        cout << "Building not found at " << coordinates << endl;
    }
}

void GameEngine::show_building_long_info() const {
    City::Coordinates coordinates = prompt_for_coordinates(city->get_grid_size());

    Building *building = city->get_at(coordinates);
    if (building) {
        cout << building->get_long_information() << endl;
    }
    else {
        cout << "Building not found at " << coordinates << endl;
    }
}

void GameEngine::show_city_status() const {
    cout << "Turn: " << city->get_turn() << endl;
    cout << "Budget: $" << city->get_budget() << endl;
    cout << "Revenue: " << city->get_revenue() << endl;
    cout << "Max Population: " << city->get_max_population() << endl;
    cout << "Population: " << city->get_population() << endl;
    cout << "Population Change: " << city->get_population_growth() << endl;
    cout << "Population Growth Rate: " << city->get_population_growth_rate() << endl;
}

void GameEngine::show_city_map() const {
    cout << string(3, ' ');
    for (int x = 0; x < city->get_grid_size(); ++x) {
        if (x / 10 > 0)
            cout << x / 10;
        else
            cout << ' ';
    }
    cout << endl;
    cout << string(3, ' ');
    for (int x = 0; x < city->get_grid_size(); ++x)
        cout << x % 10;
    cout << endl;

    cout << string(2, ' ') << '+' << string(city->get_grid_size(), '-') << '+' << endl;
    for (int y = 0; y < city->get_grid_size(); ++y) {
        if (y / 10 > 0)
            cout << y / 10;
        else
            cout << ' ';
        cout << y % 10;
        cout << '|';
        for (int x = 0; x < city->get_grid_size(); ++x) {
            Building *building = city->get_at(x, y);
            if (building) {
                switch (building->get_type()) {
                    case Building::Type::CLINIC:
                        cout << 'C';
                        break;
                    case Building::Type::HOSPITAL:
                        cout << 'H';
                        break;
                    case Building::Type::SILVER_MINE:
                        cout << 'S';
                        break;
                    case Building::Type::GOLD_MINE:
                        cout << 'G';
                        break;
                    case Building::Type::HOUSE:
                        cout << 'E';
                        break;
                    case Building::Type::APARTMENT:
                        cout << 'A';
                        break;
                }
            }
            else {
                cout << ' ';
            }
        }
        cout << "|" << endl;
    }
    cout << string(2, ' ') << '+' << string(city->get_grid_size(), '-') << '+' << endl;
}

void GameEngine::next_turn() const {
    city->move_to_next_turn();
}

void GameEngine::save() const {
    city->save(prompt_for_filename());
}

void GameEngine::run() {
    while (true) {
        switch (prompt_for_game_option()) {
            case GameOption::CONSTRUCT:
                construct();
                break;
            case GameOption::DEMOLISH:
                demolish();
                break;
            case GameOption::SHOW_BUILDING_SHORT_INFO:
                show_building_short_info();
                break;
            case GameOption::SHOW_BUILDING_LONG_INFO:
                show_building_long_info();
                break;
            case GameOption::SHOW_CITY_STATUS:
                show_city_status();
                break;
            case GameOption::SHOW_CITY_MAP:
                show_city_map();
                break;
            case GameOption::NEXT_TURN:
                next_turn();
                break;
            case GameOption::SAVE_GAME:
                save();
                break;
            case GameOption::QUIT:
                return;
        }
        cout << endl;
    }
}

GameEngine::StartOption prompt_for_start_option() {
    int input;
    while (true) {
        cout << "Please select:" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "> ";
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(80, '\n');
        }

        if (input == 1 || input == 2)
            return static_cast<GameEngine::StartOption>(input);
    }
}

GameEngine::GameOption prompt_for_game_option() {
    int input;
    while (true) {
        cout << "Please select:" << endl;
        cout << "1. Construct a Building" << endl;
        cout << "2. Demolish a Building" << endl;
        cout << "3. Show Building Short Info" << endl;
        cout << "4. Show Building Long Info" << endl;
        cout << "5. Show City Status" << endl;
        cout << "6. Show City Map" << endl;
        cout << "7. Go to Next Turn" << endl;
        cout << "8. Save Game" << endl;
        cout << "9. Quit" << endl;
        cout << "> ";
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(80, '\n');
            continue;
        }

        if (input >= 1 && input <= 9)
            return static_cast<GameEngine::GameOption>(input);
    }
}

Building::Type prompt_for_building_type() {
    int input;
    while (true) {
        cout << "Please select:" << endl;
        cout << "1. Clinic (C)" << endl;
        cout << "2. Hospital (H)" << endl;
        cout << "3. Silver Mine (S)" << endl;
        cout << "4. Gold Mine (G)" << endl;
        cout << "5. House (E)" << endl;
        cout << "6. Apartment (A)" << endl;
        cout << "> ";
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(80, '\n');
            continue;
        }

        if (input >= 1 && input <= 6)
            return static_cast<Building::Type>(input);
    }
}

City::Coordinates prompt_for_coordinates(int grid_size) {
    while (true) {
        int x, y;
        cout << "Please enter x y:" << endl;
        cout << "> ";
        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(80, '\n');
            continue;
        }

        if (x >= 0 && x < grid_size && y >= 0 && y < grid_size)
            return City::Coordinates{x, y};
    }
}

int prompt_for_grid_size() {
    while (true) {
        cout << "Please enter grid size (Even number in 10 - 20): ";
        int size;
        if (!(cin >> size)) {
            cin.clear();
            cin.ignore(80, '\n');
            continue;
        }
        if (size >= 10 && size <= 20 && size % 2 == 0)
            return size;
    }
}

std::string prompt_for_filename() {
    string filename;
    cout << "Please enter the filename: ";
    cin >> filename;
    return filename;
}

City *prompt_for_city() {
    switch (prompt_for_start_option()) {
        case GameEngine::StartOption::NEW_GAME:
            return new City(prompt_for_grid_size());
        case GameEngine::StartOption::LOAD_GAME:
            return new City{prompt_for_filename()};
    }
    return nullptr;
}
