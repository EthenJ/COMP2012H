#include <iostream>
#include <cstring>
#include "cleaning_robot.h"
using namespace std;

// Please do all your work in this file. You just need to submit this file.
int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   int return_value = 0;
   if (robot_x < 0 || robot_x >= MAP_WIDTH || robot_y < 0 || robot_y >= MAP_HEIGHT || robot_energy < 0 || map[robot_y][robot_x] == BLOCKED)
   {
      (target_x == -1 && target_y == -1) ? return_value = 0 : return_value = PA2_MAX_PATH;
   }
   else
   {
      char new_map[MAP_HEIGHT][MAP_WIDTH]{};
      copyMap(new_map, map);
      if (map[robot_y][robot_x] == CHARGER && robot_full_energy != -1)
      {
         robot_energy = robot_full_energy;
         new_map[robot_y][robot_x] = AVAILABLE;
      }
      else if (map[robot_y][robot_x] == ROBOT)
      {
         char empty_string[MAX_STRING_SIZE]{};
         strcpy(result_sequence, empty_string);
      }

      if ((target_x == -1 && target_y == -1) && temp_map[robot_y][robot_x] != VISITED)
      {
         temp_map[robot_y][robot_x] = VISITED;
         return_value = 1;
      }
      else if (robot_y == target_y && robot_x == target_x)
      {
         strcat(result_sequence, "T");
         return 1;
      }

      char up_sequence[MAX_STRING_SIZE]{};
      strcpy(up_sequence, result_sequence);
      strcat(up_sequence, "U");

      int up = findPathSequence(robot_x, robot_y - 1, target_x, target_y, robot_energy - 1, robot_full_energy, up_sequence, new_map, temp_map);
      char right_sequence[MAX_STRING_SIZE]{};
      strcpy(right_sequence, result_sequence);
      strcat(right_sequence, "R");

      int right = findPathSequence(robot_x + 1, robot_y, target_x, target_y, robot_energy - 1, robot_full_energy, right_sequence, new_map, temp_map);
      char down_sequence[MAX_STRING_SIZE]{};
      strcpy(down_sequence, result_sequence);
      strcat(down_sequence, "D");
      int down = findPathSequence(robot_x, robot_y + 1, target_x, target_y, robot_energy - 1, robot_full_energy, down_sequence, new_map, temp_map);

      char left_sequence[MAX_STRING_SIZE]{};
      strcpy(left_sequence, result_sequence);
      strcat(left_sequence, "L");
      int left = findPathSequence(robot_x - 1, robot_y, target_x, target_y, robot_energy - 1, robot_full_energy, left_sequence, new_map, temp_map);

      if (target_x == -1 && target_y == -1)
         return_value += up + down + left + right;
      else
      {
         return_value = 1 + min(min(up, right), min(down, left));
         if (return_value == up + 1)
            strcpy(result_sequence, up_sequence);
         else if (return_value == right + 1)
            strcpy(result_sequence, right_sequence);
         else if (return_value == down + 1)
            strcpy(result_sequence, down_sequence);
         else if (return_value == left + 1)
            strcpy(result_sequence, left_sequence);
      }
   }
   return return_value;
}

int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   char result_sequence[MAX_STRING_SIZE]{};
   return findPathSequence(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, result_sequence, map, temp_map);
}

int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   char new_map[MAP_HEIGHT][MAP_WIDTH]{};
   copyMap(new_map, result_map);
   return findShortestDistance(robot_x, robot_y, -1, -1, robot_energy, robot_full_energy, new_map, result_map);
}

int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, int &target_x, int &target_y, int robot_energy, int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   if (robot_x < 0 || robot_x >= MAP_WIDTH || robot_y < 0 || robot_y >= MAP_HEIGHT || robot_energy < 0 || map[robot_y][robot_x] == BLOCKED)
   {
      return -1;
   }

   int current = 0;

   if (map[robot_y][robot_x] == CHARGER)
   {
      target_x = robot_x, target_y = robot_y;
      current = findShortestDistance(robot_original_x, robot_original_y, robot_x, robot_y, robot_full_energy, -1, map, temp_map);
   }

   int up_x, up_y;
   int up = findFarthestPossibleCharger(robot_x, robot_y - 1, robot_original_x, robot_original_y, up_x, up_y, robot_energy - 1, robot_full_energy, map, temp_map);

   int right_x, right_y;
   int right = findFarthestPossibleCharger(robot_x - 1, robot_y, robot_original_x, robot_original_y, right_x, right_y, robot_energy - 1, robot_full_energy, map, temp_map);

   int down_x, down_y;
   int down = findFarthestPossibleCharger(robot_x, robot_y + 1, robot_original_x, robot_original_y, down_x, down_y, robot_energy - 1, robot_full_energy, map, temp_map);

   int left_x, left_y;
   int left = findFarthestPossibleCharger(robot_x + 1, robot_y, robot_original_x, robot_original_y, left_x, left_y, robot_energy - 1, robot_full_energy, map, temp_map);

   int farthest = max(max(max(up, right), max(down, left)), current);
   
   if (farthest == up)
      target_x = up_x, target_y = up_y;
   else if (farthest == right)
      target_x = right_x, target_y = right_y;
   else if (farthest == down)
      target_x = down_x, target_y = down_y;
   else if (farthest == left)
      target_x = left_x, target_y = left_y;

   return farthest;
}