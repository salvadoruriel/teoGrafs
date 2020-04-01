#ifndef salvador_matricesINT
#define salvador_matricesINT
#include <cmath>
#include <string>
#include <iostream>
/*WARNING: Usa algunos detalles de c++11*/
namespace salvador{


	class MatrizI{
		int ren,col; /*renglones,columnas, contando desde 1*/
		int** mat;

		public:/*sobrecarga de operadores al final*/
			MatrizI(int oren,int ocol);
			MatrizI(int oren,int ocol,int oval);
			MatrizI(const MatrizI &A,int minren, int mincol); /*MatrizI reducida en minren y mincol*/
			MatrizI(const MatrizI &A);
			~MatrizI();
            friend std::ostream& operator<<(std::ostream &,const MatrizI &);
			/**Operaciones logicas*/
			bool es_cuadrada() const;
			bool es_simetrica() const;


            /**************************************************
                    Operaciones sobre la matriz o sus valores
            ****************************************************/
            /** \brief reemplaza una matriz con un vector de valores
             *
             * \param data[] int, vector con valores
             * \param datasize size_t, tamanio del vector
             * \return int,  retorna cantidad de elementos faltantes(negativo),
             *			    o sobrantes(positivo), si fueron exactos, el return es 0;
             */
			int replace_Mat(int data[],size_t datasize); /*to change it with a vector of values*/
			MatrizI replace_Mat(int data);/*replace all slots with data, sirven para clases anonimas*/
			MatrizI replace_Mat(std::string type);/*matrices especiales*/
			//*
            MatrizI ingresaMatrizI();
            //*/ /* \WARNING :non-standard, works only on CONSOLE. */
			//*
            MatrizI inputMatDisplay(int pos); //0 todos, 1 solo positivos
            //*/ /* \WARNING :non-standard, works only on CONSOLE. */
            MatrizI mpow(int x);
			MatrizI recurmpow(MatrizI a,int x); /*TODO: use double exp.*/
			int change_val(int ren_buscado,int col_buscada,int nuevo_val);
			void intercambia_rens(unsigned int original,unsigned int cambio);

            /**************************************************
                        RETORNO o impresion de datos de la matriz
            ****************************************************/
			int print_Mat(int busca_ren,int busca_col) const; //para imprimir la matriz hasta un punto
			//*
			int print_full_Mat() const;
			//*/ /*DEPRECATED: use operator << and send it to stream*/
			int * toArray(int data[]) const;
            /** \brief manda el renglon de numeros de la matriz al vector data
             *
             * \param data[] int: vector donde se alojaraon los valores del renglon
             * \param ren_buscado unsigned int
             * \return int* un puntero al vector
             * \TODO regresar un puntero a un vector de datos creado localmente en la func
             */
			int * da_ren(int data[], unsigned int ren_buscado) const;
			int get_val(int ren_buscado,int col_buscada) const;
			int get_norma_ESPECTRAL() const; /*regresa el VALOR de mayor magnitud*/
			int get_Biggest() const; /*regresa el numero con SIGNO de mayor magnitud*/
			int get_Traza() const;

			int get_renglones() const;
			int get_columnas() const;

			MatrizI transpuesta() const;

            /**************************************************
                            Sobrecarga de operadores
            ****************************************************/
                /**< operadores de asignacion */
          /*MatrizI &operator=(const MatrizI &B);*//**< Leer comentario en el cpp */
			MatrizI operator=(const MatrizI &B);
			MatrizI operator*=(const MatrizI &B);
			MatrizI operator+=(const MatrizI &B);
			MatrizI operator-=(const MatrizI &B);
                /**< operadores aritmeticos */
			friend MatrizI operator*(const int &c,const MatrizI &A) ;/*TODO: template*/
			friend MatrizI operator*(const MatrizI &A,const MatrizI &B) ;
			friend MatrizI operator+(const MatrizI &A,const MatrizI &B) ;
			friend MatrizI operator-(const MatrizI &A,const MatrizI &B) ;
                /**< operadores relacionales  */
			friend bool operator==(const MatrizI &A,const MatrizI &B) ;
			friend bool operator!=(MatrizI &A,MatrizI &B) ;
	};
}
#endif
