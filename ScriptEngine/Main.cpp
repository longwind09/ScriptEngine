#include "stdafx.h"
#include <DbgEng.h>
#include <iostream>

#include "DEngine.h"


using namespace std;





int main( int ac, char *av[] )
{

    string path ( av[0] );
    //rfind find reverse �������
    //ֻ����Ŀ¼���֣�������.exe������
    path = path.substr ( 0, path.rfind ( "\\" ) + 1 );
    cout << path << endl;
    boost::shared_ptr<DEngine> engine_ptr ( new DEngine() );
    engine_ptr->init (path);
    engine_ptr->start_service();


    system("pause");
    return 0;
}