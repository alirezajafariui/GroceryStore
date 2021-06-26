#include <iostream>
#include <map>

using namespace std ;

class product
{
    private :
        //map<string,product> kind ;
        string name ;
        string kind ;
        int num ;
        product * next ;
    public :
        string getName ()
        {
            return this->name ;
        }
        void setName ( string name )
        {
            this->name = name ;
        }
        
        string getKind ()
        {
            return this->kind ;
        }
        void setKind ( string kind )
        {
            this->kind = kind ;
        }

        int getNum ()
        {
            return this->num ;
        }
        void setNum ( int num )
        {
            this->num = num ;
        }

        product * getNext ()
        {
            return this->next ;
        }
        void setNext ( product * next )
        {
            this->next = next ;
        }
};


class store
{
    private :
        product * head ;
        product * tail ;
        int num ;
    public:
        store()
        {
            this->head = nullptr ;
            this->tail = nullptr ;
            this->num = 0 ;
        }
        ~store()
        {
            product * pro = this->head ;

            while ( pro != nullptr )
            {
                product * tmp = pro ;
                pro = pro->getNext() ;
                delete [] tmp ;
            }

            this->head = nullptr ;
            this->tail = nullptr ;
            this->num = 0 ;
        }


};

int main( void )
{



    return 0 ;
}

