#include <bits/stdc++.h>
using namespace std;

class Flight{
public:
    int src;
    int dst;
    int dep;
    int arr;
    int cost;
    string fnum;

    Flight(int _src, int _dst, int _dep, int _arr, int _cost, string _fnum){

        src = _src;
        dst = _dst;
        dep = _dep;
        arr = _arr;
        cost = _cost;
        fnum = _fnum;
    }
};