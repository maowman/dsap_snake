#include "CustomController.h"
#include "DirectionType.h"
#include "Position.h"
#include "StraightForwardController.h"

#define pi 3.14159265358979323846
#include <iostream>
#include <cmath>

inline float getLength(Position p)
{
    return std::abs(std::pow(p.x, 2) + std::pow(p.y, 2));
}

inline float dot(Position a, Position b)
{
    return a.x * b.x + a.y * b.y;
}

inline float cross(Position a, Position b)
{
    return a.x * b.y - a.y * b.x;
}

float getWeight(Position snakePosition, Position snakeDirection, Position foodPosition)
{
    float distance = getLength(snakePosition - foodPosition);
    float deltaTheta = std::asin(cross(snakeDirection, foodPosition - snakePosition) / distance);
    if (abs(deltaTheta) > pi / 2)
    {
        return 0;
    }
    return 2000 * deltaTheta / (std::pow(distance, 0.45) * (std::pow(std::log(distance), 1)));
}

DirectionType
CustomController::NextDirection(const Game &game, size_t id)
{
    float kP = 1, kD = 0, kW = -50, dangerDistance = 200;
    // std::cout << "gamemode: " << id << std::endl;
    auto self = game.Snakes().at(id);
    double error = 0, lastError = 0;
    for (auto food : game.Foods())
    {
        error += getWeight(self.Head(), self.Forward(), food);
    }

    std::vector<Position> walls = {Position{0, self.Head().y},
                                   Position{(float)game.FieldWidth(), self.Head().y},
                                   Position{self.Head().x, 0},
                                   Position{self.Head().x, (float)game.FieldHeight()}};
    for (auto wall : walls)
    {
        if (getLength(wall - self.Head()) < dangerDistance)
        {
            error += kW * getWeight(self.Head(), self.Forward(), wall);
        }
    }

    // std::cout << "Error= " << error << std::endl;
    DirectionType nxtStep;
    double output = error * kP + (error - lastError) * kD;
    if (std::abs(output) < 0.01)
    {
        nxtStep = DirectionType::kForward;
    }
    else
    {
        if (output > 0)
        {
            nxtStep = DirectionType::kRight;
        }
        else
        {
            nxtStep = DirectionType::kLeft;
        }
    }
    lastError = error;
    return nxtStep;
}

/*
get data from game
1. Get current location
2. Get current snake direction
3. Get food location
4.

first consider gamemode 0 -> 1. fixed path

kill other snake?

*/
