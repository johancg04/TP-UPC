#pragma once
#include "Envio.h"
#include "Headers.h"

template <typename T>
class Pago
{
private:
	string dniUsuario;
	string metodo;
	T monto;
	int idEnvio;
public:
	Pago() {
		this->dniUsuario = "";
		this->metodo = "";
		this->monto = 0;
		this->idEnvio = 0;
	}

	Pago(string dni, string metodo, Envio* envio) {
		this->dniUsuario = dni;
		this->metodo = metodo;
		this->monto = envio->getCosto();
		this->idEnvio = envio->getId();
    }

    Pago(string dni, string metodo, T monto) {
        this->dniUsuario = dni;
        this->metodo = metodo;
        this->monto = monto;
        this->idEnvio = 0;
    }

	~Pago(){}

    string getDni() const { return dniUsuario; }
    string getMetodo() const { return metodo; }
    T getMonto() const { return monto; }

	void registrarPago() {
		ofstream archivo("pagos.txt", ios::app);
		archivo << "---------PAGO---------\n";
		archivo << "DNI:" << dniUsuario << "\n";
		archivo << "ID:" << idEnvio << "\n";
		archivo << "Metodo:" << metodo << "\n";
		archivo << "Monto:" << monto << "\n";
		archivo << "----------------------\n";
		archivo.close();

		cout << "Pago registrado correctamente\n";
	}

	void mostrarPagos(const string& dniFiltro = "") {
		ifstream archivo("pagos.txt");
		if (!archivo.is_open()) {
			cout << "Error al abrir pagos.txt\n";
			return;
		}

		string linea;
		string dniArchivo, metodoArchivo, montoArchivo, idArchivo;

		cout << "\n===== LISTA DE PAGOS =====\n";
		while (getline(archivo, linea)) {
			if (linea.rfind("DNI:", 0) == 0) {
				dniArchivo = linea.substr(4);
			}
			else if(linea.rfind("ID:", 0) == 0) {
				idArchivo = linea.substr(3);
			}
			else if (linea.rfind("Metodo:", 0) == 0) {
				metodoArchivo = linea.substr(7);
			}
			else if (linea.rfind("Monto:", 0) == 0) {
				montoArchivo = linea.substr(6);

				if (dniFiltro == "" || dniArchivo == dniFiltro) {
					cout << "DNI: " << dniArchivo << "\n";
                    cout << "ID: " << idArchivo << "\n";
					cout << "Metodo: " << metodoArchivo << "\n";
					cout << "Monto: " << montoArchivo << "\n";
					cout << "-------------------\n";
				}

				dniArchivo = "";
				metodoArchivo = "";
				montoArchivo = "";
                idArchivo = "";
			}
		}
		archivo.close();
	}

    void merge(vector<Pago<T>>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Pago<T>> L(n1), R(n2);

        for (int i = 0; i < n1; i++) {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = arr[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i].getMonto() <= R[j].getMonto()) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k++] = L[i++];
        }
        while (j < n2){
            arr[k++] = R[j++];
        }
    }

    void mergeSort(vector<Pago<T>>& arr, int left, int right) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    void mostrarPagosOrdenadosPorCosto() {
        ifstream archivo("pagos.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir archivo de pagos.\n";
            return;
        }

        vector<Pago<T>> pagos;
        string linea, d, m;
        T mon;

        while (getline(archivo, linea)) {
            if (linea.rfind("DNI:", 0) == 0) {
                d = linea.substr(4);
            }
            else if (linea.rfind("Metodo:", 0) == 0) {
                m = linea.substr(7);
            }
            else if (linea.rfind("Monto:", 0) == 0) {
                mon = stod(linea.substr(6));
            }
            else if (linea == "----------------------") {
                pagos.push_back(Pago<T>(d, m, mon));
            }
        }
        archivo.close();

        if (pagos.empty()) {
            cout << "No hay pagos registrados.\n";
            return;
        }

        mergeSort(pagos, 0, pagos.size() - 1);

        cout << "\n===== PAGOS ORDENADOS POR MONTO =====\n";
        for (auto& p : pagos) {
            cout << "DNI: " << p.getDni() << "\n";
            cout << "Metodo: " << p.getMetodo() << "\n";
            cout << "Monto: S/." << p.getMonto() << "\n";
            cout << "-------------------\n";
        }
    }
};