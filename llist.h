#ifndef LINKED_LIST_llist
#define LINKED_LIST_llist
#include <iostream>

// Nodos de la lista:
template <typename T>
class llnode{
   public:
        // Esta clase es para ser usada por otras clases.
        // Por eficiencia los atributos se dejan publicos.
        T key;
        llnode<T> *prev, *next;
        //enum colors color;

        // Constructor por omision.
        llnode(){
        };

      // Inicializacion de los datos miembro.
        llnode (const T& k, llnode<T> *w = NULL, llnode<T> *y = NULL):key(k), prev(w), next(y) {}

        ~llnode(){

        }
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist{
    public:
        llist(){
            llnode<T> *sentinela=new llnode<T>(0);
            nil=new llnode<T>;
            getNil()->next=sentinela;
            sentinela->next=sentinela;
            sentinela->prev=sentinela;

        };
            // Constructor (crea una lista vacia)

        llist(const llist<T>& obj){
            nil= new llnode<T>;

            llnode<T> *sentinela=new llnode<T>(0);
            llnode<T> *newNode=obj.getNil()->next->next;
            getNil()->next=sentinela;
            sentinela->next=sentinela;
            sentinela->prev=sentinela;

            while(newNode!=obj.getNil()->next){
                llnode<T> *Nodo=new llnode<T>(newNode->key);
                listInsert(Nodo);
                newNode=newNode->next;
            }

        };
            // Constructor copia

        ~llist(){
            llnode<T> *posicion=getNil()->next->prev;
            llnode<T> *anterior;
            posicion->next=nullptr;
            getNil()->next->prev=nullptr;

            while(posicion->prev!=0){
                posicion->prev->next=nullptr;
                anterior=posicion->prev;
                posicion->prev=nullptr;
                delete posicion;
                posicion=anterior;


            }
            delete posicion;
            getNil()->next=nullptr;
            delete getNil();




        };
            // Destructor (borra la lista)

        llnode<T>* listSearch(const T& k){
            llnode<T> *posicion=getNil()->next->next;

            while(posicion!=getNil()->next){
                if(posicion->key==k)
                    return posicion;
                posicion=posicion->next;
            }
            return nullptr;
        };
            // Busca la llave iterativamente. Si la encuentra, devuelve un
            // apuntador al nodo que la contiene; sino devuelve NULL.

        void listInsert(llnode<T>* x){
            x->prev=getNil()->next->prev;
            getNil()->next->prev->next=x;
            x->next=getNil()->next;
            getNil()->next->prev=x;

        };
            // Inserta el nodo x en la lista.

        llnode<T>* listDelete(llnode<T>* x){
            x->prev->next=x->next;
            x->next->prev=x->prev;

            return x;
        };
            // Saca de la lista la llave contenida en el nodo apuntado por x.
            // Devuelve la direccion del nodo eliminado para que se pueda
            // disponer de el.

        llnode<T> * getNil() const{
            return nil;
        };
        // Devuelve el nodo centinela. (Para efectos de revision de la tarea).

        private:

        llnode<T> *nil;	    // nodo centinela

};

#endif	// LINKED_LIST_llist
