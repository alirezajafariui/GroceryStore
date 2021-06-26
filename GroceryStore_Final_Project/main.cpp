#include <iostream>
#include <map>

using namespace std ;

class productkind
{
    public :

        class product
        {
        public:
            string name ;
            int available ; // available count of this product .
            product * next ;
            product * prev ;

            product ( string name , int available )
            {
                this->name = name ;
                this->available = available ;
            }
        };

        string kname ;
        int pknum ; // Number of products of this kind .
        productkind * next ;
        productkind * prev ;
        product * head ;
        product * tail ;

        productkind ()
        {
            this->head = nullptr ;
            this->tail = nullptr ;
            this->pknum = 0 ;
        }
        productkind ( string kname )
        {
            this->kname = kname ;
        }
        ~productkind()
        {
            product * pro = this->head ;
            
            while ( pro != nullptr )
            {
                product * tmp = pro ;
                pro = pro->next ;
                delete [] tmp ;
            }
            
            this->head = nullptr ;
            this->tail = nullptr ;
            this->pknum = 0 ;
        }
        
        void addProduct ( string name , int available )
        {
            product * pro = new product ( name , available ) ;
            pro = this->head ;
            this->pknum ++ ;

            if ( pro == nullptr )
            {
                pro->next = this->head ;
                pro->prev = this->tail ;
                this->head = pro ;
                this->tail = pro ;
            }
            else
            {
                product * tmp = this->head ;

                if ( pro <= this->head )
                {
                    pro->prev = this->head->prev ;
                    pro->next = this->head ;
                    this->head = pro ;
                    return ;
                }
                if ( pro >= this->tail )
                {
                    pro->prev = this->tail ;
                    pro->next = this->tail->next ;
                    this->tail = pro ;
                    return ;
                }
                if ( pro <= tmp->next )
                {
                    pro->prev = tmp ;
                    pro->next = tmp->next ;
                    tmp->next->prev = pro ;
                    tmp->next = pro ;
                    return ;
                }
            }
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

