#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<int>& visited, vector<int>& edges_to_vis, int n) {    
    queue<int> Q;
    Q.push(1);// zaczynane od pierwszego (ktory tez bedzie trzeba wypisac na koncu)
    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();
        for (int i : { 0,1 }) {
            int index = (10 * current + i) % n;// liczenie nowej reszty
            if (visited[index] == -1) {// jesli nowa reszta nie odwiedzona 
                visited[index] = current;
                edges_to_vis[index] = i;
                Q.push(index);// aby rozwazyc pozniej
            }
        }   
    }
}

void print_the_shortest(vector<int>& visited, vector<int>& edges_to_vis) {
    vector<int> the_shortest;
    
    int current = 0;
    while (current != 1) {
        the_shortest.push_back(edges_to_vis[current]);
        current = visited[current];
    }
    the_shortest.push_back(1);
    
    for (int i = the_shortest.size()-1; i >= 0; --i)
        cout << the_shortest[i];
    cout << '\n';
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;// liczba ktorej wielokrotnosc jest szukana
        cin >> n;
        
        vector<int> visited(n, -1);// zawiera poprzedzajace reszty
        vector<int> edges_to_vis(n, -1);// zawiera krawedzie do tych poprzedzajacych reszt

        bfs(visited, edges_to_vis, n);
        print_the_shortest(visited, edges_to_vis);
    }
}
