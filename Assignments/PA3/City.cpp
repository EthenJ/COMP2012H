#include "City.h" /*City.cpp*/

/*Creates a new City.
 *Allocate the 2D array of grid cells with dimensions size by size.
 *Set all grid cells to nullptr.
 *Set grid size accordingly.
 *Set turn to 1.
 *Initially, the budget is $150. size is always greater than or equal to 1.*/
City::City(int size)
{
    /*Allocate the 2D array of grid cells with dimensions size by size.*/
    grid = new Building **[size];
    for (int i = 0; i < size; i++)
    {
        grid[i] = new Building *[size];
        /*Set all grid cells to nullptr*/
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = nullptr;
        }
    }
    grid_size = size; // Set grid size accordingly.
    turn = 1;         // Set turn to 1.
    budget = 1;       // Initially, the budget is $150.
}

/*Loads a city from the file filename. See Save File Format for the format of the save file.
 *You can assume the file always exists and the format is correct.
 *You can make use of the >> operator.
 *Don't forget to set neighbors when adding buildings to the city.*/
City::City(const std::string &filename)
{
}

City::~City()
{
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
            }
        }
        delete[] grid[i];
    }
    delete[] grid;
}

/*Saves the city to a file such that it can be loaded later.
 *If the file already exists, overwrite existing content. You can make use of the << operator.*/
void City::save(const std::string &filename) const
{
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

/*Check whether the provided coordinates are out-of-bound*/
inline bool is_out_of_bound(const int &x, const int &y, const int &size)
{
    if (x < 0 || x >= size || y < 0 || y >= size)
    {
        return true; // the coordinates are out-of-bound
    }
    return false;
};

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
    return cost_of_building[int(type) - 1];
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
    if (!is_out_of_bound(coordinates.x + 1, coordinates.y, grid_size))
        grid[coordinates.x + 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x - 1, coordinates.y, grid_size))
        grid[coordinates.x - 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x, coordinates.y + 1, grid_size))
        grid[coordinates.x][coordinates.y + 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x, coordinates.y - 1, grid_size))
        grid[coordinates.x][coordinates.y - 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
    return true;
}

/*Demolishes the building at the grid cell specified by the coordinates.
 *If the coordinates are out-of-bound or the grid cell is empty, return false.
 *Otherwise, demolish the building by setting the grid pointer accordingly and deregister neighboring buildings. Return true.*/
bool City::demolish_at(const Coordinates &coordinates)
{
    if ((is_out_of_bound(coordinates.x, coordinates.y, grid_size)) && // Return false if the coordinates are out-of-bound
        grid[coordinates.x][coordinates.y] == nullptr)                // grid cell is empty
        return false;

    /*deregister neighboring buildings*/
    if (!is_out_of_bound(coordinates.x + 1, coordinates.y, grid_size))
        grid[coordinates.x + 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x - 1, coordinates.y, grid_size))
        grid[coordinates.x - 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x, coordinates.y + 1, grid_size))
        grid[coordinates.x][coordinates.y + 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    if (!is_out_of_bound(coordinates.x, coordinates.y - 1, grid_size))
        grid[coordinates.x][coordinates.y - 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);

    delete grid[coordinates.x][coordinates.y];
    grid[coordinates.x][coordinates.y] = nullptr;
    return true;
}

/*Proceeds to next turn by following the steps in Game Mechanics.*/
void City::move_to_next_turn()
{
}