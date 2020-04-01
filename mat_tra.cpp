#include "mat_tra.hpp"
#include <vector>

using namespace std;

int checkTra(MatrizI &matinc){
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

int mat_tra(){
    char adyopt,c;
    int rens,cols,con=0,hay=0,sum;
    MatrizI *mattra;

    cout<< endl <<"Ingrese el tamanio de la Matriz Trayectoria, (renglon columna):"<< endl;
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
        mattra = new MatrizI(rens,cols);
    }catch(const std::bad_alloc& e){
        std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
            <<std::endl << "Error: " << e.what() << std::endl;
        return -1;
    }

    cout << (*mattra).inputMatDisplay(1) << endl;

    while(con!=0){
        cout << (*mattra).inputMatDisplay(0) ;

        con = checkTra(*mattra);
        if(con != 0){
                //<< con
        cout<< endl <<"La matriz no es valida, revise que solo halla "
                << "\"1\" y \"0\", y que no hay renglon de 0s "
                << "ni renglones iguales. "<< endl;
        cout <<endl <<"Presione ENTER para continuar... " ;
        cin.get();
        }
    }

    cout << endl << "Consideracion 7: " ;
    int con7aristasSinUsar=0;
    for(int j =0; j< cols ; j++){
        sum=0;
        for(int i =0; i < rens ; i++){
            sum += (*mattra).get_val(i,j);
        }
        if(sum==0){
            cout <<endl << "-La arista E" << j << " no se usa en alguna "
            << "trayectoria." ;
            con7aristasSinUsar=1;
        }
    }
    if(con7aristasSinUsar == 0) cout << "No hay aristas sin usar en las trayectorias dadas."  << endl;
    else cout << endl;

    cout << endl << "Consideracion 8: ";
    int con8aristasSiempreUsadas=0;
    for(int j =0; j< cols ; j++){
        int found=0;
        for(int i =0; i < rens ; i++){
            if( (*mattra).get_val(i,j) == 0 ){
                found = 1;
                break;
            }
        }
        if(found==0){ //no hay 0s, solo 1s
            cout <<endl << "-La arista E" << j << " se usa en todas las "
            << "trayectorias." ;
            con8aristasSiempreUsadas=1;
        }
    }
    if(con8aristasSiempreUsadas == 0) cout << "No hay aristas que se usen en todas las trayectorias dadas."  << endl;
    else cout << endl;

    cout << endl << "Consideracion 12: "<<endl;
    int maslarg=0;
    vector<int> rutas;
    vector<int> rutascortas;
    vector<int> rutaslargas;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += (*mattra).get_val(i,j);
        }
        rutas.push_back(sum);
        cout  << "-Longitud de la trayectoria " << i << ": " << sum <<endl;
    }
    int mascort=sum;//solo para tener 1 valor asignado

    for(int i =0; i < rutas.size(); i++){
        if( rutas[i] > maslarg ) maslarg = rutas[i];
        if( rutas[i] < mascort ) mascort = rutas[i];
    }
    for(int i =0; i < rutas.size(); i++){
        if( rutas[i] == maslarg ) rutaslargas.push_back(i);
        if( rutas[i] == mascort ) rutascortas.push_back(i);
    }
    if( rutaslargas.size()>1 ){
        cout << "Las rutas mas largas son: ";
        for(int i=0; i < rutaslargas.size() ;i++ ){
            cout << rutaslargas[i] << (i == rutaslargas.size()-1 ? "." : ", " );
        }
    }
    else cout << "La ruta " <<rutaslargas[0] << " es la mas larga.";
    cout << endl;

    if( rutascortas.size()>1 ){
        cout << "Las rutas mas cortas son: ";
        for(int i=0; i < rutascortas.size() ;i++ ){
            cout << rutascortas[i] << (i == rutascortas.size()-1 ? "." : ", " );
        }
    }
    else cout << "La ruta " <<rutascortas[0] << " es la mas corta.";
    cout << endl;


    cout << endl << "Consideracion 13: " <<endl;
    for(int j =0; j< cols ; j++){
        sum=0;
        for(int i =0; i < rens ; i++){
            sum += (*mattra).get_val(i,j);
        }
        cout  << "-La proporcion de uso de la arista " << j
        << " es: " << static_cast<double>(sum)/rens <<endl;
    }

return 0;}
