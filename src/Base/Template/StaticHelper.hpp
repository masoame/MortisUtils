#pragma once
#include<utils.hpp>

namespace Mortis
{
    class StaticHelper 
    {
        StaticHelper() = delete;
        StaticHelper(const StaticHelper&) = delete;
        StaticHelper& operator=(const StaticHelper&) = delete;
        StaticHelper(StaticHelper&&) = delete;
        StaticHelper& operator=(StaticHelper&&) = delete;
    };
}