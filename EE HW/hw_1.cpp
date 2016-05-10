#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;
void printArr (int[], int);
void generate_rand_array (int[], int);
void tuning_fork(int);

int main(){
    const int num_of_rock = 7;
    int rock [num_of_rock] = {0};
    int user_choice;
    int health = 100;
    int num_of_bumb = 2 ;
    generate_rand_array( rock, num_of_rock );
    int cur_level_of_rock = 0;
    bool again = true;

    while( again && health > 0 )
    {
        if (cur_level_of_rock < num_of_rock){
            cout << "��" << cur_level_of_rock + 1 << "�����Y �i�_HP�G" << health << " ���u�ƶq�G" << num_of_bumb << "\n" ;
            cout << "(1)���e (2)�K�� (3)�q�p (4)���u (5)��� >> ���:"  ;
            cin >> user_choice;
            cout << "\n";
            switch (user_choice){
                case 1:{
                    tuning_fork(cur_level_of_rock);
                    break;
                }
                case 2:{
                    if( rock[cur_level_of_rock] < 4 ){
                        cout << "<< ���\���H���Y >>" <<"\n";
                        cur_level_of_rock++;
                    }
                    else{
                        cout << "<< ���Y���͵��� >>" <<"\n";
                    }
                    health -= 10;
                    break;
                }
                case 3:{
                    if( rock[cur_level_of_rock] < 7 ){
                        cout << "<< ���\���H���Y >>" <<"\n";
                        cur_level_of_rock++;
                    }
                    else{
                        cout << "<< ���Y���͵��� >>" <<"\n";
                    }
                    health -= 20;
                    break;
                }
                case 4:{
                    if(num_of_bumb > 0){
                        cout << "<< ���\���H���Y >>" <<"\n";
                        cur_level_of_rock++;
                        num_of_bumb --;
                    }
                    else{
                        cout << "<< ���u�w�κ� >>"<< "\n";
                    }
                    break;
                }
                case 5:{
                    again = false;
                    break;
                }
            }
            cout << "\n";
        }
        else
        {
            break ;
        }
    }

    if (health <= 0 ){
        cout << "HP�w�ӺɡK << �M�_���� >>"<< "\n";
    }
    else if( !again ){
        cout << "<< �M�_���� >>"<< "\n";
    }
    else{
        cout << "<< ������o�_�� >>"<< "\n";
    }

    return 0;
}

void tuning_fork(int level_of_rock){
    int check = rand() % 100;
    if(level_of_rock < 5)
    {
        if ( check < 10 )
            cout << " << ���e�o�X�I���n >>" << "\n";
        else
            cout << " << ���e�o�X�M���n >>" << "\n";
    }
    else if(level_of_rock >=5 && level_of_rock <=6)
    {
        if ( check < 50 )
            cout << " << ���e�o�X�I���n >>" << "\n";
        else
            cout << " << ���e�o�X�M���n >>" << "\n";
    }
    else
    {
        if ( check < 75 )
            cout << " << ���e�o�X�I���n >>" << "\n";
        else
            cout << " << ���e�o�X�M���n >>" << "\n";
    }
}


void generate_rand_array ( int rock [], int len)
{
    int count_the_random = 0;
    int index = 0 ;
    srand(time(0));
    while ( count_the_random < len )
    {
        int temp = rand() % len + 1;
        bool isIn = false;
        for ( ; index < len ;  index++ )
        {
            if ( rock[index] == 0 )
            {
                bool isIn = false ;
                for( int i = 0 ; i < index ; i++ )
                    if ( temp == rock[i] )
                    {
                        isIn = true;
                        break;
                    }
                if(!isIn){
                    rock[index] = temp;
                    count_the_random++;
                }
                break;
            }
        }
    }
}
