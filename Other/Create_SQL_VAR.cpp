#include <iostream>
#include <fstream>

using namespace std;

void Create_type_of_room(void);

int main (){
    Create_type_of_room();
}

void Create_type_of_room(){
    char filename[]="helloFile.txt";
    fstream fp;
    fp.open(filename, ios::out);
    int bound ;
    cout << "Bound of max room";
    cin >> bound;
    if(fp){
        for(int i = 1 ;i < 5; i++){
            for(int j=0;j<3;j++){
                int cnt = 0;
                int lv =i+j;
                for(int z=0 ;z< bound-2*lv;z++,cnt++){
                    if(cnt<10)
                        fp << "INSERT INTO room (room_ID,rmLevel,type_of_room) VALUES ('"<< i<<lv<<0<<cnt<<"',"<<(i+j)<<","<<i<<");"<<'\n';
                    else
                        fp << "INSERT INTO room (room_ID,rmLevel,type_of_room) VALUES ('"<< i<<lv<<cnt<<"',"<<(i+j)<<","<<i<<");"<<'\n';

                }
            }
        }
    }
    fp.close();
}
