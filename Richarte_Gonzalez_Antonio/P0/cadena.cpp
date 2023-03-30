//
// Created by Anton on 19/03/2023.
//
#include "cadena.hpp"
#include <cstring>


Cadena::Cadena(unsigned t, char s):
    s_(new char[t + 1]),
    tam_(t)
{
    for(unsigned i = 0; i < tam_; i++){
        s_[i] = s;
    }
    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena &c):
    s_(new char[c.tam_ + 1]),
    tam_(c.tam_)
{
    for(unsigned i = 0; i < tam_; i++){
        s_[i] = c.s_[i];
    }
    s_[tam_] = '\0';
}

Cadena::Cadena(const char *cad):
    s_(new char [(unsigned) strlen(cad) + 1]),
    tam_((unsigned) strlen(cad))
{
    for(unsigned i = 0; i < tam_; i++){
        s_[i] = cad[i];
    }
    s_[tam_] = '\0';
}

Cadena &Cadena::operator=(const Cadena &c2) {

    // evitamos autoasignación.
    if(this != &c2){
        if(tam_ != c2.tam_){
            delete[] s_;
            tam_ = c2.tam_;
            s_ = new char[tam_ + 1];
        }

        for (unsigned i = 0; i < tam_; i++){
            s_[i] = c2.s_[i];
        }
        s_[tam_] = '\0';
    }

    return *this;
}

Cadena &Cadena::operator=(const char *cad) {

    // Creamos una cadena con la cadena de bajo nivel.
    Cadena cadenanueva(cad);
    delete[] cad;
    if(tam_ != cadenanueva.tam_){
        delete[] s_;
        tam_ = cadenanueva.tam_;
        s_ = new char[tam_ + 1];
    }

    for (unsigned i = 0; i < tam_; i++){
        s_[i] = cadenanueva.s_[i];
    }
    s_[tam_] = '\0';
    return *this;
}

Cadena &Cadena::operator+=(const Cadena &c2) {
    char* cadaux = new char[tam_ + c2.tam_ + 1];

    // copiamos la primera cadena en la cadena que hemos creado antes.
    for(unsigned i = 0; i < tam_; i++){
        cadaux[i] = s_[i];
    }

    // ahora, copiamos la otra cadena justo después del último caracter introducido en la cadena ppal.
    for(unsigned i = tam_; i < tam_ + c2.tam_; i++){
        cadaux[i] = c2.s_[i - tam_];    // i - tam_ porque i = tam_.
                                        // por ej. tam_ = 5 i = tam_, pues si empezamos a copiar, 5 - 5 = 0, 5 - 4 = 1
                                        // y así sucesivamente hasta llegar al final de la segunda cadena.
    }

    // una vez que hayamos copiado la cadena, introducimos el carácter terminador.
    cadaux[tam_ + c2.tam_] = '\0';

    // ahora tenemos la cadena lista, pero no nos han dicho que tengamos que crear una cadena nueva, por lo tanto
    // tenemos que copiar cadaux en this.
    // borramos el antiguo contenido
    delete[] s_;

    // definimos el nuevo tamaño.
    tam_ = tam_ + c2.tam_;

    // reservamos memoria para albergar la nueva cadena.
    s_ = new char[tam_ + 1];

    // copiamos la cadena nueva a this.
    for (unsigned i = 0; i < tam_; i++){
        s_[i] = cadaux[i];
    }
    delete[] cadaux;
    // devolvemos this.
    return *this;
}

Cadena Cadena::operator+(const Cadena &c2) const {
    char* cadaux = new char[tam_ + c2.tam_ + 1];

    // copiamos la primera cadena en la cadena que hemos creado antes.
    for(unsigned i = 0; i < tam_; i++){
        cadaux[i] = s_[i];
    }

    // ahora, copiamos la otra cadena justo después del último caracter introducido en la cadena ppal.
    for(unsigned i = tam_; i < tam_ + c2.tam_; i++){
        cadaux[i] = c2.s_[i - tam_];    // i - tam_ porque i = tam_.
        // por ej. tam_ = 5 i = tam_, pues si empezamos a copiar, 5 - 5 = 0, 5 - 4 = 1
        // y así sucesivamente hasta llegar al final de la segunda cadena.
    }

    // una vez que hayamos copiado la cadena, introducimos el carácter terminador.
    cadaux[tam_ + c2.tam_] = '\0';

    // ahora tenemos la cadena lista, devolvemos esa cadena, pero hemos creado un char*, simplemente
    // creamos un objeto Cadena pasándole como parámetro cadaux.
    Cadena cad(cadaux);
    delete[] cadaux;
    // devolvemos la cadena.
    return cad;
}

// ahora, vamos a hacer cada uno de los operadores de comparación de la clase cadena.
bool operator ==(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1, c2) == 0);
}

bool operator !=(const Cadena& c1, const Cadena& c2){
    return !(c1 < c2);
}

bool operator >=(const Cadena& c1, const Cadena& c2){
    return !(c1 < c2);
}

bool operator <=(const Cadena& c1, const Cadena& c2){
    return !(c2 < c1);
}

bool operator >(const Cadena& c1, const Cadena& c2){
    return (c2 < c1);
}

bool operator <(const Cadena& c1, const Cadena& c2){
    return (strcmp(c1, c2) < 0);
}

char &Cadena::at(size_t i) {
    if((int)i < 0 or i >= tam_){
        throw std::out_of_range("Límites de rango excedidos.");
    }

    return s_[i];
}

char Cadena::at(size_t i) const {
    if((int)i < 0 or i >= tam_){
        throw std::out_of_range("Límites de rango excedidos.");
    }

    return s_[i];
}

Cadena Cadena::substr(size_t i, unsigned int tam) const {
    char* cadaux = new char[tam + 1];

    if((int)i < 0 or (int)tam < 0 or i + tam >= tam_){
        throw std::out_of_range("Límites de rangos excedidos.");
    }

    int j = (int)i;
    int cont = 0;

    while(cont < (int)tam){
        if(s_[i] == '\0'){
            throw std::out_of_range("Límites de rangos excedidos.");
        }else {
            cadaux[cont] = s_[j + cont];
            cont++;
        }
    }

    Cadena cad{cadaux};
    delete[] cadaux;
    return cad;

}