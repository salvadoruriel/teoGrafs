#include "mat_cir.hpp"

using namespace std;

int checkCir(MatrizI &matinc){
    int testing;
    int found;
    //cout <<endl <<"ENTRANDO CHECK Presione ENTER para continuar... " ;
    //cin.get();
    for(int i=0; i< matinc.get_renglones() ; i++){
        found=0;
        for(int j=0; j< matinc.get_columnas() ; j++){
            testing = matinc.get_val(i,j);
            //cout << i << " " << j << ";" ;
            switch(testing){
                case 1:{ //revisando por un 1
                    found= 1;
                    i=matinc.get_renglones(); //exito en esta columna
                    break;}
                case 0:
                    break;
                default:
                    return -2; //invalid character
                    break;
            }
        }
        if(found==0) return -1; //renglon de ceros
    }
    int prim,seg;
    for(int i=0; i< matinc.get_renglones() ; i++) //probando renglones distintos
        for(int isig=i+1; isig< matinc.get_renglones() ; isig++)
            for(int j=0; j< matinc.get_columnas() ; j++){
                prim =matinc.get_val(i,j);
                seg =matinc.get_val(isig,j);
                if( prim!= seg  ) break;
                if( j==matinc.get_columnas()-1 ){
                    return -3; //renglones iguales
                }
            }
return 0;} //success

int mat_cir(){
    char adyopt,c;
    int rens,cols,con=0,hay=0,sum;
    MatrizI *matcir;

    cout<< endl <<"Ingrese el tamanio de la Matriz de Circuito, (renglon columna):"<< endl;
    while (1) {
      if (cin >> rens >> cols  &&  rens>0 && cols>0) break; // Dato valido
      else {
          cout << " Datos no validos" << endl;
          cin.clear();
          while (cin.get() != '\n') ; //vaciar hasta el enter
      }
    }
    cin.get();

    try{ //Remember new throws exceptions, in cpp yes
        matcir = new MatrizI(rens,cols);
    }catch(const std::bad_alloc& e){
        std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
            <<std::endl << "Error: " << e.what() << std::endl;
        return -1;
    }

    cout << (*matcir).inputMatDisplay(1) << endl;

    while(con!=0){
        cout << (*matcir).inputMatDisplay(0) ;

        con = checkCir(*matcir);
        if(con != 0){
                //<< con
        cout<< endl <<"La matriz no es valida, revise que solo halla "
                << "\"1\" y \"0\", y que no hay renglon de 0s "
                << "ni renglones iguales. "<< endl;
        cout <<endl <<"Presione ENTER para continuar... " ;
        cin.get();
        }
    }
    cout << endl << "Consideracion 3: " ;
    int con3aristasSinUsar=0;
    for(int j =0; j< cols ; j++){
        sum=0;
        for(int i =0; i < rens ; i++){
            sum += (*matcir).get_val(i,j);
        }
        if(sum==0){
            cout <<endl << "-La arista E" << j << " no se usa en algun "
            << "circuito." ;
            con3aristasSinUsar=1;
        }
    }
    if(con3aristasSinUsar == 0) cout << "No hay aristas sin usar en los circuitos dados."  << endl;
    else cout << endl;

    cout << endl << "Consideracion 6: ";
    int con6bucles=0;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += (*matcir).get_val(i,j);
        }
        if(sum==1){
            cout <<endl << "-El circuito " << i << " es un bucle.";
            con6bucles=1;
        }
    }
    if(con6bucles == 0) cout << "No hay circuitos de bucles." << endl;
    else cout << endl;

    cout << endl << "Consideracion 7: ";
    int con7paralelas=0;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += (*matcir).get_val(i,j);
        }
        if(sum==2){
            cout <<endl << "-El circuito " << i << " tiene lineas paralelas"
                << " en la grafica (o recurrentes en una digrafica).";
            con7paralelas=1;
        }
    }
    if(con7paralelas == 0) cout << "No hay circuitos de lineas paralelas (o recurrentes)." << endl;
    else cout << endl;

    cout << endl << "Consideracion 8: "<<endl;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += (*matcir).get_val(i,j);
        }
        cout  << "-Longitud del circuito " << i << ": " << sum <<endl;
    }

    cout << endl << "Consideracion 19: " <<endl;
    for(int j =0; j< cols ; j++){
        sum=0;
        for(int i =0; i < rens ; i++){
            sum += (*matcir).get_val(i,j);
        }
        cout  << "-La proporcion de uso de la arista " << j
        << " es: " << static_cast<double>(sum)/rens <<endl;
    }

return 0;}
