//
// Created by Alexander Krajči on 28/05/2022.
//

#pragma once
template <typename objectType, typename resultType>
class Criterion {
public:
    virtual  resultType evaluate(const objectType &data) = 0;
    virtual ~Criterion() = default;
};
