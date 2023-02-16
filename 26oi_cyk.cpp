#include <bits/stdc++.h>
#include "cyklib.hpp"

using namespace std;

bool too_long(long long A, long long B, long long C)
{
    if(A == C) return false;
    return ((A > B) + (B > C) + (A > C))%2;
}

int main(void)
{
    long long x = circular_shift(0), // current after shifts
        prev = x,
        next = circular_shift(1);

    int shift = 1;
    while((prev >= x && next > x && prev < next) || (next < x && (prev < next || prev >= x))){
        prev = next;
        next = circular_shift(shift);
        shift <<= 1;
    }

    x = next;
    int len = 0;
    while(shift != 1){
        long long A = x, B = circular_shift((shift+len)/2), C = circular_shift((shift+len)/2);
        if(!too_long(A, B, C)) len += shift;

        x = C;
        shift >>= 1;
    }
    if(len == 0 || x != circular_shift(len)) // dla shift == 1 (czyli ostatniego porownania) sprawdzamy, czy dla mniejszej wartosci sie zgadza
        len++; // (jesli nie, to ta wieksza bedzie rozwiazaniem)

    give_answer(len);
}
