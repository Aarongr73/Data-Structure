#ifndef HASH_CLASS
#define HASH_CLASS
#include <list>
#include <vector>

template <typename T>

class hasht{
    public:
        hasht(int nEntradas){
           numEntradas=nEntradas;
           tabla.resize(nEntradas);
        };
            // Constructor que especifica el numero de cubetas (entradas)
            // en la tabla

        hash(const hash<T>& obj){
            numEntradas=obj.getTam();
            tabla.resize(numEntradas);

            for(int i=0;i<numEntradas;i++){
                if(!tabla[i].empty()){
                    tabla[i]=obj.tabla[i];
                }
            }

        };
            // Constructor copia

        ~hasht(){
            for(int i=0;i<numEntradas;i++){
                if(!tabla[i].empty())
                    tabla[i].clear();
            }
            tabla.clear();

        };
            // Destructor (borra la tabla)

        T* search(const T& item){
            for (auto it = tabla[item%numEntradas].begin(); it !=  tabla[item%numEntradas].end(); ++it){
                if(*it==item){
                    return &(*it);
                }
            }
            return nullptr;
        };
            // Retorna un puntero a la llave o NULL si no se encuentra

        void insert(const T& item){
           tabla[item%numEntradas].push_front(item);
        };
            // Inserta el elemento en la tabla

    private:
        int numEntradas;
            // Nœmero de entradas en la tabla
        vector<list<T> > tabla;
            // La tabla es un vector de listas de STL
        int getTam(){
            return  numEntradas;
        }
        int getTabla(){
            return  tabla;
        }
 };
#endif
