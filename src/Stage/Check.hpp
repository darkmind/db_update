// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Stage.hpp"

#include <memory>

class Check : public Stage
{
public:
    Check();

    bool run() override;
private:

    void check_schema();

    bool success;

//    std::size_t counter;
};

