#include "mat_ady_dir.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int conectado(int nodo, MatrizI &matady, vector<int> &vec){
    for(int iren =0; iren< matady.get_columnas() ; iren++){ //conexion por renglon
        if(nodo == iren) continue;
        if( matady.get_val(nodo,iren) > 0 )
            if( find(vec.begin(), vec.end(), iren)
               == vec.end() ){ //didnt find
                //cout << ", " << iren; //DEBUGGING
                vec.push_back(iren);
                conectado(iren, matady, vec);
               }
    }
return 0;}

int mat_ady_dir(){
    char adyopt,c;
    int tam;
    MatrizI *matady;
    /*
    do{
        cout<< endl <<"Ingrese el tamanio de la Matriz de Adyacencia No Dirigida:"<< endl;
        while (1) {
          if (cin >> tam &&  tam >0) break; // Dato valido
          else {
              cout << " Dato no valido" << endl;
              cin.clear();
              while (cin.get() != '\n') ; //vaciar hasta el enter
          }
        }

        try{ //Remember new throws exceptions, in cpp yes
            matady = new Matriz(tam,tam);
        }catch(const std::bad_alloc& e){
            std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
                <<std::endl << "Error: " << e.what() << std::endl;
            return -1;
        }

        (*matady).ingresaMatriz();
        do{
            cout<< *matady << endl <<"Son correctos los datos?"<< endl
                << "S - si" << endl
                << "N - no" <<endl
                << "--> ";
            while(scanf(" %c",&adyopt) != 1)
                        while((c = getchar()) != '\n' && c != EOF);
            while((c = getchar()) != '\n' && c != EOF);

        }while(adyopt!='S' && adyopt!='s' &&
               adyopt!='N' && adyopt!='n');
        if(adyopt == 'N' || adyopt=='n') delete(matady);
    }while(adyopt!='S' && adyopt!='s');
    /*/

    cout<< endl <<"Ingrese el tamanio de la Matriz de Adyacencia Dirigida:"<< endl;
    while (1) {
      if (cin >> tam &&  tam >0) break; // Dato valido
      else {
          cout << " Dato no valido" << endl;
          cin.clear();
          while (cin.get() != '\n') ; //vaciar hasta el enter
      }
    }

    try{ //Remember new throws exceptions, in cpp yes
        matady = new MatrizI(tam,tam);
    }catch(const std::bad_alloc& e){
        std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
            <<std::endl << "Error: " << e.what() << std::endl;
        return -1;
    }
    //*/

    cout << (*matady).inputMatDisplay(1) << endl;

    cout << "Consideracion 4: " << endl;
    int rens= (*matady).get_renglones(), cols= (*matady).get_columnas(), con4Paralelas= 0;
    for(int i =0; i < rens ; i++){
        for(int j =0; j< cols ; j++){
            if( (*matady).get_val(i,j) >1 ){
                cout << "-Hay "<< (*matady).get_val(i,j)
                    << " lineas paralelas del nodo " << i << " al nodo "
                    << j << "." << endl;
                con4Paralelas = 1;
            }
        }
    }
    if(con4Paralelas == 0) cout << "-No hay lineas paralelas."<< endl;


    cout << endl << "Consideracion 5: " << endl;
    int hay = 1;
    int con = 0;
    for(int i =0; i < rens ; i++){
        hay = 1;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matady).get_val(i,j) > 0 ){
                hay = 0;
                break;
            }
        }
        if(hay == 1){ //si no hubo 0s
            hay =0; //revisando que haya elementos de 1 o mas
            for(int j =0; j< cols; j++){
                if( (*matady).get_val(j,i) > 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 1){
                cout << "-El nodo "<<i << " es nodo terminal." << endl;
                con = 1;
            }
        }
    }
    if(con == 0) cout << "-No hay nodos terminales."<< endl;


    cout << endl << "Consideracion 6: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay = 1;
        for(int j =0; j< cols ; j++){ //revisando que la columna solo tenga 0s
            if( (*matady).get_val(j,i) > 0 ){
                hay = 0;
                break;
            }
        }
        if(hay == 1){ //si no hubo 0s
            hay =0; //revisando que haya elementos de 1 o mas
            for(int j =0; j< cols; j++){
                if( (*matady).get_val(i,j) > 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 1){
                cout << "-El nodo "<<i << " es nodo inicial." <<endl;
                con = 1;
            }
        }
    }
    if(con == 0) cout << "-No hay nodos iniciales."<< endl;


    cout << endl << "Consideracion 7: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matady).get_val(i,j) > 0){
                hay = 1;
                break;
            }
        }
        if(hay == 1){ //si hubo elemento mayor a 0
            hay =0; //revisando que haya elementos de 1 o mas
            for(int j =0; j< cols; j++){
                if( (*matady).get_val(j,i) > 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 1){
                cout << "-El nodo "<<i << " es nodo intermedio." << endl;
                con = 1;
            }
        }
    }
    if(con == 0) cout << "-No hay nodos intermedios."<< endl;


    cout << endl << "Consideracion 8: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matady).get_val(i,j) > 0){
                hay = 1;
                break;
            }
        }
        if(hay == 0){ //si no hubo elemento mayor a 0
            hay =0; //revisando que no haya elementos de 1 o mas
            for(int j =0; j< cols; j++){
                if( (*matady).get_val(j,i) > 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 0){
                cout << "-El nodo "<<i << " es nodo aislado." << endl;
                con = 1;
            }
        }
    }
    if(con == 0) cout << "-No hay nodos aislados."<< endl;


    cout << endl << "Consideracion 9: ";
    if( (*matady).get_Traza() != 0 )
        cout << " Al tener bucles no es simetrico ni asimetrico."
        << endl;
    else if( con4Paralelas== 1 )
        cout << " Al tener lineas paralelas no es simetrico ni asimetrico."
        << endl;
    else if( (*matady) == (*matady).transpuesta() )
        cout << " La digrafica es simetrica."<< endl;
    else cout << " El digrafo es asimetrico."<< endl;


    cout << endl << "Consideracion 10: " << endl;
    int con10Bucles = 0;
    for(int i =0; i < rens ; i++){ //dado que es cuadrada no ocupamos j
        if( (*matady).get_val(i,i) > 0 ){
            cout << "-El nodo "<<i << " tiene "<< (*matady).get_val(i,i)
             << ((*matady).get_val(i,i) >1 ? " bucles." : " bucle.") <<endl;
            con10Bucles = 1;
        }
    }
    if(con10Bucles == 0) cout << "-No hay bucles."<< endl;


    cout << endl << "Consideracion 11: ";
    if( con10Bucles == 1 )
        cout << " Se tiene una pseudodigrafica (hay bucles)."
        << endl;
    else if( con4Paralelas== 1 )
        cout << " Al tener lineas paralelas se tiene una multidigráfica."
        << endl;
    else cout << " La digrafica es simple."<< endl;


    cout << endl << "Consideracion 12: " ;
    int sum=0;
    for(int i =0; i < rens ; i++){
        for(int j =0; j< cols ; j++){
            sum += (*matady).get_val(i,j);
        }
    }
    if(sum > 1) cout << " Hay "<< sum << " lineas en la digrafica."<< endl;
    else if(sum == 1) cout << " Hay 1 linea en la digrafica."<< endl;
    else cout << " No hay lineas en la digrafica."<< endl;


    cout << endl << "Consideracion 13: " << endl;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += (*matady).get_val(i,j);
        }
        cout << "-El grado externo del nodo " << i << " es "
            << sum <<"." <<endl;
    }


    cout << endl << "Consideracion 14: " << endl;
    for(int i =0; i < cols ; i++){
        sum=0;
        for(int j =0; j< rens ; j++){
            sum += (*matady).get_val(j,i);
        }
        cout << "-El grado interno del nodo " << i << " es "
            << sum <<"." <<endl;
    }

    cout << endl << "Consideracion 15: " ;
    int con15Regular= 0;
    if( con10Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es regular." << endl;
    }
    else{
        int totsum = 0;
        for(int j =0; j< cols ; j++){ //val a comparar
            totsum += (*matady).get_val(0,j);
        }
        con15Regular = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){ //comparando cada renglon
            if (con15Regular== 0) break;
            sum = 0;
            for(int j =0; j< cols ; j++){
                sum += (*matady).get_val(i,j);
            }
            if(totsum != sum){
                cout << " La digrafica no es regular."<<endl;
                con15Regular = 0;
            }
        }
        for(int i =0; i < cols ; i++){ //comparando cada columna
            if (con15Regular== 0) break;
            sum = 0;
            for(int j =0; j< rens ; j++){
                sum += (*matady).get_val(j,i);
            }
            if(totsum != sum){
                cout << " La digrafica no es regular."<<endl;
                con15Regular = 0;
            }
        }
        if (con15Regular == 1) cout << " La digrafica es regular."<<endl;
    }

    cout << endl << "Consideracion 16: " ;
    if( con10Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es balanceada." << endl;
    }
    else{
        int rensum = 0,colsum= 0;
        int con16Balanceada = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){ //comparando cada renglon
            if (con16Balanceada== 0) break;
            rensum = 0;
            colsum=0;
            for(int j =0; j< cols ; j++){ //suma por renglon
                rensum += (*matady).get_val(i,j);
                colsum += (*matady).get_val(j,i);
            }
            if(rensum != colsum){
                cout << " La digrafica no es balanceada." << endl;
                con16Balanceada = 0;
            }
        }

        if (con16Balanceada == 1) cout << " La digrafica es balanceada."<<endl;
    }

    cout << endl << "Consideracion 17: " ;
    int con17Completa = 0;
    if( con10Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es completa." << endl;
    }
    else{
        con17Completa = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){
            if (con17Completa== 0) break;
            for(int j =0; j< cols ; j++){
                if(i== j) continue;
                if( (*matady).get_val(i,j) != 1){
                    con17Completa = 0;
                    break;
                }
            }
        }

        if(con17Completa == 0) cout << " La digrafica no es completa." << endl;
        else cout << " La digrafica es completa."<<endl;
    }

    cout << endl << "Consideracion 18: " ;
    if( con17Completa== 1 || con10Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es asimetrica completa." << endl;
    }
    else{
        int con18Balanceada = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){ //comparando cada renglon
            if (con18Balanceada== 0) break;
            sum = 0;
            for(int j =0; j< cols ; j++){ //suma por renglon
                sum += (*matady).get_val(i,j) + (*matady).get_val(j,i);
            }
            if(sum != rens-1 ){
                cout << " La digrafica no asimetrica completa." << endl;
                con18Balanceada = 0;
                break;
            }
        }
        if(con18Balanceada == 1) cout
                                <<" La digrafica es asimetrica completa."
                                <<endl;
    }

    cout << endl << "Consideracion 19: " ;
    vector< vector<int> >vec;
    vector<int> minvec;
    int found; //supongamos min 1 vector
    for(int i =0; i < rens ; i++){ //comparando cada renglon
        found= 0; //si encuentra el val en algun conjunto
        for(int j =0; j < vec.size() ; j++){ //revisando en cada vector
            if( find(vec[j].begin(), vec[j].end(), i )
                   != vec[j].end() )
                found=1;
        }
        //cout << i<<"G"<<vec.size() - 1 <<"={" << i;
        if(found == 0){
            vec.push_back(minvec);
            vec[vec.size() - 1].push_back(i);
            conectado(i, *matady, vec[vec.size() - 1]);
        }
        //cout << "}"<<endl;
    } //terminamos de hacer conjuntos
    for(int i =0; i < vec.size() ; i++){ //comparando cada vector
        for(int j =0; j < vec[i].size() ; j++){ //revisando cada valor del vector
            for(int k =0; k < vec.size() ; k++){ //comparando con los demas
                if(k == i) continue; //evitar comparar mismo vector
                if( vec[k][0] == vec[i][j]  ) //el primer elemento se conecta con el resto
                    vec.erase(vec.begin() + k); //se elimina este vector
            }
        }
    } //terminamos de eliminar subgraficas.
    if(vec.size() >1 ){
        /*
        cout << endl<<"-La digrafica es desconectada." << endl;
        /*/
        cout << endl<<"-La digrafica es desconectada con: " << endl;
        for(int i =0; i < vec.size() ; i++){
            cout << "--G"
                <<i<<"= {";
            for(int j =0; j < vec[i].size() ; j++){
                cout << vec[i][j] << (j+1 == vec[i].size() ? "" : ",");
            }
            cout << "}" <<endl;
        }
        //*/
    }
    else cout << " La digrafica no es desconectada." << endl;

    cout << endl << "Consideracion 20: Las potencias de la matriz son:" ;
    for(int i =2; i < rens ; i++){
        cout << "X(G)"<< i <<(*matady).mpow(i);
    }

    cout << endl << "Consideracion 21: La suma de las potencias de la matriz da:" ;
    con=1;
    MatrizI temp(rens,cols);
    for(int i =1; i < rens ; i++){
        temp += (*matady).mpow(i);
    }
    cout << temp;
    for(int i = 0; i<rens; i++){
        for(int j = 0; j<cols; j++){
            if(temp.get_val(i,j) == 0){
                con =0;
            }
        }
    }
    if( con == 0) cout << "Al haber 0s, no es una digrafica conectada" << endl;
    else cout << "Es una digrafica conectada" <<endl;
    cout << endl <<"FIN de las consideraciones para una matriz de adyacencia dirigida" <<endl;

return 0;}
