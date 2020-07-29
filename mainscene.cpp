#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //添加游戏制作者
    QLabel* nameLabel = new QLabel;
    nameLabel->setParent(this);
    QString str = QString("游戏制作者:杨凡");
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(14);
    nameLabel->setFont(font);
    nameLabel->setText(str);
    nameLabel->setGeometry(QRect(80,50,300,100));


    //实现点击退出
    connect(ui->actionQuit,&QAction::triggered,[=](){
       this->close();
    });
    //设置标题和标题大小
    this->setFixedSize(320,588);
    this->setWindowTitle("翻金币小游戏");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //创建出选择关卡界面的对象
    chooseScene = new ChooseLevelScene();

    //监听回跳事件
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        QTimer::singleShot(300,this,[=](){
            chooseScene->hide();
            this->setGeometry(chooseScene->geometry());
            this->show();
        });
    });

    //开始创建按钮
    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //开始按钮音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);

    connect(startBtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"点击了开始按钮";
        //播放音效
        startSound->play();
        startBtn->Zoom1();
        startBtn->Zoom2();
        //延时显示动画在进入下一个界面
        QTimer::singleShot(300,this,[=](){
            //先将自己隐藏
            this->hide();
            //跳转到关卡选择界面
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });

    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent*){
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

