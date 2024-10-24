#include <iostream>
#include <cmath>  // Para usar sqrt en el cálculo del perímetro del triángulo

using namespace std;

// Interfaz Figura
class IFigura {
public:
    virtual void setNumLados(int n) = 0;
    virtual int getNumLados() const = 0;
    virtual double getArea() const = 0;
    virtual double getPerimetro() const = 0;
};

// Clase abstracta Figura
class Figura : public IFigura {
protected:
    int numLados;

public:
    // Constructor
    Figura(int n) : numLados(n) {}

    // Métodos concretos para numLados
    void setNumLados(int n) override {
        numLados = n;
    }

    int getNumLados() const override {
        return numLados;
    }

    // Métodos abstractos
    virtual double getArea() const = 0;
    virtual double getPerimetro() const = 0;
};

// Subclase concreta Rectangulo
class Rectangulo : public Figura {
private:
    double ancho;
    double alto;

public:
    // Constructor
    Rectangulo(double a, double h) : Figura(4), ancho(a), alto(h) {}

    // Métodos específicos de Rectangulo
    void setAncho(double a) {
        ancho = a;
    }

    void setAlto(double h) {
        alto = h;
    }

    double getArea() const override {
        return ancho * alto;
    }

    double getPerimetro() const override {
        return 2 * (ancho + alto);
    }
};

// Subclase concreta Triangulo
class Triangulo : public Figura {
private:
    double base;
    double altura;

public:
    // Constructor
    Triangulo(double b, double h) : Figura(3), base(b), altura(h) {}

    // Métodos específicos de Triangulo
    void setBase(double b) {
        base = b;
    }

    void setAltura(double h) {
        altura = h;
    }

    double getArea() const override {
        return (base * altura) / 2;
    }

    double getPerimetro() const override {
        // Asumimos que es un triángulo equilátero para este ejemplo
        return 3 * base;
    }
};

int main() {
    // Crear objetos Rectangulo y Triangulo
    Rectangulo rect(5, 7);
    Triangulo tri(5, 7);

    // Imprimir área y perímetro del rectángulo
    cout << "Rectángulo:" << endl;
    cout << "Área: " << rect.getArea() << endl;
    cout << "Perímetro: " << rect.getPerimetro() << endl;

    // Imprimir área y perímetro del triángulo
    cout << "Triángulo:" << endl;
    cout << "Área: " << tri.getArea() << endl;
    cout << "Perímetro: " << tri.getPerimetro() << endl;

    return 0;
}
