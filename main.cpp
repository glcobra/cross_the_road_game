#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>

using namespace std;
class cPlayer
{
public:
    int x, y;
    cPlayer(int width){x=width/2; y=0;}
};
class cLane
{
private:
    deque<bool>cars;
    bool right;
public:
    cLane(int width)
    {
      for(int i=0; i<width; i++)
        cars.push_front(true);
        right=rand()%2;
    }
    void move()
    {
        if(right)
        {
            if(rand()%10==1)
            cars.push_front(true);
        else
            cars.push_front(false);
        cars.pop_back();
        }
        else
        {
             if(rand()%10==1)
            cars.push_back(true);
        else
            cars.push_back(false);
        cars.pop_front();

        }

    }
    bool checkPos(int pos){return cars[pos];}
    void changeDirection(){right=!right;}
};
class cGame
{
private:
    bool quit;
    int numberOfLanes;
    int width;
    int score;
    cPlayer*player;
    vector<cLane*>map;
public:
    cGame(int w=20, int h=10)
    {
        numberOfLanes=h;
        width=w;
        quit=false;
        for(int i=0; i<numberOfLanes; i++)
            map.push_back(new cLane(width));
        player=new cPlayer(width);
    }
    void draw()
    {
       system("cls");
       for(int i=0; i<numberOfLanes; i++)
       {
           for(int j=0; j<width; j++)
           {
               if( i==0&&(j==0||j==width-1))
                cout<<"S";
               if( i==numberOfLanes-1&&(j==0||j==width-1))
                cout<<"F";
               if(map[i]->checkPos(j)&&i!=0&&i!=numberOfLanes-1)
                cout<<"#";
               else if(player->x==j&&player->y==i)
                cout<<"V";
                else
                cout<<" ";
                }
           cout<<endl;
       }
       cout<<"Score:"<<score<<endl;
    }
    void input()
    {
       if(_kbhit())
       {
           char current=getch();
           if(current=='a')
            player->x--;
           if(current=='d')
            player->x++;
           if(current=='s')
            player->y++;
           if(current=='w')
            player->y--;
            if(current=='q')
                quit=true;
       }
    }
    void logic()
    {
       for(int i=1; i<numberOfLanes-1; i++)
       {
           if(rand()%10==1)
            map[i]->move();
           if(map[i]->checkPos(player->x)&&player->y==i)
            quit=true;
       }
       if(player->y==numberOfLanes-1)
       {
           score++;
           player->y=0;
           cout<<"\x07";
           map[rand()%numberOfLanes]->changeDirection();
       }
    }
    void run()
    {
        while(!quit)
        {
            input();
            draw();
            logic();
        }
    }
};

int main()
{
    srand(time(NULL));
    cGame game(30, 5);
    game.run();
    cout<<"Game over!"<<endl;
    getchar();
    return 0;
}
