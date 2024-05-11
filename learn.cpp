#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

template <typename T>
class Graph
{
public:
    unordered_map<T, list<T>> AdjList;
    void addEdge(T u, T v, bool direction)
    {
        if (direction == 1)
        {
            AdjList[u].push_back(v);
        }
        else
        {
            AdjList[u].push_back(v);
            AdjList[v].push_back(u);
        }
    }

    void Level_Order_Traversal(T src)
    {
        queue<T> pq;
        unordered_map<T, bool> visited;
        pq.push(src);
        visited[src] = true;
        while (!pq.empty())
        {
            T frontnode = pq.front();
            pq.pop();
            cout << frontnode << " ";

            for (T nbr : AdjList[frontnode])
            {
                if (!visited[nbr])
                {
                    pq.push(nbr);
                    visited[nbr] = true;
                }
            }
        }
    }

    void dfs(T src, unordered_map<T, bool> &visited)
    {
        visited[src] = true;
        cout << src << " ";
        for (T nbr : AdjList[src])
        {
            if (!visited[nbr])
            {
                dfs(nbr, visited);
            }
        }
    }

    bool Check_cycle_BFS(T src)
    {
        unordered_map<T, bool> visited;
        unordered_map<T, T> parent;
        queue<T> pq;
        pq.push(src);
        visited[src] = true;
        parent[src] = -1;
        while (!pq.empty())
        {
            T frontNode = pq.front();
            pq.pop();

            for (T nbr : AdjList[frontNode])
            {
                if (!visited[nbr])
                {
                    pq.push(nbr);
                    visited[nbr] = true;
                    parent[nbr] = frontNode;
                }
                else if (visited[nbr] == true && nbr != parent[frontNode])
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool solveusingDFS(T src, unordered_map<T, bool> &visited, int parent)
    {
        visited[src] = true;
        for (T nbr : AdjList[src])
        {
            if (!visited[nbr])
            {
                bool ans = solveusingDFS(nbr, visited, src);
                if (ans == true)
                {
                    return true;
                }
            }
            else if (visited[nbr] == true && nbr != parent)
            {
                return true;
            }
        }
        return false;
    }

    bool Detect_Cycle_In_Directed_Graph_Using_DFS(T src, unordered_map<int, bool> &visited, unordered_map<T, bool> &dfs, int parent)
    {
        visited[src] = true;
        dfs[src] = true;
        for (T nbr : AdjList[src])
        {
            if (!visited[nbr])
            {
                bool ans = Detect_Cycle_In_Directed_Graph_Using_DFS(nbr, visited, dfs, src);
                if (ans == true)
                {
                    return true;
                }
            }
            else if (visited[nbr] == true && dfs[nbr] == true)
            {
                return true;
            }
        }
        // BackTracking
        dfs[src] = false;
        return false;
    }
};

int main()
{
    Graph<int> g;
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 1);
    unordered_map<int, bool> vis;
    unordered_map<int, bool> dfs;
    bool ans = g.Detect_Cycle_In_Directed_Graph_Using_DFS(0, vis, dfs, -1);
    if (ans)
    {
        cout << "Cycle Present" << endl;
    }
    else
    {
        cout << "Cycle not present" << endl;
    }
    return 0;
}