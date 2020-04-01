#include <iostream>
#include "salvador_matriz_int.hpp"
#include "mat_ady_NoDir.hpp" //1
#include "mat_ady_dir.hpp" //2
#include "mat_inc_NoDir.hpp" //3
#include "mat_inc_dir.hpp" //4
#include "mat_acc.hpp" //5
#include "mat_cir.hpp" //6
#include "mat_tra.hpp" //7

using namespace std;

int main(){

    char opt,c;
    setlocale(LC_ALL,"");
    do{
        cout<< endl <<"~~Programa para Teoria de graficas~~"<< endl;
        cout<< endl<<"Seleccione matriz a analizar: "<< endl << endl
                 << "1 - Matriz de adyacencia No dirigida" << endl
                 << "2 - Matriz de adyacencia Dirigida" <<endl
                 << "3 - Matriz de Incidencia No dirigida" <<endl
                 << "4 - Matriz de Incidencia Dirigida" <<endl
                 << "5 - Matriz de accesibilidad" <<endl
                 << "6 - Matriz de circuito" <<endl
                 << "7 - Matriz de Trayectoria" <<endl
                 << "q - salir" << endl
                 << "--> ";
        while(scanf(" %c",&opt) != 1)
					while((c = getchar()) != '\n' && c != EOF);
		while((c = getchar()) != '\n' && c != EOF);

	    switch(opt){
            case '1':
                mat_ady_No_dir();
                break;

            case '2':
                mat_ady_dir();
                break;

            case '3':
                mat_inc_No_dir();
                break;

            case '4':
                mat_inc_dir();
                break;

            case '5':
                mat_acc();
                break;

            case '6':
                mat_cir();
                break;

            case '7':
                mat_tra();
                break;

            case 'Q':
            case 'q':
                cout << endl << "Fin de programa" << endl <<endl
                    << "Integrantes: " << endl
                    << "Aguirre Andrade Salvador Uriel" << endl
                    << "Rodriguez Modesto Carlos Aldair" << endl;
                break;

            default:
                cout <<endl <<"Opcion incorrecta" << endl;
                break;
	    }
        cout <<endl <<"Presione ENTER para continuar... " ;
        cin.get();
		#ifdef _WIN32
                system("cls"); /*WARNING: Comando especifico de WINDOWS*/
		#endif
	}while(opt != 'q' && opt != 'Q');

return 0;}

