// K-d-Trees in Nearest Neighbour Searches.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>

#define dim 5

using namespace std;

int no_of_neighbours = 0;

typedef struct Node {
    float key[dim];
    struct Node* left;
    struct Node* right;
    struct Node* p;
    int depth;
    int side;
}node;

typedef struct {
    node* root;
}KDTree;

void initializePoint(node* z) 
{
    for (int i = 0; i < dim; i++) 
    {
        float r1 = rand() % 100;
		int	r2 = rand() % 2;
	    z->key[i] = (r1 / 10.0) * pow(-1, r2);
    }
    z->depth = 0;
    z->side = 0;
    z->left = NULL;
    z->right = NULL;
    z->p = NULL;
}

int distfbox(node* z, node* q) 
{
    int d = 0 ;
    int index{ (z->depth) - 1 };
    if (z->depth != 0) 
    {
        if (z->side == 1) {
            d = (z->p)->key[index % dim] - q->key[index % dim];
        }
        else if (z->side == -1) {
            d = q->key[index % dim] - (z->p)->key[index % dim];
        }
    }
    else {
        d = 0;
    }
    if (d <= 0) 
    {
        return 0;
    }
    else {
        return d;
    }
}

double eucDist(node* z, node* q) 
{
    double sum = 0;
    for (int i = 0; i < dim; i++) 
    {
        sum += pow((z->key[i] - (q->key[i])), 2);
    }
    return sqrt(sum);
}

void printPoint(node* z) 
{
    cout << "(";
    for (int i = 0; i < dim; i++) {
        cout << z->key[i];
        if (i != dim - 1) {
            cout << ",";
        }
    }
    cout << ") ";
}

void buildRandomKDt(KDTree* bst, int num) 
{
    while (num--) {
        node* z = new node;
        initializePoint(z);
        printPoint(z);
        node* y = NULL;
        node* x = bst->root;
        int index = 0;
        while (x != NULL) 
        {
            y = x;
            if (z->key[index % dim] < x->key[index % dim]) 
            {
                x = x->left;
            }
            else {
                x = x->right;
            }
            index++;
        }
        z->depth = index;
        index--;
        z->p = y;
        if (y == NULL) 
        {
            bst->root = z;
        }
        else if (z->key[index % dim] < y->key[index % dim]) 
        {
            y->left = z;
            z->side = -1;
        }
        else {
            y->right = z;
            z->side = 1;
        }
    }
}

void inOrderTreeWalk(node* x) 
{
    if (x != NULL) {
        inOrderTreeWalk(x->left);
        printPoint(x);
        inOrderTreeWalk(x->right);
    }
}

typedef struct {
    double min;
    node* point;
}nearn;

void nn(node* z, node* q, nearn* near) 
{
    if (z != NULL && (distfbox(z, q) <= near->min)) 
    {
        if (near->min >= eucDist(z, q)) {
            near->min = eucDist(z, q);
            near->point = z;
        }
        if ((q->key[z->depth % dim] < z->key[z->depth % dim])) {
            if (z->left != NULL) {
                nn(z->left, q, near);
            }
            if (z->right != NULL) {
                nn(z->right, q, near);
            }
        }
        else {
            if (z->right != NULL) {
                nn(z->right, q, near);
            }
            if (z->left != NULL) {
                nn(z->left, q, near);
            }
        }
    }
}

void knn(node* z, node* q, double radius) 
{
    if (z != NULL && (distfbox(z, q) <= radius)) 
    {
        if (eucDist(z, q) <= radius) {
            printPoint(z);
            no_of_neighbours ++;
        }
        if ((q->key[z->depth % dim] < z->key[z->depth % dim])) 
        {
            if (z->left != NULL) {
                knn(z->left, q, radius);
            }
            if (z->right != NULL) {
                knn(z->right, q, radius);
            }
        }
        else {
            if (z->right != NULL) {
                knn(z->right, q, radius);
            }
            if (z->left != NULL) {
                knn(z->left, q, radius);
            }
        }
    }

}

int main()
{
    cout << "Building a KD Tree\n";
    int num = 200 ;
    KDTree* tree = new KDTree;
    tree->root = NULL;
    buildRandomKDt(tree, num);
    cout << endl << "Inorder traversal of the KD Tree" << endl;
    inOrderTreeWalk(tree->root);
    node* q = new node;
    initializePoint(q);
    cout <<endl<< "\nnearest neighbour of the point";
    printPoint(q);
    cout << ":" << endl;
    nearn* near = new nearn;
    near->point = NULL;
    near->min = 15;
    nn(tree->root, q, near);
    printPoint(near->point);
    double radius = 5;
    cout <<endl<< "\nneighbours of";
    printPoint(q);
    cout<<" under radius "<<radius<<":"<< endl;
    knn(tree->root, q, radius);
    cout <<endl<<"no_of_nearest_neignbours: "<<no_of_neighbours;
    delete(q);
    delete(tree);
    delete(near);
}
