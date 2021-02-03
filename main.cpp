#include <iostream>
#include <bits/stdc++.h>
#define MP make_pair
//typedef pair<node,int> pni;

using namespace std;
typedef pair<int,int> pii;
typedef pair<char,int> pci;

class Graph{
    map<char,vector<pci> >adj_list;
    map<char,int>Nodes;
public:
    void get_node_values(vector<pci>values);
    void add_edge(char src, char dest, int edge_wt);
    void print_graph();
    void A_star_search(char initial, char goal);
    int find_heuristic_value(int path_val, int g_val, int h_val);
};

void Graph::get_node_values(vector<pci>values){//adds weights to each node
    for(int i=0;i<values.size();i++){
        Nodes[values[i].first]=values[i].second;
    }
}
void Graph::print_graph(){
    cout<<"graph has the following edges:\n\n";
    map<char,vector<pair<char,int> > >::iterator it;
    for(it=adj_list.begin();it!=adj_list.end();it++){
        cout<<(it->first)<<" :\n";
        for(int j=0;j<(it->second).size();j++){
            cout<<"  -- "<< (it->second)[j].second<<" --> "<<(it->second)[j].first<<"\n";
        }
        cout<<"\n";
    }
}
void Graph:: add_edge(char src, char dest, int edge_wt){
    adj_list[src].push_back(MP(dest,edge_wt));
    adj_list[dest].push_back(MP(src,edge_wt));
}
int Graph:: find_heuristic_value(int path_val, int g_val, int h_val){
    return(path_val+g_val+h_val);
}
void Graph::A_star_search(char init, char goal){
    cout<<"\n\nPath from "<<init<<" to "<<goal<<"\n";
    stack<char>s;
    s.push(init);
    int path_value = 0;
    while(s.top()!=goal){
        int minima = INT_MAX;
        int add_path_value=0;
        char next;
        for(int i=0;i<adj_list[s.top()].size();i++){
            char neighbour = adj_list[s.top()][i].first;
            int h_val = Nodes[neighbour];
            int g_val = adj_list[s.top()][i].second;
            int f_val = find_heuristic_value(path_value,g_val,h_val);
            if(minima>f_val){
                minima = f_val;
                add_path_value = g_val;
                next = neighbour;
            }
        }
        path_value+=add_path_value;
        s.push(next);
    }

    vector<char>path;
    while(!s.empty()){
        path.push_back(s.top());
        s.pop();
    }
    for(int i=path.size()-1;i>=0;i--){
        cout<<path[i];
        if(i!=0) cout<<"-->";
    }
    cout<<"\n";

}

int main()
{
    cout<<"Done by Tanya Gupta, UE183109\n\n";
    Graph g;
    vector<pci>Nodes;//stores the value of each node
    Nodes= {MP('A',10),MP('B',8),MP('C',5),MP('D',7),MP('E',3),MP('F',6),MP('G',5),MP('H',3),MP('I',1),MP('J',0)};
    g.get_node_values(Nodes);
    g.add_edge('A','B',6);
    g.add_edge('A','F',3);
    g.add_edge('B','C',3);
    g.add_edge('B','D',2);
    g.add_edge('C','D',1);
    g.add_edge('C','E',5);
    g.add_edge('D','E',8);
    g.add_edge('E','I',5);
    g.add_edge('E','J',5);
    g.add_edge('F','G',1);
    g.add_edge('F','H',7);
    g.add_edge('G','I',3);
    g.add_edge('H','I',2);
    g.add_edge('I','J',3);
    g.print_graph();
    g.A_star_search('A','J');
    return 0;
}
