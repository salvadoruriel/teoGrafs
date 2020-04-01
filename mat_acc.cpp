#include "mat_acc.hpp"
#include <vector>
#include <algorithm>

using namespace std;
int conectadoACC(int nodo, MatrizI &matacc, vector<int> &vec){
    for(int iren =0; iren< matacc.get_columnas() ; iren++){ //conexion por renglon
        if(nodo == iren) continue;
        if( matacc.get_val(nodo,iren) > 0 )
            if( find(vec.begin(), vec.end(), iren)
               == vec.end() ){ //didnt find
                vec.push_back(iren);
                conectadoACC(iren, matacc, vec);
               }
    }
}


int checkACC(MatrizI &matinc){
    int testing;
    //cout <<endl <<"ENTRANDO CHECK Presione ENTER para continuar... " ;
    //cin.get();
    for(int j=0; j< matinc.get_columnas() ; j++){
        testing= 0;
        for(int i=0; i< matinc.get_renglones() ; i++){
            testing = matinc.get_val(i,j);
            if( testing != 1 && testing != 0) return -2; //dato no valido
        }
    }

return 0;} //success


int mat_acc(){
    char adyopt,adymenu,c;
    int tam,rens,cols,con=1,sum;
    double temx,temy;
    MatrizI *matacc;

    cout<< endl <<"Ingrese el tamaño de la Matriz de Accesibilidad:"<< endl;
    while (1) {
      if (cin >> tam &&  tam >0) break; // Dato valido
      else {
          cout << " Dato no valido" << endl;
          cin.clear();
          while (cin.get() != '\n') ; //vaciar hasta el enter
      }
    }
    rens = tam;
    cols = tam;

    try{ //Remember new throws exceptions, in cpp yes
        matacc = new MatrizI(tam,tam);
    }catch(const std::bad_alloc& e){
        std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
            <<std::endl << "Error: " << e.what() << std::endl;
        return -1;
    }
    //*/

    cout<< endl <<"Use 1 en lugar del caracter +" << endl;
    cout <<endl <<"Presione ENTER para continuar... " ;
    cin.get();

    while(con!=0){
        cout << (*matacc).inputMatDisplay(1) ;

        con = checkACC(*matacc);
        if(con != 0){
                //<< con
        cout<< endl <<"La matriz no es valida, revise que solo halla "
                << "\"1\"s y  \"0\"s en la tabla."<< endl;
        cout <<endl <<"Presione ENTER para continuar... " ;
        cin.get();
        }
    }

    //Consideracion 2 Grafica Conectada Todos Los Elementos son +
    cout << endl << "Consideracion 2: " ;
    int con2Conectada=1;
    for(int i =0; i < rens ; i++){
        for(int j =0; j< cols ; j++){ //revisando que solo hay 1s
            if( (*matacc).get_val(i,j) != 1){
                con2Conectada = 0 ;
                i=rens;
                break;
            }
        }
    }
    if(con2Conectada == 1) cout << "La grafica es conectada." << endl;
    else cout << "La grafica no es conectada."<< endl;


	//Consideracion 3 Nodo Intermedio
	 cout << endl<<"Consideracion 3: " << endl;
    int con3Intermedios = 0;
    for(int i =0; i < rens ; i++){
        sum = 0;
        for(int j =0; j< cols ; j++){ //revisando por renglon
            sum +=(*matacc).get_val(i,j) ;
        }
        if(sum >= 1){ //si hubo elemento mayor a 0
            sum =0; //revisando que haya 1 o mas por columna
            for(int j =0; j< rens; j++){ //como es cuadrada no cambia mucho
                sum += (*matacc).get_val(j,i);
            }
            if(sum >= 1){
                cout << "-El nodo "<<i << " es nodo intermedio." << endl;
                con3Intermedios = 1;
            }
        }
    }
    if(con3Intermedios == 0) cout << "-No hay nodos intermedios."<< endl;

	//Consideracion 4 Nodo Colgante
	cout << endl << "Consideracion 4: " << endl;
    int con4Colgante = 0;
    for(int i =0; i < rens ; i++){
        sum = 0;
        for(int j =0; j< cols ; j++){ //revisando renglon de 0s
            sum += (*matacc).get_val(i,j);
        }
        if(sum == 0){ //si hubo 0s, checando que columna si tenga
            sum =0; //revisando que haya elementos de 1 o mas en su columna
            for(int j =0; j< cols; j++){
                sum += (*matacc).get_val(j,i);
            }
            if(sum >= 1){
                cout << "-El nodo "<<i << " es nodo colgante." <<endl;
                con4Colgante = 1;
            }
        }

        for(int j =0; j< cols ; j++){ //revisando por columna de 0s
            sum += (*matacc).get_val(j,i);
        }
        if(sum == 0){ //si hubo 0s, checando que columna si tenga
            sum =0; //revisando que haya elementos de 1 o mas en su columna
            for(int j =0; j< cols; j++){
                sum += (*matacc).get_val(i,j);
            }
            if(sum >= 1){
                cout << "-El nodo "<<i << " es nodo colgante." <<endl;
                con4Colgante = 1;
            }
        }
    }
    if(con4Colgante == 0) cout << "-No hay nodos colgantes."<< endl;


	//Consideracion 5 NoTerminal, NoInicial, NoAislado
	cout << endl << "Consideracion 5: " << endl;
	cout << "-Nodo Inicial: " << endl;
    int con5Inicial = 0;
    for(int i =0; i < rens ; i++){
        int hay = 1;
        for(int j =0; j< cols ; j++){ //revisando que la columna solo tenga 0s
            if( (*matacc).get_val(j,i) != 0 ){
                hay = 0;
                break;
            }
        }
        if(hay == 1){ //si hubo 0s
            hay =0; //revisando que haya elementos de 1 o mas
            for(int j =0; j< cols; j++){ //checando por renglon
                if( (*matacc).get_val(i,j) != 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 1){
                cout << "--El nodo "<<i << " es nodo inicial." <<endl;
                con5Inicial = 1;
            }
        }
    }
    if(con5Inicial == 0) cout << "--No hay nodos iniciales."<< endl;

    cout << endl << "-Nodo Terminal: " << endl;
    int hay = 1;
    int con5Terminal = 0;
    for(int i =0; i < rens ; i++){
        hay = 1;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matacc).get_val(i,j) != 0 ){
                hay = 0;
                break;
            }
        }
        if(hay == 1){ //si no hubo 0s
            hay =0; //revisando que haya elementos de 1 o mas
            for(int j =0; j< cols; j++){ //por columna
                if( (*matacc).get_val(j,i) != 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 1){
                cout << "--El nodo "<<i << " es nodo terminal." << endl;
                con5Terminal = 1;
            }
        }
    }
    if(con5Terminal == 0) cout << "--No hay nodos terminales."<< endl;


    cout << endl << "-Nodo Aislado: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matacc).get_val(i,j) > 0){
                hay = 1;
                break;
            }
        }
        if(hay == 0){ //si no hubo elemento mayor a 0
            hay =0; //revisando que no haya elementos de 1 o mas
            for(int j =0; j< cols; j++){
                if( (*matacc).get_val(j,i) > 0 ){
                    hay = 1;
                    break;
                }
            }
            if(hay == 0){
                cout << "--El nodo "<<i << " es nodo aislado." << endl;
                con = 1;
            }
        }
    }
    if(con == 0) cout << "--No hay nodos aislados."<< endl;





	//Consideracion 7 Conectada/Desconectada
    cout << endl << "Consideracion 7: " ;
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
            conectadoACC(i, *matacc, vec[vec.size() - 1]);
        }

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

        cout << endl<<"-La Grafica/digrafica es desconectada con: " << endl;
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
    else cout << " La grafica/digrafica no es desconectada." << endl;

    cout << endl <<"FIN de las consideraciones para una matriz de accesibilidad" <<endl;

return 0;}
