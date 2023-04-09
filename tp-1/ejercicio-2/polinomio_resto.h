//
// Created by luli on 09/04/23.
//

#ifndef TP_1_POLINOMIO_RESTO_H
#define TP_1_POLINOMIO_RESTO_H

#include <vector>
#include <math.h>
#include <iostream>
#include <tuple>
using namespace std;

int mod(int x, int m);
bool combinacion_con_resto(int i, int k, int* v, tuple<bool, bool>** M);
bool combinacion_con_resto_bottom_up(int* v);


#endif //TP_1_POLINOMIO_RESTO_H
