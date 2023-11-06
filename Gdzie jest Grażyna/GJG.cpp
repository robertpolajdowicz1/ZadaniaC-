#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N = 1000000;
    int room;
    float* rooms = new float[6];
    for (int i = 0; i < 6;++i) {
        rooms[i] = 0.0;
    }

    int HH_start, mm_start, HH_end, mm_end;
    int HH_mm_G;
    int m_MAX, m_MIN, index;
    float result;

    scanf("%d:%d %d:%d", &HH_start, &mm_start, &HH_end, &mm_end);
    scanf("%d", &room);

    m_MIN = HH_start * 60 + mm_start;
    m_MAX = HH_end * 60 + mm_end;

    for (int i = 0; i <= N;++i)
    {
        HH_mm_G = rand() % (m_MAX - m_MIN + 1) + m_MIN;
        index = Grazyna(HH_mm_G / 60, HH_mm_G % 60);

        rooms[index]++;
    }
    result = 1.f * rooms[room] / N;
    printf("%.2f", result);
}