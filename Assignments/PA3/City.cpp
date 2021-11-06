#include "City.h" /*City.cpp*/
#include <iostream>
#include <fstream>

/*Creates a new City.
 *Allocate the 2D array of grid cells with dimensions size by size.
 *Set all grid cells to nullptr.
 *Set grid size accordingly.
 *Set turn to 1.
 *Initially, the budget is $150. size is always greater than or equal to 1.*/
City::City(int size) : grid_size(size), budget(150), turn(1)
{
    if (grid_size < 1)
    {
        grid_size = 1;
    }
    /*Allocate the 2D array of grid cells with dimensions size by size.*/
    grid = new Building **[grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        grid[i] = new Building *[grid_size];
        /*Set all grid cells to nullptr*/
        for (int j = 0; j < grid_size; j++)
        {
            grid[i][j] = nullptr;
        }
    }
    // Set grid size accordingly.
    // Set turn to 1.
    // Initially, the budget is $150.
}

/*Check whether the provided coordinates are out-of-bound*/
inline bool is_out_of_bound(const int &x, const int &y, const int &size)
{
    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        return true; // the coordinates are out-of-bound
    }
    return false;
}

/*Loads a city from the file filename. See Save File Format for the format of the save file.
 *You can assume the file always exists and the format is correct.
 *You can make use of the >> operator.
 *Don't forget to set neighbors when adding buildings to the city.*/
City::City(const std::string &filename) : budget(66666666)
{
    using namespace std;
    ifstream input_stream;
    input_stream.open(filename, ios::in); // open the file (read-only)
    if (!input_stream)
    {
        // cerr << "Unable to open " + filename + " :(" << endl;
        grid_size = 0, budget = 150, turn = 1;
        return;
    }
    // cerr << 1 << endl;
    /*The first three values are the grid size, budget and turns of the city.*/
    string input_str;
    getline(input_stream, input_str);
    grid_size = atoi(input_str.c_str()); // grid size
    getline(input_stream, input_str);
    int new_budget = atoi(input_str.c_str()); // budget
    getline(input_stream, input_str);
    turn = atoi(input_str.c_str()); // turn
    // cerr << 2 << endl;
    /*Allocate the 2D array of grid cells with dimensions size by size.*/
    grid = new Building **[grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        grid[i] = new Building *[grid_size];
        /*Set all grid cells to nullptr*/
        for (int j = 0; j < grid_size; j++)
        {
            grid[i][j] = nullptr;
        }
    }
    // cerr << 3 << endl;
    Building::Type type;
    Coordinates coordinates;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            getline(input_stream, input_str);

            /*If the grid cell has no building, save 0*/
            if (input_str[0] == '0')
            {
                continue;
            }
            else
            {
                /*If the grid cell has a building, save the value in the Building::Type enum*/
                type = static_cast<Building::Type>(input_str[0] - '0');
                coordinates.x = i, coordinates.y = j;
                /*For Residential building, also store the population after a space.*/
                if (type == Building::Type::APARTMENT || type == Building::Type::HOUSE)
                {
                    if (type == Building::Type::APARTMENT)
                    {
                        grid[i][j] = new Apartment(*this, atoi((input_str.erase(0, 2)).c_str()));
                    }
                    else
                    {
                        grid[i][j] = new House(*this, atoi((input_str.erase(0, 2)).c_str()));
                    }

                    // register neighboring buildings
                    if (!is_out_of_bound(coordinates.x + 1, coordinates.y, grid_size) && grid[coordinates.x + 1][coordinates.y] != nullptr)
                    {
                        grid[coordinates.x + 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
                        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x + 1][coordinates.y]);
                    }
                    if (!is_out_of_bound(coordinates.x - 1, coordinates.y, grid_size) && grid[coordinates.x - 1][coordinates.y] != nullptr)
                    {
                        grid[coordinates.x - 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
                        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x - 1][coordinates.y]);
                    }
                    if (!is_out_of_bound(coordinates.x, coordinates.y + 1, grid_size) && grid[coordinates.x][coordinates.y + 1] != nullptr)
                    {
                        grid[coordinates.x][coordinates.y + 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
                        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y + 1]);
                    }
                    if (!is_out_of_bound(coordinates.x, coordinates.y - 1, grid_size) && grid[coordinates.x][coordinates.y - 1] != nullptr)
                    {
                        grid[coordinates.x][coordinates.y - 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
                        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y - 1]);
                    }
                }
                else
                {
                    construct_at(type, coordinates);
                }
            }
        }
    }

    budget = new_budget;
    input_stream.close(); // close the file
}

/*Deallocates all dynamically allocated memory, including the memory of Building objects added to the city.*/
City::~City()
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                delete grid[i][j]; // memory of Building objects added to the city
                grid[i][j] = nullptr;
            }
        }
        delete[] grid[i];
        grid[i] = nullptr;
    }
    delete[] grid;
    grid = nullptr;
}

/*Saves the city to a file such that it can be loaded later.
 *If the file already exists, overwrite existing content. You can make use of the << operator.*/
void City::save(const std::string &filename) const
{
    using namespace std;
    ofstream output_stream;
    output_stream.open(filename, ios::out | ios::trunc); // open the file (overwrite)
    if (!output_stream)
    {
        cerr << "Unable to open " + filename + " :(" << endl;
        return;
    }
    output_stream << to_string(grid_size) << endl;
    output_stream << to_string(budget) << endl;
    output_stream << to_string(turn) << endl;

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] == nullptr)
            {
                output_stream << '0';
            }
            else
            {
                output_stream << to_string(static_cast<int>(grid[i][j]->get_type()));
                if (grid[i][j]->get_category() == Building::Category::RESIDENTIAL)
                {
                    output_stream << " " + to_string(grid[i][j]->get_population());
                }
            }
            output_stream << endl;
        }
    }

    output_stream.close(); // close the file
}

// Returns the turn, budget and grid size of the city, respectively.
/*Returns the turn*/
int City::get_turn() const
{
    return turn;
}

/*Returns the budget*/
int City::get_budget() const
{
    return budget;
}

/*Returns the grid size*/
int City::get_grid_size() const
{
    return grid_size;
}

/*Returns the corresponding attribute of the city.
 *  The revenue of the city is the sum of revenue of all buildings in the city.
 *  The population of the city is the sum of population of all buildings in the city.
 *  The max population of the city is the sum of max population of all buildings in the city.
 *  The population growth of the city is the sum of population growth of all buildings in the city.
 *  The population growth rate of the city is the sum of population growth rate contribution of all buildings in the city.*/
/*The revenue of the city is the sum of revenue of all buildings in the city.*/
int City::get_revenue() const
{
    int revenue = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                revenue += grid[i][j]->get_revenue();
            }
        }
    }
    return revenue;
}

/*The population of the city is the sum of population of all buildings in the city.*/
int City::get_population() const
{
    int population = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                population += grid[i][j]->get_population();
            }
        }
    }
    return population;
}

/*The max population of the city is the sum of max population of all buildings in the city.*/
int City::get_max_population() const
{
    int max_population = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                max_population += grid[i][j]->get_max_population();
            }
        }
    }
    return max_population;
}

/*The population growth of the city is the sum of population growth of all buildings in the city.*/
int City::get_population_growth() const
{
    int population_growth = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                population_growth += grid[i][j]->get_population_growth();
            }
        }
    }
    return population_growth;
}

/*The population growth rate of the city is the sum of population growth rate contribution of all buildings in the city.*/
int City::get_population_growth_rate() const
{
    int population_growth_rate = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                population_growth_rate += grid[i][j]->get_population_growth_rate_contribution();
            }
        }
    }
    return population_growth_rate;
}

/*Returns a pointer to the building at the grid cell specified by the coordinates.
 *Return nullptr if the cell has no buildings or the coordinates are out-of-bound.*/
Building *City::get_at(const Coordinates &coordinates) const
{
    if (is_out_of_bound(coordinates.x, coordinates.y, grid_size))
    {
        return nullptr; // the coordinates are out-of-bound
    }
    // For (x,y) coordinates, it refers to the grid cell grid[x][y].
    /*Returns a pointer to the building at the grid cell specified by the coordinates
     *Return nullptr if the cell has no buildings*/
    return grid[coordinates.x][coordinates.y];
}

/*Returns whether the grid cell specified by the coordinates is empty (has no buildings).
 *Return false if the coordinates are out-of-bound.*/
bool City::is_empty_at(const Coordinates &coordinates) const
{
    if (is_out_of_bound(coordinates.x, coordinates.y, grid_size) || // the coordinates are out-of-bound
        grid[coordinates.x][coordinates.y] == nullptr)              // the grid cell specified by the coordinates is empty (has no buildings)
    {
        return false;
    }
    return true;
}

/*CLINIC        = 1,    $50
 *HOSPITAL      = 2,    $500
 *SILVER_MINE   = 3,    $50
 *GOLD_MINE     = 4,    $400
 *HOUSE         = 5,    $50
 *APARTMENT     = 6     $300      0    1   2    3   4    5 */
const int cost_of_building[6] = {50, 500, 50, 400, 50, 300};
/*Returns the cost of the given type of building*/
inline int get_cost_of_building(const Building::Type &type)
{
    return cost_of_building[static_cast<int>(type) - 1];
}

/*Returns whether the city has enough budget to construct the given type of building.*/
bool City::can_construct(Building::Type type) const
{
    if (budget >= get_cost_of_building(type))
    {
        return true;
    }
    return false;
}

/*Returns whether the city has enough budget to construct the given type of building.
 *If coordinates are provided, also check whether the building can be constructed at the grid cell specified by the coordinates.
 *Return false if the coordinates are out-of-bound.*/
bool City::can_construct(Building::Type type, const Coordinates &coordinates) const
{
    // also check whether the building can be constructed at the grid cell specified by the coordinates
    if ((!is_out_of_bound(coordinates.x, coordinates.y, grid_size)) && // Return false if the coordinates are out-of-bound
        can_construct(type) &&
        grid[coordinates.x][coordinates.y] == nullptr) // The building can be constructed only if the cost does not exceed the budget and the grid cell has no buildings.
    {
        return true;
    }
    return false;
}

/*Constructs a building with the specified type at the grid cell specified by the coordinates.
 *If the building cannot be constructed (with reasons mentioned above), then return false.
 *Otherwise, construct the building by setting the grid pointer accordingly, decrease budget and register neighboring buildings.
 *For residential buildings, set the population to 0. Return true.*/
bool City::construct_at(Building::Type type, const Coordinates &coordinates)
{
    if (!can_construct(type, coordinates))
        return false; // If the building cannot be constructed (with reasons mentioned above), then return false.

    // Otherwise, construct the building by setting the grid pointer accordingly,
    if (type == Building::Type::CLINIC)
        grid[coordinates.x][coordinates.y] = new Clinic(*this);
    else if (type == Building::Type::HOSPITAL)
        grid[coordinates.x][coordinates.y] = new Hospital(*this);
    else if (type == Building::Type::SILVER_MINE)
        grid[coordinates.x][coordinates.y] = new SilverMine(*this);
    else if (type == Building::Type::GOLD_MINE)
        grid[coordinates.x][coordinates.y] = new GoldMine(*this);
    else if (type == Building::Type::HOUSE)
        grid[coordinates.x][coordinates.y] = new House(*this);
    else if (type == Building::Type::APARTMENT)
        grid[coordinates.x][coordinates.y] = new Apartment(*this);

    // decrease budget and register neighboring buildings.
    budget -= grid[coordinates.x][coordinates.y]->get_cost(); // decrease budget

    // register neighboring buildings
    if (!is_out_of_bound(coordinates.x + 1, coordinates.y, grid_size) && grid[coordinates.x + 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x + 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x + 1][coordinates.y]);
    }
    if (!is_out_of_bound(coordinates.x - 1, coordinates.y, grid_size) && grid[coordinates.x - 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x - 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x - 1][coordinates.y]);
    }
    if (!is_out_of_bound(coordinates.x, coordinates.y + 1, grid_size) && grid[coordinates.x][coordinates.y + 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y + 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y + 1]);
    }
    if (!is_out_of_bound(coordinates.x, coordinates.y - 1, grid_size) && grid[coordinates.x][coordinates.y - 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y - 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y - 1]);
    }
    return true;
}

/*Demolishes the building at the grid cell specified by the coordinates.
 *If the coordinates are out-of-bound or the grid cell is empty, return false.
 *Otherwise, demolish the building by setting the grid pointer accordingly and deregister neighboring buildings. Return true.*/
bool City::demolish_at(const Coordinates &coordinates)
{
    if ((is_out_of_bound(coordinates.x, coordinates.y, grid_size)) || // Return false if the coordinates are out-of-bound
        grid[coordinates.x][coordinates.y] == nullptr)                // grid cell is empty
        return false;

    /*deregister neighboring buildings*/
    if (!is_out_of_bound(coordinates.x + 1, coordinates.y, grid_size) && grid[coordinates.x + 1][coordinates.y] != nullptr)
        grid[coordinates.x + 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x - 1, coordinates.y, grid_size) && grid[coordinates.x - 1][coordinates.y] != nullptr)
        grid[coordinates.x - 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x, coordinates.y + 1, grid_size) && grid[coordinates.x][coordinates.y + 1] != nullptr)
        grid[coordinates.x][coordinates.y + 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x, coordinates.y - 1, grid_size) && grid[coordinates.x][coordinates.y - 1] != nullptr)
        grid[coordinates.x][coordinates.y - 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);

    delete grid[coordinates.x][coordinates.y];
    grid[coordinates.x][coordinates.y] = nullptr;
    return true;
}

/*Proceeds to next turn by following the steps in Game Mechanics.*/
void City::move_to_next_turn()
{
    /*1. The turn number of the city is increased by one.*/
    turn++;
    /*2. The budget of the city is increased by the sum of revenue generated by all Revenue buildings*/
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                budget += grid[i][j]->get_revenue();
            }
        }
    }
    /*3. The population is increased by the following steps*/

    /*The new population does not affect population population of other buildings.
     *You need to save the population growth of each Residential building and apply them in a batch.*/
    int **population_growth = new int *[grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        population_growth[i] = new int[grid_size]{};
    }

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                population_growth[i][j] = grid[i][j]->get_population_growth();
            }
        }
    }

    /*For each Residential building, the population is increased (or decreased) by its population growth.*/
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] != nullptr)
            {
                grid[i][j]->increase_population(population_growth[i][j]);
            }
        }
    }

    for (int i = 0; i < grid_size; i++)
    {
        delete[] population_growth[i];
        population_growth[i] = nullptr;
    }
    delete[] population_growth;
    population_growth = nullptr;
}