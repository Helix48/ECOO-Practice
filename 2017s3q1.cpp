#include <iostream>
#include <iomanip>

using namespace std;

struct tree_node
{
    int data;
    tree_node *left;
    tree_node *right;
};

// Declare functions
void output_tree (tree_node* curr_node);
tree_node* insert_tree_node (tree_node* curr_node, tree_node* new_node);
int get_pos_int ();
void print_tree (tree_node* curr_node);
tree_node* create_new_node (int data);

tree_node* delete_tree_node (tree_node* true_root, tree_node* curr_node, tree_node* curr_parent, int data);



int main()
{
    // Create tree
    tree_node* tree_root = nullptr;

    int input = 1;

    while (true)
    {
        cout << "Enter a positive integer: ";
        cin >> input;

        if (input <= 0)
        {
            break;
        }

        tree_node* new_node = create_new_node(input);
        tree_root = insert_tree_node(tree_root, new_node);
    }

    print_tree(tree_root);

    input = 1;

    // Let the user choose what should be done to the tree
    while (input == 1 || input == 2 || input == 3)
    {
        cout << "Enter 1 to insert node, 2 to delete node, 3 to print tree, other to exit: ";
        cin >> input;

        // Check whether to delete, insert, or print
        if (input == 1)
        {
            int data = get_pos_int();
            tree_node* new_node = create_new_node(data);
            tree_root = insert_tree_node(tree_root, new_node);
        }
        else if (input == 2)
        {
            int data = get_pos_int();
            tree_root = delete_tree_node(tree_root, tree_root, nullptr, data);
        }
        else if (input == 3)
        {
            print_tree(tree_root);

            if (tree_root == nullptr)
            {
                cout << "Nothing to print. (No nodes are in the tree)." << endl;
            }
        }
    }

    return 0;
}

int get_pos_int ()
{
    int input = 0;
    while (input < 1)
    {
        cout << "Enter a positive integer: ";
        cin >> input;
    }
    return input;
}

// Function to create a new node
tree_node* create_new_node (int data)
{
    tree_node* new_node = new tree_node;
    new_node->data = data;
    new_node->left = new_node->right = nullptr;
    return new_node;
}

void print_tree (tree_node* curr_node)
{
    if (curr_node != nullptr)
    {
        cout << "data: " << setw(10) << left << curr_node->data ;
        if (curr_node->left != nullptr)
        {
            cout << "left: " << setw(10) << left << curr_node->left->data;
        }
        else
        {
            cout << "left: " << setw(10) << left << "null";
        }
        if (curr_node->right != nullptr)
        {
            cout << "right: " << setw(10) << left << curr_node->right->data;
        }
        else
        {
            cout << "right: " << setw(10) << left << "null";
        }
        cout << endl;
        print_tree(curr_node->left);
        print_tree(curr_node->right);
    }
}

tree_node* delete_tree_node (tree_node* true_root, tree_node* curr_node, tree_node* curr_parent, int data)
{
    if (curr_node == nullptr)
    {
        cout << "data value does not exist" << endl;
        return true_root;
    }

    // If the root of the tree is deleted
    else if (data == true_root->data)
    {
        // If both branches exist, insert right branch onto left branch
        if (true_root->left != nullptr && true_root->right != nullptr)
        {
            true_root->right = insert_tree_node(true_root->right, true_root->left);
            delete true_root;
            return true_root->right;
        }
        // If only left branch exists, root is left branch
        else if (true_root->left != nullptr)
        {
            tree_node* temp = true_root->left;
            delete true_root;
            return temp;
        }
        // If only right branch exists, root is right branch
        else if (true_root->right != nullptr)
        {
            tree_node* temp = true_root->right;
            delete true_root;
            return temp;
        }
        // If no branches, then return null
        else
        {
            delete true_root;
            return nullptr;
        }
    }
    else if (data == curr_node->data)
    {
        // Make the parent node point to null
        if (curr_parent->left == curr_node)
        {
            curr_parent->left = nullptr;
        }
        else
        {
            curr_parent->right = nullptr;
        }

        // Insert left branch back into the tree
        if (curr_node->left != nullptr)
        {
            true_root = insert_tree_node(true_root, curr_node->left);
        }
        // Insert right branch back into the tree
        if (curr_node->right != nullptr)
        {
            true_root = insert_tree_node(true_root, curr_node->right);
        }

        delete curr_node;
        return true_root;
    }
    // Recursively go down the tree
    else if (data < curr_node->data)
    {
        return delete_tree_node(true_root, curr_node->left, curr_node, data);
    }
    // Recursively go down the tree
    else if (data >= curr_node->data)
    {
        return delete_tree_node(true_root, curr_node->right, curr_node, data);
    }
}

tree_node* insert_tree_node (tree_node* curr_node, tree_node* new_node)
{
    if (curr_node == nullptr)
    {
        return new_node;
    }
    else if (new_node->data < curr_node->data)
    {
        curr_node->left = insert_tree_node(curr_node->left, new_node);
        return curr_node;
    }
    else if (new_node->data >= curr_node->data)
    {
        curr_node->right = insert_tree_node(curr_node->right, new_node);
        return curr_node;
    }
}
