#include <iostream>
using namespace std;


struct Node {
    double value;
    Node* next;
    Node* prev;
    Node(double v = 0) : value(v), next(nullptr), prev(nullptr) {}
};

struct Row {
    Node* head;
    Row* next;
    Row* prev;
    Row() : head(nullptr), next(nullptr), prev(nullptr) {}
};

struct Matrix {
    Row* head;
    int n;

    Matrix(int size) : head(nullptr), n(size) {
        for (int i = 0; i < n; i++)
            AddRow();
    }

   
    void AddRow() {
        Row* r = new Row();
        for (int i = 0; i < n; i++)
            AddNode(r);

        if (!head) {
            head = r;
        } else {
            Row* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = r;
            r->prev = temp;
        }
    }

    void AddNode(Row* r) {
        Node* node = new Node(0.0);
        if (!r->head) {
            r->head = node;
        } else {
            Node* temp = r->head;
            while (temp->next) temp = temp->next;
            temp->next = node;
            node->prev = temp;
        }
    }
};

Node* getNode(Matrix& M, int i, int j) {
    Row* r = M.head;
    for (int k = 0; k < i; k++) r = r->next;

    Node* c = r->head;
    for (int k = 0; k < j; k++) c = c->next;

    return c;
}

double get(Matrix& M, int i, int j) {
    return getNode(M, i, j)->value;
}

void set(Matrix& M, int i, int j, double v) {
    getNode(M, i, j)->value = v;
}

void printMatrix(Matrix& M) {
    Row* r = M.head;
    while (r) {
        Node* c = r->head;
        while (c) {
            cout << c->value << " ";
            c = c->next;
        }
        cout << endl;
        r = r->next;
    }
    cout << endl;
}


void LU(Matrix& A, Matrix& L, Matrix& U) {
    int n = A.n;

    for (int i = 0; i < n; i++) {

        // ---------- حساب U ----------
        for (int j = i; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += get(L, i, k) * get(U, k, j);

            set(U, i, j, get(A, i, j) - sum);
        }

        
        for (int j = i; j < n; j++) {
            if (i == j) {
                set(L, i, i, 1.0);  // Lii = 1
            } else {
                double sum = 0;
                for (int k = 0; k < i; k++)
                    sum += get(L, j, k) * get(U, k, i);

                set(L, j, i, (get(A, j, i) - sum) / get(U, i, i));
            }
        }
    }
}

int main() {
    int n;

    cout << "Entrer la taille de la matrice (n x n): ";
    cin >> n;

    Matrix A(n), L(n), U(n);

    cout << "\nEntrer les elements de la matrice A :" << endl;

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double x;
            cout << "A[" << i << "][" << j << "] = ";
            cin >> x;
            set(A, i, j, x);
        }
    }

    cout << "\nMatrix A:" << endl;
    printMatrix(A);
    LU(A, L, U);
    cout << "\nMatrix L:" << endl;
    printMatrix(L);
    cout << "\nMatrix U:" << endl;  
    printMatrix(U);
    return 0;
}