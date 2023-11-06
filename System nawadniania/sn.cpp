#include <iostream>

using namespace std;

int min_global_cost;

void finding_lowest_cost(int* style_array, int* cost_array, int n, int current_index, int current_style, int current_cost, bool flag)
{

    if (current_cost >= min_global_cost)
    {
        return;
    }
    if (current_style == 0 && current_cost < min_global_cost && flag == true)
    {
        min_global_cost = current_cost;
        return;
    }
    if (current_index >= n)
    {
        return;
    }

    finding_lowest_cost(style_array, cost_array, n, current_index + 1, current_style, current_cost, flag);
    finding_lowest_cost(style_array, cost_array, n, current_index + 1, current_style + style_array[current_index], current_cost + cost_array[current_index], true);

}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string NO_banner = "NIE\n";
    int t;
    int n;

    cin >> t;
    if (1 <= t && t <= 10)
    {
        for (int i = 0; i < t; i++)
        {
            min_global_cost = 2147483647;
            cin >> n;
            if (1 <= n && n <= 100)
            {
                int* style_array = new int[n];
                int* cost_array = new int[n];

                for (int j = 0; j < n; j++)
                {
                    cin >> style_array[j] >> cost_array[j];
                }

                finding_lowest_cost(style_array, cost_array, n, 0, 0, 0, false);
                if (min_global_cost != 2147483647)
                {
                    cout << min_global_cost << "\n";
                }
                else {
                    cout << NO_banner;
                }
                delete[] style_array;
                delete[] cost_array;
            }
        }
    }
}