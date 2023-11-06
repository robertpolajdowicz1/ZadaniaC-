#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<double, int> diPair;
double money = 100000.0;
bool flag = false;

void add_edge(vector <pair<double, int> > adj_list[], int vertex_1, int vertex_2, double weight) {

    adj_list[vertex_1].push_back(make_pair(weight, vertex_2));
    adj_list[vertex_2].push_back(make_pair(weight, vertex_1));
}

vector<double> lowest_Provisions(vector<pair<double, int> > adj[], int V, int src, double money)
{
    priority_queue< diPair, vector <diPair>, less<diPair> > pq;

    vector<double> dist(V, 0.0);
    vector<bool> visited(V, false);

    pq.push(make_pair(1, src));

    if (!flag) {
        dist[src] = money;
        flag = true;
    }
    else {
        dist[src] = 1.0;
    }

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        visited[u] = true;

        for (auto x : adj[u])
        {
            int v = x.second;
            double weight = x.first;

            if (visited[v] == false && dist[v] < dist[u] * weight)
            {
                dist[v] = dist[u] * weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

double choose(bool* isBajtCoin, vector<double> options1, vector<double> options2) {

    double result = 0.0;

    for (int i = 0; i < options1.size(); i++)
    {
        if (isBajtCoin[i])
        {
            if (options1[i] * options2[i] > result)
            {
                result = options1[i] * options2[i];
            }
        }
    }
    return result;
}

void calculations(double min_prov) {
    min_prov = min_prov * (double)1.2;
    cout << min_prov << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    //moje zmienne
    vector<double> first_prov_vec;
    vector<double> second_prov_vec;
    double min_prov = 0.0;

    //iloœæ gie³d i status posiadania BajtCoina
    int x_stocks;
    cin >> x_stocks;
    bool* isBajtCoin = new bool[x_stocks];

    for (int i = 0; i < x_stocks; i++) { cin >> isBajtCoin[i]; }

    //iloœæ krawêdzi i wrzucenie ich do list
    int n_Edges;
    cin >> n_Edges;
    vector<diPair>* adj_list_w1 = new vector<diPair>[n_Edges];
    vector<diPair>* adj_list_w2 = new vector<diPair>[n_Edges];

    for (int i = 0; i < n_Edges; i++)
    {
        int v1, v2;
        double w1, w2;
        cin >> v1 >> v2 >> w1 >> w2;
        add_edge(adj_list_w1, v1, v2, 1.0 - w1);
        add_edge(adj_list_w2, v1, v2, 1.0 - w2);
    }

    //gie³da wiod¹ca
    int m_stock_market;
    cin >> m_stock_market;

    //szukanie najlepszej drogi
    first_prov_vec = lowest_Provisions(adj_list_w1, x_stocks, m_stock_market, money);
    second_prov_vec = lowest_Provisions(adj_list_w2, x_stocks, m_stock_market, money);

    min_prov = choose(isBajtCoin, first_prov_vec, second_prov_vec);

    calculations(min_prov);

    delete[] adj_list_w1;
    delete[] adj_list_w2;
    delete[] isBajtCoin;
}