#include"Flight.cpp"
#include"Airports.cpp"

class allFlights{
public:
    vector<vector<Flight*>> adj; //out-adjacency list

    allFlights(int n){
        //n is number of cities (airports)
        vector<Flight*> temp;
        for (int i=0; i<n+1; i++) {
            adj.push_back(temp); //1-indexed
        }
    }

    void addFlight(Flight* f){
        int src = f->src;

        adj[src].push_back(f);
    }

    void printADJ(){
        for (int i=1; i<adj.size(); i++){

            cout<<i<<"\n";

            for (int j=0; j<adj[i].size(); j++){

                cout<<adj[i][j]->dst<<" "<<adj[i][j]->dep<<" "<<adj[i][j]->arr<<" "<<adj[i][j]->cost<<endl;
            }
        }
    }

    int cheapest(int src, int dst, int t1, int t2, Airports* airp){

        //return fare of cheapest trip starting at src on or after t1, reaching dst on or before t2

        int n = adj.size();

        vector<int> temp(1441, -1); //24*60 = 1440
        vector<vector<int>>dp (n, temp);//dp[src][t1] = cost of reaching dst on or before t2 if you start at src on or after t1

        int cost = findCost(src, dst, t1, t2, dp, airp); //start at source after t1, reach ast dest before t2

        if (cost == INT_MAX) return -1;

        return cost;
    }

    int findCost(int src, int dst, int t1, int t2, vector<vector<int>> &dp, Airports* airp){

        //Shortes path property does not hold true in case of calculating min_cost
        //We will have to check all possible paths that satisfy constraints
        //Dynamic Programing

        int cost = INT_MAX;

        if (dp[src][t1] != -1) return dp[src][t1];

        for (int i=0; i<adj[src].size(); i++){

            if (adj[src][i]->dep < t1 || adj[src][i]->arr > t2) continue; //ignore these flights

            if (adj[src][i]->dst == dst) cost = min(cost, adj[src][i]->cost);
            else{

                int temp_cost = adj[src][i]->cost;

                int x = findCost(adj[src][i]->dst, dst, adj[src][i]->arr + airp->wait(src), t2, dp, airp); //airp->wait(src) is transit time

                if (x == INT_MAX) temp_cost = INT_MAX;
                else temp_cost += x;

                cost = min(cost, temp_cost);
            }
        }

        return dp[src][t1] = cost;
    }

    int min_time(int src, int dst, int t1, Airports* airp){

        //returns earliest time (in min) you can reach at dst airport, if starting from src on or after t1
        //Single Source Shortest Path property holds true
        //Dijkstra's Algorithm

        int n = adj.size();
        vector<int> d(n, INT_MAX);

        set<pair<int, int>> st; //{d[i], i} where i is an airport

        d[src] = 0;

        for (int i=1; i<=n; i++){
            st.insert({d[i], i});
        }

        while(!st.empty()){

            int v = (*st.begin()).second;

            st.erase(st.begin());

            if (d[v] == INT_MAX) continue;

            for (int i=0; i<adj[v].size(); i++){

                if (adj[v][i]->dep < t1) continue;

                if (adj[v][i]->dep < d[v] + airp->wait(v)) continue;

                //int flight_time = adj[v][i]->arr - adj[v][i]->dep;

                int new_time =  adj[v][i]->arr;

                if (new_time < d[adj[v][i]->dst]){

                    st.erase({d[adj[v][i]->dst], adj[v][i]->dst});

                    d[adj[v][i]->dst] = new_time;

                    st.insert({d[adj[v][i]->dst], adj[v][i]->dst});
                }
            }
        }

        if (d[dst] == INT_MAX) return -1;

        return d[dst];
    }
  
};