#ifndef BINARY_SEARCH_Tree
#define BINARY_SEARCH_Tree
#include <iostream>
#include <stack>
using namespace std;
// Nodos del arbol:
template <typename T>
class node{
   public:
        // Esta clase es usada por otras clases.
        // Para mayor eficiencia, los atributos se hacen publicos.
        T key;
        node<T> *p, *left, *right;

        // Constructor por omision
        node(){
        };

        // Constructor por copia. Copia el nodo y sus hijos.
        node(const node<T> * obj, node<T> * padre){
            key=obj->key;
            right=nullptr;
            left=nullptr;
            Copy(obj,this);
        }

        // Inicializacion de datos miembro
        node(const T& k, node<T> *w = nullptr, node<T> *y = nullptr, node<T> *z = nullptr):key(k), p(w), left(y), right(z){}

        ~node(){
        }

private:
        void insertNode(node<T>* z,node<T>* Node){
            bool NotInserted=true;
            if(z->key==Node->key){
                NotInserted=false;
            }
            while(NotInserted){
                if(z->key<Node->key){
                    if(Node->left==nullptr){
                        Node->left=z;
                        z->p=Node;
                        NotInserted=false;
                    }else{
                        Node=Node->left;
                    }
                }else if(z->key>Node->key){
                    if(Node->right==nullptr){
                        Node->right=z;
                        z->p=Node;
                         NotInserted=false;
                    }else{
                        Node=Node->right;
                    }
                }
            }
        }
        void Copy(const node<T>* nodo, node<T>* raiz){
            node<T> *nuevo=new node<T>(0);
            if(nodo!=nullptr){
                const node<T>* izq=nodo->left;
                const node<T>* der=nodo->right;
                nuevo->key=nodo->key;
                insertNode(nuevo,raiz);
                Copy(izq,raiz);
                Copy(der,raiz);
            }

        }

};

// Arbol:
template <typename T>
class tree{
    public:
        tree(){
            root=new node<T>;
            root->p=nullptr;
        };
            // Constructor. Crea un arbol vacio

        tree(const tree<T>& obj){
            root=new node<T>(0);
            root->p=nullptr;

            node<T>*Node=obj.getRoot()->p;
            Copy(Node);

        };
            // Constructor copia

        ~tree(){
            while(getRoot()->p->right!=nullptr || getRoot()->p->left!=nullptr){
                treeDelete(getRoot()->p);
            }
            getRoot()->p=nullptr;
            delete getRoot()->p;

        };
            // Destructor (borra el arbol)

        void inorderTreeWalk(node<T>* x, stack<T> & pila){
            if(x!=nullptr){
                inorderTreeWalk(x->left,pila);
                pila.push(x->key);
                inorderTreeWalk(x->right,pila);
            }
        };

            // Efectua un recorrido en orden del sub‡rbol cuya raiz es apuntada
            // por x, guardando en cada visita la llave de cada nodo en la pila.
            // Es decir, cada vez que se llega a un nodo se hace
            // pila.push(x->key). Si se hace correctamente, al finalizar el
            // metodo la pila debe contener las llaves de los nodos del
            // subarbol ordenadas de mayor a menor.


        node<T>* treeSearch(const T& k){

            return treeSearchRecursive(getRoot()->p,k);
        };
            // Busca la llave recursivamente; si la encuentra, devuelve un
            // apuntador al nodo que la contiene, sino devuelve NULL

        node<T>* iterativeTreeSearch(const T& k){
            bool notFoud=true;
            node<T>*nodo=getRoot()->p;
            while(notFoud && nodo!=nullptr){
                if(nodo->key==k){
                    notFoud=false;;
                }else{
                    if(k<nodo->key){
                        nodo=nodo->left;
                    }else{
                        nodo=nodo->right;
                    }
                }
            }
            return nodo;
        };
            // Lo mismo que en el anterior pero usando un procedimiento
            // iterativo

        node<T>* treeMinimum(){
            node<T> *Node=getRoot()->p;
            while(Node->left!=nullptr){
                Node=Node->left;
            }
            return Node;
        };
            // Devuelve el nodo que tiene la llave menor.
            // Si el arbol est‡ vacio devuelve NULL.

        node<T>* treeMaximum(){
            node<T> *Node=getRoot()->p;
            while(Node->right!=nullptr){
                Node=Node->right;
            }
            return Node;
        };
            // Devuelve el nodo que tiene la llave mayor.
            // Si el arbol esta vacio devuelve NULL.

         node<T>* treeSuccessor(const node<T>* x){
            node<T> Node;
            if(x->right!=nullptr){
                return MinimunRightTree(x);

            }else{
                return x->p;
            }
        };
            // Devuelve el nodo cuya llave es la que le sigue a la
            // del nodo x. Si no existe tal nodo devuelve NULL.

        void treeInsert(node<T>* z){
            bool NotInserted=true;
            node<T> * Node=getRoot();

            if(Node->p==nullptr){
                Node->p=z;
                z->p=Node;
                NotInserted=false;
            }
            Node=Node->p;
            while(NotInserted){
                if(z->key<Node->key){
                    if(Node->left==nullptr){
                        Node->left=z;
                        z->p=Node;
                        NotInserted=false;
                    }else{
                        Node=Node->left;
                    }
                }else if(z->key>Node->key){
                    if(Node->right==nullptr){
                        Node->right=z;
                        z->p=Node;
                         NotInserted=false;
                    }else{
                        Node=Node->right;
                    }
                }else{
                    NotInserted=false;
                }
            }
        };
        // Inserta el nodo z en la posicion que le corresponde en el arbol.

        node<T>* treeDelete(node<T>* z){
            //variables para dar legibilidad al codigo;
            node<T>*izqPadre=new node<T>(0);
            node<T>*derPadre=new node<T>(0);
            node<T>*Hijo=new node<T>(0);
            node<T>*abuelo=new node<T>(0);
            node<T>*padre=new node<T>();
            node<T>*Eliminado=new node<T>(0);

            if(getRoot()->p!=z){
                izqPadre=z->p->left;
                derPadre=z->p->right;;
                abuelo=z->p;
            }
            //no tiene hijos
            if(z->left==nullptr && z->right==nullptr){
                z->p=nullptr;//eliminamos puntero al padre
                if(izqPadre==z){//si es hijo izq se elimina de ese puntero de su padre
                    izqPadre=nullptr;
                }else{
                    derPadre=nullptr;//para el derecho
                }

                Eliminado->key=z->key;
                z=nullptr;
            //caso tiene 1 hijo pero no es la raiz
            }else if(((z->left!=nullptr && z->right==nullptr)||(z->left==nullptr && z->right!=nullptr))&& z!=getRoot()->p){
                if(z->left!=nullptr){//nieto es hijo izquierdo?
                    Hijo=z->left;
                    if(abuelo->left==z){//mi padre es hijo izquierdo ?
                        abuelo->left=Hijo;//paso a ser el hijo izquiero de mi abuelo
                    }
                    else{
                        abuelo->right=Hijo;//para el derecho
                    }
                    Hijo->p=abuelo;//abuelo ahora es mi padre
                    z->left=nullptr;

                }else{//nieto hijo derecho?
                    Hijo=z->right;
                    if(abuelo->right==z){//es mi padre hijo derecho
                        abuelo->right=Hijo;//paso a ser hijo derecho de mi abuelo
                    }
                    else{
                        abuelo->left=Hijo;//para el izquierdo
                    }
                    z->right=nullptr;

                };
                 Eliminado->key=z->key;
                 z->p=nullptr;

             //caso 1 hijo y quien elimino es la raiz
            //en mi caso root->p es el primer elemento del arbol
            }else if(((z->left!=nullptr && z->right==nullptr)||(z->left==nullptr && z->right!=nullptr))&& getRoot()->p==z){
                if(z->left!=nullptr){//tengo hijo izqierdo?
                    getRoot()->p=z->left;//mi primer elemento va ser mi hijo izquierdo
                    z->left=nullptr;
                }else{//es un hijo derecho
                    getRoot()->p=z->right;//el primer elemento va a ser mi hijo derecho
                    z->right=nullptr;
                }
                 z->p=nullptr;
             //caso 2 hijos
            }else{
                 Eliminado->key=z->key;

                 node<T> *succesor=treeSuccessor(z);//buscamos el sucesor de z
                 z->key=succesor->key;// la clave de z ahora es la de su sucesor
                 if(succesor->right!=nullptr){//sucersor tiene hijo derecho? no puede tener izquierdo, sino seria
                     //sucesor
                     succesor->right->p=succesor->p;//mi abuelo ahora es el padre

                     if(succesor->p->left==succesor){//el sucesor es hijo izquierdo?
                        succesor->p->left=succesor->right;//el hijo derecho ahora es el hijo
                        //izquierdo del abuelo
                     }
                     else{
                         succesor->p->right=succesor->right;//caso en que sea derecho
                     }
                 }else{//sucesor tiene hijo izquierdo?
                     if(succesor->p->right->key==z->key)//sucesor es hijo derecho?
                        succesor->p->right=nullptr;//eliminamos a la posicion original del sucesor;
                     else
                         succesor->p->left=nullptr;//"                                              "
                     succesor->p=nullptr;
                 }

            }

            return Eliminado;
        };
            // Saca del arbol la llave contenida en el nodo apuntado por z.
            // Devuelve la direccion del nodo eliminado para que se pueda
            // disponer de ella.

        node<T> * getRoot() const{
            return this->root;
        };
        // Devuelve la raiz del arbol. (Para efectos de revisi—n de la tarea).

        void InsertTreeList(){
            int i=1;
            node<T>* incial=new node<T>();
            getRoot()->p=incial;
            node<T>* posicion=getRoot()->p;

            while(i<1000000){
                node<T>* nodo=new node<T>(i);
                posicion->right=nodo;
                posicion=posicion->right;
                i++;
            }
        }


    private:
        node<T> *root;	// root of the Tree

        node<T>* MinimunRightTree(const node<T> *Nodo){
            node<T>* Node;
            //debido a que es const, hice una variable non-const
            Node->left=Nodo->left;
            Node->right=Nodo->right;
            Node->p=Nodo->p;

            //si hay un arbol derecho, busca el minimo de este
            Node=Node->right;
            while(Node->left!=nullptr){
                Node=Node->left;
            }
            return Node;

        }

        void Copy(node<T>* nodo){
            node<T> *nuevo=new node<T>(0);
            if(nodo!=nullptr){
                nuevo->key=nodo->key;
                treeInsert(nuevo);
                Copy(nodo->left);
                Copy(nodo->right);
            }
        }

        node<T>* treeSearchRecursive(node<T> *nodo,int key){
            if(nodo==nullptr || key==nodo->key){
                return nodo;
            }
            if(key<nodo->key){
                return treeSearchRecursive(nodo->left,key);
            }else{
                return treeSearchRecursive(nodo->right,key);
            }

        }





};
#endif	// BINARY_SEARCH_Tree
