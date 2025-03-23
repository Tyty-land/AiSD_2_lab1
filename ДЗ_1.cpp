#include <iostream>
#include <vector>

using namespace std;

class BinaryTree
{
    struct Node
    {
        int _value;
        Node* _left_branch;
        Node* _right_branch;
        Node()
        {
            _value = 0;
            _left_branch = nullptr;
            _right_branch = nullptr;
        }
        Node(int value)
        {
            _value = value;
            _left_branch = nullptr;
            _right_branch = nullptr;
        }
    };

    Node* _root;
    int _count_elems;
    //Приватные Методы
    void sortarray_in_binarytree(int* sort_node_array, Node*& root, int size, int index_start = 0)//Возможно после создания дерева, так как не будут созданны новые элементы, а будут использованны старые из масива, только сформированные опред. образом, в виде дерева;
    {
        if (size > 0)
        {
            root = new Node;
            int middle = int(round(double(size - 1) / 2));
            root->_value = sort_node_array[index_start + middle];
            sortarray_in_binarytree(sort_node_array, root->_left_branch, abs(middle), index_start);
            sortarray_in_binarytree(sort_node_array, root->_right_branch, (size - 1) - abs(middle), middle + index_start + 1);
        }
    }
    void sortarray_in_binarytree(vector<int> sort_node_array, Node*& root, int size, int index_start = 0)//Возможно после создания дерева, так как не будут созданны новые элементы, а будут использованны старые из масива, только сформированные опред. образом, в виде дерева;
    {
        if (size > 0)
        {
            root = new Node;
            int middle = int(round(double(size - 1) / 2));
            root->_value = sort_node_array[index_start + middle];
            sortarray_in_binarytree(sort_node_array, root->_left_branch, abs(middle), index_start);
            sortarray_in_binarytree(sort_node_array, root->_right_branch, (size - 1) - abs(middle), middle + index_start + 1);
        }
    }
    void print(Node* root)
    {
        if (root->_left_branch)
            print(root->_left_branch);
        cout << root->_value << " ";
        if (root->_right_branch)
            print(root->_right_branch);
    }
    //Для конструктора копирования
    void print(Node* root, vector<int>& sort_array)
    {
        if (root->_left_branch)
            print(root->_left_branch, sort_array);
        sort_array.push_back(root->_value);
        if (root->_right_branch)
            print(root->_right_branch, sort_array);
    }
    vector<int> get_sortarray(const BinaryTree& other_tree)
    {
        vector<int> sort_array;
        print(other_tree._root, sort_array);
        return sort_array;
    }
    void print_legal(Node* root, vector<int>& sort_array) const
    {
        if (root->_left_branch)
            print_legal(root->_left_branch, sort_array);
        sort_array.push_back(root->_value);
        if (root->_right_branch)
            print_legal(root->_right_branch, sort_array);
    }
    vector<int> get_sortarray_legal(const BinaryTree& other_tree) const
    {
        vector<int> sort_array;
        print_legal(other_tree._root, sort_array);
        return sort_array;
    }
    void insert(Node* root, int key) 
    {
        if (root->_value <= key)
        {
            if (!root->_right_branch)
            {
                root->_right_branch = new Node(key);
                this->_count_elems += 1;
            }
            else
                insert(root->_right_branch, key);
        }
        else if (root->_value > key)
        {
            if (!root->_left_branch)
            {
                root->_left_branch = new Node(key);
                this->_count_elems += 1;
            }
            else
                insert(root->_left_branch, key);
        }
    }
    bool contains(Node* root, int key) const
    {
        bool result = 0;
        if (root->_value == key)
            return 1;
        else
        {
            if (root->_left_branch != nullptr)
            {
                result = contains(root->_left_branch, key);
                if (result == 1)
                    return 1;
            }
            if (root->_right_branch != nullptr)
            {
                result = contains(root->_right_branch, key);
                if (result == 1)
                    return 1;
            }
        }
        return 0;
    }
    int erase(Node*& root, int key, int flag = 0, bool flag_null = 0, bool flag_lr = 0)
    {
        int result = 0;
        //Поиск
        if (root->_value != key && flag == 0)
        {
            if (root->_left_branch != nullptr)
            {
                result = erase(root->_left_branch, key);
                if (result != 0)
                    return result;
            }
            if (root->_right_branch != nullptr)
            {
                result = erase(root->_right_branch, key);
                if (result != 0)
                    return result;
            }
            return 0;
        }
        //Выбор ветки для сдвига
        else if (root->_value == key)
        {
            if (root->_left_branch != nullptr)
            {
                result = root->_value;
                root->_value = erase(root->_left_branch, key, 1);
                return result;
            }
            if (root->_right_branch != nullptr)
            {
                result = root->_value;
                root->_value = erase(root->_right_branch, key, 2);
                return result;
            }
            if (root->_left_branch == nullptr && root->_right_branch == nullptr)
            {
                result = root->_value;
                this->_count_elems -= 1;
                delete root;
                root = nullptr;
                return result;
            }
        }
        //Замена с учётом выбранной ветки
        //Левое направление
        else if (root->_value != key && flag == 1)
        {
            if (root->_left_branch == nullptr && root->_right_branch == nullptr)
            {
                result = root->_value;
                this->_count_elems -= 1;
                delete root;
                root = nullptr;
                return result;
            }
            if (root->_right_branch != nullptr && flag_null == 0)
            {
                result = erase(root->_right_branch, key, 1, flag_null, 1);
                return result;
            }
            if (root->_left_branch != nullptr && flag_lr == 0)
            {
                result = erase(root->_left_branch, key, 1, flag_null, flag_lr);
                return result;
            }
            else if (root->_right_branch == nullptr && flag_null == 0)
                flag_null = 1;
            if (root->_right_branch != nullptr && flag_null == 1)
            {
                result = root->_value;
                root->_value = erase(root->_right_branch, key, 1, flag_null, flag_lr);
                return result;
            }
            if (root->_left_branch != nullptr && flag_null == 1)
            {
                result = root->_value;
                root->_value = erase(root->_left_branch, key, 1, flag_null, flag_lr);
                return result;
            }
        }
        //Правое направление
        else if (root->_value != key && flag == 2)
        {
            if (root->_left_branch == nullptr && root->_right_branch == nullptr)
            {
                result = root->_value;
                this->_count_elems -= 1;
                delete root;
                root = nullptr;
                return result;
            }
            if (root->_left_branch != nullptr && flag_null == 0)
            {
                result = erase(root->_left_branch, key, 1, flag_null, 1);
                return result;
            }
            if (root->_right_branch != nullptr && flag_lr == 0)
            {
                result = erase(root->_right_branch, key, 1, flag_null, flag_lr);
                return result;
            }
            else if (root->_left_branch == nullptr && flag_null == 0)
                flag_null = 1;
            if (root->_left_branch != nullptr && flag_null == 1)
            {
                result = root->_value;
                root->_value = erase(root->_left_branch, key, 1, flag_null, flag_lr);
                return result;
            }
            if (root->_right_branch != nullptr && flag_null == 1)
            {
                result = root->_value;
                root->_value = erase(root->_right_branch, key, 1, flag_null, flag_lr);
                return result;
            }
        }
    }
    //Для диструктора
    void deleter(Node* root)
    {
        if (root->_left_branch)
            deleter(root->_left_branch);
        if (root->_right_branch)
            deleter(root->_right_branch);
        delete root;
        root = nullptr;
        _count_elems = 0;
    }
    
public:
    //Конструкторы
    BinaryTree()
    {
        _root = new Node;
        _count_elems = 1;
    }
    BinaryTree(int val_root)
    {
        _root = new Node(val_root);
        _count_elems = 1;
    }
    BinaryTree(int* sort_node_array, int size)
    {
        _root = nullptr;
        sortarray_in_binarytree(sort_node_array, _root, size);
        _count_elems = size;
    }
    BinaryTree(vector<int> sort_node_array, int size)
    {
        _root = nullptr;
        sortarray_in_binarytree(sort_node_array, _root, size);
        _count_elems = size;
    }
    //Конструктор копирования
    BinaryTree(const BinaryTree& other_tree)
    {
        _root = nullptr;
        vector<int> tmp_sort_vector = get_sortarray(other_tree);
        sortarray_in_binarytree(tmp_sort_vector, _root, other_tree._count_elems);
        _count_elems = other_tree._count_elems;
    }
    //Методы
    void print()
    {
        print(_root);
    }
    int get_count_elems() const
    {
        return _count_elems;
    }
    //По заданию
    vector<int> get_sortarray_legal_and_safely() const
    {
        return get_sortarray_legal(*this);
    }
    bool insert(int key)
    {
        insert(_root, key);
        return 0;
    }
    bool contains(int key)
    {
        vector<int> tmp_sort_array = get_sortarray(*this);
        for (int i = 0; i < _count_elems; i++)
        {
            if (tmp_sort_array[i] == key)
                return 1;
        }
        return 0;
    }
    bool contains(int key) const
    {
        return contains(_root, key);
    }
    bool erase(int key)
    {
        int tmp = erase(_root, key);
        if (tmp)
            return 1;
        return 0;
    }
    //операторы
    void operator=(const BinaryTree& other_tree)
    {
        _root = nullptr;
        vector<int> tmp_sort_vector = get_sortarray(other_tree);
        sortarray_in_binarytree(tmp_sort_vector, _root, other_tree._count_elems);
        _count_elems = other_tree._count_elems;
    }
    //Диструктор
    ~BinaryTree()
    {
        deleter(_root);
    }

};

//Функции по заданию
void sort(vector<int>& any_vector)
{
    int x = 0;
    while (x < any_vector.size() - 1)
    {
        if (any_vector[x] > any_vector[x + 1])
        {
            int y = x + 1;
            while (y != 0 && any_vector[y] < any_vector[y - 1])
            {
                int tmp = any_vector[y];
                any_vector[y] = any_vector[y - 1];
                any_vector[y - 1] = tmp;
                y--;
                if (y == 0 || any_vector[y] > any_vector[y - 1])
                    x = y;
            }
        }
        x++;
    }
}
bool find_s(vector<int> any_vector, int key)
{
    for (int i = 0; i < any_vector.size(); i++)
    {
        if (any_vector[i] == key)
            return 1;
    }
    return 0;
}
vector<int> find_intersection(const BinaryTree& tree_1, const BinaryTree& tree_2)
{
    vector<int> intersection_vector;
    vector<int> tree_1_vector = tree_1.get_sortarray_legal_and_safely();
    for (int i = 0; i < tree_1_vector.size(); i++)
    {
        if (tree_2.contains(tree_1_vector[i]) && !find_s(intersection_vector, tree_1_vector[i]))
            intersection_vector.push_back(tree_1_vector[i]);
    }
    return intersection_vector;
}
vector<int> find_unification(const BinaryTree& tree_1, const BinaryTree& tree_2)
{
    vector<int> unification_vector;
    vector<int> tree_1_vector = tree_1.get_sortarray_legal_and_safely();
    vector<int> tree_2_vector = tree_2.get_sortarray_legal_and_safely();
    for (int i = 0; i < tree_1_vector.size(); i++)
    {
        if (i < tree_1_vector.size())
        {
            if (!find_s(unification_vector, tree_1_vector[i]))
                unification_vector.push_back(tree_1_vector[i]);
        }
    }
    for (int j = 0; j < tree_2_vector.size(); j++)
    {
        if (j < tree_2_vector.size())
        {
            if (!find_s(unification_vector, tree_2_vector[j]))
                unification_vector.push_back(tree_2_vector[j]);
        }
    }
    sort(unification_vector);
    return unification_vector;
}



int main()
{
    int* ArrayNode = new int[10];
    for (int i = 0, j = 2; i < 10; i++, j += 2)
        ArrayNode[i] = j;
    BinaryTree tree(ArrayNode, 10);
    BinaryTree tree_2;
    tree_2 = tree;
    cout << "start tree: ";
    tree.print();
    cout << endl;
    cout << "start tree_2: ";
    tree_2.print();
    cout << endl;

    tree.insert(2);
    tree.insert(125);
    tree.insert(13);
    tree_2.erase(12);
    tree_2.erase(16);
    tree_2.insert(250);
    cout << "tree_2.erase(20): " << tree_2.erase(20) << endl;
    cout << "tree_2.erase(250): " << tree_2.erase(250) << endl;
    tree_2.insert(11);
    cout << "end tree: ";
    tree.print();
    cout << endl;
    cout << tree_2.contains(16) << " - tree_2, " << tree.contains(16) << " - tree" << endl;
    cout << "end tree_2: ";
    tree_2.print();
    cout << endl;
    cout << "ins: ";
    vector<int> in_vec = find_intersection(tree, tree_2);
    for (int i = 0; i < in_vec.size(); i++)
        cout << in_vec[i] << " ";
    cout << endl;
    cout << "uni: ";
    vector<int> un_vec = find_unification(tree_2, tree);
    for (int i = 0; i < un_vec.size(); i++)
        cout << un_vec[i] << " ";
    cout << endl;
}