#捣蛋猫跑酷
##项目概述
本项目为南京大学软件工程CPL期末项目题F.
本项目是基于SDL2和C语言编写的跑酷游戏,游戏中玩家将扮演捣蛋猫收集金币,避开障碍物尽可能跑得更远.

---

##环境要求
平台:
Windows11
C语言环境:
MinGw32 8.1.0
MSVC 19.36.32535
##编译选项
1. gcc编译请使用指令
```
gcc common.c main.c menu.c guide.c game.c -o RUN -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
```
2. 使用Clion编译
请注意文件夹中的```CMakeLists.txt```
在编译时,请点开**编辑配置**窗口,将**工作目录改为本文件夹的绝对路径**

---

##第三方库
SDL2库中的```SDL2main SDL2 SDL2_image SDL2_ttf```

---

##游戏方式与内容
1. 当您点开```RUN.exe```时,呈现的是**开始菜单**,包括**开始游戏**,**生存指南**,**退出游戏**三个选项.
在开始菜单可以使用**键盘的方向键**移动选择光标,
按下**空格**或**回车**确定选择.
在程序运行的任意时刻都可以通过按下**Esc**或**鼠标点击右上角的叉**退出程序
2. 强烈建议第一次游玩本游戏先进入**生存指南**以查看本游戏的操作说明.
在操作说明界面按下**Backspace**或点击右上角的**返回标识**回到**开始菜单**.
3. 在**游戏界面**使用**键盘的方向键**控制捣蛋猫的**左右移动**和**跳跃蹲下**,以进行跑酷游戏
按下**P**键进入暂停界面
4. 在**暂停界面**中,会出现**返回标题**,**继续游戏**,**重新开始**三个选项,
可以使用**鼠标**点击操作.
5. 当捣蛋猫的**帕鲁球**数量为0时或在遇到**佩克龙事件**时撞到障碍物时,游戏结束,进入**结算界面**.
6. 在**结算界面**玩家可以看到自己的**分数**,和**复活**,**返回标题**两个选项,
可以使用**鼠标**点击操作.
7. 该游戏中遇到**刺**可以按**Up**跳跃躲过,遇到**跨栏**可以按**Down**蹲下躲过,遇到**较大的障碍物**则必须按**Right**或**Left**切换跑道.
8. 随着游戏的进行会遇到两种**道具**
(1) **帕鲁球**也就是捣蛋猫的生命,捣蛋猫每碰到一次障碍物**帕鲁球**数量减1,当数量为0时**游戏结束**(**佩克龙事件**除外)
(2) **护盾**获得护盾时捣蛋猫将获得持续一段时间的无敌效果.
9. 随着游戏的进行会遇到两种**事件**
(1) **博爱蜥事件**玩家的上下左右的方向**颠倒**
(2) **佩克龙事件**捣蛋猫一旦碰到障碍物直接**结束游戏**
事件会持续一段时间,在事件持续时间玩家获得的**分数**翻两倍

---
##代码设计思路
通过将每一个界面的绘制写入不同的.c文件中,在```main.c```中调用```Menu_logic()```函数以绘制**开始菜单**,
在```menu.c```中通过不同的选择调用```Game_logic()```,```Guide_logic```,```Quit_Menu```三种函数,以实现不同界面的绘制.
在项目编写初期曾遇到**严重的内存泄露问题**,导致内存占用持续增加,键盘操作卡顿,在网上查阅相关资料后对代码进行重构,将每一个图形的绘制单独写成一个函数
```
void Draw_background(){
    menu.surface_background=IMG_Load("res/img/background/background_start.png");
    menu.texture_background=SDL_CreateTextureFromSurface(app.renderer,menu.surface_background);
    SDL_Rect rect_background ={0,0,menu.surface_background->w,menu.surface_background->h};
    SDL_RenderCopy(app.renderer,menu.texture_background,NULL,&rect_background);
    SDL_FreeSurface(menu.surface_background);
    SDL_DestroyTexture(menu.texture_background);
}
```
每次调用完```SDL_RenderCopy```后即将```SDL_Surface```和```SDL_Texture```的相关空间清除,可以有效解决内存泄露问题