//
// Created by Alexander Krajči on 28/05/2022.
//
#include "../UzemneJednotky/Obec.h"
#pragma once


class Filter {
public:
    virtual bool pass(const structures::Obec& data) = 0;
    virtual ~Filter() = default;
};