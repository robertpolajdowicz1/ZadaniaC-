#include <iostream>
#include <cmath>

using namespace std;


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n_textSize, m_patternSize;
    int d_dictSize = 101;
    int q_firstNumber = 1997;
    int h = 1;
    int founded_count = 0;
    bool found;
    bool first_founded = false;
    bool stop = false;
    int j;
    int i;
    int founded_index_1 = 0;
    int founded_index_2 = 0;

    cin >> n_textSize;
    int* textArray = new int[n_textSize];
    for (int i = 0; i < n_textSize; ++i) { cin >> textArray[i]; }
    cin >> m_patternSize;
    int* patternArray = new int[m_patternSize];
    for (int i = 0; i < m_patternSize; ++i) { cin >> patternArray[i]; }

    for (int i = 0; i < m_patternSize - 1; i++)
    {
        h = (h * d_dictSize) % q_firstNumber;
    }

    int p = 0;
    int t = 0;

    for (int i = 0; i < m_patternSize; i++) {
        p = (d_dictSize * p + patternArray[i]) % q_firstNumber;
        t = (d_dictSize * t + textArray[i]) % q_firstNumber;
    }
    i = 0;

    while (true)
    {
        if (p == t) {
            found = true;

            for (j = 0; j < m_patternSize; j++)
            {
                if (textArray[i + j] != patternArray[j])
                {
                    found = false;
                    break;
                }
            }
            if (j == m_patternSize)
            {
                if (first_founded == false) {
                    founded_index_1 = i;
                    first_founded = true;
                }
                else {
                    founded_index_2 = i;
                    stop = true;
                }
            }
        }

        if (stop) {
            break;
        }
        if (i < n_textSize - m_patternSize)
        {
            t = (d_dictSize * (t - textArray[i] * h) + textArray[i + m_patternSize]) % q_firstNumber;
            if (t < 0) {
                t = (t + q_firstNumber);
            }
        }
        i++;
    }

    long int a = founded_index_1;
    long int b = founded_index_2;
    long int sum = 0;

    while (true)
    {
        sum = a + b;
        a = b;
        b = sum;

        if (sum >= n_textSize) {
            cout << sum - n_textSize << " ";
            break;
        }
    }

    delete[] textArray;
    delete[] patternArray;
    return 0;
}