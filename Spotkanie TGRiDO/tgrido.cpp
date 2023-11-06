#include <iostream>
#include <vector>

using namespace std;
struct social {

	int index;
	int value;
};

int lock;

bool check_lower(int first, int second)
{
	return first < second;
}

bool check_lower_equal(int first, int second)
{
	return first <= second;
}

bool check_equal(int first, int second)
{
	return first == second;
}

bool check_equal_larger(int first, int second)
{
	return first >= second;
}

bool check_larger(int first, int second)
{
	return first > second;
}

void push(social* social_arr, int value_to_add, int index)
{
	int i = lock++;
	int j = (i - 1) / 2;

	while (check_lower_equal(social_arr[j].value, value_to_add) && i > 0)
	{
		if (check_equal(social_arr[j].value, value_to_add) && check_larger(social_arr[j].index, index)) {
			social_arr[i] = social_arr[j];
			i = j;
			j = (i - 1) / 2;
		}
		else if (check_equal(social_arr[j].value, value_to_add) && check_lower(social_arr[j].index, index)) {
			break;
		}
		else if (check_lower(social_arr[j].value, value_to_add)) {
			social_arr[i] = social_arr[j];
			i = j;
			j = (i - 1) / 2;
		}
	}

	social_arr[i].value = value_to_add;
	social_arr[i].index = index;
}

social pop(social* social_arr)
{
	int i = 0;
	int j = 1;
	social social_tmp = social_arr[0];

	lock--;

	int value_tmp = social_arr[lock].value;
	int index_tmp = social_arr[lock].index;

	while (j < lock)
	{
		if (j < lock - 1 && check_equal_larger(social_arr[j + 1].value, social_arr[j].value)) {
			if (check_equal(social_arr[j + 1].value, social_arr[j].value) && check_lower(social_arr[j + 1].index, social_arr[j].index)) {
				j++;
			}
			else if (check_larger(social_arr[j + 1].value, social_arr[j].value)) {
				j++;
			}
		}
		if (check_equal_larger(value_tmp, social_arr[j].value))
		{
			if (check_equal(value_tmp, social_arr[j].value) && check_larger(index_tmp, social_arr[j].index))
			{
				social_arr[i] = social_arr[j];
				i = j;
				j = 2 * j + 1;
			}
			else
			{
				break;
			}
		}
		else
		{
			social_arr[i] = social_arr[j];
			i = j;
			j = 2 * j + 1;
		}
	}

	social_arr[i].value = value_tmp;
	social_arr[i].index = index_tmp;

	return social_tmp;
}

void printer(vector<int> array, int n)
{
	cout << n << '\n';

	for (int i = 0; i < n * 2; i++)
	{
		if (i % 2 == 0)
		{
			cout << array[i] << " ";
		}
		else {
			cout << array[i] << "\n";
		}
	}
}

void chatting(social* social_arr)
{
	int chatts_number = 0;
	social chatter_1;
	social chatter_2;
	vector <int> chatts_combinations;

	while (true)
	{
		if (lock >= 2)
		{
			chatter_1 = pop(social_arr);
			chatter_2 = pop(social_arr);

			if (chatter_1.value > 0 && chatter_2.value > 0)
			{
				chatts_number++;
				if (chatter_1.index < chatter_2.index)
				{
					chatts_combinations.push_back(chatter_1.index);
					chatts_combinations.push_back(chatter_2.index);
				}
				if (chatter_2.index < chatter_1.index)
				{
					chatts_combinations.push_back(chatter_2.index);
					chatts_combinations.push_back(chatter_1.index);
				}

				chatter_1.value--;
				chatter_2.value--;

				if (chatter_1.value > 0)
				{
					push(social_arr, chatter_1.value, chatter_1.index);
				}
				if (chatter_2.value > 0)
				{
					push(social_arr, chatter_2.value, chatter_2.index);
				}
			}
		}
		else {
			break;
		}
	}

	printer(chatts_combinations, chatts_number);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		int n;
		cin >> n;

		if (n >= 2 && n <= 200000)
		{
			lock = 0;
			social* social_arr = new social[n];

			for (int j = 0; j < n; j++)
			{
				int value_to_add;
				cin >> value_to_add;
				push(social_arr, value_to_add, j + 1);
			}

			chatting(social_arr);
			delete[] social_arr;
		}
	}
}