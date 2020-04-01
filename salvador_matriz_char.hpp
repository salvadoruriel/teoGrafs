#ifndef salvador_matricesCHAR
#define salvador_matricesCHAR
#include <cmath>
#include <string>
#include <iostream>
/*WARNING: Usa algunos detalles de c++11*/
namespace salvador{


	class MatrizC{
		int ren,col; /*renglones,columnas, contando desde 1*/
		char** mat;

		public:/*sobrecarga de operadores al final*/
			MatrizC(int oren,int ocol);
			MatrizC(int oren,int ocol,char oval);
			MatrizC(const MatrizC &A,int minren, int mincol); /*MatrizC reducida en minren y mincol*/
			MatrizC(const MatrizC &A);
			~MatrizC();
            friend std::ostream& operator<<(std::ostream &,const MatrizC &);
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
			int replace_Mat(char data[],size_t datasize); /*to change it with a vector of values*/
			MatrizC replace_Mat(char data);/*replace all slots with data, sirven para clases anonimas*/
			MatrizC replace_Mat(std::string type);/*matrices especiales*/
			//*
            MatrizC ingresaMatrizC();
            //*/ /* \WARNING :non-standard, works only on CONSOLE. */
			//*
            MatrizC inputMatDisplay();
            //*/ /* \WARNING :non-standard, works only on CONSOLE. */
            MatrizC mpow(int x);
			MatrizC recurmpow(MatrizC a,int x); /*TODO: use double exp.*/
			int change_val(int ren_buscado,int col_buscada,char nuevo_val);
			void intercambia_rens(unsigned int original,unsigned int cambio);

            /**************************************************
                        RETORNO o impresion de datos de la matriz
            ****************************************************/
			int print_Mat(int busca_ren,int busca_col) const; //para imprimir la matriz hasta un punto
			//*
			int print_full_Mat() const;
			//*/ /*DEPRECATED: use operator << and send it to stream*/
			char * toArray(char data[]) const;
            /** \brief manda el renglon de numeros de la matriz al vector data
             *
             * \param data[] int: vector donde se alojaraon los valores del renglon
             * \param ren_buscado unsigned int
             * \return int* un puntero al vector
             * \TODO regresar un puntero a un vector de datos creado localmente en la func
             */
			char * da_ren(char data[], unsigned int ren_buscado) const;
			char get_val(int ren_buscado,int col_buscada) const;
			char get_norma_ESPECTRAL() const; /*regresa el VALOR de mayor magnitud*/
			char get_Biggest() const; /*regresa el numero con SIGNO de mayor magnitud*/
			char get_Traza() const;

			int get_renglones() const;
			int get_columnas() const;

			MatrizC transpuesta() const;

            /**************************************************
                            Sobrecarga de operadores
            ****************************************************/
                /**< operadores de asignacion */
          /*MatrizC &operator=(const MatrizC &B);*//**< Leer comentario en el cpp */
			MatrizC operator=(const MatrizC &B);
			MatrizC operator*=(const MatrizC &B);
			MatrizC operator+=(const MatrizC &B);
			MatrizC operator-=(const MatrizC &B);
                /**< operadores aritmeticos */
			friend MatrizC operator*(const char &c,const MatrizC &A) ;/*TODO: template*/
			friend MatrizC operator*(const MatrizC &A,const MatrizC &B) ;
			friend MatrizC operator+(const MatrizC &A,const MatrizC &B) ;
			friend MatrizC operator-(const MatrizC &A,const MatrizC &B) ;
                /**< operadores relacionales  */
			friend bool operator==(const MatrizC &A,const MatrizC &B) ;
			friend bool operator!=(MatrizC &A,MatrizC &B) ;
	};
}
#endif

