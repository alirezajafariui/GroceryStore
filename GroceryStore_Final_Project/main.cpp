#include <iostream>
#include <string>
#include <QString>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
using namespace std ;

class product
{
    public:
        QString name ;
        int available ; // available count of this product .
        product * next ;
        product * prev ;

        product ( QString name , int available )
        {
            this->name = name ;
            this->available = available ;
        }
};


class productkind
{
    public :
        QString kname ;
        int pknum ; // Number of products of this kind .
        productkind * next ;
        productkind * prev ;
        product * head ;
        product * tail ;

        productkind ( QString kname )
        {
            this->kname = kname ;
            this->head = nullptr ;
            this->tail = nullptr ;
            this->pknum = 0 ;
        }
        ~productkind ()
        {
            product * pro = this->head ;

            while ( pro != nullptr )
            {
                product * tmp = pro ;
                pro = pro->next ;
                delete tmp ;
            }

            this->head = nullptr ;
            this->tail = nullptr ;
            this->pknum = 0 ;
        }

        void addProduct ( QString name , int available )
        {
            this->pknum ++ ;

            if ( this->head == nullptr )
            {
                product * pro = new product ( name , available ) ;
                pro->next = this->head ;
                pro->prev = this->tail ;
                this->head = pro ;
                this->tail = pro ;
            }
            else
            {
                if ( findproduct( name ) )
                {
                    this->pknum -- ;
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

                product * tmp = this->head ;

                if ( pro->name <= this->head->name )
                {
                    pro->prev = this->head->prev ;
                    pro->next = this->head ;
                    this->head->prev = pro ;
                    this->head = pro ;
                    return ;
                }
                if ( pro->name >= this->tail->name )
                {
                    pro->prev = this->tail ;
                    pro->next = this->tail->next ;
                    this->tail->next = pro ;
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

        void editproduct ( QString name , QString newname )
        {
            product * pro = this->head ;

            while ( pro != nullptr )
            {
                if ( name == pro->name )
                    break ;
                else
                    pro = pro->next ;
            }

            pro->name = newname ;
        }

        void popproduct ( QString name )
        {
            product * pro = this->head ;
            this->pknum -- ;

            if ( name == this->head->name )
            {
                pro->next->prev = pro->prev ;
                this->head = pro->next ;
                delete pro ;
                return ;
            }
            if ( name == this->tail->name )
            {
                pro = this->tail ;
                pro->prev->next = this->tail->next ;
                this->tail = pro->prev ;
                delete pro ;
                return ;
            }

            while ( pro != nullptr )
            {
                if ( name == pro->name )
                {
                    pro->prev->next = pro->next ;
                    pro->next->prev = pro->prev ;
                    delete pro ;
                    return ;
                }
                else
                    pro = pro->next ;
            }
        }

        bool findproduct ( QString name )
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

        QStringList search ( QString word )
        {
            product * pro = this->head ;
            QStringList qstl ;

            while ( pro != nullptr )
            {
                if ( checkword( pro->name , word ) )
                    qstl += pro->name ;
                pro = pro->next ;
            }

            return qstl ;
        }

        bool checkword ( QString name , QString word )
        {
            bool flag = true ;
            if ( word.size() > name.size() )
                return false ;
            for ( int i = 0 ; i < word.size() ; ++ i )
            {
                if ( name[i] != word[i] )
                    flag = false ;
            }
            return flag ;
        }

        void print ()
        {
            product * pro = this->head ;

            while ( pro != nullptr )
            {
                cout << pro->name.toStdString() << " " << pro->available << "\n" ;
                pro = pro->next ;
            }
        }
};


class Store
{
    public :
        productkind * head ;
        productkind * tail ;
        int Knum ; //Number of productkinds .


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
                delete tmp ;
            }

            this->head = nullptr ;
            this->tail = nullptr ;
            this->Knum = 0 ;
        }

        void addproductkind ( QString kname , QString name , int available )
        {
            this->Knum ++ ;

            if ( this->head == nullptr )
            {
                productkind * kind = new productkind ( kname ) ;
                kind->addProduct( name , available ) ;
                kind->prev = this->tail ;
                kind->next = this->head ;
                this->head = kind ;
                this->tail = kind ;
            }
            else
            {
                if ( findproductkind( kname ) )
                {
                    this->Knum -- ;
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

                productkind * tmp = this->head ;

                if ( kind->kname <= this->head->kname )
                {
                    kind->prev = this->head->prev ;
                    kind->next = this->head ;
                    this->head->prev = kind ;
                    this->head = kind ;
                    return ;
                }
                if ( kind->kname >= this->tail->kname )
                {
                    kind->prev = this->tail ;
                    kind->next = this->tail->next ;
                    this->tail->next = kind ;
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

        void editproductkind ( QString kname , QString newkname , QString name = "0" , QString newname = "0" )
        {
            productkind * kind = this->head ;

            while ( kind != nullptr )
            {
                if ( kname == kind->kname )
                    break ;
                else
                    kind = kind->next ;
            }

            if ( name == "0" )
            {
                kind->kname = newkname ;
            }
            if ( name != "0" )
            {
                kind->editproduct( name , newname ) ;
            }
        }

        void popproductkind ( QString kname , QString name = "0" )
        {
            productkind * kind = this->head ;

            if ( name == "0" )
            {
                this->Knum -- ;

                if ( kname == this->head->kname )
                {
                    kind->next->prev = kind->prev ;
                    this->head = kind->next ;
                    delete kind ;
                    return ;
                }
                if ( kname == this->tail->kname )
                {
                    kind = this->tail ;
                    kind->prev->next = this->tail->next ;
                    this->tail = kind->prev ;
                    delete kind ;
                    return ;
                }

                while ( kind != nullptr )
                {
                    if ( kname == kind->kname )
                    {
                        kind->prev->next = kind->next ;
                        kind->next->prev = kind->prev ;
                        delete kind ;
                        return ;
                    }
                    else
                        kind = kind->next ;
                }

            }
            else
            {
                while ( kind != nullptr )
                {
                    if ( kname == kind->kname )
                        break ;
                    else
                        kind = kind->next ;
                }

                kind->popproduct( name ) ;
                
            }
        }

        bool findproductkind ( QString kname )
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

        QStringList search ( QString kname , QString word )
        {
            productkind * kind = this->head ;
            QStringList qstl ;

            if ( kname == "0" )
            {
                while ( kind != nullptr )
                {
                    qstl += kind->search( word ) ;
                    kind = kind->next ;
                }
            }
            else
            {
                while ( kind != nullptr )
                {
                    if ( kname == kind->kname )
                        break ;
                    else
                        kind = kind->next ;
                }

                qstl += kind->search( word ) ;
            }

            return qstl ;
        }

        void clear ()
        {
            productkind * kind = this->head ;

            while ( kind != nullptr )
                this->popproductkind( kind->kname ) ;
        }

        void print ( QString kname = "0" )
        {
            productkind * kind = this->head ;

            if ( kname == "0" )
            {
                cout << endl << this->Knum << endl ;
                while ( kind != nullptr )
                {
                    cout << kind->kname.toStdString() << " " << kind->pknum << endl ;
                    kind->print() ;
                    cout << endl ;
                    kind = kind->next ;
                }
            }
            else
            {
                while ( kind != nullptr )
                {
                    if ( kind->kname == kname )
                        break ;
                    else
                        kind = kind->next ;
                }
                cout << kind->kname.toStdString() << " " << kind->pknum << endl ;
                kind->print() ;
                cout << endl ;
            }
        }
};



int main( void )
{
    Store store ;
    QString qst , command , kind , name , ans , newkname , newname , let ;
    QStringList qstl ;
    int num ;

    QMap<QString,QString> ID ;
    QString username , password ;


    QFile file( "out.txt" );
    file.open( QFile::Text | QFile::ReadOnly ) ;
    QTextStream in ( &file ) ;

    qst = in.readLine() ;
    for ( int i = 0 ; i < qst[0].digitValue() ; ++ i )
    {
        qstl = in.readLine().split( ' ' ) ;
        ID[qstl[0]] = qstl[1] ;
    }

    qst = in.readLine() ;
    for ( int i = 0 ; i < qst[0].digitValue() ; ++ i )
    {
        //qDebug() << 1 ;
        qstl = in.readLine().split( ' ' ) ;
        kind = qstl[0] ;
        int a = qstl[1][0].digitValue() ;
        for ( int j = 0 ; j < a ; ++ j )
        {
            //qDebug() << 2 << qstl[1][0].digitValue() ;
            qstl = in.readLine().split( ' ' ) ;
            name = qstl[0] ;
            num = qstl[1][0].digitValue() ;
            store.addproductkind( kind , name , num ) ;
        }
    }
    file.close() ;


    cout << "Welcome to your store." << endl ;
    while ( true )
    {
        cout << "sign in. please enter your user name : " ;

        QTextStream Qtin( stdin );
        Qtin >> username ;
        if ( ID.find( username ) != ID.end() )
        {
            cout << "hello " << username.toStdString() << ". please enter your password : " ;
            Qtin >> password ;
            if( ID[username] == password )
            {
                cout << "Welecome " << username.toStdString() << endl ;
                break ;
            }
            else
            {
                cout << "The password is not true. please try another time." << endl ;
                continue ;
            }
        }
        else
        {
            cout << username.toStdString() << " not founded. please sign up. enter your username : " ;
            Qtin >> username ;
            cout << "enter your password : " ;
            Qtin >> password ;

            ID[username] = password ;

            cout << "signed up successfuly." << endl ;
        }
    }


    while ( true )
    {
        QTextStream Qtin( stdin );

        Qtin >> command ;

        if ( command == "add" )
        {
            cout << "What kind of product do you want to add? " ;
            Qtin >> kind ;
            cout << "What is the product name? " ;
            Qtin >> name ;
            cout << "How many of this product do you want to add? " ;
            Qtin >> num ;

            store.addproductkind( kind , name , num ) ;

            cout << "product saved." << endl ;
        }

        if ( command == "edit" )
        {
            cout << "Do you want to edit the name of a product kind? Y/N : " ;
            Qtin >> ans ;
            if ( ans == "Y" )
            {
                cout << "What kind of product do you want to edit? : " ;
                Qtin >> kind ;
                cout << "What is the new name? : " ;
                Qtin >> newkname ;

                store.editproductkind( kind , newkname ) ;

                cout << "product kind name changed." << endl << endl ;
            }
            if ( ans == "N" )
            {
                cout << "Do you want to edit the name of a product? Y/N : " ;
                Qtin >> ans ;
                if ( ans == "Y" )
                {
                    cout << "What kind of product do you want to edit? : " ;
                    Qtin >> kind ;
                    cout << "What product do you want to edit? : " ;
                    Qtin >> name ;
                    cout << "What is the new name ? : " ;
                    Qtin >> newname ;

                    store.editproductkind( kind , "0" , name , newname ) ;

                    cout << "product name changed." << endl << endl ;
                }
                if ( ans == "N" )
                {
                    cout << "Nothing changed." << endl << endl ;
                }
            }
        }

        if ( command == "popkind" )
        {
            cout << "What kind of product do you want to delete? " ;
            Qtin >> kind ;

            store.popproductkind( kind ) ;

            cout << "This kind of product deleted." << endl ;
        }

        if ( command == "popproduct" )
        {
            cout << "What kind of product do you want to delete? " ;
            Qtin >> kind ;
            cout << "What is the product name? " ;
            Qtin >> name ;

            store.popproductkind( kind , name ) ;

            cout << "This product deleted." << endl ;
        }

        if ( command == "search" )
        {
            cout << "Do you want to search among all the products? Y/N : " ;
            Qtin >> ans ;
            if ( ans == "Y" )
            {
                cout << "Please enter the first letters of the word. : " ;
                Qtin >> let ;

                QStringList qstl = store.search( "0" , let ) ;

                for ( auto y : qstl )
                    qDebug() << y ;
            }
            else
            {
                cout << "What kind of product do you want to search among? : " ;
                Qtin >> kind ;
                cout << "Please enter the first letters of the word. : " ;
                Qtin >> let ;

                QStringList qstl = store.search( kind , let ) ;

                for ( auto y : qstl )
                    qDebug() << y ;
            }

        }

        if ( command == "print" )
        {
            store.print() ;
        }

        if ( command == "printgroup" )
        {
            cout << "What kind of product list do you want print? : " ;
            Qtin >> kind ;

            store.print( kind ) ;
        }

        if ( command == "clear" )
        {
            cout << "Do you want to clear users? Y/N : " ;
            Qtin >> ans ;

            if ( ans == "Y" )
            {
                ID.clear() ;
                cout << "List of users is empty." << endl ;
            }
            else
            {
                cout << "Do you want to clear the store list? Y/N : " ;
                Qtin >> ans ;

                if ( ans == "Y" )
                {
                    store.clear() ;
                    cout << "Store list is empty." << endl ;
                }
            }
        }

        if ( command == "fin" )
        {
            break ;
        }
    }



    file.open( QFile::Text | QFile::WriteOnly ) ;
    QTextStream out ( &file ) ;

    // ?? ?? ??????? ???? ???? ?? ??????
    out << ID.size() << "\n" ;
    for ( auto it = ID.begin() ; it != ID.end() ; ++ it )
        out << it.key() << " " << it.value() << "\n" ;

    // ???? ????? ??????? ???????
    out << store.Knum << "\n" ;
    for ( int i = 0 ; i < store.Knum ; ++ i )
    {
        if ( store.head == nullptr )
            break ;

        out << store.head->kname << " " << store.head->pknum << "\n" ;

        for ( int j = 0 ; j < store.head->pknum ; ++ j )
        {
            out << store.head->head->name << " " << store.head->head->available << "\n" ;
            store.head->head = store.head->head->next ;
        }

        store.head = store.head->next ;
    }
    file.close() ;



    return 0 ;
}

