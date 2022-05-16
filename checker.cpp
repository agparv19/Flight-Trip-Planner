#include <bits/stdc++.h>
using namespace std;

#include"allFlights.cpp"


int getTime(string &word){
    //2104, 0045
    //return time in minutes
    //x1 x2 x3 x4

    int hour = stoi(word.substr(0,2));
    int min = stoi(word.substr(2));

    return hour*60 + min;
}

int main(){
    
    fstream file;
    string word;
    string filename = "data_and_queries.txt";
    file.open(filename.c_str());

    int i = 0;

    allFlights* all = NULL;
    Airports* airp = NULL;

    int tc = 0; //total cities
    int tf = 0; //total flight
    int tq = 0; //total queries for cheapest flight
    int tqt = 0; //total queries for minimum time

    while(file >> word){
        
        if (i == 0){
            tc = stoi(word);
            all = new allFlights(tc);
            airp = new Airports();
            
        }
        else if (i > 0 && i<=tc){
            
            int x = 2;
            int city;
            int wait_time;

            do{

                if (x==2) city = stoi(word);
                else wait_time = getTime(word);

                x--;

            }while(x>0 && file >> word);

            airp->addAirport(city, wait_time);
            
        }
        else if (i == tc+1){
            tf= stoi(word);
            
        }
        else if (i>tc+1 && i<= tc+tf+1){

            int x = 6;
            int src;
            int dst;
            int dep;
            int arr;
            int cost;
            string fnum;
            
            do{

                if (x == 6) src = stoi(word);
                else if (x == 5) dst = stoi(word);
                else if (x == 4) dep = getTime(word);
                else if (x == 3) arr = getTime(word);
                else if (x == 2) fnum = word;
                else if (x == 1) cost = stoi(word);

                x--;

            }while(x>0 && file >> word);

            Flight* f = new Flight(src, dst, dep, arr, cost, fnum);
            
            all->addFlight(f);

        }
        else if (i == tc+tf+2){
            tq = stoi(word);
            
        }
        else if (i>tc+tf+2 && i<=tc+tf+2+tq){
            int x = 4;
            int A;
            int B;
            int t1;
            int t2;

            do{
                if (x == 4) A = stoi(word);
                else if (x == 3) B = stoi(word);
                else if (x == 2) t1 = getTime(word);
                else if (x == 1) t2 = getTime(word);

                x--;

            }while(x>0 && file >> word);

            cout<<all->cheapest(A, B, t1, t2, airp)<<endl; //prints fare of cheapest trip
        }
        else if (i == tc+tf+tq+3){
            tqt = stoi(word);
            cout<<endl;
        }
        else{
            int x = 3;
            int A;
            int B;
            int t1;

            do{
                if (x == 3) A = stoi(word);
                else if (x == 2) B = stoi(word);
                else if (x == 1) t1 = getTime(word);

                x--;

            }while(x>0 && file >> word);

            cout<<all->min_time(A, B, t1, airp)<<endl; //print the earliest time you can reach airport B
        }

        i++;
        
    }

    //all->printADJ();

    
}