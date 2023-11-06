#include <iostream>
#include <algorithm>
using namespace std;

bool previously_found;

struct Building
{
    int x1;
    int y1;
    int x2;
    int y2;
};

void printer(Building* buildings, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << buildings[i].x1 << " " << buildings[i].y1 << " " << buildings[i].x2 << " " << buildings[i].y2 << endl;
    }
}

bool comp_X1(Building first, Building second) { return first.x1 < second.x1; }
bool comp_Y1(Building first, Building second) { return first.y1 < second.y1; }

int split_point_x(Building* buildings, int start, int end)
{
    int x_split_id = -1;
    int i = 0;
    int max_x2 = buildings[start].x2;
    if (start != end)
    {
        for (i = start; i < end - 1; i++)
        {
            if (buildings[i].x2 > max_x2)
            {
                max_x2 = buildings[i].x2;
            }
            if (buildings[i + 1].x1 >= max_x2)
            {
                x_split_id = i;
                break;
            }
        }
    }
    return x_split_id + 1;
}

int split_point_y(Building* buildings, int start, int end)
{
    int y_split_id = -1;
    int i = 0;
    int max_y2 = buildings[start].y2;
    for (i = start; i < end - 1; i++)
    {
        if (buildings[i].y2 > max_y2)
        {
            max_y2 = buildings[i].y2;
        }
        if (buildings[i + 1].y1 >= max_y2)
        {
            y_split_id = i;
            break;
        }
    }
    return y_split_id + 1;
}
bool sorting_y(Building* buildings, int start, int end);
bool sorting_x(Building* buildings, int start, int end)
{
    if (end - start < 4) return true;//4 bo podzia³ dla 2 i 3 budynków bêdzie zawsze mo¿liwy

    sort(buildings + start, buildings + end, comp_X1);

    int split_x = split_point_x(buildings, start, end);

    if (split_x != 0) {
        previously_found = true;
        return sorting_y(buildings, start, split_x) && sorting_x(buildings, split_x, end);
    }
    else {
        if (previously_found) {
            previously_found = false;
            return sorting_y(buildings, start, end);
        }
        else {
            return false;
        }
    }
}

bool sorting_y(Building* buildings, int start, int end)
{
    if (end - start < 4) return true;//4 bo podzia³ dla 2 i 3 budynków bêdzie zawsze mo¿liwy

    sort(buildings + start, buildings + end, comp_Y1);

    int split_y = split_point_y(buildings, start, end);

    if (split_y != 0) {
        previously_found = true;
        return sorting_x(buildings, start, split_y) && sorting_y(buildings, split_y, end);
    }
    else {
        if (previously_found == true) {
            previously_found = false;
            return sorting_x(buildings, start, end);
        }
        else {
            return false;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    cin >> t;
    int n;

    for (int i = 0; i < t; ++i)
    {
        cin >> n;
        if (n >= 1 && n <= 1000)
        {
            Building* buildings = new Building[n];
            for (int j = 0; j < n; j++)
            {
                cin >> buildings[j].x1 >> buildings[j].y1 >> buildings[j].x2 >> buildings[j].y2;
            }
            previously_found = true;
            if (sorting_x(buildings, 0, n) == true) {
                cout << "TAK\n";
            }
            else {
                cout << "NIE\n";
            }

            delete[] buildings;
        }
    }
}