//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Mason Grosko
// Version     : 1.0
// Date        : 2/16/2020
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"
#include "CSVparser.cpp"

using namespace std;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================
// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

struct Node {
    Bid current;
    Node* idLeft;
    Node* idRight;
    Node* amountParent;
    Node* amountLeft;
    Node* amountRight;

    Node(Bid bid) {
        current = bid;
        idLeft = NULL;
        idRight = NULL;
        amountParent = NULL;
        amountLeft = NULL;
        amountRight = NULL;
    }

    ~Node() {
        if (idLeft) {
            delete idLeft;
        }
        if (idRight) {
            delete idRight;
        }
        if (amountParent) {
            delete amountParent;
        }
        if (amountLeft) {
            delete amountLeft;
        }
        if (amountRight) {
            delete amountRight;
        }
    }
};



void displayBid(Bid bid) {
    cout
        << bid.bidId
        << ": "
        << bid.title
        << " | "
        << bid.amount
        << " | "
        << bid.fund
        << endl;

    return;
}


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
    private:
        Node* root;
        Node* amountRoot;
        void inIdOrder(Node* node);
        void inAmountOrder(Node* node);
        void insertId(Bid bid, Node* createdNode);
        void insertAmount(Bid bid, Node* createdNode);
        void removeNode(Node* rootNode, string removeBidId);
        void amountSearch(Node* node, double lowAmount, double highAmount);

    public:
        BinarySearchTree();
        virtual ~BinarySearchTree();
        void InIdOrder();
        void InAmountOrder();
        void Insert(Bid bid);
        void Remove(string bidId);
        Bid IdSearch(string bidId);
        void AmountSearch(double lowAmount, double highAmount);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = NULL;
    amountRoot = NULL;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    if (this->root) {
        delete root;
        delete amountRoot;
    }
}

/**
 * Traverse the tree in id order
 */
void BinarySearchTree::InIdOrder() {
    this->inIdOrder(this->root);
}

/**
* Traverse the tree in amount order
*/
void BinarySearchTree::InAmountOrder() {
    this->inAmountOrder(this->root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid inputBid) {
    Node* createdNode = new Node(inputBid);
    insertId(inputBid, createdNode);
    insertAmount(inputBid, createdNode);
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string removeBidId) {
    // FIXME (4a) Implement removing a bid from the tree
    removeNode(this->root, removeBidId);
}

/**
 * Search for a bid by id
 */
Bid BinarySearchTree::IdSearch(string searchBidId) {
    // FIXME (3) Implement searching the tree for a bid
    Bid bid;
    Node* testNode = this->root;

    while (testNode) {
        if (testNode->current.bidId == searchBidId) {
            bid = testNode->current;
            break;
        }
        if (searchBidId < testNode->current.bidId) {
            testNode = testNode->idLeft;
        }
        else {
            testNode = testNode->idRight;
        }
    }
    return bid;
}

/**
 * Search for bids by range of values
 */
void BinarySearchTree::AmountSearch(double lowAmount, double highAmount) {
    amountSearch(this->root, lowAmount, highAmount);
}

void BinarySearchTree::inIdOrder(Node* node) {
    if (node) {
        // Recursive call left
        inIdOrder(node->idLeft);

        // If left is done display current
        displayBid(node->current);

        // Recursive call right
        inIdOrder(node->idRight);
    }
}

void BinarySearchTree::inAmountOrder(Node* node) {
    if (node) {
        // Recursive call left
        inAmountOrder(node->amountLeft);

        // If left is done display current
        displayBid(node->current);

        // Recursive call right
        inAmountOrder(node->amountRight);
    }
}

void BinarySearchTree::insertId(Bid inputBid, Node* createdNode) {
    // FIXME (2a) Implement inserting a bid into the tree
    Node* prevNode = NULL;
    Node* testNode = this->root;
    string direction = "Z";

    while (testNode) {
        // cout << testNode->current.bidId;
        prevNode = testNode;
        if (inputBid.bidId < testNode->current.bidId) {
            direction = "L";
            testNode = testNode->idLeft;
        }
        else {
            direction = "R";
            testNode = testNode->idRight;
        }
    }

    if (not prevNode) {
        this->root = createdNode;
    }
    else {
        if (direction == "L") {
            prevNode->idLeft = createdNode;
        }
        else {
            prevNode->idRight = createdNode;
        }
    }
}

void BinarySearchTree::insertAmount(Bid inputBid, Node* createdNode) {
    Node* prevNode = NULL;
    Node* testNode = this->amountRoot;
    string direction = "Z";

    while (testNode) {
        // cout << testNode->current.amount;
        prevNode = testNode;
        if (inputBid.amount < testNode->current.amount) {
            direction = "L";
            testNode = testNode->amountLeft;
        }
        else {
            direction = "R";
            testNode = testNode->amountRight;
        }
    }

    if (not prevNode) {
        this->amountRoot = createdNode;
    }
    else {
        createdNode->amountParent = prevNode;
        if (direction == "L") {
            prevNode->amountLeft = createdNode;
        }
        else {
            prevNode->amountRight = createdNode;
        }
    }
}


void BinarySearchTree::removeNode(Node* rootNode, string removeBidId) {
    Node* parentNode = NULL;
    Node* currentNode = rootNode;
    while (currentNode) {
        // If we found bid
        if (currentNode->current.bidId == removeBidId) {
            // clean up amount order
            Node* amountParentNode = currentNode->amountParent;
            if (not currentNode->amountLeft && not currentNode->amountRight) {
                if (amountParentNode) {
                    if (amountParentNode->amountLeft == currentNode) {
                        amountParentNode->amountLeft = NULL;
                    }
                    else {
                        amountParentNode->amountRight = NULL;
                    }
                }
            }
            else if (currentNode->amountLeft && not currentNode->amountRight) {
                if (not amountParentNode) {
                    this->amountRoot = currentNode->amountLeft;
                }
                else if (amountParentNode->amountLeft == currentNode) {
                    amountParentNode->amountLeft = currentNode->amountLeft;
                }
                else {
                    amountParentNode->amountRight = currentNode->amountLeft;
                }
            }
            else if (not currentNode->amountLeft && currentNode->amountRight) {
                if (not amountParentNode) {
                    this->amountRoot = currentNode->amountRight;
                }
                else if (amountParentNode->amountLeft == currentNode) {
                    amountParentNode->amountLeft = currentNode->amountRight;
                }
                else {
                    amountParentNode->amountRight = currentNode->amountRight;
                }
            }
            else {
                Node* amountSuccessorNode = currentNode->amountRight;
                Node* amountSuccessorParent = currentNode;
                while (amountSuccessorNode->amountLeft) {
                    amountSuccessorParent = amountSuccessorNode;
                    amountSuccessorNode = amountSuccessorNode->amountLeft;
                }
                amountSuccessorNode->amountLeft = currentNode->amountLeft;
                amountSuccessorNode->amountRight = currentNode->amountRight;
                amountSuccessorParent->amountLeft = NULL;
            }


            // if neither left or right exist
            if (not currentNode->idLeft && not currentNode->idRight) {
                if (parentNode) {
                    if (parentNode->idLeft == currentNode) {
                        parentNode->idLeft = NULL;
                    }
                    else {
                        parentNode->idRight = NULL;
                    }
                }
            }
            // if only left exists
            else if (currentNode->idLeft && not currentNode->idRight) {
                if (not parentNode) {
                    this->root = currentNode->idLeft;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = currentNode->idLeft;
                }
                else {
                    parentNode->idRight = currentNode->idLeft;
                }
                currentNode->idLeft = NULL;
            }
            // if only right exists
            else if (currentNode->idRight) {
                if (not parentNode) {
                    this->root = currentNode->idRight;
                }
                else if (parentNode->idLeft == currentNode) {
                    parentNode->idLeft = currentNode->idRight;
                }
                else {
                    parentNode->idRight = currentNode->idRight;
                }
                currentNode->idRight = NULL;
            }
            // if both exist
            else {
                Node* successorNode = currentNode->idRight;
                Node* successorParent = currentNode;
                while (successorNode->idLeft) {
                    successorParent = successorNode;
                    successorNode = successorNode->idLeft;
                }
                successorNode->idLeft = currentNode->idLeft;
                successorNode->idRight = currentNode->idRight;
                successorParent->idLeft = NULL;
            }

            // Remove current node
            currentNode->idLeft = NULL;
            currentNode->idRight = NULL;
            currentNode->amountParent = NULL;
            currentNode->amountLeft = NULL;
            currentNode->amountRight = NULL;
            delete currentNode;
            currentNode = NULL;
        }
        // If removeBidId is less than current its in left branch
        else if (currentNode->current.bidId > removeBidId) {
            parentNode = currentNode;
            currentNode = currentNode->idLeft;
        }
        // Else right branch
        else {
            parentNode = currentNode;
            currentNode = currentNode->idRight;
        }
    }
    return;
}

void BinarySearchTree::amountSearch(Node* node, double lowAmount, double highAmount) {
    if (node) {
        // Recursive call left
        amountSearch(node->amountLeft, lowAmount, highAmount);

        // If left is done display current if it matches reqs
        if (node->current.amount >= lowAmount && node->current.amount <= highAmount) {
            displayBid(node->current);
        }

        // Recursive call right
        amountSearch(node->amountRight, lowAmount, highAmount);
    }
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    double amountHigh, amountLow;
    switch (argc) {
        case 2:
            csvPath = argv[1];
            bidKey = "98109";
            amountLow = 200;
            amountHigh = 500;
            break;
        case 3:
            csvPath = argv[1];
            bidKey = argv[2];
            amountLow = 200;
            amountHigh = 500;
            break;
        default:
            csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
            bidKey = "98109";
            amountLow = 200;
            amountHigh = 500;
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst = new BinarySearchTree();

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids by ID" << endl;
        cout << "  3. Display All Bids by Amount" << endl;
        cout << "  4. Find Bid by ID" << endl;
        cout << "  5. Find Bids in Amount Range" << endl;
        cout << "  6. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;


        switch (choice) {
            case 1:
                bst = new BinarySearchTree();

                // Initialize a timer variable before loading bids
                ticks = clock();

                // Complete the method call to load the bids
                loadBids(csvPath, bst);

                //cout << bst->Size() << " bids read" << endl;

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

            case 2:
                bst->InIdOrder();
                break;

            case 3:
                bst->InAmountOrder();
                break;
            
            case 4:
                ticks = clock();

                bid = bst->IdSearch(bidKey);

                ticks = clock() - ticks; // current clock ticks minus starting clock ticks

                if (!bid.bidId.empty()) {
                    displayBid(bid);
                }
                else {
                    cout << "Bid Id " << bidKey << " not found." << endl;
                }

                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
            
            case 5:
                bst->AmountSearch(amountLow, amountHigh);
                break;

            case 6:
                bst->Remove(bidKey);
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
