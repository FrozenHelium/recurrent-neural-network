#pragma once

#include <random>


class RandomNumber
{
public:
    static float Get()
    {
        return RandomNumber::distribution(RandomNumber::engine);
    }
private:
    static std::random_device randomDevice;
    static std::default_random_engine engine;
    static std::uniform_real_distribution<float> distribution;
};

std::random_device RandomNumber::randomDevice;
std::default_random_engine RandomNumber::engine(RandomNumber::randomDevice());
std::uniform_real_distribution<float> RandomNumber::distribution;

#define RANDOM_NUM    RandomNumber::Get()
#define RANDOM_VALUE  RandomNumber::Get()