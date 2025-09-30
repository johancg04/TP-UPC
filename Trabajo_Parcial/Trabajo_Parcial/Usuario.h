#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Usuario {
private:
    string dni;
    string nombre;
    string correo;
    string direccion;
    string telefono;
    string password;

public:
    Usuario() {}

    Usuario(string d, string n, string c, string dir, string t, string p) {
        dni = d;
        nombre = n;
        correo = c;
        direccion = dir;
        telefono = t;
        password = p;
    }

    string getCorreo() { return correo; }

    string getNombre() { return nombre; }

    void registrarUsuario() {
        cout << "=== REGISTRO DE USUARIO ===\n";
        cout << "DNI: "; cin >> dni;
        cout << "Nombre: "; cin.ignore(); getline(cin, nombre);
        cout << "Correo: "; getline(cin, correo);
        cout << "Direccion: "; getline(cin, direccion);
        cout << "Telefono: "; getline(cin, telefono);
        cout << "Password: "; getline(cin, password);

        for (char c : telefono) {
            if (!isdigit(c)) {
                cout << "Telefono invalido. Debe contener solo numeros.\n";
                return;
            }
        }

        ofstream archivo("usuarios.txt", ios::app);
        if (!archivo.is_open()) {
            cout << "Error al abrir archivo de usuarios.\n";
            return;
        }

        archivo << "DNI:" << dni << endl;
        archivo << "Nombre:" << nombre << endl;
        archivo << "Correo:" << correo << endl;
        archivo << "Direccion:" << direccion << endl;
        archivo << "Telefono:" << telefono << endl;
        archivo << "Password:" << password << endl;
        archivo << "----" << endl;

        archivo.close();
        cout << "Usuario registrado exitosamente.\n";
    }

    bool iniciarSesion(const string& correoIngresado, const string& passwordIngresado) {
        ifstream archivo("usuarios.txt");
        if (!archivo.is_open()) {
            cout << "Error al abrir archivo de usuarios.\n";
            return false;
        }

        string linea;
        string correoArchivo, passArchivo;
        while (getline(archivo, linea)) {
            if (linea.rfind("Correo:", 0) == 0) {
                correoArchivo = linea.substr(7);
            }
            else if (linea.rfind("Password:", 0) == 0) {
                passArchivo = linea.substr(9);
                if (correoArchivo == correoIngresado && passArchivo == passwordIngresado) {
                    archivo.close();
                    return true;
                }
            }
        }

        archivo.close();
        return false;
    }
};
