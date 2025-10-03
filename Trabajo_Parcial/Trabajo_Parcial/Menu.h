#pragma once
#include "Headers.h"

void mostrarMenuAcceso() {
	cout << "=== BIENVENIDO AL SISTEMA DE ENCOMIENDAS ===\n";
	cout << "1. Registrarse\n";
	cout << "2. Iniciar Sesion\n";
	cout << "3. Salir\n";
	cout << "Opcion: ";
}

void mostrarMenuCliente() {
	cout << "\n=== MENU CLIENTE ===\n";
	cout << "1. Registrar envio\n";
	cout << "2. Buscar envio por ID\n";
	cout << "3. Ver historial Tracking\n";
	cout << "4. Ver ultima ubicacion\n";
	cout << "5. Registrar pago\n";
	cout << "6. Mostrar mis pagos\n";
	cout << "7. Mostrar mis envios\n";
	cout << "0. Cerrar sesion\n";
}

void mostrarMenuAdmin() {
	cout << "=== MENU ADMINISTRADOR ===\n";
	cout << "1. Buscar envio por ID\n";
	cout << "2. Eliminar envio por ID\n";
	cout << "3. Actualizar estado\n";
	cout << "4. Agregar ubicacion Tracking\n";
	cout << "5. Ver historial Tracking\n";
	cout << "6. Ver ultima ubicacion\n";
	cout << "7. Mostrar cola de pendientes\n";
	cout << "8. Procesar siguiente envio\n";
	cout << "9. Mostrar todos los pagos\n";
	cout << "10. Mostrar lista completa de envios\n";
	cout << "0. Cerrar sesion\n";
}