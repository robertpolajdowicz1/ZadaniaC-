#include <iostream>

using namespace std;

struct ldk
{
    ldk() {
        next = nullptr;
        prev = nullptr;
    }
    string name;
    int space;
    ldk* next, * prev;
};

void add_element(ldk** begin, int i, string s, int c)
{
    ldk* new_ldk = new ldk;
    new_ldk->name = s;
    new_ldk->space = c;
    //pusta lista
    if (begin[i] == nullptr)
    {
        new_ldk->next = new_ldk;
        new_ldk->prev = new_ldk;
        begin[i] = new_ldk;
        return;
    }
    
    ldk* end = begin[i]->prev;
    
    new_ldk->next = begin[i];
    new_ldk->prev = end;
    
    begin[i]->prev = new_ldk;
    end->next = new_ldk;
    
}

void deleter(ldk** current_list, int i)
{
    //jedyny element?
    if (current_list[i]->next == current_list[i])
    {
        delete current_list[i];
        current_list[i] = nullptr;
        return;
    }
    current_list[i]->prev->next = current_list[i]->next;
    current_list[i]->next->prev = current_list[i]->prev;
    ldk* next = current_list[i]->next;
    delete current_list[i];
    current_list[i] = next;
}

ldk* rotater_right(ldk** begin, int i, int rotate) {
    ldk* buffor = begin[i];
    for (int i = 0; i < rotate; i++)
    {
        buffor = buffor->next;
    }
    return buffor;
}

ldk* rotater_left(ldk** begin, int i, int rotate) {
    ldk* buffor = begin[i];
    for (int i = 0; i < rotate; i++)
    {
        buffor = buffor->prev;
    }
    return buffor;
}

int sumator(ldk** plants, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += plants[i]->space;
    }
    return sum;
}

int id_list_to_rotate(int current, int go, int n)
{   //likwidacja nadmiarowych przesunięć
    return ((((current + go) % n) + n) % n);
}

bool fixer(ldk** plants, int k, int n)
{   //funkcja do naprawy tablicy list
    //jeśli komórka tablicy jest pustą listą(nullptr)
    //przesuwamy na koniec
    if (plants[k] == nullptr)
    {
        for (int i = k; i < n - 1; ++i) {
            ldk* buffer = plants[i];
            plants[i] = plants[i + 1];
            plants[i + 1] = buffer;
        }
        return true;
    }
    return false;
}

int binary_search(int arr[], int left, int right, int search_value)
{
    while (left <= right) {
        int m = left + (right - left) / 2;
        
        if (arr[m] == search_value)
            return m;
        
        if (arr[m] < search_value)
            left = m + 1;
        
        else
            right = m - 1;
    }
    return -1;
}
void push_minus_one_to_end(int arr[], int n)
{   //funkcja do naprawy sizes
    //gdy mechanical helper znajduje
    //rabatke wstawia w miejsce jej rozmiaru
    //wartosc -1 dlatego trzeba przesunąć minus jedynki na koniec
    //bo binary search potrzebuje uporządkowanej tablicy
    int count = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] != -1)
            arr[count++] = arr[i];
    
    while (count < n)
        arr[count++] = -1;
}
void mechanical_helper(ldk* plants[], int n, int sizes_l, int rotacje_h, int sizes[], int drivers_for_array[], int drivers_for_lists[]) {
    int n_for_index = n; //zmniejszamy podczas przesuwania komórek z pustymi listami na koniec
    int sizes_l_for_push= sizes_l; //zmniejszamy podczas przesuwania wykluczonych rozmiarów na koniec
    
    int counter_founded_rabat = 0;
    int rotation_it = 0;
    int index = 0;
    
    int tmp_sum = sumator(plants, n);
    
    
    while (n_for_index && counter_founded_rabat < sizes_l && rotation_it - 1 < rotacje_h)
    {
        bool flag = true;
        
        while(true)
        {               
           int found = binary_search(sizes,0,sizes_l_for_push-1,tmp_sum);       // sprawdzamy czy rozmiar znaleziony
            
            if(found!=-1 && tmp_sum==sizes[found])
            {
                
                cout << tmp_sum << " ";         // jeśli znaleziony wyswietlamy sume
                tmp_sum = 0;                            // po wyswietleniu mozna od razu ja wyzerowac
                for (int k = 0; k < n_for_index; k++)
                {
                    cout << plants[k]->name << " ";             // wyswietlamy nazwe rosliny 
                    deleter(plants, k);                         // i kasujemy pozycje z poszczegolnych list
                    if (fixer(plants, k, n_for_index))          // jesli trzeba naprawic tablice list
                    {
                        if (index > k) {                        // jesli index do rotacji > od aktualnego k zmniejszamy go 
                            index--;
                        }
                        n_for_index--;                          // zmniejszamy index plants ponieważ pusta lista przeszła na koniec
                        if (!n_for_index)                       // jeśli rozmiar plants wynosi 0 po usunięciu przerywamy pętle
                        {
                            break;
                        }
                        k--;                                    // jesli trafilismy na pustą liste i  
                                                                // została przesunięta na koniec musimy sie cofnąc                                         
                                                                // kolejna pusta lista mogła trafić w jej miejsce
                    }
                    else //jesli nie trzeba naprawić tablicy list po prostu dodajemy nowy elemnt list po usunieciu starego
                    {
                        tmp_sum += plants[k]->space;
                    }                    
                }
                cout << "\n";
                
                sizes[found] = -1;                                  // wykluczenie znalezionego rozmiaru rabatki
                push_minus_one_to_end(sizes,sizes_l_for_push);       // uporządkowanie tablicy (-1 na koniec)
                sizes_l_for_push--;                                  // zmniejszamy rozmiar "dostępnej tablicy" dla binarysearch'a i dla pusha             
                flag = false;                                       // trzeba sprawdzic czy rosliny które wskoczyly może akurat pasują
                counter_founded_rabat++;                               // zwiększamy licznik znalezionych rabatek
                break;
            }else{break;}
        }
        
        if (!n_for_index) { break; }                                //plants rozmiar jest zerem przerywamy
        if (rotation_it == rotacje_h && flag) { break; }            //koniec dostepnych rotacji oraz rośliny które wskoczyły nie pasują
        
        if (flag == true)                                           //flaga true zatem obracamy rabatki ktore same wskoczyly nie dały rozmiaru pasującego
        {
            index = id_list_to_rotate(index, drivers_for_array[rotation_it], n_for_index);//ustalamy którą komórke tablicy musimy obrócić
            
            tmp_sum -= plants[index]->space;//odejmujemy wartość aktualnej pozycji listy w komórce plants[index]
            
            if (drivers_for_lists[rotation_it] <= 0)//obrót lewo
            {
                plants[index] = rotater_left(plants, index, abs(drivers_for_lists[rotation_it]));
            }
            if (drivers_for_lists[rotation_it] > 0)//obrót prawo
            {
                plants[index] = rotater_right(plants, index, drivers_for_lists[rotation_it]);
            }
            rotation_it++;// zwiększamu ilośc wykonanych rotacji
            tmp_sum += plants[index]->space; //dodajemy nową wartość po obróceniu listy w komórce plants[index]
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    //ilosc list
    int n;
    cin >> n;
    
    //tablica list cyklicznych
    ldk** plant_array = new ldk * [n]();
    
    string tmp_s;
    int tmp_c;
    int m;
    int h;
    int l;
    //wprowadzenie list
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        
        for (int j = 0; j < m; j++)
        {
            cin >> tmp_s >> tmp_c;
            add_element(plant_array, i, tmp_s, tmp_c);
        }
    }   
    //wprowadzenie rozmiarow rabat
    cin >> l;
    
    int* sizes = new int[l];
    for (int i = 0; i < l; i++) { cin >> sizes[i]; }
    
    //wprowadzenie ilości komend sterujących oraz wartości komend
    cin >> h;
    
    int* drivers_for_array = new int[h];
    int* drivers_for_lists = new int[h];
    
    for (int i = 0; i < h; i++)
    {
        cin >> drivers_for_array[i] >> drivers_for_lists[i];
    }
    //koniec wprowadzania
    
    if (n > 0) { mechanical_helper(plant_array, n, l, h, sizes, drivers_for_array, drivers_for_lists); }
    //usuwanie
    delete[] plant_array;
    delete[] sizes;
    delete[] drivers_for_array;
    delete[] drivers_for_lists;
    return 0;
}