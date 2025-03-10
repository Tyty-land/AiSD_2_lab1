#include <iostream>
#include <vector>

using namespace std;

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

class BinaryTree
{
    Node* _root;
    int _count_elems;
    //Приватные Методы
    void sa_in_bt(Node* sort_node_array, Node*& root, int size, int index_start = 0)//Возможно после создания дерева, так как не будут созданны новые элементы, а будут использованны старые из масива, только сформированные опред. образом, в виде дерева;
    {
        if (size > 0)
        {
            root = new Node;
            int middle = int(round(double(size - 1) / 2));
            root->_value = sort_node_array[index_start + middle]._value;
            sa_in_bt(sort_node_array, root->_left_branch, abs(middle), index_start);
            sa_in_bt(sort_node_array, root->_right_branch, (size - 1) - abs(middle), middle + index_start + 1);
        }
    }
    void sa_in_bt(vector<Node*> sort_node_array, Node*& root, int size, int index_start = 0)//Возможно после создания дерева, так как не будут созданны новые элементы, а будут использованны старые из масива, только сформированные опред. образом, в виде дерева;
    {
        if (size > 0)
        {
            root = new Node;
            int middle = int(round(double(size - 1) / 2));
            root->_value = sort_node_array[index_start + middle]->_value;
            sa_in_bt(sort_node_array, root->_left_branch, abs(middle), index_start);
            sa_in_bt(sort_node_array, root->_right_branch, (size - 1) - abs(middle), middle + index_start + 1);
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
    void print(Node* root, vector<Node*>& sort_array)
    {
        if (root->_left_branch)
            print(root->_left_branch, sort_array);
        sort_array.push_back(root);
        if (root->_right_branch)
            print(root->_right_branch, sort_array);
    }
    vector<Node*> get_sa(const BinaryTree& other_tree)
    {
        vector<Node*> sort_array;
        print(other_tree._root, sort_array);
        return sort_array;
    }
    void print_l(Node* root, vector<int>& sort_array) const
    {
        if (root->_left_branch)
            print_l(root->_left_branch, sort_array);
        sort_array.push_back(root->_value);
        if (root->_right_branch)
            print_l(root->_right_branch, sort_array);
    }
    vector<int> get_sa_l(const BinaryTree& other_tree) const
    {
        vector<int> sort_array;
        print_l(other_tree._root, sort_array);
        return sort_array;
    }
    void insert(Node* root, int key)
    {
        if (root->_value <= key)
        {
            if (!root->_right_branch)
                root->_right_branch = new Node(key);
            else
                insert(root->_right_branch, key);
        }
        else if (root->_value > key)
        {
            if (!root->_left_branch)
                root->_left_branch = new Node(key);
            else
                insert(root->_left_branch, key);
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
    BinaryTree(Node* sort_node_array, int size)
    {
        _root = nullptr;
        sa_in_bt(sort_node_array, _root, size);
        _count_elems = size;
    }
    BinaryTree(vector<Node*> sort_node_array, int size)
    {
        _root = nullptr;
        sa_in_bt(sort_node_array, _root, size);
        _count_elems = size;
    }
    //Конструктор копирования
    BinaryTree(const BinaryTree& other_tree)
    {
        _root = nullptr;
        vector<Node*> tmp_sort_vector = get_sa(other_tree);
        sa_in_bt(tmp_sort_vector, _root, other_tree._count_elems);
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
    vector<int> get_sa_ls() const
    {
        return get_sa_l(*this);
    }
    bool insert(int key)
    {
        insert(_root, key);
        return 0;
    }
    bool contains(int key)
    {
        vector<Node*> tmp_sort_array = get_sa(*this);
        for (int i = 0; i < _count_elems; i++)
        {
            if (tmp_sort_array[i]->_value == key)
                return 1;
        }
        return 0;
    }
    bool erase(int key)
    {
        vector<Node*> tmp_sort_vector = get_sa(*this);
        vector<Node*> tmp_new_sort_vector;
        for (int i = 0; i < tmp_sort_vector.size(); i++)
        {
            if (tmp_sort_vector[i]->_value != key)
            {
                tmp_new_sort_vector.push_back(tmp_sort_vector[i]);
            }
        }
        sa_in_bt(tmp_new_sort_vector, _root, tmp_new_sort_vector.size());
        _count_elems = tmp_new_sort_vector.size();
        return 0;
    }
    //операторы
    void operator=(const BinaryTree& other_tree)
    {
        _root = nullptr;
        vector<Node*> tmp_sort_vector = get_sa(other_tree);
        sa_in_bt(tmp_sort_vector, _root, other_tree._count_elems);
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
    vector<int> tree_1_vector = tree_1.get_sa_ls();
    vector<int> tree_2_vector = tree_2.get_sa_ls();
    for (int i = 0; i < tree_1_vector.size(); i++)
    {
        for (int j = 0; j < tree_2_vector.size(); j++)
        {
            if (tree_1_vector[i] == tree_2_vector[j] && !find_s(intersection_vector, tree_2_vector[j]))
            {
                intersection_vector.push_back(tree_2_vector[j]);
            }
        }
    }
    return intersection_vector;
}
vector<int> find_unification(const BinaryTree& tree_1, const BinaryTree& tree_2)
{
    vector<int> unification_vector;
    vector<int> tree_1_vector = tree_1.get_sa_ls();
    vector<int> tree_2_vector = tree_2.get_sa_ls();
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
    Node* ArrayNode = new Node[10];
    for (int i = 0, j = 2; i < 10; i++, j += 2)
        ArrayNode[i]._value = j;
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
    tree_2.insert(11);
    cout << "end tree: ";
    tree.print();
    cout << endl;
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