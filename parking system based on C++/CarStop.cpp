#include "LinkQueue.h"
#include "LinkStack.h"
#include <string>
struct Car
{
    Car(){}
    Car(const std::string& name,int arriveTime):name(name),arriveTime(arriveTime){}

    std::string name; //车牌号
    int arriveTime;   //到达时间
    int leaveTime;    //离开时间
};
class CarStop
{
public:
    CarStop(const int &size):size(size){}

    //车来
    void ComeCar();
    //车走
    void LeaveCar();

    void show();
private:
    LinkStack stop; //停车场
    LinkQueue pavement; //便道
    const int size;//停车场停车数量
};


void CarStop::ComeCar()
{
    Car* c = new Car;
    std::cout<<"请输入车牌:";
    std::cin>>c->name;
    std::cout<<"请输入到达时间:";
    std::cin>>c->arriveTime;

    if(stop.Size() == size) //停车场满了
    {
        pavement.Push(c);
        std::cout<<"停车场已满,车牌为|"<<c->name<<"|的车停在了便道上\n";
    }
    else
    {
        stop.Push(c);
        std::cout<<"车辆|"<<c->name<<"|停在了停车场内"<<std::endl;
    }

}

void CarStop::LeaveCar()
{
    std::cout<<"请输入要离开的车牌:";
    std::string name;
    std::cin>>name;
    int LeaveTime = 0;
    LinkStack tmp;
    while(!stop.IsEmpty())
    {
        Car* c = (Car*)*stop.GetTop();
        if(c->name == name)
        {
            std::cout<<"请输入车辆离开时间:";
            std::cin>>c->leaveTime;
            LeaveTime = c->leaveTime;
            int money = (c->leaveTime - c->arriveTime) * 5;
            std::cout<<"\n"<<"车辆|"<<c->name<<"|"<<"在"<<c->leaveTime<<"|离开停车场，缴费:|"<<money<<"|"<<std::endl;
            delete c;
            stop.Pop();
            break;
        }
        stop.Pop();
        tmp.Push(c);
    }
    while(!tmp.IsEmpty())
    {
        stop.Push(*tmp.GetTop());
        tmp.Pop();
    }

    //停车场不满且便道上有车
    if(stop.Size() < size && !pavement.IsEmpty())
    {
        Car* c = (Car*)*pavement.GetFront();
        c->arriveTime = LeaveTime;
        std::cout<<"便道上的车|"<<c->name<<"|在|"<<c->arriveTime<<"|进入停车场!\n";
        pavement.Pop();
        stop.Push(c);
    }

}

void CarStop::show()
{
    LinkStack tmp;
    std::cout<<std::endl;
    std::cout<<"停车场:\n";
    while(!stop.IsEmpty())
    {
        tmp.Push(*stop.GetTop());
        stop.Pop();
    }
    while(!tmp.IsEmpty())
    {
        Car* c = (Car*)*tmp.GetTop();
        std::cout<<"|"<<c->name<<"|,到达时间:|"<<c->arriveTime<<"|"<<std::endl;
        stop.Push(c);
        tmp.Pop();
    }
    std::cout<<"便道:\n";
    LinkQueue q;
    while(!pavement.IsEmpty())
    {
        Car* c = (Car*)*pavement.GetFront();
        std::cout<<"|"<<c->name<<"|"<<std::endl;
        pavement.Pop();
        q.Push(c);
    }
    while(!q.IsEmpty())
    {
        pavement.Push(*q.GetFront());
        q.Pop();
    }
}

int main()
{
    CarStop Car(3);
    while(1)
    {
        Car.show();
        std::cout<<std::endl;
        std::cout<<"1、进入停车场\n";
        std::cout<<"2、离开停车场\n";
        std::cout<<"3、退出\n";
        std::cout<<std::endl;
        int choice = 0;
        std::cin>>choice;
        switch (choice)
        {
        case 1:
            Car.ComeCar();
            break;
        case 2:
            Car.LeaveCar();
            break;
        default: exit(-1);
            break;
        }

    }


    return 0;
}

