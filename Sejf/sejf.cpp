#include <iostream>
#include <bitset>
#include <string>

using namespace std;
bitset<20> changer(string doors, int size)
{
    bitset<20> result = 0b00000000000000000000;
    int size_xoxo = size;

    for (int i = 0; i < size; i++)
    {
        if (doors.at(size_xoxo - 1) == 'X')
            result.set(i, true);
        size_xoxo--;
    }
    return result;
}

void printer(bitset<20>* arr, int size, int picked, int doors)
{
    for (int i = 0; i < picked; i++)
    {
        for (int j = doors - 1; j > -1; j--)
        {
            if (arr[i][j] == true) {
                cout << "X";
            }
            else {
                cout << "o";
            }
        }
        cout << "\n";
    }
}

int counting_X(bitset<20>* arr, int i, int n)
{
    int result = 0;

    for (int j = 0; j < n; j++)
    {
        if (arr[j][i] == true)
        {
            result++;
        }
    }
    return result;
}

void sorting(bitset<20>*& locks_array, int n, int bit_position)
{
    bitset<20>* tmp_array = new bitset<20>[n];
    int o_index = counting_X(locks_array, bit_position, n);
    int x_index = 0;

    for (int i = 0; i < n; i++)
    {
        if (locks_array[i][bit_position] == 1)
        {
            tmp_array[x_index] = locks_array[i];
            x_index++;
        }
        else
        {
            tmp_array[o_index] = locks_array[i];
            o_index++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        locks_array[i] = tmp_array[i];
    }
    delete[] tmp_array;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, k, m;
    cin >> n >> k >> m;
    string buffer;

    if (n >= 1 && k >= 1 && n <= 10000000 && k <= 20 && m <= n)
    {
        bitset<20>* locks_array = new bitset<20>[n];

        for (int i = 0; i < n; i++)
        {
            cin >> buffer;
            locks_array[i] = changer(buffer, k);
        }

        for (int i = 0; i < k; i++)
        {
            sorting(locks_array, n, i);
        }

        printer(locks_array, n, m, k);
        delete[] locks_array;
    }
}