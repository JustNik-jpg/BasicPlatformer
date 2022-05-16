//
// Created by JustNik on 16 May 2022.
//

#include <bitset>
#include <array>

#pragma once

constexpr std::size_t MAX_COMPONENTS = 32;

using Entity = std::uint32_t;
using ComponentID = std::uint32_t;
using Archetype = std::bitset<MAX_COMPONENTS>;

const Entity MAX_ENTITIES = 4096;
