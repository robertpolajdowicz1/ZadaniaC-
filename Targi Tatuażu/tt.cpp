#include <iostream>

using namespace std;

double calc_ratio(double x, int y) {

    double first = x / 5;
    double second = y / 1000;

    return (first * second);
}

class Artist {
public:
    int price;
    double ratio;
    int visited;
    string name;
    Artist* left;
    Artist* right;

    Artist(int, double, int, const string&);
};

Artist* best_ratio_artist = NULL;
int node_index = 0;
bool* index_visited;

Artist::Artist(int cost, double to_send, int index, const  string& nick)
{
    price = cost;
    ratio = to_send;
    visited = index;
    left = NULL;
    right = NULL;
    name = nick;
}

Artist* add_artist(Artist* root, int cost, double x, int index, const string& nick)
{
    if (!root) {

        return new Artist(cost, x, index, nick);
    }

    if (cost > root->price) {

        root->right = add_artist(root->right, cost, x, index, nick);
    }
    else if (cost == root->price) {

        if (root->ratio <= x) {

            root->right = add_artist(root->right, cost, x, index, nick);
        }
        else {
            root->left = add_artist(root->left, cost, x, index, nick);
        }
    }
    else {
        root->left = add_artist(root->left, cost, x, index, nick);
    }

    return root;
}

void search(Artist* root, int cost, double ratio)
{
    if (root == NULL) {
        return;
    }

    if (root->price == cost && root->ratio >= ratio && index_visited[root->visited] == false && root->ratio >= best_ratio_artist->ratio) {

        best_ratio_artist = root;
        search(root->right, cost, ratio);
        search(root->left, cost, ratio);
        return;
    }

    if (cost > root->price) {

        search(root->right, cost, ratio);
        return;
    }

    else if (root->price == cost) {

        search(root->right, cost, ratio);
        search(root->left, cost, ratio);
        return;
    }
    else {

        search(root->left, cost, ratio);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin >> n;
    index_visited = new bool[n];

    for (int i = 0; i < n; i++) {
        index_visited[i] = NULL;
    }
    Artist* root = NULL;

    for (int i = 0; i < n; i++)
    {
        char A_S;
        cin >> A_S;

        if (A_S == 'A') {

            double x_prm = -1.0;
            int y_prm = -1;
            int z_cost = -1;
            string s_nick = "";

            cin >> x_prm >> y_prm >> z_cost >> s_nick;
            double to_send = calc_ratio(x_prm, y_prm);

            if (i == 0) {

                root = add_artist(root, z_cost, to_send, node_index, s_nick);
                node_index++;
            }
            else {

                add_artist(root, z_cost, to_send, node_index, s_nick);
                node_index++;
            }
        }
        else {

            int b_money;
            double f_ratio;

            cin >> b_money >> f_ratio;
            best_ratio_artist = NULL;
            best_ratio_artist = new Artist(0, 0, -1, "");

            search(root, b_money, f_ratio);

            if (best_ratio_artist->visited != -1) {
                cout << best_ratio_artist->name << "\n";
                index_visited[best_ratio_artist->visited] = true;
            }
            else
            {
                cout << "-\n";
            }
        }
    }
    delete[] index_visited;
    return 0;
}