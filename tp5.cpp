#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct{
    int TareaID;   //Numerado en ciclo iterativo
    char* Descripcion;
    int Duracion;  //entre 10-100
}Tarea;


struct N{
    Tarea T;
    struct N *siguiente;
};
typedef struct N Tnodo;



Tnodo * CrearListaVacia();
Tnodo *CrearNodo(int id);
void AgregarTarea(Tnodo **start,Tnodo *tarea);
void MostrarTareas(Tnodo *start,Tnodo *realizadas);
Tnodo *QuitarNodo(Tnodo **start,int id);

int main(){
srand (time(NULL));

int opcion,id;
Tnodo *NuevaTarea;
Tnodo * Tpendientes = CrearListaVacia();
Tnodo * Trealizadas = CrearListaVacia();






    do{
		printf("1.Agregar Tarea\n");
        printf("2.Mostrar Tareas Realizadas y Pendientes\n");
		printf("3.Marcar Tareas ya Realizadas\n");
		printf("4.Salir\n");
        printf("Opcion: ");
		scanf("%d", &opcion);

        switch(opcion) {
            case 1: {
                id = id +1;
                NuevaTarea = CrearNodo(id);
                AgregarTarea(&Tpendientes,NuevaTarea);
                printf("\n");
                break;
            }
            case 2: {
                MostrarTareas(Tpendientes,Trealizadas);
                break;
            }
            case 3: {
                char respuesta[3];
                Tnodo *aux = Tpendientes;
                while(aux!=NULL){
                    printf("\nSe completo la tarea ID: %d?\n Descripcion de tarea: %s\n SI/NO: ",aux->T.TareaID,aux->T.Descripcion);
                    scanf("%s",respuesta);

                    if(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0 || strcmp(respuesta,"Si") == 0){
                        Tnodo* NodoAux;
                        int IDaux = aux->T.TareaID;
                        aux = aux->siguiente;
                        NodoAux = QuitarNodo(&Tpendientes,IDaux); 
                        AgregarTarea(&Trealizadas,NodoAux);
                    }else{
                        aux = aux->siguiente;
                    }
                    
                }
            }
        }
    }while(opcion != 4);

    scanf(" %c");
    return 0;
}



//////////////////////////////FUNCIONES////////////////////////////////
Tnodo * CrearListaVacia(){
    return NULL;
}


Tnodo *CrearNodo(int id){
    char descripcion[100];
    Tnodo *aux = (Tnodo*) malloc(sizeof(Tnodo));

    aux->T.TareaID = id;
    aux->T.Duracion = rand() % 91+10;

    printf("Descripcion de la tarea ID %d: ",id);
    scanf("%s",descripcion);
    aux->T.Descripcion = (char*) malloc(strlen(descripcion)+1 * sizeof(char));
    strcpy(aux->T.Descripcion,descripcion);

    aux->siguiente = NULL;

    return aux;
}



void AgregarTarea(Tnodo **start,Tnodo *tarea){ //Agrego tareas en forma de fila
    tarea->siguiente = *start;
    *start = tarea;
}




void MostrarTareas(Tnodo *start, Tnodo *realizadas){

    printf("\nTAREAS PENDIENTES:\n");
    while(start != NULL){
        printf("\nID de tarea: %d\n",start->T.TareaID);
        printf("Descripcion: %s\n",start->T.Descripcion);
        printf("Duracion: %d\n",start->T.Duracion);
        printf("--------------------------------------\n");
        start = start->siguiente;
    }

    printf("\nTAREAS REALIZADAS:\n");
     while(realizadas != NULL){
        printf("\nID de tarea: %d\n",realizadas->T.TareaID);
        printf("Descripcion: %s\n",realizadas->T.Descripcion);
        printf("Duracion: %d\n",realizadas->T.Duracion);
        printf("--------------------------------------\n");
        realizadas = realizadas->siguiente;
    }
    printf("\n\n");
}


Tnodo *QuitarNodo(Tnodo **start,int id){
   if(*start != NULL){
       Tnodo *aux = *start;
       Tnodo *temp;
        if(aux->T.TareaID == id){ //Si el primer nodo es igual al id entonces apunto start al segundo nodo y retorno el primero
            *start = (*start)->siguiente;
            return aux;
        }else{
            while((aux->siguiente)->T.TareaID != id){ //Mientras el siguiente nodo sea != al id, avanzo de nodo
                aux = aux->siguiente;
            }
            temp = aux->siguiente; //Guardo el nodo que buscaba
            aux->siguiente = (aux->siguiente)->siguiente; //Hago que el nodo apunte al siguiente que apuntaba el que voy a quitar
            return temp;
        }

   }
}




