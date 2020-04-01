#include <cstdlib> /*para calloc y free*/
#include <cmath> /*operaciones*/

#include <iostream>
#include <algorithm> /*for the max*/
#include <iomanip> /*Para dar formato a std con internal,left,right*/

/** \brief operaciones basicas con matrices dinamicas, usando ENTEROS INT
 *
 * Se recomienda leer los comentarios al lado de cada funcion
 *  ya que algunas requieren detalles, de todas formas
 *  los campos deberian ser lo suficientemente especificos
 *  Autor Salvador Uriel Aguirre Andrade
 * WARNING: Usa algunos detalles de c++11.
 *
 */
#include "salvador_matriz_int.hpp"

namespace salvador{

    MatrizI::MatrizI(int oren=2,int ocol=2){
        ren = oren;
        col = ocol;

        if(ren > 0) mat = (int**) calloc(ren,sizeof(int));
        for(int i = 0; i < ren; i++){
            mat[i] = (int*) calloc(col,sizeof(int));
        }
    }

    /*! \brief creates a smaller matrix without the row and column selected
     *
     * \param A, la matriz a copiar
     * \param minren el renglon a excluir
     * \param mincol la columna a excluir
     * \note use -1 to avoid excluding any row or col
     *
     * \WARNING avoid vectors, they will make empty memory
     */
    MatrizI::MatrizI(const MatrizI &A,int minren, int mincol){
        if(minren >= 0) ren = (A.get_renglones() -1 > 0 ? A.get_renglones()-1 : 0);
        else ren = A.get_renglones();

        if(mincol >= 0)col = (A.get_columnas() -1 > 0 ? A.get_columnas()-1 : 0);
        else col = A.get_columnas();

        if(ren > 0) mat = (int**) calloc(ren,sizeof(int));
        for(int i = 0; i < ren; i++){
            mat[i] = (int*) calloc(col,sizeof(int));
        }
        int avoidren{0}, avoidcol{0};
        for(int i=0; i<ren; i++){
            if(i == minren) avoidren = 1;
            avoidcol = 0;
            for(int j=0; j<col; j++){
                if(j == mincol) avoidcol = 1;
                mat[i][j] = A.mat[i+avoidren][j+avoidcol];
            }
        }
    }
    MatrizI::MatrizI(const MatrizI &A){
        ren = A.ren;
        col = A.col;
        if(ren > 0) mat = (int**) calloc(ren,sizeof(int));
        for(int i = 0; i < ren; i++){
            mat[i] = (int*) calloc(col,sizeof(int));
        }
        for(int i=0; i<ren; i++){
            for(int j=0; j<col; j++){
                mat[i][j] = A.mat[i][j];
            }
        }
    }

    MatrizI::~MatrizI(){
        int i;
        for(i = 0; i < ren; i++){
            free(mat[i]);
        }
        free(mat);
    }

    std::ostream& operator<<(std::ostream &out, const MatrizI &A){
        int i,j,ren = A.get_renglones(), col = A.get_columnas()
                ,precision{ 3 },espacio{precision+1+2+1} ;
                /**< precision: n de digitos despues del punto */
                /**< setw(r) donde r= n +1(por el .) +2(por unidad a decena)
                                        +1(por el signo)*/
        int temp;
        out <<std::endl<<"r\\c ";/*Ya que desconocemos el tamanio de la matriz*/
        for(i = 0; i < col ; i++){
            out <<std::setw(espacio) << i;
            if(i != col-1) out << " |";
        }
        out << std::endl;
        for(i = 0; i < ren ; i++){
                out  << std::setw(2) << i<<": ";
            for (j = 0; j < col ; j++){
                temp = ( std::fabs(A.get_val(i,j))
                        < (1/std::pow(10, precision)) ? 0 : A.get_val(i,j) );
                out << std::setw(espacio)<< temp  ;
                if(j != col-1) out << " |";
            }
            if(j == col) out << std::endl;
        }
        out << std::endl;
    return out;}

    /**************************************************
                    Operaciones logicas
    ****************************************************/
    bool MatrizI::es_cuadrada() const { return ren == col;}
    bool MatrizI::es_simetrica() const{
        if( ren == 0 || col == 0 || ren != col) return false;

        for(int i =0; i < ren ; i++){
            for(int j =0; j < i; j++){
                if(mat[i][j] != mat[j][i] ) return false;

            }
        }
    return true;}

    /**************************************************
            Operaciones sobre la matriz o sus valores
    ****************************************************/
    int MatrizI::replace_Mat(int data[],size_t datasize){ /*Ya que la matriz esta iniciada en ceros*/
        int temp_ren= 0,temp_col= 0, available =(int) (datasize/sizeof(int));
        int current=0,i,j,state=available - ren*col;

        if(state < 0){/*control en caso de tener menos datos que los necesarios*/
            while(available - 1 >=0){
                temp_col++;
                if(temp_col == col){
                    temp_ren++;
                    temp_col = 0;
                }
                available--;
            }
        }else{
            temp_ren = ren;
            temp_col = col;
        }

        for(i = 0; i < temp_ren; i++){
            for (j = 0; j < temp_col; j++){
                        /*
                        std::cout << "mat["<<i << "][" << j<<"] = data[" << current <<"] === " ;
                        printf("%f = %f",(mat[i][j]), (data[current]) );
                        std::cout  <<std::endl;
                        //*/           /*******DEBUGGING*/
                mat[i][j] = data[current];
                        /*
                        std::cout << "mat["<<i << "][" << j<<"] = data[" << current <<"] === " ;
                        printf("%f = %f",(mat[i][j]), (data[current]) );
                        std::cout  <<std::endl;
                        //*/           /*******DEBUGGING*/
                current++;
            }
        }
    return state;}
	MatrizI MatrizI::replace_Mat(int data){
		 for(int i = 0; i < ren; i++){
	            for (int j = 0; j < col; j++){
		                mat[i][j] = data;
	                        /*
	                        std::cout << "mat["<<i << "][" << j<<"] = data === " ;
	                        printf("%f = %f",(mat[i][j]), data );
	                        std::cout  <<std::endl;
	                        //*/           /*******DEBUGGING*/
	            }
       		 }

	return *this;}
	MatrizI MatrizI::replace_Mat(std::string type){
		if(type.compare("I") == 0 ){ /*IDENTITY matrix*/
			for(int i = 0; i < ren; i++){
		            for (int j = 0; j < col; j++){
		                        /*
		                        std::cout << "mat["<<i << "][" << j<<"] = i==j?1:0 === " ;
		                        printf("%f = %f",(mat[i][j]), i==j?1:0 );
		                        std::cout  <<std::endl;
		                        //*/           /*******DEBUGGING*/
			               mat[i][j] = ( i==j ? 1 : 0 );
		                        /*
		                        std::cout << "mat["<<i << "][" << j<<"] = i==j?1:0 === " ;
		                        printf("%f = %f",(mat[i][j]), i==j?1:0 );
		                        std::cout  <<std::endl;
		                        //*/           /*******DEBUGGING*/
		            }
	       		 }
		return *this;}
		MatrizI::replace_Mat(std::nan("")); /*function doesnt exist*/
	return *this;}

	//*
    MatrizI MatrizI::ingresaMatrizI(){
        std::cout << std::endl;
        for(int i =0; i<ren; i++) {
            for(int j=0; j<col; j++) {
                std::cout <<"Ingrese el valor de la matriz en ["
                            << i+1 <<"]["<< j+1 <<"]: ";
                while (1) {
                  if (std::cin >> mat[i][j]) break; // Dato valido
                  else {
                      std::cout << " Dato no valido" << std::endl;
                      std::cin.clear();
                      while (std::cin.get() != '\n') ; //vaciar hasta el enter
                  }
                }
                std::cin.get(); //para deshacernos del enter.
            }
        }
        std::cout << std::endl;
    return *this;}
    //*/ /* \WARNING :non-standard, works only on CONSOLE. */

    //*
    MatrizI MatrizI::inputMatDisplay(int pos){ //0 todos, 1 solo positivos
        int temp;

        for(int i = 0; i < ren; i++){
            for (int j = 0; j < col; j++){
                    #ifdef _WIN32
                    system("cls");
                    #endif
                std::cout << std::endl <<"Matriz Actual: ren(" << i <<"), col("
                            << j <<")" << std::endl;
                if(!(i== 0 && j== 0) ) MatrizI::print_Mat(i,j-1);
                while (1) {
                  if (std::cin >> mat[i][j] && (pos == 0 ? 1 : mat[i][j] >=0 ) ) break; // Dato valido
                  else {
                      std::cout << " Dato no valido" << std::endl;
                      std::cin.clear();
                      while (std::cin.get() != '\n') ; //vaciar hasta el enter
                  }
                }
                std::cin.get(); //para deshacernos del enter.
                //while(scanf(" %lf",&temp) != 1)
                //        while((c = getchar()) != '\n' && c != EOF);
                //(**A).change_val(i,j,temp);
            }
        }
        char opt;
                #ifdef _WIN32
                system("cls");
                #endif
        do{
            std::cout <<std::endl <<"Es correcta la matriz introducida? " << std::endl
                        << (*this) << std::endl
                        <<"S - Si" << std::endl
                        <<"N - No" << std::endl
                        <<"--> ";
            while (1) {
              if (std::cin >> opt ) break; // Dato valido
              else {
                  std::cout << " Opcion no valida" << std::endl;
                  std::cin.clear();
                  while (std::cin.get() != '\n') ; //vaciar hasta el enter
              }
            }
            //while(scanf(" %c",&opt) != 1)
            //            while((c = getchar()) != '\n' && c != EOF);

            switch(opt){
                case 's':
                case 'S':
                    break;

                case 'n':
                case 'N':
                    int aux_ren,aux_col;
                    char c;
                    int nuevo;
                    std::cout <<std::endl <<"Dame la posicion del valor a corregir,"
                            <<" como \"renglon columna valor_nuevo\": "
                            <<std::endl <<"Ejemplo: 3 2 -5.2 "
                            <<std::endl <<"--> ";
                    while(scanf(" %d %d %d",&aux_ren,&aux_col,&nuevo) != 3)
                            while((c = getchar()) != '\n' && c != EOF);
                    MatrizI::change_val(aux_ren,aux_col,nuevo);
                    break;

                default:
                    std::cout <<std::endl <<"Opcion incorrecta" << std::endl;
                    break;
                }
                std::cout <<std::endl <<"Presione ENTER para continuar... ";
                std::cin.get();
                        #ifdef _WIN32
                        system("cls");
                        #endif
            }while(opt != 's' && opt != 'S');

    return *this;}

    //*/ /* \WARNING :non-standard, works only on CONSOLE. */

    MatrizI MatrizI::mpow(int x){
        if(x <= 1) return *this;
        return (*this)* MatrizI::recurmpow((*this),x-1);
    }
    MatrizI MatrizI::recurmpow(MatrizI a,int x){
        if(x <= 1) return a;
        return a * MatrizI::recurmpow(a,x-1);
    }

    int MatrizI::change_val(int ren_buscado,int col_buscada,int nuevo_val){/*contando desde 0*/
        if(ren_buscado >= ren || col_buscada >= col) return -1; /*error: value out of bounds*/

        mat[ren_buscado][col_buscada] = nuevo_val;
    return 0;}/*success!*/

    void MatrizI::intercambia_rens(unsigned int original,unsigned int cambio){
        if(original == cambio) return;
        int a_orig[col], b_camb[col];
        MatrizI::da_ren(a_orig,original);
        MatrizI::da_ren(b_camb,cambio);
        int i;
        /*Ya estamos dentro de la funcion de la clase MatrizI, no hace
        falta llamar a la func de cambiar un cierto valor*/
        for(i= 0; i< col; i++){
            mat[original][i] = b_camb[i];
            mat[cambio][i] = a_orig[i];
        }
    }

    /**************************************************
                RETORNO de datos de la matriz
    ****************************************************/
    /*Imprime la matriz hasta la posicion ren,col, empezando desde 0*/
    int MatrizI::print_Mat(int busca_ren,int busca_col) const{
        if(busca_ren >= ren) busca_ren = ren -1; /*Para evitar desbordes */
        if(busca_col >= col) busca_col = col -1; /* al buscar en memoria que no exista*/
        int i,j;
                        /*
                        std::cout << "\n busca_col = " << busca_col << ", busca_ren= " << busca_ren << std::endl;
                        //*/ /*******DEBUGGING*/
        std::cout << "   ";
        for(i = 0; i <= ((busca_ren>0) ? col-1 : busca_col ) ; i++){
            std::cout <<std::setw(3) << std::left << i;
            if(i != col-1) std::cout << std::setw(3)<< " | ";
        }
        std::cout << std::endl;
        for(i = 0; i <= busca_ren ; i++){
                std::cout  << std::left << i<<": ";
                if (i==busca_ren && busca_col<0) return 1;
            for (j = 0; j < col ; j++){
                std::cout  <<  std::setw(3) << std::left << mat[i][j] ;
                if(j != col-1) std::cout << std::setw(3)<< " | ";
                        /*
                        std::cout <<"(" <<std::boolalpha  << "(busca_ren == ren -1)= " <<(busca_ren == ren -1)
                                    <<",(busca_col == col -1)= " << (busca_col == col -1)
                            <<",(busca_ren == ren -1) && (busca_col == col -1)= " << ((busca_ren == ren -1) && (busca_col == col -1))
                                    << std::noboolalpha<<")" << std::endl;
                            //*/ /*******DEBUGGING*/
                if ( !((busca_ren == ren -1) && (busca_col == col -1)) ){ /*If we don't search the full matrix*/
                    if (i==busca_ren && (j==busca_col || busca_col<0) ) return 1;} /*found spot*/
            }
            if(j == col) std::cout << std::endl;
        }
    return 0;}/*Printed whole matrix*/
    //*
    int MatrizI::print_full_Mat() const{ return MatrizI::print_Mat(ren,col);}
    //*/ /*DEPRECATED: use operator << and send it to stream*/
    int * MatrizI::toArray(int data[]) const{ /*data is required to be of size ren*col atleast*/
        for(int i = 0; i < ren ; i++){
            for (int j = 0; j < col ; j++){
                data[i*col + j] = mat[i][j] ;
            }
        }
    return data;}

    int * MatrizI::da_ren(int data[],unsigned int ren_buscado) const{ /*Warning, data is required to be of size col*/
        if(ren_buscado > ren){ /*Non existent row*/
            data[0] = std::nan("");
            return data;
        }
        if(ren_buscado == ren) ren_buscado--;
        int i;
        for(i = 0; i < col; i++){
            data[i] = mat[ren_buscado][i];
        }

    return data;}

    int MatrizI::get_val(int ren_buscado,int col_buscada) const{
        if(ren_buscado == ren) ren_buscado = ren -1; /*Para evitar desbordes */
        if(col_buscada == col) col_buscada = col -1;
        if(ren_buscado > ren) return std::nan("");
        if(col_buscada > col) return std::nan("");
    return mat[ren_buscado][col_buscada];}

    int MatrizI::get_norma_ESPECTRAL() const{
        if( ren == 0 || col == 0) return std::nan("");

        int mayor = std::fabs(mat[0][0]), aux_temp;

        for(int i =0; i < ren ; i++){
            for(int j =0; j < col; j++){ /*even if we go to i,i the evaluation should fail*/
                aux_temp = std::fabs(mat[i][j]);
                if(mayor < aux_temp ) mayor = aux_temp;
            }
        }
    return mayor;}
    int MatrizI::get_Biggest() const{
            if( ren == 0 || col == 0) return std::nan("");

            int mayor = mat[0][0];

            for(int i =0; i < ren ; i++){
                for(int j =0; j < col; j++){
                    if(std::fabs(mayor) < std::fabs(mat[i][j]) ) mayor = mat[i][j];
                }
            }
    return mayor;}

    int MatrizI::get_Traza() const{
        if( !((*this).es_cuadrada()) ) return std::nan("");
        int traz{0};
        for(int i=0; i < ren; i++){
            traz += mat[i][i];
        }

    return traz;}

    int MatrizI::get_renglones() const{ return ren;}
    int MatrizI::get_columnas() const{ return col;}

	MatrizI MatrizI::transpuesta() const {
	    if((*this).es_cuadrada() ){
            MatrizI trans(*this);
            for(int i=0; i< ren; i++){
                for(int j=i+1; j< col; j++){
                    trans.change_val(i,j, (*this).get_val(j,i)  );
                    trans.change_val(j,i, (*this).get_val(i,j)  );
                }
            }
            return trans;
	    }
	    int new_ren{ (*this).get_columnas() }, new_col{ (*this).get_renglones() };
	    MatrizI trans( new_ren, new_col);
            for(int i=0; i< new_ren; i++){
                for(int j=0; j< new_col; j++){
                    trans.change_val(i,j, (*this).get_val(j,i)  );
                    trans.change_val(j,i, (*this).get_val(i,j)  );
                }
            }
	return trans;}

    /**************************************************
                        Sobrecarga de operadores
    ****************************************************/
                /**< operadores de asignacion */
        /* TODO: TEST 2nd case and replace in the other operators.
    MatrizI &MatrizI::operator=(const MatrizI &B){
        if((*this).ren != B.ren ) return *this;
        if((*this).col != B.col) return *this;
        /*/
    MatrizI MatrizI::operator=(const MatrizI &B){
        if((*this).ren != B.ren || (*this).col != B.col){
            (*this).replace_Mat(std::nan(""));
        return *this;}
        //*/ /*2nd case is optimal error return value, 1st case is what allows us to use &operator*/
        /*Los demas operadores de asignacion se definen como el segundo caso
            para tener un error rastreable en caso de suceder*/

        for(int i=0; i<(*this).ren; i++){
            for(int j=0; j<(*this).col; j++){
                (*this).mat[i][j] = B.mat[i][j];
            }
        }
    return *this;}

    MatrizI MatrizI::operator*=(const MatrizI &B){ /*NECESITAN SER CUADRADAS y mismo tamanio*/
        if((*this).ren != B.ren || (*this).col != B.col){
            (*this).replace_Mat(std::nan(""));
        return *this;} /*Error: not same size*/

        MatrizI aux(*this);
        (*this) = ((*this)* B);

    return *this;}

    MatrizI MatrizI::operator+=(const MatrizI &B){
        if((*this).ren != B.ren) return MatrizI(0,0); /*Error: not same size*/
        if((*this).col != B.col) return MatrizI(0,0); /*Error: not same size*/
        (*this) = (*this) + B;

    return *this;}

    MatrizI MatrizI::operator-=(const MatrizI &B){
        if((*this).ren != B.ren) return MatrizI(0,0); /*Error: not same size*/
        if((*this).col != B.col) return MatrizI(0,0); /*Error: not same size*/
        (*this) = (*this) - B;

    return *this;}

                /**< operadores aritmeticos */
    MatrizI operator*(const int &c,const MatrizI &A) {/*TODO: Template*/
        MatrizI temp(A);
        for(int i=0; i< A.get_renglones() ; i++){
            for(int j=0; j<A.get_columnas() ; j++){
                temp.change_val(i,j, temp.get_val(i,j) * c);
            }
        }
    return temp;}

    MatrizI operator*(const MatrizI &A,const MatrizI &B) {
        int A_ren = A.get_renglones(), A_col = A.get_columnas()
            ,B_ren = B.get_renglones(), B_col = B.get_columnas();
        if(A_col != B_ren) return MatrizI(0,0); /*Error: not same size*/
        MatrizI temp( A_ren,B_col );
        /*
        std::cout << std::endl << A <<" * " << B;
        //*/ /**< DEBUGGING */
        int resultado;
        for(int r=0; r< A_ren; r++){
            for(int c=0; c< B_col; c++){
                resultado =0;
                for(int i=0; i< A_col; i++){
                    resultado += A.get_val(r,i) * B.get_val(i,c);
                    /*
                        printf("\nA(%d,%d)= %f , ",r,i,A.get_val(r,i));
                        printf("B(%d,%d) = %f ",i,c,B.get_val(i,c));
                    std::cout << "  , A*B resultado: " <<resultado;
                    //*/ /**< DEBUGGING */
                }
                temp.change_val(r,c, resultado);
                    /*
                    std::cout << std::endl<<" ,r: " << r << " ,c: "<<c
                                <<" ,temp: "<< temp;
                    //*/ /**< DEBUGGING */
            }
        }

    return temp;}

    MatrizI operator+(const MatrizI &A,const MatrizI &B) {
        if(A.get_renglones() != B.get_renglones()) return MatrizI(0,0); /*Error: not same size*/
        if(A.get_columnas() != B.get_columnas()) return MatrizI(0,0); /*Error: not same size*/
        MatrizI temp(A.get_renglones(),A.get_columnas());
        for(int i=0; i<temp.get_renglones(); i++){
            for(int j=0; j<temp.get_columnas(); j++){
                temp.change_val(i,j, A.get_val(i,j) + B.get_val(i,j) );
            }
        }

    return temp;}

    MatrizI operator-(const MatrizI &A,const MatrizI &B) {
        if( A.get_renglones() != B.get_renglones() ) return MatrizI(0,0); /*Error: not same size*/
        if( A.get_columnas() != B.get_columnas() ) return MatrizI(0,0); /*Error: not same size*/
        MatrizI temp(A.get_renglones(),A.get_columnas());
        for(int i=0; i<temp.get_renglones(); i++){
            for(int j=0; j<temp.get_columnas(); j++){
                temp.change_val(i,j, A.get_val(i,j) - B.get_val(i,j) );
            }
        }

    return temp;}

                /**< operadores relacionales  */
    bool operator==(const MatrizI &A,const MatrizI &B) {
        if(A.get_columnas() != B.get_columnas()) return false; /*Error: not same size*/
        if(A.get_renglones() != B.get_renglones()) return false; /*Error: not same size*/

        bool ans = true;
        for(int i=0; i<A.get_renglones(); i++){
            for(int j=0; j<A.get_renglones(); j++){
             ans = (ans && A.get_val(i,j) == B.get_val(i,j)  );
            }
        }

    return ans;}

    bool operator!=(MatrizI &A,MatrizI &B) {
    return !(A == B);}
}
