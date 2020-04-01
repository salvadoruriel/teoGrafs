#include "mat_inc_dir.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int conectadoINC(int nodo, MatrizI &matinc, vector<int> &vec){
    for(int j =0; j< matinc.get_columnas() ; j++){ //buscando en el renglon donde hay 1
        //if(nodo == j) continue; //la matriz no puede ser cuadrada ya
        if( matinc.get_val(nodo,j) == 1 ) // si lo hay
            for(int i=0; i< matinc.get_renglones() ; i++) //buscando su -1 en la col
                if( matinc.get_val(i,j) == -1 )
                    if( find(vec.begin(), vec.end(), i)
                       == vec.end() ){ //didnt find
                        //cout << ", " << j; //DEBUGGING
                        vec.push_back(i);
                        conectadoINC(i, matinc, vec);
                       }
    }
}

int check(MatrizI &matinc){
    int testing;
    //cout <<endl <<"ENTRANDO CHECK Presione ENTER para continuar... " ;
    //cin.get();
    for(int j=0; j< matinc.get_columnas() ; j++){
        for(int i=0; i< matinc.get_renglones() ; i++){
            testing = matinc.get_val(i,j);
            //cout << i << " " << j << ";" ;
            switch(testing){
                case 1:{ //revisando por un - y 0s
                    int cond = 0;
                    for(int iren=0; iren< matinc.get_renglones() ; iren++){
                        if( i==iren ) continue;
                        testing = matinc.get_val(iren,j);
                        if( cond == 0 && testing == -1){
                            cond = 1; //found it
                            continue;
                        }
                        if( testing != 0 )
                            return 2; //sobra algo que no es 0, invalido
                    }
                    if (cond== 0) return -2; //encontro solo -, pero falto el 1
                    i=matinc.get_renglones(); //exito en esta columna
                    break;}
                case -1:{ //revisando por un 1 y 0s
                    int cond = 0;
                    for(int iren=0; iren< matinc.get_renglones() ; iren++){
                        if( i==iren ) continue;
                        testing = matinc.get_val(iren,j);
                        if( cond == 0 && testing == 1){
                            cond = 1; //found it
                            continue;
                        }
                        if( testing != 0)
                            return 3; //sobra algo que no es 0, invalido
                    }
                    if (cond== 0) return -3; //encontro solo -, pero falto el 1
                    i=matinc.get_renglones(); //exito en esta columna
                    break;}
                case 3:{ //revisando que no haya algo que no sea 0
                    for(int iren=0; iren< matinc.get_renglones() ; iren++){
                        if( i==iren ) continue;
                        if( matinc.get_val(iren,j) != 0)
                            return 4; //sobro algo
                    }
                    i=matinc.get_renglones(); //exito en esta columna
                    break;}
                case 0:
                    if(i== matinc.get_renglones()-1 ) return 0; //col de 0s
                    else continue;
                    break;
                default:
                    return -1; //invalid character
                    break;
            }
        }
    }

return 1;} //success

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

int mat_inc_dir(){
    //ConfiguraIdioma();
    char adyopt,c;
    int rens,cols,con=0,hay=0,sum;
    MatrizI *matinc;

    cout<< endl <<"Ingrese el tamanio de la Matriz de Incidencia Dirigida, (renglon columna):"<< endl;
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

    cout<< endl <<"Use 3 en lugar del caracter "<< (char) 177 <<" para representar bucles" << endl;
    cout <<endl <<"Presione ENTER para continuar... " ;
    cin.get();
    //for(int i =0; i < 255 ; i++) cout << i << "= " << (char) i <<" ;";
    //for(int i =0; i<9999999 ; i++) pow(tam++,tam++);
    while(con!=1){
        cout << (*matinc).inputMatDisplay(0) ;

        con = check(*matinc);
        if(con != 1){
                //<< con
        cout<< endl <<"La matriz no es valida, revise que solo halla "
                << "\"1\",\"-1\" o \"3\", y que solo haya 1 par de las primeras "
                << "dos por columna, o 1 solo 3 por columna. "<< endl;
        cout <<endl <<"Presione ENTER para continuar... " ;
        cin.get();
        }
    }
    //cout <<endl <<"SALI DE CONDICIONAL Presione ENTER para continuar... " ;
    //cin.get();

    cout << endl << "Consideracion 3: " << endl;
    con = 0;
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
            con = 1;
        }
    }
    if(con == 0) cout << "-No hay nodos aislados."<< endl;


    cout << endl<<"Consideracion 4: " << endl;
    int con4Paralelas= 0;
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
                    << endl;
                con4Paralelas = 1;
            }
    }
    if(con4Paralelas == 0) cout << "-No hay lineas paralelas."<< endl;


    cout << endl << "Consideracion 5: " << endl;
    for(int i =0; i < rens ; i++){
        sum=0;
        for(int j =0; j< cols ; j++){
            sum += ( ( (*matinc).get_val(i,j) == 1 ||
                      (*matinc).get_val(i,j) == 3 ) ? 1 : 0);
        }
        cout << "-El grado externo del nodo " << i << " es "
            << sum <<"." <<endl;
    }


    cout << endl << "Consideracion 6: " << endl;
    for(int i =0; i < cols ; i++){
        sum=0;
        for(int j =0; j< rens ; j++){
            sum += ( ( (*matinc).get_val(i,j) == -1 ||
                      (*matinc).get_val(i,j) == 3 ) ? 1 : 0);
        }
        cout << "-El grado interno del nodo " << i << " es "
            << sum <<"." <<endl;
    }


    cout << endl << "Consideracion 7: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando ren de 0s y 1s
            if( (*matinc).get_val(i,j) == 1 ){
                hay = 1; //minimo un 1
            }
            if( (*matinc).get_val(i,j) == -1 ||
               (*matinc).get_val(i,j) == 3 ){
                hay = 0; //falla y salimos del renglon
                break;
            }
        }
        if(hay == 1){
            cout << "-El nodo "<<i << " es nodo inicial." <<endl;
            con = 1;
        }
    }
    if(con == 0) cout << "-No hay nodos iniciales."<< endl;


    cout << endl << "Consideracion 8: " << endl;
    for(int i =0; i < rens ; i++){
        hay = 0;
        for(int j =0; j< cols ; j++){ //revisando ren de 0s y -1s
            if( (*matinc).get_val(i,j) == -1 ){
                hay = 1; //minimo un -1
            }
            if( (*matinc).get_val(i,j) == 1 ||
               (*matinc).get_val(i,j) == 3){
                hay = 0;
                break;
            }
        }
        if(hay == 1){
            cout << "-El nodo "<<i << " es nodo terminal." << endl;
            con = 1;
        }
    }
    if(con == 0) cout << "-No hay nodos terminales."<< endl;


    cout << endl << "Consideracion 9: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay =0;
        int hay1 = 0;
        for(int j =0; j< cols ; j++){ //revisando ren sin bucles(3)
            if( (*matinc).get_val(i,j) == 1 ){
                hay1 = 1; //minimo un -1
            }
            if( (*matinc).get_val(i,j) == -1 ){
                hay = 1; //minimo un -1
            }
            if( (*matinc).get_val(i,j) == 3){
                hay = 0;
                break;
            }
        }
        if(hay && hay1){
            cout << "-El nodo "<<i << " es nodo intermedio." << endl;
            con = 1;
        }
    }
    if(con == 0) cout << "-No hay nodos intermedios."<< endl;

    cout << endl << "Consideracion 10: " << endl;
    con = 0;
    for(int i =0; i < rens ; i++){
        hay =0;
        for(int j =0; j< cols ; j++){ //revisando ren con 1 solo 1 o -1
            if( hay ==0 && ( (*matinc).get_val(i,j) == 1 ||
               (*matinc).get_val(i,j) == -1) ){
                hay = 1; //minimo un 1 o -1
                continue;
            }
            if( hay ==1 && ( (*matinc).get_val(i,j) == 1 ||
               (*matinc).get_val(i,j) == -1) ){
                hay = 0; //maximo un 1 o -1
                break;
            }
            if( (*matinc).get_val(i,j) == 3){
                hay = 0;
                break;
            }
        }
        if(hay){
            cout << "-El nodo "<<i << " es nodo colgante." << endl;
            con = 1;
        }
    }
    if(con == 0) cout << "-No hay nodos colgantes."<< endl;



    cout << endl << "Consideracion 11: " << endl;
    int con12Bucles = 0;
    for(int i =0; i < rens ; i++){
        sum = 0;
        for(int j =0; j < cols ; j++){
            if( (*matinc).get_val(i,j) == 3 ){
                sum++;
            }
        }
        if(sum>0){
            cout << "-El nodo "<<i << " tiene "<< sum
             << (sum >1 ? " bucles." : " bucle.") <<endl;
            con12Bucles = 1;
        }
    }
    if(con12Bucles == 0) cout << "-No hay bucles."<< endl;


    cout << endl << "Consideracion 13: ";
    if( con12Bucles == 1 )
        cout << " Se tiene una pseudodigrafica (hay bucles)."
        << endl;
    else if( con4Paralelas== 1 )
        cout << " Al tener lineas paralelas se tiene una multidigráfica."
        << endl;
    else cout << " La digrafica es simple."<< endl;


    cout << endl << "Consideracion 14: ";
    con=0;
    if( con12Bucles == 1)
        cout << " Al tener bucles no es digrafica asimetrica."
        << endl;
    else if( con4Paralelas== 1 )
        cout << " Al tener lineas paralelas no es digrafica asimetrica."
        << endl;
    else{
        con=1;
        for(int j =0; j< cols ; j++){ //comparando columna por columna
            for(int i =j+1; i< cols ; i++){
                vector<int> revsvec = tempvec[i];
                reverse(revsvec.begin(), revsvec.end());
                if( tempvec[j] == revsvec ){
                    con=0;
                }
            }
        }
        if(con == 1) cout << " La digrafica es asimetrica."<< endl;
        else cout << " La digrafica no es asimetrica."<< endl;
    }


    cout << endl << "Consideracion 15: ";
    con=0;
    if( con12Bucles == 1)
        cout << " Al tener bucles no es digrafica simetrica."
        << endl;
    else if( con4Paralelas== 1 )
        cout << " Al tener lineas paralelas no es digrafica simetrica."
        << endl;
    else{
        con=1;
        for(int j =0; j< cols ; j++){ //comparando columna por columna
            hay = 0;
            for(int i =j+1; i< cols ; i++){
                vector<int> revsvec = tempvec[i];
                reverse(revsvec.begin(), revsvec.end());
                if( tempvec[j] == revsvec ){
                    hay=1;
                }
            }
            if (hay == 0){
                con = 0;
                break;
            }
        }
        if(con == 1) cout << " La digrafica es simetrica."<< endl;
        else cout << " La digrafica no es simetrica."<< endl;
    }


    cout << endl << "Consideracion 16: " ;
    int con16Completa = 0,sumneg=0,operado;
    if( con12Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es completa." << endl;
    }
    else{
        con16Completa = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){
            if (con16Completa== 0) break;
            sum = 0;
            sumneg = 0;
            for(int j =0; j< cols ; j++){
                operado= (*matinc).get_val(i,j);
                if( operado == 1) sum++;
                if( operado == -1) sumneg++;
            }
            if( sum != rens -1 || sumneg != rens -1 ){
                con16Completa = 0;
                break;
            }
        }

        if(con16Completa == 0) cout << " La digrafica no es completa." << endl;
        else cout << " La digrafica es completa."<<endl;
    }


    cout << endl << "Consideracion 17: " ;
    int con17ACompleta;
    if( con16Completa== 1 || con12Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es asimetrica completa." << endl;
    }
    else{
        con17ACompleta = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){
            if (con17ACompleta== 0) break;
            sum = 0;
            sumneg = 0;
            for(int j =0; j< cols ; j++){
                operado= (*matinc).get_val(i,j);
                if( operado == 1) sum++;
                if( operado == -1) sumneg++;
            }
            if( sum +sumneg != rens -1 ){
                con17ACompleta = 0;
                break;
            }
        }

        if(con17ACompleta == 0) cout << " La digrafica no es asimetrica completa." << endl;
        else cout << " La digrafica es asimetrica completa."<<endl;
    }

    cout << endl << "Consideracion 18: " ;
    int con18Regular= 0;
    if( con12Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es regular." << endl;
    }
    else{
        con18Regular = 1; //suponer que si es hasta ver lo contrario
        int totsum = 0;
        for(int j =0; j< cols ; j++){ //val a comparar
            totsum += ( (*matinc).get_val(0,j) == 1 ? 1: 0 );
        }
        for(int i =0; i < rens ; i++){
            if (con18Regular== 0) break;
            sum = 0;
            sumneg = 0;
            for(int j =0; j< cols ; j++){
                operado= (*matinc).get_val(i,j);
                if( operado == 1) sum++;
                if( operado == -1) sumneg++;
            }
            if( sum != sumneg && sumneg != totsum){
                con18Regular = 0;
                break;
            }
        }
        if (con18Regular == 1) cout << " La digrafica es regular."<<endl;
        else cout << " La digrafica no es regular."<<endl;
    }

    cout << endl << "Consideracion 19: " ;
    if( con12Bucles == 1 || con4Paralelas == 1 ){
        cout << " La digrafica no es balanceada." << endl;
    }
    else{
        int rensum = 0,colsum= 0;
        int con19Balanceada = 1; //suponer que si es hasta ver lo contrario
        for(int i =0; i < rens ; i++){ //comparando cada renglon
            if (con19Balanceada== 0) break;
            rensum = 0;
            colsum=0;
            for(int j =0; j< cols ; j++){ //suma por renglon
                rensum += (*matinc).get_val(i,j);
                colsum += (*matinc).get_val(j,i);
            }
            if(rensum != colsum) con19Balanceada = 0;
        }

        if (con19Balanceada == 1) cout << " La digrafica es balanceada."<<endl;
        else cout << " La digrafica no es balanceada." << endl;
    }

    cout << endl << "Consideracion 20: " ;
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
            conectadoINC(i, *matinc, vec[vec.size() - 1]);
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
            cout << "--G" <<i<<"= {";
            for(int j =0; j < vec[i].size() ; j++){
                cout << vec[i][j] << (j+1 == vec[i].size() ? "" : ",");
            }
            cout << "}" <<endl;
        }
        //*/
    }
    else cout << " La digrafica no es desconectada." << endl;

    cout << endl <<"FIN de las consideraciones para una matriz de incidencia dirigida" <<endl;

return 0;}
