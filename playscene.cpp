#include "playscene.h"

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int index){
    //保存当前关卡数
    levelIndex = index;
    //初始化游戏是否胜利标志
    isWin = false;
    //设置当前窗体的各种属性
    this->setFixedSize(320,588);
    QString gameLevel = QString("翻金币第 %1 关").arg(index);
    this->setWindowTitle(gameLevel);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //用代码设置菜单栏
    QMenuBar* bar = menuBar();
    this->setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });
    //返回按钮、游戏胜利和翻金币音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound* winSound = new QSound(":/res/LevelWinSound.wav",this);
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav",this);

    //返回按钮创建
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&QPushButton::clicked,this,[=](){
        //返回按钮音效播放
        backSound->play();
        qDebug()<<"点击了返回按钮";
        emit this->playSceneBack();
    });
    //显示具体关卡号
    QLabel* label = new QLabel;
    label->setParent(this);
    QString str = QString("Level: %1").arg(this->levelIndex);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,200,50));

    //初始化金币二维数组
    dataConfig data;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=data.mData[this->levelIndex][i][j];
        }
    }

    //创建胜利的图片
    QLabel* winLabel = new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->move((this->width()-pix.width())*0.5,-pix.height());

    //创建金币的背景图片
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
           QLabel* bg = new QLabel(this);
           QPixmap pix;
           pix.load(":/res/BoardNode.png");
           bg->setGeometry(0,0,pix.width(),pix.height());
           bg->setPixmap(pix);
           bg->move(57+i*pix.width(),200+j*pix.height());
           //创建金币
           QString coinStr;
           if(this->gameArray[i][j] == 1){
               coinStr = ":/res/Coin0001.png";
           }
           else{
               coinStr = ":/res/Coin0008.png";
           }
           MyCoin* coin = new MyCoin(coinStr);
           coin->posx = i;
           coin->posy = j;
           coin->flag = gameArray[i][j];
           coin->setParent(this);
           coin->move(59+i*50,204+j*50);
           //把金币放进数组
           coinBtn[i][j]=coin;
           connect(coin,&MyCoin::clicked,this,[=](){
               //!!!点击后，所有按钮先禁用
               for(int i=0;i<4;i++){
                   for(int j=0;j<4;j++){
                       this->coinBtn[i][j]->isWin = true;
                   }
               }


               //翻动自己
               //翻金币音效
               flipSound->play();

               coin->changeFlag();
               gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;
               //反动上下左右的金币
               QTimer::singleShot(200,this,[=](){
                   if(coin->posx+1<=3){
                       coinBtn[coin->posx+1][coin->posy]->changeFlag();
                       gameArray[coin->posx+1][coin->posy] = gameArray[coin->posx+1][coin->posy] == 0 ? 1 : 0;
                   }
                   if(coin->posx-1>=0){
                       coinBtn[coin->posx-1][coin->posy]->changeFlag();
                       gameArray[coin->posx-1][coin->posy] = gameArray[coin->posx-1][coin->posy] == 0 ? 1 : 0;
                   }
                   if(coin->posy+1<=3){
                       coinBtn[coin->posx][coin->posy+1]->changeFlag();
                       gameArray[coin->posx][coin->posy+1] = gameArray[coin->posx][coin->posy+1] == 0 ? 1 : 0;
                   }
                   if(coin->posy-1>=0){
                       coinBtn[coin->posx][coin->posy-1]->changeFlag();
                       gameArray[coin->posx][coin->posy-1] = gameArray[coin->posx][coin->posy-1] == 0 ? 1 : 0;
                   }


                   //!!!所有按钮翻完后，所有按钮解开禁用
                   for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           this->coinBtn[i][j]->isWin = false;
                       }
                   }


                   //翻一次检验是否全部是金币
                   this->isWin = true;
                   for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           if(coinBtn[i][j]->flag == false){
                               this->isWin = false;
                               break;
                           }
                       }
                   }
                   if(this->isWin){
                       //游戏胜利音效
                       winSound->play();
                       qDebug()<<"游戏胜利!";
                       //将左右按钮的isWin都设置为true，将不能继续点击按钮
                       for(int i=0;i<4;i++){
                           for(int j=0;j<4;j++){
                               coinBtn[i][j]->isWin=true;
                           }
                       }
                       QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");
                       //设定时间间隔
                       animation->setDuration(1000);
                       //设置起始位置
                       animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                       //设置结束位置
                       animation->setEndValue(QRect(winLabel->x(),-winLabel->y(),winLabel->width(),winLabel->height()));
                       //设置曲线
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       //执行动画
                       animation->start();
                   }
               });

           });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    //绘制背景图
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制标题图
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
