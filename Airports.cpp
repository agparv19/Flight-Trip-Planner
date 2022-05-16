#include <bits/stdc++.h>
using namespace std;

class Airports{
    //class contains waiting time of all airports
private:
    unordered_map<int, int> waitingTime;
public:
    Airports(){}
    void addAirport(int airport_num, int time){

        waitingTime[airport_num] = time;
    }

    int wait(int airport_num){

        if (waitingTime.find(airport_num) == waitingTime.end()){
            return INT_MAX;
        }

        return waitingTime[airport_num];
    }
};