#pragma once

#include "config.h"
#include <random>
#include <memory>
#include <chrono>

template<typename T>
class RandomGenerator
{
public:
    explicit RandomGenerator(const std::vector<T>& elements) : elements_(elements)
    {
        engine_.seed(std::chrono::system_clock::now().time_since_epoch().count());
        distribution_ = std::make_unique<std::uniform_int_distribution<unsigned>>(0, elements.size() - 1);
    }

    T operator()()
    {
        return elements_.at((*distribution_)(engine_));
    }

private:
    std::default_random_engine engine_;
    std::unique_ptr<std::uniform_int_distribution<unsigned>> distribution_;

    const std::vector<T>& elements_;
};
