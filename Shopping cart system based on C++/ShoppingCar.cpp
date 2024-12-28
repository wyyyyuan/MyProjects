#include "LinkStack.h"
#include "LinkQueue.h"

struct Item
{
    Item() {}
    Item(const int id, const std::string name, const double price) : id(id), name(name), price(price) {}
    int id;
    std::string name;
    double price;
};

class ShopCart
{
public:
    ShopCart() : size(0) {}

    ShopCart(const int &size) : size(size) {};

    void BuyShop();     // 购买商品
    void pop();         // 撤销购买的商品
    void show();        // 遍历显示购物车商品
    void enqueue();     // 将商品加入结算队列
    void dequeue();     // 按顺序结算商品
    void showHistory(); // 查看历史支付记录
private:
    LinkStack cart;
    LinkQueue Pay;
    LinkQueue History;
    const int size;
};

void ShopCart::BuyShop()
{
    Item *s = new Item;
    std::cout << "请输入商品编号:\n";
    std::cin >> s->id;
    std::cout << "请输入商品名称:\n";
    std::cin >> s->name;
    std::cout << "请输入商品价格:\n";
    std::cin >> s->price;
    if (cart.Size() == size)
    {
        std::cout << "购物车已满!\n";
    }
    else
    {
        cart.Push(s);
        std::cout << "编号为" << s->id << "的商品已成功添加进购物车!\n";
    }
}

void ShopCart::pop()
{
    cart.Pop();
    std::cout << "上一次添加已撤销!\n";
}

void ShopCart::show()
{
    if (cart.Size() == 0)
    {
        std::cout << "购物车为空!\n";
    }
    else
        std::cout << "购物车商品:\n";
    LinkStack temp;
    while (!cart.IsEmpty())
    {
        temp.Push(*cart.GetTop());
        cart.Pop();
    }

    while (!temp.IsEmpty())
    {
        Item *s = (Item *)*temp.GetTop();
        std::cout << "商品编号:" << s->id << " " << "商品名称:" << s->name << " " << "商品价格:" << s->price << std::endl;
        cart.Push(s);
        temp.Pop();
    }
}

void ShopCart::enqueue()
{
    while (!cart.IsEmpty())
    {
        Pay.Push(*cart.GetTop());
        cart.Pop();
    }
}

void ShopCart::dequeue()
{
    int money = 0;
    while (!Pay.IsEmpty())
    {
        Item *s = (Item *)*Pay.GetFront();
        money += s->price;
        History.Push(s);
        Pay.Pop();
    }
    std::cout << "本次消费:" << money << "元" << std::endl;
}

void ShopCart::showHistory()
{
    LinkQueue temp;
    if (History.IsEmpty())
        std::cout << "暂未有历史记录!\n";
    else
        std::cout << "历史购物车:\n";
    while (!History.IsEmpty())
    {
        temp.Push(*History.GetFront());
        History.Pop();
    }
    int money = 0;
    while (!temp.IsEmpty())
    {
        Item *s = (Item *)*temp.GetFront();
        money += s->price;
        std::cout << "商品编号:" << s->id << " " << "商品名称:" << s->name << " " << "商品价格:" << s->price << std::endl;
        History.Push(s);
        temp.Pop();
    }
    std::cout << "总消费:" << money << "元" << std::endl;
}

int main()
{
    ShopCart Cart(5);
    while (1)
    {
        std::cout << std::endl;
        std::cout << "====在线购物车管理系统====\n";
        std::cout << "1、添加商品\n";
        std::cout << "2、撤销上一次添加\n";
        std::cout << "3、查看购物车内容\n";
        std::cout << "4、结算商品\n";
        std::cout << "5、查看支付历史记录\n";
        std::cout << "0、退出系统\n";
        std::cout << "==========================";
        std::cout << std::endl;
        int choice = -1;
        std::cout << "请输入功能:\n";
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Cart.BuyShop();
                break;
            }
            case 2:
            {
                Cart.pop();
                break;
            }
            case 3:
            {
                Cart.show();
                break;
            }
            case 4:
            {
                Cart.enqueue();
                Cart.dequeue();
                break;
            }
            case 5:
            {
                Cart.showHistory();
                std::cout << std::endl;
                break;
            }
            case 0:
            {
                std::cout << "系统已退出!\n";
                exit(-1);
                break;
            }
        }
    }

    return 0;
}
