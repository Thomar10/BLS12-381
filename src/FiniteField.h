//
// Created by tlux- on 30-05-2022.
//
#pragma once
#ifndef BLS12_381_FINITEFIELD_H
#define BLS12_381_FINITEFIELD_H

template<typename T>
class FiniteField {

    virtual T operator+(const T &rhs) = 0;

    virtual T operator-(const T &rhs) = 0;

    virtual T operator*(const T &rhs) = 0;

    virtual bool operator==(const T &rhs) const = 0;

};


#endif //BLS12_381_FINITEFIELD_H
