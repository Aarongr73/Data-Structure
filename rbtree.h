#ifndef RED_BLACK_rbtree
#define RED_BLACK_rbtree
#include <stack>
#include <iostream>

enum colors {RED, BLACK};

// Nodos del arbol:
template <typename T>
class rbnode{
   public:
        // Esta clase es para ser usada por otras clases.
        // Por eficiencia se hacen los atributos publicos.
        T key;
        rbnode<T> *p, *left, *right;
        enum colors color;

        // Constructor por omision.
        rbnode(){
            p=nullptr;
            left=nullptr;
            right=nullptr;
            color=BLACK;
        };

        // Constructor por copia del nodo.
        rbnode(const rbnode<T> * obj, const rbnode<T> * objNil, rbnode<T> * parent, rbnode<T> * nilPtr){

        }

      // Inicializacion de datos miembro.
        rbnode (const T& k, rbnode<T> *w = NULL, rbnode<T> *y = NULL,
                 rbnode<T> *z = NULL, enum colors c = RED):
                    key(k), p(w), left(y), right(z), color(c)
        {};

        ~rbnode(){

        }
};

// Arbol:
template <typename T>
class rbtree{
    public:
        rbtree(){
            nil=new rbnode<T>();
            nil->left=nullptr;
            nil->right=nullptr;
            nil->color=BLACK;
            root=nil;


        };
            // Constructor (crea un arbol vacio)

        rbtree(const rbtree<T>& obj){
            nil=new rbnode<T>();
            nil->left=nullptr;
            nil->right=nullptr;
            nil->color=BLACK;
            root=nil;

            rbnode<T>*raiz=new rbnode<T>();
            raiz->key=obj.getRoot()->key;
            treeInsert(raiz);
            Copy(obj.getRoot()->left,obj);
            Copy(obj.getRoot()->right,obj);
        };
            // Constructor copia

        ~rbtree(){
            Destruir();
        };
            // Destructor (borra el arbol)

        void inorderTreeWalk(rbnode<T>* x, stack<T> & pila){
            inorderTreeWalkR(x,pila);
        };
            // Efectua un recorrido en orden del subarbol cuya ra’z es apuntada
            // por x. En cada visita apila la llave de cada nodo y su color.
            // Es decir, cada vez que se llega a un nodo se ejecutan las
            // instrucciones pila.push(x->key); y luego pila.push(colorDeX).
            // Para efectos de la tarea, si el color del nodo es rojo,
            // ponga en la pila un 0, y si es negro, ponga un 1.
            // Si se hace correctamente, al finalizar el mŽtodo la pila deber’a
            // contener las llaves de los nodos del sub‡rbol (y su color)
            // ordenadas de mayor a menor.

        rbnode<T>* treeSearch(const T& k){
            rbnode<T>*nodo=new rbnode<T>();
            nodo=treeSearchRecursive(root,k);
            if(nodo==nil)
                nodo=nullptr;
            return nodo;
        };
            // Busca la llave recursivamente, si la encuentra devuelve un
            // puntero al nodo que la contiene, sino devuelve NULL.

        rbnode<T>* iterativeTreeSearch(const T& k){
            bool notFoud=true;
            rbnode<T>*nodo=getRoot();
            while(notFoud && nodo!=nil){
                if(nodo->key==k){
                    notFoud=false;
                }else{
                    if(k<nodo->key){
                        nodo=nodo->left;
                    }else{
                        nodo=nodo->right;
                    }
                }
            }
            if(nodo==nil)
                nodo=nullptr;
            return nodo;
        };
            // Igual que en el anterior pero usa un procedimiento iterativo.

        rbnode<T>* treeMinimum(){
           rbnode<T> *Node=getRoot()->p;
            while(Node->left!=nil){
                Node=Node->left;
            }
            return Node;
        };
            // Devuelve el nodo con la llave menor.
            // Si el arbol esta vacio devuelve NULL.

        rbnode<T>* treeMaximum(){
            rbnode<T> *Node=getRoot()->p;
            while(Node->right!=nullptr){
                Node=Node->right;
            }
            return Node;
        };
            // Devuelve el nodo con la llave mayor.
            // Si el arbol esta vacio devuelve NULL.

        rbnode<T>* treeSuccessor(const rbnode<T>* x){
            if(x->right!=nil){
                return MinimunRightTree(x);

            }else{
                return x->p;
            }
        };
            // Devuelve el nodo cuya llave es la siguiente mas grande que
            // la del nodo x. Si no existe tal nodo devuelve NULL.

        void treeInsert(rbnode<T>* z){ //aux es y, actual es x.
            rbnode<T>*y=nil;
            rbnode<T>*x=root;

            while(x!=nil){
                y=x;
                if(z->key<x->key){
                    x=x->left;
                }else{
                    x=x->right;
                }
            }
            z->p=y;
            if(y==nil){
                root=z;
                root->color=BLACK;
            }else if(z->key<y->key){
                y->left=z;
            }else{
                y->right=z;
            }
            z->left=nil;
            z->right=nil;
            z->color=RED;

            CorreccionRotando(z);
            ++numElem;
        };
            // Inserta el nodo z en la posicion que le corresponde en el arbol.

        node<T>* treeDelete(node<T>* z){//OMITIR
        };
            // Saca del arbol la llave contenida en el nodo apuntado por z.
            // Devuelve la direccion del nodo eliminado para que se pueda
            // disponer de el.

        rbnode<T> * getRoot() const{
            return this->root;
        };

        // Devuelve la raiz del arbol. (Para efectos de revision de la tarea).

        rbnode<T> * getNil() const{
            return this->nil;
        };
        // Devuelve T.nil. (Para efectos de revision de la tarea).

        private:

        rbnode<T> *root;	// raiz del arbol
        rbnode<T> *nil;	    // nodo nil (hoja) del arbol
        int numElem=0;


        void Rotacion_Izquierda(rbnode<T>* x){
            rbnode<T>* HijoDerecho=x->right;
            rbnode<T>* PadreX=x->p;

            x->right=HijoDerecho->left;

            if(HijoDerecho->left!=nil){
                HijoDerecho->left->p=x;
            }
           HijoDerecho->p=PadreX;

            if(x->p==nil){
                root=HijoDerecho;
            }else if(x==PadreX->left){
                x->p->left=HijoDerecho;
            }else{
                x->p->right=HijoDerecho;

            }
            HijoDerecho->left=x;
            x->p=HijoDerecho;

        }
        void Rotacion_Derecha(rbnode<T>* x){
            rbnode<T>* HijoIzquierdo=x->left;
            rbnode<T>* PadreX=x->p;
            rbnode<T>* aux=nullptr;


            x->left=HijoIzquierdo->right;

            if(HijoIzquierdo->right!=nil){
                HijoIzquierdo->right->p=x;
            }
            HijoIzquierdo->p=x->p;

            if(x->p==nil){
                root=HijoIzquierdo;
            }else if(x==PadreX->right){
                x->p->right=HijoIzquierdo;
            }else{
               x->p->left=HijoIzquierdo;

            }
            HijoIzquierdo->right=x;
            x->p=HijoIzquierdo;
        }
        void CorreccionRotando(rbnode<T>*z){

            if(z->p!=nullptr){

                while(z->p->color==RED){
                    if(z->p==z->p->p->left){

                        rbnode<T>* DerAbuelo=z->p->p->right;
                        if(DerAbuelo->color==RED){

                            z->p->color=BLACK;
                            DerAbuelo->color=BLACK;
                            z->p->p->color=RED;
                            z=z->p->p;

                        }else {
                            if(z==z->p->right){
                                z=z->p;
                                Rotacion_Izquierda(z);
                            }
                            z->p->color=BLACK;
                            z->p->p->color=RED;
                            Rotacion_Derecha(z->p->p);


                        }
                    }else{
                    rbnode<T>* IzqAbuelo=z->p->p->left;
                    if(IzqAbuelo->color==RED){

                        z->p->color=BLACK;
                        IzqAbuelo->color=BLACK;
                        z->p->p->color=RED;
                        z=z->p->p;

                    }else{
                        if(z==z->p->left){
                            z=z->p;
                            Rotacion_Derecha(z);
                        }
                        z->p->color=BLACK;
                        z->p->p->color=RED;
                        Rotacion_Izquierda(z->p->p);
                    }

                }

            }
        }
             root->color=BLACK;
    }

        void Destruir(){
            DestruirR(root);

        }
        void DestruirR(rbnode<T>* nodo){
            while(nodo->left!=nil && nodo->right!=nil){
                DestruirR(nodo->left);
                DestruirR(nodo->right);
            }
            if(nodo->p->right==nodo){
                nodo->p->right=nil;
            }else{
                nodo->p->left=nil;
            }
            nodo->p=nullptr;
            nodo=nullptr;
            delete nodo;
        }

        rbnode<T>* treeSearchRecursive(rbnode<T> *nodo,int key){
            if(nodo==nil || key==nodo->key){
                return nodo;
            }
            if(key<nodo->key){
                return treeSearchRecursive(nodo->left,key);
            }else{
                return treeSearchRecursive(nodo->right,key);
            }

        }
        void Copy(rbnode<T>* nodo,const rbtree<T>& obj){
            rbnode<T> *nuevo=new rbnode<T>();
            rbnode<T> *pnuevo=new rbnode<T>();
            rbnode<T> *padre=new rbnode<T>();
            if(nodo!=obj.getNil()){
                nuevo->key=nodo->key;
                nuevo->color=nodo->color;
                nuevo->right=nil;
                nuevo->left=nil;
                padre=iterativeTreeSearch(nodo->p->key);

                if(nodo->p->left->key==nodo->key){
                    padre->left=nuevo;
                }else{
                    padre->right=nuevo;
                }
                nuevo->p=padre;

                Copy(nodo->left,obj);
                Copy(nodo->right,obj);
            }
        }

        rbnode<T>* MinimunRightTree(const rbnode<T> *Nodo){
            rbnode<T>* Node;
            //debido a que es const, hice una variable non-const
            Node->left=Nodo->left;
            Node->right=Nodo->right;
            Node->p=Nodo->p;

            //si hay un arbol derecho, busca el minimo de este
            Node=Node->right;
            while(Node->left!=nil){
                Node=Node->left;
            }
            return Node;

        }

        void inorderTreeWalkR(rbnode<T>* x, stack<T> & pila){
            if(x!=nil){
                inorderTreeWalk(x->left,pila);
                pila.push(x->key);
                if(x->color==RED){
                    pila.push(0);
                }else{
                    pila.push(1);
                }
                inorderTreeWalk(x->right,pila);
            }
        };


};

#endif	// RED_BLACK_rbtree

