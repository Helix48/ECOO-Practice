// assign_2_7_queueAndStack.cpp
//
// Will Lei
// This program will create a queue and a stack from a doubly-linked list

#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int data;
    node *prev;
    node *next;
};

// Declare necessary functions
void createList ();
void destroyList ();
void eraseNode ();
void stackInsert ();
void queueInsert ();
void printForward (node *curr);
void printBackward (node *curr);

node *start = new node, *last = new node;
int listSize = 0;

int main()
{
    int num;
    cin >> num;
    vector <int> outputs;

    // Allow the user to repeatedly enter in commands
    for (int i = 0; i < num; i++)
    {
        int input;
        cin >> input;

        // Check which command the input is
        switch (input)
        {
            // Erasing node
            case 1:
                if (listSize == 0)
                {
                    createList();
                }
                else
                {
                    queueInsert();
                }
                break;

            // Adding node
            case 2:
                eraseNode();
                break;

            // Printing forward
            case 3:
                outputs.push_back(last->data);
                break;
        }
    }

    for (int i = 0; i < outputs.size(); i++)
    {
        cout << outputs[i] << endl;
    }
    // Finish the program
    return 0;
}

// Function to create a linked list
void createList ()
{
    node *curr = new node, *newNode;
    int numNodes = 1, input;

    // Fill the linked list
    for (int i = 1; i <= numNodes; i++)
    {
        // Get input
        cin >> input;

        // Create the new node and fill it with data
        newNode = new node;
        newNode->data = input;
        newNode->next = NULL;
        newNode->prev = curr;

        // Check to see if this is the first node
        if (i == 1)
        {
            newNode->prev = NULL;
            start = newNode;
        }

        // Make the current node point to the new node and reset it
        curr->next = newNode;
        curr = newNode;
    }
    last = curr;
    listSize = numNodes;
}

// Function to destroy a linked list (delete all the nodes)
void destroyList ()
{
    int n = listSize;

    for (int i = 1; i <= n; i++)
        eraseNode();
}

// Function to erase a node
void eraseNode ()
{
    node *curr = last;

    // Allow for a list with only 1 node
    if (listSize == 1)
    {
        delete curr;
        start = NULL;
        last = NULL;
        listSize--;
        return;
    }

    // Repoint pointers
    last = curr->prev;
    curr->prev->next = NULL;

    delete curr;
    listSize--;
}

// Function to insert a new node before a given node
void stackInsert ()
{
    node *newNode = new node;
    int data;

    cout << "Enter the new node's integer: ";
    cin >> data;

    // Create the new node
    newNode->data = data;
    newNode->prev = last;
    newNode->next = NULL;

    // Repoint pointers
    newNode->prev->next = newNode;
    last = newNode;

    listSize++;
}

// Function to insert a new node after a given node
void queueInsert ()
{
    node *newNode = new node;
    int data;

    cin >> data;

    // Create the new node
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = start;

    // Repoint pointers
    newNode->next->prev = newNode;
    start = newNode;

    listSize++;

}

// Function to prints the linked list forwards
void printForward (node *curr)
{
    while (curr != NULL)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}


