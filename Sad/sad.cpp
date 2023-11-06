#include <iostream>

using namespace std;

int search_max_amount(int* array, int m)
{
    int i;
    int max = array[0];
    for (i = 1; i < m; i++)
        if (array[i] > max)
        {
            max = array[i];
        }
    return max;
}
int searcha_max_index(int* array, int m)
{
    int i;
    int max = array[0];
    int max_i = 0;
    for (i = 1; i < m; i++)
        if (array[i] > max)
        {
            max = array[i];
            max_i = i;
        }
    return max_i;
}
int max_of_three(int first, int second, int third)
{
    if (first >= second && first >= third)
    {
        return first;
    }
    else if (second >= first && second >= third)
    {
        return second;
    }
    else
    {
        return third;
    }
}
int find_max(int indeks_j, int* row_up, int row_size)
{
    if (indeks_j == 0)
    {
        if (row_size == 1)
        {
            return row_up[indeks_j];
        }
        else
        {
            return max_of_three(0, row_up[indeks_j], row_up[indeks_j + 1]);
        }
    }
    else if (indeks_j == row_size - 1)
    {
        return max_of_three(row_up[indeks_j - 1], row_up[indeks_j], 0);
    }
    else
    {
        return max_of_three(row_up[indeks_j - 1], row_up[indeks_j], row_up[indeks_j + 1]);
    }
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int* row_now = new int[m];
    int* row_up = new int[m];
    if (n >= 1 && n <= 10000 && m >= 1 && m <= 1000)
    {
        for (int i = 0;i < n;++i)
        {
            for (int j = 0;j < m;++j)
            {
                if (i == 0) {
                    cin >> row_now[j];
                }
                else {
                    int tmp;
                    cin >> tmp;
                    row_now[j] = tmp + find_max(j, row_up, m);
                }
            }
            for (int k = 0;k < m;++k)
            {
                row_up[k] = row_now[k];
            }
        }
    }
    cout << searcha_max_index(row_up, m) << " " << search_max_amount(row_up, m);
    delete[] row_now;
    delete[] row_up;
}