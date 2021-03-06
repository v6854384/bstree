#include<iostream>
#include<locale>
using namespace std;

struct Node { //создаем структуру
    int data; //поле для информации
    Node *left; //указатель на левую ветку
    Node *right; //указатель на правую ветку
};

class BSTree { //создаем класс дерево
    private: //параметр с начальной информацией, который недоступен для редактирования
        Node *root;
    public: //публичные данные
        BSTree() { root = nullptr; } //объявляем переменную, тип которой структура дерево
        auto insert(Node*& root, int value) -> Node* {
            if (root == nullptr) {
                root = new Node { value, nullptr, nullptr };
            } else {
                if (root->data < value) 
                    root->left = insert(root->left, value);
                else if (root->data > value) 
                    root->right = insert(root->right, value);
                else if (root -> data == value) {
                    cout << "дерево имеет этот узел" << endl;
                    return root;
                }
            }
            return root;
        }
        void insert(int value) { insert(root, value); } //создание дерева
        void delete_tree(Node *&data) { //удаление дерева
            if (data != nullptr) { //поиск не пустых узлов
                delete_tree(data->left); //удаление всех элементов с помощью рекурсии 
                delete_tree(data->right); //удаление всех элементов с помощью рекурсии 
                delete data;
                data = nullptr;
            }
        }
        ~BSTree() {
            delete_tree(root); //полное удаление дерева
        }
        void show(Node*node, int stage) { //функция вывода дерева на экран
            if (node->left != nullptr)
                show(node->left, stage+1);
            if (node != root) { 
                cout.width(stage*4);
                cout << "--";
            }
            cout << "(" << node->data << ")" << endl;
            if (node->right != nullptr)
                show(node->right, stage + 1);
        }
        void show() { 
            show (root, 1);
        }
        void direct_bypass(Node* root) { //функция прямого обхода дерева
            if (root != nullptr) {
                cout << root->data << " ";
                direct_bypass(root->right);
                direct_bypass(root->left);
            }
        }
        void cross_bypass(Node* root) { //функция поперчного обхода дерева
            if (root != nullptr) {
                cross_bypass(root->right);
                cout << root->data << " ";
                cross_bypass(root->left);
            }
            return;
        }
        void reverse_bypass(Node* root) { //функция обратного обхода дерева
            if (root != nullptr) {
                reverse_bypass(root->left);
                reverse_bypass(root->right);
                cout << root->data << " ";
            }
        }
        void select_bypass( char choice_bypass ) { //функция выбора обхода дерева (а-прямой, б-поперечный, с-обратный)
            if (choice_bypass == 'a') 
                direct_bypass(root);
            if (choice_bypass == 'b') 
                cross_bypass(root);
            if (choice_bypass == 'c') 
                reverse_bypass(root);
        }
};

void menu(){
    cout << "Выберете одну из операций:" << endl;
    cout << "1. Вывести дерево на экран" << endl;
    cout << "2. Вывести список узлов дерева" << endl;
    cout << "3. Добавить узел в дерево" << endl;
    cout << "4. Удалить узел из дерева" << endl;
    cout << "5. Сохранить дерево в файл" << endl;
    cout << "6. Загрузить дерево из файла" << endl;
    cout << "7. Проверить наличие узла" << endl;
    cout << "8. Завершить работу программы" << endl;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    BSTree tree; //создаем пустое дерево класса дерево
    for (int i=1; i<argc; i++) { 
        tree.insert(atoi(argv[i])); //заполнение дерева элементами
    };
    string choice_exit;
    char choice_bypass;
    int choice = 0;
    while (true) {
        menu();
        cin >> choice;
        switch (choice) {
            case 1: tree.show ();
            break;
            case 2: cout << "Выберите способ обхода" << endl;
                    cin >> choice_bypass;
                    tree.select_bypass(choice_bypass);
                    cout << endl;
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
            break;
            case 8: cout << "Вы уверены, что хотите выйти из программы?" << endl;
                    cin >> choice_exit;
                    if (choice_exit == "Да")
                        return 0;
                    else if (choice_exit == "да") 
                        return 0;
            default: cout << " Неверная команда " << endl;
        }
    }
}
