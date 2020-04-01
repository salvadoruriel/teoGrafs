#include "mat_ady_NoDir.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int conectadoNODIR(int nodo, MatrizI &matady, vector<int> &vec){
    for(int iren =0; iren< matady.get_columnas() ; iren++){ //conexion por renglon
        if(nodo == iren) continue;
        if( matady.get_val(nodo,iren) > 0 )
            if( find(vec.begin(), vec.end(), iren)
              == vec.end() ){ //didnt find
                                vec.push_back(iren);
                conectadoNODIR(iren, matady, vec);
               }
    }
return 0;}

int mat_ady_No_dir(){
    char adyopt,adymenu,c;
    int tam,sum;
    double temx,temy;
    MatrizI *matady;

    while(1){
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
            matady = new MatrizI(tam,tam);
        }catch(const std::bad_alloc& e){
            std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
                <<std::endl << "Error: " << e.what() << std::endl;
            return -1;
        }
        //*/

        cout << (*matady).inputMatDisplay(1) << endl;
        if( !(*matady).es_simetrica() ) cout << "La matriz no es simetrica, por lo que no corresponde "
            << "a una matriz de adyacencia no dirigida. Ingrese una matriz valida." << endl;
        else break;
        delete(matady);
    }

    cout << "Consideracion 5: " << endl;
    int rens= (*matady).get_renglones(), cols= (*matady).get_columnas(), con5Paralelas= 0;
    for(int i =0; i < rens ; i++){
        for(int j =0; j< i ; j++){
            if( (*matady).get_val(i,j) >1 ){
                cout << "-Hay "<< (*matady).get_val(i,j)
                    << " lineas paralelas entre los nodos " << i << " y "
                    << j << "." << endl;
                con5Paralelas = 1;
            }
        }
    }
    if(con5Paralelas == 0) cout << "-No hay lineas paralelas."<< endl;

    cout << endl << "Consideracion 6: ";
    int con6Bucles = 0;
    for(int i =0; i < rens ; i++){ //dado que es cuadrada no ocupamos j
        if( (*matady).get_val(i,i) > 0 ){
            cout << endl <<"-El nodo "<<i << " tiene "<< (*matady).get_val(i,i)
             << ((*matady).get_val(i,i) >1 ? " bucles." : " bucle.") ;
            con6Bucles = 1;
        }
    }
    if(con6Bucles == 0) cout << "-No hay bucles."<< endl;
    else cout << endl;


	cout << endl << "Consideracion 7: ";
    if( con6Bucles == 1 )
        cout << " Se tiene una grafica general (hay bucles)."
        << endl;
    else if( con5Paralelas== 1 )
        cout << " Se tiene una grafica general (hay lineas paralelas)."
        << endl;
    else cout << " La grafica es simple."<< endl;


    cout << endl << "Consideracion 8: ";
    if( con6Bucles == 1 )
        cout << " Se tiene una pseudografica (hay bucles)."<< endl;
    else if( con5Paralelas== 1 )
        cout << " Al tener lineas paralelas sin bucles se tiene una multigráfica."
        << endl;
    else cout << " La grafica es simple."<< endl;
//consideracion 9

    cout << endl << "Consideracion 9: " << endl;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            if(j==i) sum += 2*(*matady).get_val(i,j); //1 mas por cada bucle
            else sum += (*matady).get_val(i,j);
        }
        cout << "-El Grado del nodo " << i << " es "
            << sum <<"." <<endl;
    }


    cout << endl << "Consideracion 10: " ;
    int con10Regular= 0;
    if( con6Bucles == 1 || con5Paralelas == 1 ){
        cout << " La grafica no es regular." << endl;
    }
    else{
        int totsum = 0;
        for(int j =0; j< cols ; j++){ //val a comparar
            totsum += (*matady).get_val(0,j);
        }
        con10Regular = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){ //comparando cada renglon(nodo)
            sum = 0;
            for(int j =0; j< cols ; j++){
                sum += (*matady).get_val(i,j);
            }
            if(totsum != sum){
                cout << " La grafica no es regular."<<endl;
                con10Regular = 0;
                break;
            }
        }
        if (con10Regular == 1) cout << " La grafica es regular."<<endl;
    }


    cout << endl << "Consideracion 11: " ;
    sum=0;
    for(int i =0; i < rens ; i++){
        //cout <<endl << i << " ";
        for(int j =0; j<=i ; j++){
            sum += (*matady).get_val(i,j);
            //cout <<(*matady).get_val(i,j)<<" ";
        }
    }
    if(sum > 1) cout << " Hay "<< sum << " lineas en la grafica."<< endl;
    else if(sum == 1) cout << " Hay 1 linea en la grafica."<< endl;
    else cout << " No hay lineas en la grafica."<< endl;


    cout << endl << "Consideracion 12: " << endl;
    int con12aislados=0,hay = 1;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matady).get_val(i,j) > 0 ){
                hay = 1;
                break;
            }
        }
        if(hay == 0){ //si no hubo 0s
            for(int j =0; j< cols; j++){ //revisando que sea 0s en columna
                if( (*matady).get_val(j,i) > 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 0){
                cout << "-El nodo "<<i << " es un nodo aislado." << endl;
                con12aislados = 1;
            }
        }
    }
    if(con12aislados == 0) cout << "-No hay nodos aislados."<< endl;


    cout << endl << "Consideracion 13: " << endl;
    int con13colgantes = 0;
    for(int i =0; i < rens ; i++){
        hay = 1;
        int sumcol=0, sumren=0;
        for(int j =0; j< cols ; j++){ //revisando que col y ren solo valga 1
            sumren += (*matady).get_val(i,j);
            sumcol += (*matady).get_val(j,i);
        }
        if(sumcol == 1 && sumren ==1){
            if(hay == 1){
                cout << "-El nodo "<<i << " es nodo colgante." <<endl;
                con13colgantes = 1;
            }
        }
    }
    if(con13colgantes == 0) cout << "-No hay nodos colgantes."<< endl;


    cout << endl << "Consideracion 14: " ;
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
                if(found == 0){
            vec.push_back(minvec);
            vec[vec.size() - 1].push_back(i);
            conectadoNODIR(i, *matady, vec[vec.size() - 1]);
        }
    } //terminamos de hacer conjuntos
    /*
    for(int i =0; i < vec.size() ; i++){ //comparando cada vector
        for(int j =0; j < vec[i].size() ; j++){ //revisando cada valor del vector
            for(int k =0; k < vec.size() ; k++){ //comparando con los demas
                if(k == i) continue; //evitar comparar mismo vector
                if( vec[k][0] == vec[i][j]  ) //el primer elemento se conecta con el resto
                    vec.erase(vec.begin() + k); //se elimina este vector
            }
        }
    } //terminamos de eliminar subgraficas.
    */
    if(vec.size() >1 ){
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


    cout << endl << "Consideracion 15: " ;
    int con15Completa = 0;
    if( con6Bucles == 1 || con5Paralelas == 1 ){
        cout << " La grafica no es completa." << endl;
    }
    else{
        con15Completa = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){
            if (con15Completa== 0) break;
            for(int j =0; j< cols ; j++){
                if(i== j) continue;
                if( (*matady).get_val(i,j) != 1){
                    con15Completa = 0;
                    break;
                }
            }
        }

        if(con15Completa == 0) cout << " La grafica no es completa." << endl;
        else cout << " La grafica es completa."<<endl;
    }

    //Consideracion16	Fuertemente conectada
    cout << endl << "Consideracion 16: " ;
    int con16FuertementeConectada = 1;//suponer que si es hasta ver lo contrario
    for(int i =0; i < rens ; i++){
        if (con16FuertementeConectada== 0) break;
        for(int j =0; j< cols ; j++){
            if( (*matady).get_val(i,j) != 1){
                con16FuertementeConectada = 0;
                break;
            }
        }
    }
    if(con16FuertementeConectada == 0) cout << " La grafica no es fuertemente conectada." << endl;
    else cout << " La grafica es fuertemente conectada."<<endl;

    //Consideracion17 Potencia de Matriz
    cout << endl << "Consideracion 17: Las potencias de la matriz son:" ;
    for(int i =2; i < rens ; i++){
        cout << "X(G)"<< i <<(*matady).mpow(i);
    }
    //Consideracion 18
    cout << endl << "Consideracion 18: La suma de las potencias de la matriz da:" ;
    int con=1;
    MatrizI temp(rens,cols);
    for(int i =1; i < rens ; i++){
        temp += (*matady).mpow(i);
    }
    cout << temp;
    for(int i = 0; i<rens; i++){
        for(int j = 0; j<cols; j++){
            if(temp.get_val(i,j) == 0){
                con =0;
                i=rens;
                break;
            }
        }
    }
    if( con == 0) cout << "Al haber 0s, no es una digrafica conectada." << endl;
    else cout << "Es una digrafica conectada." <<endl;

    cout << endl <<"FIN de las consideraciones para una matriz de adyacencia NO dirigida." <<endl;

return 0;}
