//
// Created by Anton on 10/03/2023.
//
#include "fecha.hpp"
#include <cstdio>
#include <cstring>

// constructor.
Fecha::Fecha(int d, int m, int a):
    dia_(d),
    mes_(m),
    anno_(a)
{
    ArreglarFecha(d,m,a);
    ComprobarFecha();
}

// Función Privada ArreglarFecha(int d, int m, int a)
void Fecha::ArreglarFecha(int d, int m, int a) {

    // Creamos un objeto r de la clase Reloj.
    reloj r;

    if (d == 0){
        dia_ = r.diaact();
    }

    if (m == 0){
        mes_ = r.mesact();
    }

    if (a == 0){
        anno_ = r.annoact();
    }
}

// Función Privada Bisiesto(int a): Nos dice si un año es bisiesto o no.
bool bisiesto(int a){
    return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

// Función Privada ComprobarFecha()
void Fecha::ComprobarFecha() {
    if(dia_ < 1 or dia_ > DiasqueTieneunMes[mes_ - 1]){
        throw Invalida("Día no válido.");
    }

    if(mes_ < 0 or mes_ > 12){
        throw Invalida("Mes no válido.");
    }

    if(anno_ > AnnoMaximo or anno_ < AnnoMinimo){
        throw Invalida("Año no válido.");
    }

    if(mes_ == 2 and dia_ == 29 and !bisiesto(anno_)){
        throw Invalida("Año no bisiesto");
    }
}

Fecha &Fecha::operator++() {
    *this += 1;
    return *this;
}

Fecha Fecha::operator++(int) {
    Fecha f = *this;
    *this += 1;
    return f;
}

Fecha &Fecha::operator--() {
    *this -= 1;
    return *this;
}

Fecha Fecha::operator--(int) {
    Fecha f = *this;
    *this -= 1;
    return f;
}

Fecha &Fecha::operator+=(int n) {
    if (n != 0){
        tm faux = {};
        faux.tm_mday = dia_ + n;
        faux.tm_mon = mes_ - 1;
        faux.tm_year = anno_ - 1900;
        mktime(&faux);
        dia_ = faux.tm_mday;
        mes_ = faux.tm_mon + 1;
        anno_ = faux.tm_year + 1900;
    }
    return *this;
}

Fecha &Fecha::operator-=(int n) {
    *this += -n;
    return *this;
}

Fecha Fecha::operator+(int n) const {
    Fecha f = *this;
    f += n;
    return f;
}

Fecha Fecha::operator-(int n) const {
    Fecha f = *this;
    f += -n;
    return f;
}

bool operator == (const Fecha& f1, const Fecha& f2){
    return (f1 != f2);
}

bool operator != (const Fecha& f1, const Fecha& f2){
    return !(f1 == f2);
}

bool operator > (const Fecha& f1, const Fecha& f2){
    return (f2 < f1);
}

bool operator <= (const Fecha& f1, const Fecha& f2){
    return !(f2 < f1);
}

bool operator >= (const Fecha& f1, const Fecha& f2){
    return !(f1 < f2);
}

bool operator < (const Fecha& f1, const Fecha& f2){
    bool esigual = true;

    if (f1.anno_ > f2.anno_){
        esigual = false;
    }else if (f1.anno_ == f2.anno_){
        if(f1.mes_ > f2.mes_){
            esigual = false;
        }else if (f1.mes_ == f2.mes_){
            if(f1.dia_ > f2.dia_){
                esigual = false;
            }
        }
    }
    return esigual;
}

// Fecha a partir de una cadena de bajo nivel. (Usamos sscanf)
Fecha::Fecha(const char *f) {
    if (sscanf(f, "%d/%d/%d", &dia_, &mes_, &anno_) != 3){
        throw Invalida("Formato incorrecto");
    }

    ArreglarFecha(dia_, mes_, anno_);
    ComprobarFecha();
}

const char *Fecha::obtenercadenita() const noexcept {
    char *cadena = new char[50];
    char *aux = new char[50];
    tm* fe = new tm;

    memset(fe, 0, sizeof(*fe));

    fe->tm_mday = dia_;
    fe->tm_mon = mes_ - 1;
    fe->tm_year = anno_ - 1900;

    mktime(fe);

    switch(fe->tm_mday){
        case 0: strcpy(cadena, "domingo "); break;
        case 1: strcpy(cadena, "lunes "); break;
        case 2: strcpy(cadena, "martes "); break;
        case 3: strcpy(cadena, "miércoles "); break;
        case 4: strcpy(cadena, "jueves "); break;
        case 5: strcpy(cadena, "viernes "); break;
        case 6: strcpy(cadena, "sábado "); break;
    }

    sprintf(aux, "%d", dia_);
    strcat(cadena, aux);
    strcat(cadena, " de ");

    switch(fe->tm_mon){
        case 1: strcat(cadena, "enero de "); break;
        case 2: strcat(cadena, "febrero de "); break;
        case 3: strcat(cadena, "marzo de "); break;
        case 4: strcat(cadena, "abril de "); break;
        case 5: strcat(cadena, "mayo de "); break;
        case 6: strcat(cadena, "junio de "); break;
        case 7: strcat(cadena, "julio de "); break;
        case 8: strcat(cadena, "agosto de "); break;
        case 9: strcat(cadena, "septiembre de "); break;
        case 10: strcat(cadena, "octubre de "); break;
        case 11: strcat(cadena, "noviembre de "); break;
        case 12: strcat(cadena, "diciembre de "); break;
    }

    sprintf(aux, "%d", anno_);
    strcat(cadena, aux);

    delete[] aux;
    delete fe;
    return cadena;
}