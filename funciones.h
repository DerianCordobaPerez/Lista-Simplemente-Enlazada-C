#ifndef FUNCIONES_H
#define FUNCIONES_H

#define longitud 30
#define listavacia (cabecera == NULL)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int codigo;
    char *nombres, *apellidos, *direccion;
    long int telefono;
} EstructuraPaciente;

typedef struct nodopaciente {
    EstructuraPaciente paciente;
    struct nodopaciente *siguiente;
} Paciente;

int obtenercodigo();
char *asignacion(int);
EstructuraPaciente leerpaciente(bool);
Paciente *crearnuevopaciente();
Paciente *asignacionpaciente(EstructuraPaciente);
void agregarpaciente(EstructuraPaciente, Paciente **);
void mostrarpacientes(Paciente *);
void mostrarpaciente(int, Paciente *);
void eliminarpaciente(int, Paciente **);
void actualizarpaciente(int, Paciente *);
void leerpacienteactualizar(Paciente *);
void inicializacion(void);
void menu(void);
void error(void);
void limpiar(void);

#endif