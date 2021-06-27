#include <iostream>
#include <QFile>
#include <Qmap>
#include <QString>

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

            product ()
            {
                this->available = 0 ;
            }
            product ( string name , int available )
            {
                this->name = name ;
                this->available += available ;
            }
            ~product ()
            {
                this->available = 0 ;
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
            if ( findproduct( name ) )
            {
                product * pro = this->head ;

                while ( pro != nullptr )
                {
                    if ( pro->name == name )
                    {
                        pro->available += available ;
                        break ;
                    }
                    pro = pro->next ;
                }
                return ;
            }

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

                if ( pro->name <= this->head->name )
                {
                    pro->prev = this->head->prev ;
                    pro->next = this->head ;
                    this->head = pro ;
                    return ;
                }
                if ( pro->name >= this->tail->name )
                {
                    pro->prev = this->tail ;
                    pro->next = this->tail->next ;
                    this->tail = pro ;
                    return ;
                }
                if ( pro->name <= tmp->next->name )
                {
                    pro->prev = tmp ;
                    pro->next = tmp->next ;
                    tmp->next->prev = pro ;
                    tmp->next = pro ;
                    return ;
                }
            }
        }

        bool findproduct ( string name )
        {
            product * pro = this->head ;

            while ( pro != nullptr )
            {
                if ( pro->name == name )
                    return true ;
                pro = pro->next ;
            }
            return false ;
        }

        void print ()
        {
            product * pro = this->head ;

            while ( pro != nullptr )
            {
                cout << pro->name << " " << pro->available << endl ;
                pro = pro->next ;
            }
        }
};


class Store
{
    private :
        productkind * head ;
        productkind * tail ;
        int Knum ; //Number of productkinds .
    public :
        Store()
        {
            this->head = nullptr ;
            this->tail = nullptr ;
            this->Knum = 0 ;
        }
        ~Store()
        {
            productkind * kind = this->head ;

            while ( kind != nullptr )
            {
                productkind * tmp = kind ;
                kind = kind->next ;
                delete [] tmp ;
            }

            this->head = nullptr ;
            this->tail = nullptr ;
            this->Knum = 0 ;
        }

        void addproductkind ( string kname , string name , int available )
        {
            if ( findproductkind( kname ) )
            {
                productkind * kind = this->head ;

                while ( kind != nullptr )
                {
                    if ( kind->kname == kname )
                    {
                        kind->addProduct( name , available ) ;
                        break ;
                    }
                    kind = kind->next ;
                }
                return ;
            }

            productkind * kind = new productkind ( kname ) ;
            kind->addProduct( name , available ) ;
            kind = this->head ;
            this->Knum ++ ;

            if ( kind == nullptr )
            {
                kind->prev = this->tail ;
                kind->next = this->head ;
                this->head = kind ;
                this->tail = kind ;
            }
            else
            {
                productkind * tmp = this->head ;

                if ( kind->kname <= this->head->kname )
                {
                    kind->prev = this->head->prev ;
                    kind->next = this->head ;
                    this->head = kind ;
                    return ;
                }
                if ( kind->kname >= this->tail->kname )
                {
                    kind->prev = this->tail ;
                    kind->next = this->tail->next ;
                    this->tail = kind ;
                    return ;
                }
                if ( kind->kname <= tmp->next->kname )
                {
                    kind->prev = tmp ;
                    kind->next = tmp->next ;
                    tmp->next->prev = kind ;
                    tmp->next = kind ;
                    return ;
                }
            }
        }

        bool findproductkind ( string kname )
        {
            productkind * kind = this->head ;

            while ( kind != nullptr )
            {
                if ( kind->kname == kname )
                    return true ;
                kind = kind->next ;
            }
            return false ;
        }

        void print ()
        {
            productkind *  kind = this->head ;

            while ( kind != nullptr )
            {
                cout << kind->kname << endl << "Products of this kind is(are) : " << kind->pknum << endl ;
                kind->print() ;
                kind = kind->next ;
            }
        }
};

int main( void )
{
    QFile outfile( "in.txt" );
    ofstream outputFile( "output.dat" , ios::out ) ;

    cout << "Welcome to my store." << endl ;

    Store store ;
    string kind , name ;
    int num ;

    //commands
    string command ;
    string add = "add" ;

    while ( true )
    {
        cin >> command ;

        switch ( command )
        {
            case "add" :
            {
                multimap<string,product> pro ;
                cout << "What kind of product do you want to add? " ;
                cin >> kind ;
                cout << "What is the product name? " ;
                cin >> name ;
                cout << "How many of this product do you want to add? " ;
                cin >> num ;

                pro[kind] = Store.add_new_pro( name , num ) ;

                cout << "product saved." << endl ;
            }
            break;
        }

    }



    return 0 ;
}

