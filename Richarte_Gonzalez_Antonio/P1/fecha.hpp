//
// Created by Anton on 10/03/2023.
//

#ifndef P0_FECHA_HPP
#define P0_FECHA_HPP
#include <ctime>
#include <iostream>

using namespace std;

bool Bisiesto (int anno);

class Fecha{
public:

    // constructores.
    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const char* f);

    // funciones observadoras.
    int dia() const { return dia_; };
    int mes() const { return mes_; };
    int anno() const { return anno_; };

    // excepciones.
    class Invalida{
    public:
        Invalida(const char* inv): fallo(inv) {}
        const char* por_que() { return fallo; };
    private:
        const char* fallo;
    };

    // constantes a definir.
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    // Operadores para incrementar o decrementar una fecha
    Fecha& operator ++();                   // Preincrementa
    Fecha operator ++(int);                 // Postincrementa
    Fecha& operator --();                   // Predecrementa
    Fecha operator --(int);                 // Postdecrementa
    Fecha operator +(int n) const;
    Fecha operator -(int n) const;
    Fecha& operator +=(int n);
    Fecha& operator -=(int n);

    // Operadores para comparar dos fechas.
    friend bool operator == (const Fecha& f1, const Fecha& f2);
    friend bool operator != (const Fecha& f1, const Fecha& f2);
    friend bool operator > (const Fecha& f1, const Fecha& f2);
    friend bool operator < (const Fecha& f1, const Fecha& f2);
    friend bool operator >= (const Fecha& f1, const Fecha& f2);
    friend bool operator <= (const Fecha& f1, const Fecha& f2);

    // Esta clase reloj nos sirve para poder dar la fecha del sistema.
    class reloj {
    public:
        static int diaact() {
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mday;
        }

        static int mesact() {
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_mon + 1;
        }

        static int annoact() {
            std::time_t tiempo_calendario = std::time(nullptr);
            std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
            return tiempo_descompuesto->tm_year + 1900;
        }
    };

    const char* cadena() const noexcept { return obtenercadenita(); };

private:
    int dia_, mes_, anno_;

    // función auxiliar que nos permite arreglar la fecha en el caso de que el dia, mes o el año sea 0.
    void ArreglarFecha(int d, int m, int a);

    // función auxiliar que nos permite comprobar que la fecha introducida es correcta. En el caso de que falle algo,
    // con throw lanzaremos la excepción adecuada con su respectivo mensaje de error.
    void ComprobarFecha();

    // vector de enteros que almacena los días que tiene cada mes del año.
    int DiasqueTieneunMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Esta función nos permite hacer la conversión de la fecha en números a una cadena con palabras.
    const char* obtenercadenita() const noexcept;
};

ostream& operator << (ostream& os, const Fecha& f);
istream& operator >> (istream& is, Fecha& f);
#endif //P0_FECHA_HPP
