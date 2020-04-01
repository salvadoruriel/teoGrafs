#include "mat_inc_NoDir.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int conectadoINCNDIR(int nodo, MatrizI &matinc, vector<int> &vec){
    for(int j =0; j< matinc.get_columnas() ; j++){ //buscando en el renglon donde hay 1
        //if(nodo == j) continue; //la matriz no puede ser cuadrada ya
        if( matinc.get_val(nodo,j) == 1 ) // si lo hay
            for(int i=0; i< matinc.get_renglones() ; i++) //buscando su -1 en la col
                if( matinc.get_val(i,j) == 1 )
                    if( find(vec.begin(), vec.end(), i)
                       == vec.end() ){ //didnt find
                        //cout << ", " << j; //DEBUGGING
                        vec.push_back(i);
                        conectadoINCNDIR(i, matinc, vec);
                       }
    }
}

int checkINCNDIR(MatrizI &matinc){
    int sumtesting,checkgood;
    //cout <<endl <<"ENTRANDO CHECK Presione ENTER para continuar... " ;
    //cin.get();
    for(int j=0; j< matinc.get_columnas() ; j++){
        sumtesting= 0;
        for(int i=0; i< matinc.get_renglones() ; i++){
            checkgood = matinc.get_val(i,j);
            if( checkgood != 1 && checkgood != 2
               && checkgood != 0) return -2; //dato no valido
            sumtesting += checkgood;
        }
        if (sumtesting != 2) return -1;
    }

return 0;} //success

/*
void ConfiguraIdioma(){
	struct lconv *lcPtr;
	setlocale(LC_ALL, "");
	lcPtr = localeconv();
	//Configura cantidades para México
	lcPtr->decimal_point = ".";
	lcPtr->thousands_sep = ",";
	lcPtr->grouping = "3";
}
*/

int mat_inc_No_dir(){
    //ConfiguraIdioma();
    char adyopt,c;
    int rens,cols,con=1,hay=0,sum;
    MatrizI *matinc;

    cout<< endl <<"Ingrese el tamanio de la Matriz de Incidencia No Dirigida, (renglon, columna):"<< endl;
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
        matinc = new MatrizI(rens,cols);
    }catch(const std::bad_alloc& e){
        std::cerr <<std::endl <<"Error al intentar crear una nueva matriz, posible memoria insuficiente."
            <<std::endl << "Error: " << e.what() << std::endl;
        return -1;
    }

    cout<< endl <<"Use un 2 para representar bucles" << endl;
    cout <<endl <<"Presione ENTER para continuar... " ;
    cin.get();
    //for(int i =0; i < 255 ; i++) cout << i << "= " << (char) i <<" ;";
    //for(int i =0; i<9999999 ; i++) pow(tam++,tam++);
    while(con!=0){
        cout << (*matinc).inputMatDisplay(0) ;

        con = checkINCNDIR(*matinc);
        if(con != 0){
        cout<< endl<<con <<"La matriz no es valida, revise que solo halla "
                << "\"1\",\"0\" o \"2\", y que solo haya un par de \"1\" "
                << "por columna, o un solo \"2\" por columna. "<< endl;
        cout <<endl <<"Presione ENTER para continuar... " ;
        cin.get();
        }
    }
    //cout <<endl <<"SALI DE CONDICIONAL Presione ENTER para continuar... " ;
    //cin.get();

     //Consideracion 2 Bucle
     cout << endl << "Consideracion 2: " << endl;
    int con2Bucles = 0;
    for(int j =0; j < cols ; j++) {
        for(int i =0; i < rens ; i++){
            if( (*matinc).get_val(i,j) == 2){
                cout << "-La arista "<< j <<" es un bucle que incide en "
                    <<"el nodo "<<i << "." <<endl;
                con2Bucles = 1;
            }
        }
    }
    if(con2Bucles == 0) cout << "-No hay bucles."<< endl;


    //consideracion 3 Suma Por Renglon= Grado de Cada Nodo
    cout << endl << "Consideracion 3: " << endl;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += (*matinc).get_val(i,j);
        }
        cout << "-El grado del nodo " << i << " es "
            << sum <<"." <<endl;
    }


    //Consideracion 4 Nodo Aislado
    cout << endl << "Consideracion 4: " << endl;
    int con4aislado = 0;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando que el renglon solo tenga 0s
            if( (*matinc).get_val(i,j) != 0){
                hay = 1;
                break;
            }
        }
        if(hay == 0){
            cout << "-El nodo "<< i << " es nodo aislado." << endl;
            con4aislado = 1;
        }
    }
    if(con4aislado == 0) cout << "-No hay nodos aislados."<< endl;

	//Consideracion 5 Nodo Colgante
	cout << endl << "Consideracion 5: " << endl;
    int con5Colgante = 0;
    for(int i =0; i < rens ; i++){
        sum =0;
        for(int j =0; j< cols ; j++){ //revisando ren con un solo 1 y 0s
            sum += (*matinc).get_val(i,j);
        }
        if(sum == 1){
            cout << "-El nodo "<<i << " es nodo colgante." << endl;
            con5Colgante = 1;
        }
    }
    if(con5Colgante == 0) cout << "-No hay nodos colgantes."<< endl;

    //Consideracion 6 Lineas Paralelas
    cout << endl<<"Consideracion 6: " << endl;
    int con6Paralelas= 0;
    vector< vector<int> > tempvec(cols);
    for(int j =0; j< cols ; j++){ //llenando columna por columna
        for(int i =0; i < rens ; i++){
            tempvec[j].push_back((*matinc).get_val(i,j));
        }
    }
    for(int j =0; j< cols ; j++){ //comparando columna por columna
        for(int i =j+1; i< cols ; i++)
            if( tempvec[j] == tempvec[i] ){
                cout << "-La arista " << j
                    << " es paralela a la arista "  << i
                    << "."<<endl;
                con6Paralelas = 1;
            }
    }
    if(con6Paralelas == 0) cout << "-No hay lineas paralelas."<< endl;

	//Consideracion 8 Grafica Simple, General
    cout << endl<<"Consideracion 8: " << endl;
	if( con2Bucles == 1 )
        cout << " Es grafica general (hay bucles)." << endl;
    else if( con6Paralelas== 1 )
        cout << " Es grafica general (hay paralelas)." << endl;
    else cout << " La grafica es simple." << endl;


	//Consideracion 9 Pseudograficas
	cout << endl << "Consideracion 9: ";
    if( con2Bucles == 1 )
        cout << " Se tiene una pseudografica."
        << endl;
    else cout << " No es pseudografica." << endl;

	//Consideracion 10 Multigrafica
	cout << endl << "Consideracion 10: ";
    if( con6Paralelas== 1 && con2Bucles == 0 )
        cout << " Al tener lineas paralelas se tiene una multigrafica."
        << endl;
    else cout << " No es multigrafica." << endl;

    //Consideracion 11 Regular
	cout << endl << "Consideracion 11: " ;
    int con11Regular= 0;
    if( con2Bucles == 1 || con6Paralelas == 1 ){
        cout << " La grafica no es regular." << endl;
    }
    else{
        con11Regular = 1; //suponer que si es hasta ver lo contrario
        int totsum = 0;
        for(int j =0; j< cols ; j++){ //val a comparar
            totsum += (*matinc).get_val(0,j);
        }
        for(int i =1; i < rens ; i++){
            sum = 0;
            for(int j =0; j< cols ; j++){
                sum += (*matinc).get_val(i,j);
                //if( operado == -1) sumneg++;
            }
            if( sum != totsum){
                con11Regular = 0;
                break;
            }
        }
        if (con11Regular == 1) cout << " La grafica es regular."<<endl;
        else cout << " La grafica no es regular."<<endl;
    }

	//Consideracion 12 Completo
    cout << endl << "Consideracion 12: " ;
    int con12Completa = 0;
    if( con2Bucles == 1 || con6Paralelas == 1 ){
        cout << " La grafica no es completa." << endl;
    }
    else{
        con12Completa = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){
            sum = 0;
            for(int j =0; j< cols ; j++){
                sum+= (*matinc).get_val(i,j);
            }
            if( sum != rens -1 ){
                con12Completa = 0;
                break;
            }
        }

        if(con12Completa == 0) cout << " La grafica no es completa." << endl;
        else cout << " La grafica es completa."<<endl;
    }

	//Consideracion 13 Fuertemente Conectada
	cout << endl << "Consideracion 13: " ;
    int con13FuertementeConectada = 0;
    if( con6Paralelas == 1 ){
        cout << " La grafica no es fuertemente conectada." << endl;
    }
    else{
        con13FuertementeConectada = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){
            sum = 0;
            for(int j =0; j< cols ; j++){
                sum+= (*matinc).get_val(i,j);
            }
            if( sum != rens +1 ){
                con13FuertementeConectada = 0;
                break;
            }
        }

        if(con13FuertementeConectada == 0) cout << " La grafica no es fuertemente conectada." << endl;
        else cout << " La grafica es fuertemente conectada."<<endl;
    }

	//Consideracion 14  Desconectada
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
            conectadoINCNDIR(i, *matinc, vec[vec.size() - 1]);
        }

    } //terminamos de hacer conjuntos
    if(vec.size() >1 ){
        cout << endl<<"-La grafica es desconectada con: " << endl;
        for(int i =0; i < vec.size() ; i++){
            cout << "--G" <<i<<"= {";
            for(int j =0; j < vec[i].size() ; j++){
                cout << vec[i][j] << (j+1 == vec[i].size() ? "" : ",");
            }
            cout << "}" <<endl;
        }
        //*/
    }
    else cout << " La grafica no es desconectada." << endl;


    cout << endl <<"FIN de las consideraciones para una matriz de incidencia no dirigida." <<endl;

return 0;}
