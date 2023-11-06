#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>


using namespace std;

struct Point {
    int x;
    int y;
    double alfa;
    double r;
};

bool compareAlfaR(Point first, Point second) {
    if (first.alfa > second.alfa) return true;
    if (first.alfa < second.alfa) return false;
    if (first.r > second.r) return true;
    if (first.r < second.r) return false;
    return false;
}

bool isAlfaEqual(Point first, Point second) {
    return first.alfa == second.alfa;
}

double detMatrix(int p1x, int p2x, int p3x, int p1y, int p2y, int p3y) {
    return  (1 * p2x * p3y) + (1 * p3x * p1y) + (1 * p1x * p2y) - (1 * p2x * p1y) - (1 * p1x * p3y) - (1 * p3x * p2y);
}

void dealWithMess(vector <Point>& v, Point p, int n) {
    for (int i = 0; i < n; i++) {
        v[i].alfa = atan2(v[i].y - p.y, v[i].x - p.x);
        v[i].r = sqrt(((v[i].x - p.x) * (v[i].x - p.x)) + ((v[i].y - p.y) * (v[i].y - p.y)));
    }
    sort(v.begin(), v.end(), compareAlfaR);
    v.erase(unique(v.begin(), v.end(), isAlfaEqual), v.end());
}

double addArea(Point tmp_point, Point tmp_point2) {
    double third_r = sqrt(((tmp_point.x - tmp_point2.x) * (tmp_point.x - tmp_point2.x)) + ((tmp_point.y - tmp_point2.y) * (tmp_point.y - tmp_point2.y)));
    double tmp_area = (tmp_point.r + tmp_point2.r + third_r) / 2;
    return sqrt(tmp_area * (tmp_area - tmp_point.r) * (tmp_area - tmp_point2.r) * (tmp_area - third_r));
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    double det;
    double area = 0.0;
    Point p;
    Point tmp_point;
    Point tmp_point2;
    vector<Point> vectorPoints;
    stack<Point> stackPoints;
    //wczytujemy dane i od razu szukamy min y, przy równym y min x
    for (int i = 0; i < n; i++) {

        if (i == 0) {
            cin >> p.x >> p.y;
        }
        else {

            cin >> tmp_point.x >> tmp_point.y;

            if (tmp_point.y < p.y) {

                vectorPoints.push_back(p);
                p = tmp_point;

            }
            else if (tmp_point.y == p.y) {
                if (tmp_point.x < p.x) {

                    vectorPoints.push_back(p);
                    p = tmp_point;

                }
                else {
                    vectorPoints.push_back(tmp_point);
                }
            }
            else {
                vectorPoints.push_back(tmp_point);
            }
        }
    }
    //wyliczamy alfa i r sortujemy po alfa i wyrzucamy punkty z takim samym alfa ale mniejszym r
    dealWithMess(vectorPoints, p, n - 1);
    //wrzucamy p na stos i dwa punkty z "listy"
    stackPoints.push(p);
    stackPoints.push(vectorPoints.back());
    vectorPoints.pop_back();
    stackPoints.push(vectorPoints.back());
    //dopóki s¹ punkty w "liœcie" sprawdzamy kolejne punkty
    while (vectorPoints.size() != 0)
    {
        if (stackPoints.size() >= 2) {
            //sprawdzamy wyznaczik macierzy dla kolejnych punktów
            tmp_point = stackPoints.top();
            stackPoints.pop();
            det = detMatrix(stackPoints.top().x, tmp_point.x, vectorPoints.back().x, stackPoints.top().y, tmp_point.y, vectorPoints.back().y);

            if (det > 0) {
                //jeœli wyznaczik jest wiêkszy od zera wrzucamy punkt na stos i œci¹gamy z "listy"
                stackPoints.push(tmp_point);
                stackPoints.push(vectorPoints.back());
                vectorPoints.pop_back();

            }
        }
        else {
            //jeœli rozmiar stosu jest za ma³y do wyliczenia wyznacznika wrzucamy punkt z "listy" od razu
            stackPoints.push(vectorPoints.back());

        }
    }
    //dopóki na stacku s¹ 3 punkty mo¿emy stworzyæ trójk¹ty/fragmenty pola naszej figury 
    while (stackPoints.size() > 2) {
        //przypisujemy dwa punkty ze stosu do zmiennych
        tmp_point = stackPoints.top();
        stackPoints.pop();
        tmp_point2 = stackPoints.top();
        //funkcja wyliczaj¹ca 3 bok trójk¹ta/fragmentu pola, zwracaj¹ca pole tego fragmentu
        area += addArea(tmp_point, tmp_point2);
    }

    cout << fixed << setprecision(3) << area;
    return 0;
}