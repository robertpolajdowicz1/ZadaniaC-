#include <iostream>

using namespace std;
struct tree_node {

    int class_id;
    string description;
    tree_node* parent;
    tree_node* son;
    tree_node* brother;
};

bool son_not_found = false;
bool brother_not_found = false;

void print_postorder(tree_node* current) {
    if (current == nullptr) return;

    while (current) {
        if (current->son)
            print_postorder(current->son);
        cout << current->description << "\n";
        current = current->brother;
    }
}
void print_preorder(tree_node* current) {
    if (current == nullptr) return;

    while (current) {
        cout << current->description << "\n";
        if (current->son)
            print_preorder(current->son);
        current = current->brother;
    }
}
tree_node* find(tree_node* current, int id)
{
    if (current->son == nullptr) {
        son_not_found = true;
        return current;
    }
    if (current->son != nullptr)
    {
        if (current->son->class_id == id)
        {
            current = current->son;
            return current;
        }
        current = current->son;
        while (current->brother != nullptr)
        {
            if (current->brother->class_id == id)
            {
                current = current->brother;
                return current;
            }
            current = current->brother;
        }
    }
    brother_not_found = true;
    return current;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    //wprowadzenie iloœci instrukcji
    int n_instructions;

    cin >> n_instructions;
    if (n_instructions < 0 || n_instructions > 10000) { return 0; }

    //utworzenie roota
    tree_node* root = new tree_node;
    root->class_id = 0;
    root->description = "Stan spoczynku";
    root->brother = nullptr;
    root->parent = nullptr;
    root->son = nullptr;

    tree_node* current_tree_node = root;
    //wprowadzenie kolejnych instrukcji i opisów
    for (int i = 0;i < n_instructions;i++)
    {
        current_tree_node = root;

        string tmp_description;

        getline(cin, tmp_description);
        getline(cin, tmp_description);

        int k_steps;
        cin >> k_steps;
        int* k_array = new int[k_steps];
        for (int j = 0;j < k_steps;j++)
        {
            cin >> k_array[j];
        }

        for (int j = 0;j < k_steps;j++)
        {
            current_tree_node = find(current_tree_node, k_array[j]);
            //jesli znaleziono
            if (son_not_found == false && brother_not_found == false) {
                if (j == k_steps - 1)
                {
                    current_tree_node->description = tmp_description;
                }
            }//jesli brak syna
            else if (son_not_found == true)
            {
                tree_node* new_node = new tree_node;

                new_node->class_id = k_array[j];

                if (j == k_steps - 1)
                {
                    new_node->description = tmp_description;
                }
                else
                {
                    new_node->description = "X";
                }

                new_node->parent = current_tree_node;
                new_node->son = nullptr;
                new_node->brother = nullptr;

                current_tree_node->son = new_node;

                son_not_found = false;
                current_tree_node = current_tree_node->son;
                //jesli brak brata
            }
            else if (brother_not_found == true)
            {
                tree_node* new_node = new tree_node;

                new_node->class_id = k_array[j];

                if (j == k_steps - 1)
                {
                    new_node->description = tmp_description;
                }
                else
                {
                    new_node->description = "X";
                }
                new_node->parent = nullptr;
                new_node->son = nullptr;
                new_node->brother = nullptr;

                current_tree_node->brother = new_node;
                brother_not_found = false;
                current_tree_node = current_tree_node->brother;
            }

        }
        delete[] k_array;
    }

    // wybór 1-preorder, 2-postorder
    int x;
    cin >> x;
    if (x < 1 || x > 2) { return 0; }
    //wyœwietlanie
    if (x == 1) { print_preorder(root); }
    if (x == 2) { print_postorder(root); }

    return 0;
}