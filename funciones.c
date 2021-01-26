#include "funciones.h"

void inicializacion(void) {
    Paciente *paciente = NULL, *liberacion;
    EstructuraPaciente cuerpopaciente;
    int opcion, codigo = 0;

    while(1) {
        do {
            menu();
            scanf("%i", &opcion);

            if(opcion < 1 && opcion > 6) puts("La opcion ingresada es incorrecta");
            else limpiar();

        } while (opcion < 1 && opcion > 6);

        switch(opcion) {
            case 1:
                cuerpopaciente = leerpaciente(false);
                agregarpaciente(cuerpopaciente, &paciente);
                break;

            case 2:
                codigo = obtenercodigo();
                eliminarpaciente(codigo, &paciente);
                break;

            case 3:
                codigo = obtenercodigo();
                actualizarpaciente(codigo, paciente);
                break;

            case 4:
                codigo = obtenercodigo();
                mostrarpaciente(codigo, paciente);
                break;
            
            case 5:
                mostrarpacientes(paciente);
                break;
            
            case 6:
                printf("\nPrograma Finzalizado\n\n");
                liberacion = paciente;
                while(liberacion != NULL) {
                    paciente = paciente->siguiente;
                    free(paciente);
                    liberacion = paciente;
                }
                exit(0);
        }
        putchar('\n');
    }
}

void error(void) {
    perror("Error al asignar memoria en la lista\n");
    exit(0);
}

void limpiar(void) {
	#if defined(__linux__) || defined(__unix__)
	    system("clear");
	#endif
	
	#if defined(_WIN32) || defined(_WIN64)
	    system("cls");
	#endif
}

void menu(void) {
    printf("1. Agregar Paciente\n2. Eliminar Paciente\n3. Actualizar Paciente\n4. Mostrar los datos de un paciente\n5. Mostrar los datos de todos los pacientes\n6. Salir\nElegir Opcion: ");
}

int obtenercodigo() {
    int codigo = 0;
    printf("Ingresar codigo del paciente: ");
    scanf("%i", &codigo);
    return codigo;
}

char *asignacion(int cantidad) {
    char *temp;
    if((temp = (char*)malloc(cantidad * sizeof(char))) == NULL)
        error();
    return temp;
}

EstructuraPaciente leerpaciente(bool bandera) {
    EstructuraPaciente paciente;
    char *cadena = asignacion(longitud);
    
    if(!bandera) {
        printf("Ingrese el codigo del paciente: ");
        scanf("%i", &paciente.codigo);
    } else puts("El codigo del paciente se mantendra igual\n");

    fflush(stdin);
    printf("Ingrese el nombre del paciente: ");
    scanf("%30s", cadena);
    paciente.nombres = asignacion(strlen(cadena) + 1);
    paciente.nombres = strdup(cadena);

    fflush(stdin);
    printf("Ingrese el apellido del paciente: ");
    scanf("%30s", cadena);
    paciente.apellidos = asignacion(strlen(cadena) + 1);
    paciente.apellidos = strdup(cadena);

    fflush(stdin);
    printf("Ingrese la direccion del paciente: ");
    scanf("%30s", cadena);
    paciente.direccion = asignacion(strlen(cadena) + 1);
    paciente.direccion = strdup(cadena);

    printf("Ingrese el numero de telefono del paciente: ");
    scanf("%li", &paciente.telefono);
    free(cadena);
    return paciente;
}

Paciente *crearnuevopaciente() {
    Paciente *paciente;
    if((paciente = (Paciente*)malloc(sizeof(Paciente))) == NULL)
        error();
    return paciente;
}

Paciente *asignacionpaciente(EstructuraPaciente nuevo) {
    Paciente *nodo;
    nodo = crearnuevopaciente();
    nodo->paciente.codigo = nuevo.codigo;
    nodo->paciente.nombres = asignacion(strlen(nuevo.nombres));
    strcpy(nodo->paciente.nombres, nuevo.nombres);
    nodo->paciente.apellidos = asignacion(strlen(nuevo.apellidos));
    strcpy(nodo->paciente.apellidos, nuevo.apellidos);
    nodo->paciente.direccion = asignacion(strlen(nuevo.direccion));
    strcpy(nodo->paciente.direccion, nuevo.direccion);
    nodo->paciente.telefono = nuevo.telefono;
    return nodo;
}

void agregarpaciente(EstructuraPaciente nuevo, Paciente **paciente) {
    Paciente *cabecera = *paciente;
    Paciente *actual = cabecera, *anterior = cabecera, *nodo;
    if(listavacia) {
        cabecera = asignacionpaciente(nuevo);
        cabecera->siguiente = NULL;
        *paciente = cabecera;
    }

    while(actual != NULL && nuevo.codigo > actual->paciente.codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if(anterior == actual) {
        nodo = asignacionpaciente(nuevo);
        nodo->siguiente = actual;
        cabecera = nodo;
    } else {
        nodo = asignacionpaciente(nuevo);
        nodo->siguiente = actual;
        anterior->siguiente = nodo;
    }
    *paciente = cabecera;
}

void mostrarpacientes(Paciente *cabecera) {
    if(listavacia) {
        puts("No existen pacientes actualmente");
        return;
    }
    printf("%10s %30s %30s %30s %9s", "Codigos", "Nombres", "Apellidos", "Direccion", "Telefonos\n");
    while(!listavacia) {
        printf("%10i %30s %30s %30s %9li\n", cabecera->paciente.codigo, cabecera->paciente.nombres, cabecera->paciente.apellidos, cabecera->paciente.direccion, cabecera->paciente.telefono);
        cabecera = cabecera->siguiente;
    }
}

void mostrarpaciente(int codigo, Paciente *cabecera) {
    if(listavacia) {
        puts("No existen pacientes actualmente");
        return;
    } else {
        while(cabecera != NULL && codigo != cabecera->paciente.codigo) cabecera = cabecera->siguiente;
        if(cabecera) {
            printf("%10s %30s %30s %30s %9s", "Codigos", "Nombres", "Apellidos", "Direccion", "Telefonos\n");
            printf("%10i %30s %30s %30s %9li\n", cabecera->paciente.codigo, cabecera->paciente.nombres, cabecera->paciente.apellidos, cabecera->paciente.direccion, cabecera->paciente.telefono);
        } else
            puts("El codigo ingresado no se encontro dentro de los pacientes");
    }
}

void eliminarpaciente(int codigo, Paciente **paciente) {
    Paciente *cabecera = *paciente;
    Paciente *actual = cabecera, *anterior = cabecera;

    if(listavacia) {
        puts("No hay pacientes actualmente");
        return;
    }

    while(actual != NULL && codigo != actual->paciente.codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual == NULL) {
        printf("El codigo del paciente no se ha encontrado\n");
        return;
    }

    if(anterior == actual)
        cabecera = cabecera->siguiente;
    else
        anterior->siguiente = actual->siguiente;
    free(actual);
    *paciente = cabecera;
    printf("\nPaciente eliminado correctamente\n");
}

void leerpacienteactualizar(Paciente *actual) {
    printf("Nuevo Nombre: ");
    scanf("%30s", actual->paciente.nombres);

    printf("Nuevo Apellido: ");
    scanf("%30s", actual->paciente.apellidos);

    printf("Nueva Direccion: ");
    scanf("%30s", actual->paciente.direccion);

    printf("Nuevo Telefono: ");
    scanf("%li", &actual->paciente.telefono);
}

void actualizarpaciente(int codigo, Paciente *cabecera) {
    Paciente *actual = cabecera;
    bool encontrado = false;
    if(listavacia) {
        puts("No hay pacientes actualmente");
        return;
    }
    
    while(actual != NULL && !encontrado) {
        if(codigo == actual->paciente.codigo) {
            leerpacienteactualizar(actual);
            actual->paciente.codigo = codigo;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if(!encontrado) puts("El codigo ingresado no se ha encontrado");
    else puts("Datos actualizados correctamente");
    
}