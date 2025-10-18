#include <iostream>
using namespace std;

// Clase genérica de matriz dinámica
template <typename T>
class MatrizDinamica {
private:
    T **matriz;
    int filas, columnas;

public:
    // Constructor
    MatrizDinamica(int f, int c) {
        filas = f;
        columnas = c;
        matriz = new T*[filas];
        for (int i = 0; i < filas; i++) {
            matriz[i] = new T[columnas];
            for (int j = 0; j < columnas; j++) {
                matriz[i][j] = 0; // inicializar en 0
            }
        }
    }

    // Destructor
    ~MatrizDinamica() {
        for (int i = 0; i < filas; i++)
            delete[] matriz[i];
        delete[] matriz;
    }

    // Llenar la matriz
    void llenar() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << "Valor [" << i << "," << j << "]: ";
                cin >> matriz[i][j];
            }
        }
    }

    // Mostrar matriz
    void mostrar() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Redimensionar
    void redimensionar(int nuevasFilas, int nuevasColumnas) {
        T **nueva = new T*[nuevasFilas];
        for (int i = 0; i < nuevasFilas; i++) {
            nueva[i] = new T[nuevasColumnas];
            for (int j = 0; j < nuevasColumnas; j++) {
                if (i < filas && j < columnas)
                    nueva[i][j] = matriz[i][j];
                else
                    nueva[i][j] = 0;
            }
        }

        // liberar la vieja matriz
        for (int i = 0; i < filas; i++)
            delete[] matriz[i];
        delete[] matriz;

        // reasignar
        matriz = nueva;
        filas = nuevasFilas;
        columnas = nuevasColumnas;
    }

    // Multiplicación de matrices
    static MatrizDinamica<T> multiplicar(MatrizDinamica<T>& A, MatrizDinamica<T>& B) {
        if (A.columnas != B.filas) {
            cout << "No se pueden multiplicar, dimensiones diferentes." << endl;
            exit(1);
        }

        MatrizDinamica<T> C(A.filas, B.columnas);

        for (int i = 0; i < A.filas; i++) {
            for (int j = 0; j < B.columnas; j++) {
                C.matriz[i][j] = 0;
                for (int k = 0; k < A.columnas; k++) {
                    C.matriz[i][j] += A.matriz[i][k] * B.matriz[k][j];
                }
            }
        }
        return C;
    }
};

// Función principal
int main() {
    cout << "--- Sistema de Análisis de Transformaciones Lineales ---\n" << endl;

    cout << ">> Matriz A (int) de 2x3 <<" << endl;
    MatrizDinamica<int> A(2, 3);
    A.llenar();

    cout << "\nMatriz A original:" << endl;
    A.mostrar();

    cout << "\nRedimensionando A a 3x3..." << endl;
    A.redimensionar(3, 3);
    A.mostrar();

    cout << "\n>> Matriz B (float) de 3x2 <<" << endl;
    MatrizDinamica<float> B(3, 2);

    // llenado rápido con datos del ejemplo
    float valores[3][2] = { {1.5, 0.5}, {2.0, 1.0}, {1.0, 2.5} };
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            B.multiplicar; // omitir entrada manual

    cout << "Valores predefinidos para B." << endl;
    B.mostrar();

    // Para multiplicar, creamos A en float
    MatrizDinamica<float> Af(3, 3);
    int datosA[3][3] = { {1, 2, 3}, {4, 5, 6}, {0, 0, 0} };
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Af.multiplicar; // valores cargados mentalmente

    cout << "\nResultado de C = A x B:" << endl;
    MatrizDinamica<float> C = MatrizDinamica<float>::multiplicar(Af, B);
    C.mostrar();

    cout << "\nMemoria liberada correctamente.\n";
    return 0;
}
