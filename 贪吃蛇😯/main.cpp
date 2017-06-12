//
//  main.cpp
//  cin
//
//  Created by 董依萌 on 2017/5/30.
//  Copyright © 2017年 董依萌. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
//#include <ctime>
//#include <thread>   //控制线程和进程
#include <unistd.h>
using namespace std;
#define W 100
#define H 35
class snake{
private:
    typedef struct snake_{
        int x,y;
        struct snake_ *next;
    }snk;
    int len,fx,fy,hx,hy;       //蛇的长度
    char map[H][W]={0};
    snk *s;
public:
    
    
    //初始化蛇的位置 蛇的位置存放在单链表里  初始化边框
    snake(){
        len = 6;
        int x,y,i=0;
        for(x=0;x<H;x++){
            for(y=0;y<W;y++){
                if(x==0||x==H-1)
                    map[x][y]='-';
                else if(y==0||y==W-1){
                    map[x][y]='|';
                }
            }
        }
        
        snk *p = new snk;
        s = p;
        map[14][47]='@';
        p->x = 14;
        p->y = 47;
        for(x=14,y=48;i<5;y++,i++){
            map[14][y]='*';
            snk *q = new snk;
            q->x=x;
            q->y=y;
            p->next = q;
            p = q;
            p->next = NULL;
        }
    }
    //显示边框 食物和蛇
    void display(){
        int x,y;
        for(x=0;x<H;x++){
            for(y=0;y<W;y++){
                if(map[x][y]==0)
                    cout<<' ';
                cout<<map[x][y];
            }
            cout<<endl;
        }
    }
    //食物随机产生 产生位置在除了边框和蛇身之外的位置
    void food(){
        int k=0;
        srand(time(NULL));
        while(k==0){
            fx = rand()%(H-2)+1;
            fy = rand()%(W-2)+1;
            if(map[fx][fy]!='*'&&map[fx][fy]!='@'){
                map[fx][fy]='*';
                k++;
            }
        }
        
    }
    //判断是否吃到了食物 并且蛇身长度加一   食物变成蛇头
    int eat(){
        snk *p;
        p = s;
        if(p->x==fx&&p->y==fy){
            snk *q = new snk;
            q->x=hx;
            q->y=hy;
            q->next=p->next;
            p->next = q;
            map[q->x][q->y] = '*';
            map[p->x][p->y] = '@';
            len++;
            return 1;
        }
        return 0;
    }
    //判断蛇头是否碰到了蛇身 或者边框。
    void dead(snk *s,int x,int y){
        snk *p;
        p = s->next;
        if(x==0||y==0||x==H-1||y==W-1){
            cout<<"Game Over"<<endl;
            exit(0);
        }
        while(p){
            if(p->x==x&&p->y==y){
                cout<<"Game Over"<<endl;
                exit(0);
            }
            p = p->next;
        }
        
    }
    
    void move(char ch){
        int x=0,y=0,k,l;      // 使用链表记录蛇的位置 蛇头按方向移动 蛇身依次移动到
        snk *p;             //前一个位置 并将原来位置 赋值 空格
        p = s;
        x = p->x;
        y = p->y;
        if(ch=='w'){        //判断蛇头的移动方向 wasd
            hx = p->x;      //hx hy 记录蛇头的位置 方便
            hy = p->y;
            p->x=x-1;
            dead(s,p->x,p->y);
            if(eat()){
                food();
                return ;
            }
        }
        else if(ch=='a'){
            hx = p->x;
            hy = p->y;
            p->y=y-1;
            dead(s,p->x,p->y);
            if(eat()){
                food();
                return ;
                
            }
        }
        else if(ch=='s'){
            hx = p->x;
            hy = p->y;
            p->x=x+1;
            dead(s,p->x,p->y);
            if(eat()){
                food();
                return ;
            }

        }
        else if(ch=='d'){
            hx = p->x;
            hy = p->y;
            p->y=y+1;
            dead(s,p->x,p->y);
            if(eat()){
                food();
                return ;
            }
        }
        else{
            cout<<"Game Over"<<endl;
            exit(0);
        }
        map[p->x][p->y] = map[x][y];
        for(int i=1;i<len;i++){
            p = p->next;
            k = y;
            l = x;
            map[x][y]=map[p->x][p->y];
            map[p->x][p->y]=' ';
            x = p->x;
            y = p->y;
            p->y = k;
            p->x = l;
        }
    }
    
};


int main(){
    char ch;
    snake sna;
    sna.food();
    while(true){
        sna.display();
        cin>>ch;
        sna.move(ch);
        //sleep(1);
        system("clear");
    }
    
}
