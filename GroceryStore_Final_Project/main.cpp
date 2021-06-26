#include <iostream>
using namespace std ;

class product
{
    private :
        string name ;
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



int main( void )
{



    return 0 ;
}
