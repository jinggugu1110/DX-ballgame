#include "DxLib.h"
#include "FileName.h"
#include "stdlib.h"
#include "time.h"

//global 
LONGLONG fpsTimer, deltaTimer; //fps monitor
float g_deltaTime = 0.0f;
float g_seconds = 0.0f;

bool GameEnd; //game is end flag
int Enemy;//enemey
int EnemyNumber = 6;
int Enemy_Speed_Max = 250;
int Enemy_Speed_Min = 150;

int GhBackGround; //back ground image using graphic handle 
int shGameBGM;//BGM int 

int interv=100;//white accelerate ball's initial pos x location
int a, b;//mouse axis

int hit=0;
//static int Fps = 0, FpsCnt = 0;
void mouse() {
    GetMousePoint(&a, &b);//a for x axis b for y
    if (a < 20)
    {
        a = 20;
    }
    if (a > 620)
    {
        a = 620;
    }
    if (b < 20)
    {
        b = 20;
    }
    if (b > 460)
    {
        b = 460;
    }
}

enum{Game_Do,Game_Clear,Game_Over};//game status 

void gameInit() 
{
    GameEnd = false;
    //GhBackGround = LoadGraph("background.jpg");
    shGameBGM = LoadSoundMem("BGM.m4a");
    PlaySoundMem(shGameBGM,DX_PLAYTYPE_BACK);//play the BGM
    //DrawGraph(0, 0, GhBackGround, TRUE);
    //ScreenFlip();
    g_seconds = 0.0f;
    g_deltaTime = 0.0f;
}
//void gameDraw(int*m,int*n)
//{    DrawGraph(0, 0, GhBackGround, FALSE);
   
    //DrawGraph(0, 0, GhBackGround, FALSE);
    //ScreenFlip();
//}//this part not used
//typedef struct {
//    float X, Y;
//}CRD;
//
//typedef struct {
//    CRD pos;
//    float speed;
//    float angle;
//    int direction;
//    int top, bottom, left,right;
//
//}MOVE;


void updateDeltaTime(LONGLONG* prevTime) {
    LONGLONG nowTime = GetNowHiPerformanceCount();
    g_deltaTime = (float)(nowTime - *prevTime) / 1000000.0f;
    *prevTime = nowTime;
    static float total = 0.0f;
    total += g_deltaTime;
    char log[256] = "";
    sprintf_s(log, 256, "%.5f %.5f\n", g_deltaTime, total);
    OutputDebugStringA(log);
}

float getDeltaTime(LONGLONG* p)//delta time
{
    //LONGLONG now = GetNowHiPerformanceCount();
    //float deltaTime = (float)(now - *p) / 1000000.0f;

    //static float total = 0.0f;
    //total += deltaTime;
    //char log[256] = "";
    //sprintf_s(log, 256, "%.5f %.5f\n", deltaTime, total);
    //OutputDebugStringA(log);
    //*p = now;
    //return deltaTime;
    return g_deltaTime;
}
//Initiation
//yellow ball basically horizontal but slowly moving down
BALL Init()
{
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ball;
    srand((unsigned int)time(NULL));
   
        ball.RADIUS = 5;
        ball.POS.X = 0;
        ball.POS.Y = 24;
        ball.SPEED.X = 66;
        ball.SPEED.Y = 10;
        ball.colorR = 210;
        ball.colorG = 197;
        ball.colorB = 24;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ball;
}

BALL Initiroiro()
{
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL balliroiro;
    srand((unsigned int)time(NULL));

    balliroiro.RADIUS = 3;
    balliroiro.POS.X = rand()%640;
    balliroiro.POS.Y = rand()%480;
    balliroiro.SPEED.X = 75;
    balliroiro.SPEED.Y = 80;
    balliroiro.colorR = 0;
    balliroiro.colorG = 0;
    balliroiro.colorB = 0;
    //SetDrawScreen(DX_SCREEN_BACK);
    return balliroiro;
}
BALL Init4()
{
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ball4;
    srand((unsigned int)time(NULL));

    ball4.RADIUS = 5;
    ball4.POS.X = 0;
    ball4.POS.Y = 250;
    ball4.SPEED.X = 200;
    ball4.SPEED.Y = 12;
    ball4.colorR = 255;
    ball4.colorG = 165;
    ball4.colorB = 0;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ball4;
}

//jumping vertically
BALL Init2()
{
    srand((unsigned int)time(NULL));
    //int a = rand() % 20;
    //int b = rand() % 255;
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ball1;
    ball1.RADIUS = 5;
    ball1.POS.X = 300;
    ball1.POS.Y = 0;
    ball1.SPEED.X = 20;
    ball1.SPEED.Y = 200;
    ball1.colorR = 140;
    ball1.colorG = 240;
    ball1.colorB = 51;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ball1;
}
//vertical 2
BALL Init22()
{
    srand((unsigned int)time(NULL));
    //int a = rand() % 20;
    //int b = rand() % 255;
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ball12;
    ball12.RADIUS = 5;
    ball12.POS.X = 200;
    ball12.POS.Y = 480;
    ball12.SPEED.X = -10;
    ball12.SPEED.Y = 200;
    ball12.colorR = 140;
    ball12.colorG = 240;
    ball12.colorB = 51;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ball12;
}

BALL Initrightdown() //this ball appears in phase 2 
{
    srand((unsigned int)time(NULL));
    //int a = rand() % 20;
    //int b = rand() % 255;
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ballrd;
    ballrd.RADIUS = 5;
    ballrd.POS.X = -20;
    ballrd.POS.Y = b;
    ballrd.SPEED.X = 20;
    ballrd.SPEED.Y = 0;
    ballrd.colorR = 255;
    ballrd.colorG = 93;
    ballrd.colorB = 176;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ballrd;
}

//blue big ball jumping with slop
BALL Init3()
{
    srand((unsigned int)time(NULL));
    //int a = rand() % 20;
    //int b = rand() % 255;
    
    BALL ball2;
    ball2.RADIUS = 5;
    ball2.POS.X = 800;
    ball2.POS.Y = 900;
    ball2.SPEED.X = 200;
    ball2.SPEED.Y = 200;
    ball2.colorR = 50;
    ball2.colorG = 200;
    ball2.colorB = 240;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ball2;
}

//initialate a ball on the left top corner and move in key frames towards the right bottom corner
BALL Initlefttop()
{
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL balllt;
    srand((unsigned int)time(NULL));

    balllt.RADIUS = 5;
    balllt.POS.X = a;
    balllt.POS.Y = -10;
    balllt.SPEED.X = 0;
    balllt.SPEED.Y = 40;
    balllt.colorR = 102;
    balllt.colorG = 0;
    balllt.colorB = 204;
    //SetDrawScreen(DX_SCREEN_BACK);
    return balllt;
}

BALL Initsp() //this ball appears in phase 3
{
    srand((unsigned int)time(NULL));
    //int a = rand() % 20;
    //int b = rand() % 255;
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ballsp;
    ballsp.RADIUS = 5;
    ballsp.POS.X = 0;
    ballsp.POS.Y = 0;
    ballsp.SPEED.X = (a)*10;
    ballsp.SPEED.Y = (b)*10;
    ballsp.colorR = 74;
    ballsp.colorG = 151;
    ballsp.colorB = 169;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ballsp;
}

BALL Initsp2() //this ball appears in phase 3
{
    srand((unsigned int)time(NULL));
    //int a = rand() % 20;
    //int b = rand() % 255;
    fpsTimer = deltaTimer = GetNowHiPerformanceCount();
    BALL ballsp2;
    ballsp2.RADIUS = 5;
    ballsp2.POS.X = 645;
    ballsp2.POS.Y = 0;
    ballsp2.SPEED.X = -5;
    ballsp2.SPEED.Y = 5;
    ballsp2.colorR = 112;
    ballsp2.colorG = 182;
    ballsp2.colorB = 152;
    //SetDrawScreen(DX_SCREEN_BACK);
    return ballsp2;
}
void updateTime() {
    g_seconds += getDeltaTime(NULL);
}

//show FPS and draw time passed
int FpsDraw(LONGLONG* p) {
    //static int Fps = 0, FpsCnt = 0;
    //LONGLONG now = GetNowHiPerformanceCount();
    //FpsCnt++;
   //// if (now - *p > 1000000) {
   ////     Fps = FpsCnt;
    // //   FpsCnt = 0;
    //    *p = now;
    //    int seconds = FpsCnt / 60;
    //    int *t = &seconds;
    //
    ////}
    //DrawFormatString(0, 0, GetColor(2
    //static float seconds = 0.0f;
    //seconds += getDeltaTime(p);
    DrawFormatString(0, 10, GetColor(255, 255, 255), "Time: %d seconds", (int)g_seconds);
    return g_seconds;
}
//iroiro ball
void Updateballiroiro(BALL* Balliroiro)
{

    BALL();
    float deltaTime = getDeltaTime(&deltaTimer);
    int colorn;
    colorn = Balliroiro->colorB + FpsDraw(&fpsTimer);
  
    Balliroiro->colorR = colorn;
    Balliroiro->colorB = colorn;
    //Balliroiro->colorG = 10;
    

    //ball SPEED increase by time
    float j = 4.0f;

    float SPEEDX = Balliroiro->SPEED.X;
    float SPEEDY = Balliroiro->SPEED.Y;
   // if (Balliroiro->POS.Y > 30) {
       // SPEEDY = SPEEDY + (Balliroiro->SPEED.Y) * j * FpsDraw(&fpsTimer);
        //if (SPEEDY > 150) { SPEEDY = 150; }
        //if (FpsDraw(&fpsTimer) < 30) { SPEEDY = SPEEDY + (Balliroiro->SPEED.Y) * a * FpsDraw(&fpsTimer); }
        //if (FpsDraw(&fpsTimer) >= 30) { SPEEDY = SPEEDY- FpsDraw(&fpsTimer) *a+ (Balliroiro->SPEED.Y) * a * (FpsDraw(&fpsTimer)-30); }
    //}

    Balliroiro->POS.X += SPEEDX * deltaTime;
    Balliroiro->POS.Y += SPEEDY * deltaTime;
    if (Balliroiro->POS.X > 1000 || Balliroiro->POS.Y > 480)
    {
        Balliroiro->POS.X = rand()%640;
        Balliroiro->POS.Y = rand()%480;
        SPEEDX = SPEEDX ;
        SPEEDY = SPEEDY ;
    }

}
//upper dropping loop
void Updateballlt(BALL* Balllt)
{
 
    BALL();
    float deltaTime = getDeltaTime(&deltaTimer);

    //ball SPEED increase by time
    float j = 4.0f;
  
    float SPEEDX=Balllt->SPEED.X;
    float SPEEDY = Balllt->SPEED.Y;
    if (Balllt->POS.Y > 30) {
        SPEEDY = SPEEDY + (Balllt->SPEED.Y) * j * FpsDraw(&fpsTimer);
        if (SPEEDY > 950) { SPEEDY = 950; }
        //if (FpsDraw(&fpsTimer) < 30) { SPEEDY = SPEEDY + (Balllt->SPEED.Y) * a * FpsDraw(&fpsTimer); }
        //if (FpsDraw(&fpsTimer) >= 30) { SPEEDY = SPEEDY- FpsDraw(&fpsTimer) *a+ (Balllt->SPEED.Y) * a * (FpsDraw(&fpsTimer)-30); }
    }
  
        Balllt->POS.X += SPEEDX * deltaTime;
        Balllt->POS.Y += SPEEDY * deltaTime;
        if (Balllt->POS.X > 640 || Balllt->POS.Y > 480) 
        {
            Balllt->POS.X = a;
            Balllt->POS.Y = 0;
        }

}

//bottom up ball
void Updateballrb(BALL* Ballrb)
{

    BALL();
    float deltaTime = getDeltaTime(&deltaTimer);

    //ball SPEED increase by time
    float j = 4.0f;
    float SPEEDX = Ballrb->SPEED.X;
    float SPEEDY = Ballrb->SPEED.Y;
    if (Ballrb->POS.X > 30) {
        SPEEDX = SPEEDX + (Ballrb->SPEED.X) * j * FpsDraw(&fpsTimer);
        //SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * j * FpsDraw(&fpsTimer);
        if (SPEEDX > 950) { SPEEDX = 950; }
        //if (FpsDraw(&fpsTimer) >= 30) { SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * a * (FpsDraw(&fpsTimer) - 30); }
        //if (FpsDraw(&fpsTimer) >= 60) { SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * a * (FpsDraw(&fpsTimer) - 60); }
    }

    Ballrb->POS.X += SPEEDX * deltaTime;
    Ballrb->POS.Y += SPEEDY * deltaTime;
    if (Ballrb->POS.X >640)
    {
        Ballrb->POS.X = 0;
        Ballrb->POS.Y = b;

    }

}

//following bullet 1 in phase 3
void Updateballsp(BALL* Ballsp)
{

    BALL();
    float deltaTime = getDeltaTime(&deltaTimer);

    //ball SPEED increase by time
    float j = 1.0f;
    float SPEEDX = a;
    float SPEEDY = b;
    if (Ballsp->POS.X > 30) {
        SPEEDX = SPEEDX + (Ballsp->SPEED.X) * j * FpsDraw(&fpsTimer);
        SPEEDY = SPEEDY + (Ballsp->SPEED.Y) * j * FpsDraw(&fpsTimer);
        if (SPEEDX > 960) { SPEEDX = 960; }
        if (SPEEDX > 720) { SPEEDX = 720; }
        //if (FpsDraw(&fpsTimer) >= 30) { SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * a * (FpsDraw(&fpsTimer) - 30); }
        //if (FpsDraw(&fpsTimer) >= 60) { SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * a * (FpsDraw(&fpsTimer) - 60); }
    }

    Ballsp->POS.X += SPEEDX * deltaTime;
    Ballsp->POS.Y += SPEEDY * deltaTime;
    if (Ballsp->POS.X > 640)
    {
        Ballsp->POS.X = 0;
        Ballsp->POS.Y = 0;

    }

}
//following bullet 2 in phase 4
void Updateballsp2(BALL* Ballsp2)
{

    BALL();
    float deltaTime = getDeltaTime(&deltaTimer);

    //ball SPEED increase by time
    float j = 1.0f;
    float SPEEDX = a-640;
    float SPEEDY = b;
    if (Ballsp2->POS.X > 30) {
        SPEEDX = SPEEDX + (Ballsp2->SPEED.X) * j * FpsDraw(&fpsTimer);
        SPEEDY = SPEEDY + (Ballsp2->SPEED.Y) * j * FpsDraw(&fpsTimer);
        if (SPEEDX <- 640) { SPEEDX = -640; }
        if (SPEEDX <- 480) { SPEEDX = -480; }
        //if (FpsDraw(&fpsTimer) >= 30) { SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * a * (FpsDraw(&fpsTimer) - 30); }
        //if (FpsDraw(&fpsTimer) >= 60) { SPEEDY = SPEEDY + (Ballrb->SPEED.Y) * a * (FpsDraw(&fpsTimer) - 60); }
    }

    Ballsp2->POS.X += SPEEDX * deltaTime;
    Ballsp2->POS.Y += SPEEDY * deltaTime;
    if (Ballsp2->POS.X < 0)
    {
        Ballsp2->POS.X = 640;
        Ballsp2->POS.Y = 0;

    }

}
//Update the ball movements
void Update(BALL* Ball)
{
    BALL();
    float deltaTime = getDeltaTime(&deltaTimer);
   
   //ball SPEED increase by time
   
    Ball->POS.X += Ball->SPEED.X * deltaTime;
    Ball->POS.Y += Ball->SPEED.Y * deltaTime;

    if (Ball->POS.X + Ball->RADIUS >= 640.0f) {
        Ball->POS.X = 640.0f - Ball->RADIUS;
        Ball->SPEED.X *= -1.01;
        //Ball->RADIUS +=1;
    }
    else if
        (Ball->POS.X - Ball->RADIUS < 0.0f) {
        Ball->POS.X = Ball->RADIUS;
        Ball->SPEED.X *= -1.01;
        //Ball->RADIUS += 1;
    }
    if (Ball->POS.Y + Ball->RADIUS >= 480.0f) {
        Ball->POS.Y = 480.0f - Ball->RADIUS;
        Ball->SPEED.Y *= -1.01;
        //Ball->RADIUS += 1;
    }
    else if
        (Ball->POS.Y - Ball->RADIUS < 0.0f) {
        Ball->POS.Y = Ball->RADIUS;
        Ball->SPEED.Y *= -1.01;
        //Ball->RADIUS + 1;
    }
}

//Draw circle
void Draw(BALL*Ball1, BALL* Ball2,BALL*Ball ,BALL*Ball12,BALL*Ball4)
{
   
//    ClearDrawScreen();
    SetDrawScreen(DX_SCREEN_BACK);
    DrawCircleAA(Ball1->POS.X, Ball1->POS.Y, Ball1->RADIUS, 32, GetColor(Ball1->colorR, Ball1->colorG, Ball1->colorB), TRUE);
    DrawCircleAA(Ball12->POS.X, Ball12->POS.Y, Ball12->RADIUS, 32, GetColor(Ball12->colorR, Ball12->colorG, Ball12->colorB), TRUE);
    DrawCircleAA(Ball2->POS.X, Ball2->POS.Y, Ball2->RADIUS, 32, GetColor(Ball2->colorR, Ball2->colorG, Ball2->colorB), TRUE);
    FpsDraw(&fpsTimer);
    DrawCircleAA(Ball4->POS.X, Ball4->POS.Y, Ball4->RADIUS, 32, GetColor(Ball4->colorR, Ball4->colorG, Ball4->colorB), TRUE);
    DrawFormatString(Ball1->POS.X + 20, Ball1->POS.Y, GetColor(100, 100, 255), "<-これ黄じゃない？");
    DrawCircleAA(Ball->POS.X, Ball->POS.Y, Ball->RADIUS, 32, GetColor(Ball->colorR, Ball->colorG, Ball->colorB), TRUE);
   
//    ScreenFlip();
}

void Drawlt(BALL*Balllt,BALL*Ballrb,BALL*Ballsp, BALL* Ballsp2,BALL*Balliroiro)
{
    //ClearDrawScreen();
    SetDrawScreen(DX_SCREEN_BACK);
    DrawCircleAA(Balllt->POS.X, Balllt->POS.Y, Balllt->RADIUS, 32, GetColor(Balllt->colorR, Balllt->colorG, Balllt->colorB), TRUE);
    DrawCircleAA(Ballrb->POS.X, Ballrb->POS.Y, Ballrb->RADIUS, 32, GetColor(Ballrb->colorR, Ballrb->colorG, Ballrb->colorB), TRUE);
    DrawCircleAA(Ballsp->POS.X, Ballsp->POS.Y, Ballsp->RADIUS, 32, GetColor(Ballsp->colorR, Ballsp->colorG, Ballsp->colorB), TRUE);
    DrawCircleAA(Ballsp2->POS.X, Ballsp2->POS.Y, Ballsp2->RADIUS, 32, GetColor(Ballsp2->colorR, Ballsp2->colorG, Ballsp2->colorB), TRUE);
    DrawCircleAA(Balliroiro->POS.X, Balliroiro->POS.Y, Balliroiro->RADIUS, 32, GetColor(Balliroiro->colorR, Balliroiro->colorG, Balliroiro->colorB), TRUE);
    DrawFormatString(Balliroiro->POS.X + 20, Balliroiro->POS.Y, GetColor(255, 255, 255), "<-100 POINTS/S");
    //ScreenFlip();
}

void End()
{
    DeleteGraph(GhBackGround);
}



// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;         // エラーが起きたら直ちに終了
    }
    ChangeWindowMode(TRUE);
    SetWaitVSyncFlag(FALSE);//垂直同期なし
    SetWindowText("いろいろボール");
    //const float RADIUS = 20, SPEED = 640.0f/2.0f;
    //float x, y, speed;
    //ONGLONG fpsTimer,deltaTimer;

        //x = RADIUS, y = 240;
       //speed = SPEED+ fpsTimer;

        //gameDraw(&a,&b);
    BALL ball1 = Init();
    BALL ball2 = Init2();
    BALL ball12 = Init22();
    BALL ball3 = Init3();
    BALL ball4 = Init4();
    BALL balllt = Initlefttop();
    BALL ballrb = Initrightdown();
    BALL ballsp = Initsp();
    BALL ballsp2 = Initsp2();
    BALL balliroiro = Initiroiro();


    int score = 0;
    int t = FpsDraw(&fpsTimer);
    int clock = 0;

   SetDrawScreen(DX_SCREEN_BACK);
      
      
    gameInit();

    while (ProcessMessage() == 0 && clock >=0 )
    {

        updateDeltaTime(&deltaTimer);

        float deltaTime = getDeltaTime(&deltaTimer);
        t = FpsDraw(&fpsTimer) - deltaTime;
        updateTime();
        //player mouse POS draw 
        SetDrawScreen(DX_SCREEN_BACK);
        ClearDrawScreen();
        mouse();
        //GetMousePoint(&a, &b);//a for x axis b for y
        //if (a < 20)
        //{
        //    a = 20;
        //}
        //if (a > 620)
        //{
        //    a = 620;
        //}
        //if (b < 20)
        //{
        //    b = 20;
        //}
        //if (b > 460)
        //{
        //    b = 460;
        //}
        DrawCircle(a, b, 10, GetColor(255, 0, 0), TRUE);
        //ScreenFlip();
       // Update(&ball1);
        //Draw(&ball1, &ball2, &ball3, &ball12,&ball4);
       // Update(&ball12);
        //Draw(&ball1, &ball2, &ball3,&ball12, &ball4);
       // Update(&ball2);
        //Draw(&ball1, &ball2, &ball3, &ball12, &ball4);
       // Update(&ball3);
        //Draw(&ball1, &ball2, &ball3, &ball12, &ball4);
        //Update(&ball4);
       // Draw(&ball1, &ball2, &ball3, &ball12, &ball4);

        if (FpsDraw(&deltaTimer) >= 1)
        {
            Updateballlt(&balllt);
            Drawlt(&balllt, &ballrb, &ballsp, &ballsp2, &balliroiro);

        }
        if (FpsDraw(&deltaTimer) >= 5)
        {
            Updateballrb(&ballrb);
            Drawlt(&balllt, &ballrb, &ballsp, &ballsp2, &balliroiro);

        }
        if (FpsDraw(&deltaTimer) >= 1)
        {
            Updateballsp(&ballsp);
            Drawlt(&balllt, &ballrb,&ballsp, &ballsp2, &balliroiro);

        }
        if (FpsDraw(&deltaTimer) >= 1)
        {
            Updateballsp2(&ballsp2);
            Drawlt(&balllt, &ballrb, &ballsp,&ballsp2, &balliroiro);

        }
        if (FpsDraw(&deltaTimer) >= 1)
        {
            Updateballiroiro(&balliroiro);
            Drawlt(&balllt, &ballrb, &ballsp, &ballsp2, &balliroiro);

        }
        


        // check if hit by jumping balls
        if ((ball1.POS.X - a) * (ball1.POS.X - a) + (ball1.POS.Y - b) * (ball1.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit=hit+1;
        }
        if ((ball2.POS.X - a) * (ball2.POS.X - a) + (ball2.POS.Y - b) * (ball2.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit=hit+1;
        }
        if ((ball3.POS.X - a) * (ball3.POS.X - a) + (ball3.POS.Y - b) * (ball3.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit=hit+1;
        }
        if ((balllt.POS.X - a) * (balllt.POS.X - a) + (balllt.POS.Y - b) * (balllt.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit = hit + 1;
        }
        if ((ballrb.POS.X - a) * (ballrb.POS.X - a) + (ballrb.POS.Y - b) * (ballrb.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit = hit + 1;
        }
        if ((ball12.POS.X - a) * (ball12.POS.X - a) + (ball12.POS.Y - b) * (ball12.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit = hit + 1;
        }
        if ((ballsp.POS.X - a) * (ballsp.POS.X - a) + (ballsp.POS.Y - b) * (ballsp.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit = hit + 1;
        }
        if ((ballsp2.POS.X - a) * (ballsp2.POS.X - a) + (ballsp2.POS.Y - b) * (ballsp2.POS.Y - b) <= (5 + 10) * (5 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(0, 100, 200), "OUCH!!!!!!!!!!!!!!!!!!!");
            DrawCircle(a, b, 10, GetColor(255, 100, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(255, 100, 0), FALSE);
            DrawBox(10, 460, 142, 480, GetColor(255, 100, 0), TRUE);
            hit = hit + 1;
        }
        if ((balliroiro.POS.X - a) * (balliroiro.POS.X - a) + (balliroiro.POS.Y - b) * (balliroiro.POS.Y - b) <= (3 + 10) * (3 + 10))
        {
            DrawFormatString(a + 30, b, GetColor(200, 100, 200), "GOOD! SCORE+100↑");
            DrawCircle(a, b, 10, GetColor(50, 255, 0), TRUE);
            DrawCircle(a, b, 30, GetColor(50, 255, 0), FALSE);
            DrawBox(150, 460, 250, 480, GetColor(0, 100, 0), TRUE);
            score = score + 100;
        }
        //score = 420 - FpsDraw(&fpsTimer);
       clock = 184 - FpsDraw(&fpsTimer);
       score = FpsDraw(&fpsTimer);
       int points = score * 10 - hit;
       DrawFormatString(10, 460, GetColor(240, 0, 0), "HIT DAMAGE %d ", hit);
       DrawFormatString(150, 460, GetColor(0, 150, 0), "SCORE %d ", points);
        //DrawFormatString(100, 0, GetColor(255, 255, 255), "POINTS：%d", score);
        //DrawFormatString(500, 0, GetColor(255, 255, 255), "HIT :%d ", hit);
        ScreenFlip();
    }
    SetDrawScreen(DX_SCREEN_BACK);
    ClearDrawScreen();
  
    
    DrawFormatString(100,150, GetColor(0, 150, 0), "YOUR SCORE %d ", score * 10 - hit);
    DrawFormatString(100,200, GetColor(210, 197, 24), "THANK YOU FOR YOUR PLAY！\n\nCLICK x TO QUIT");
    
    ScreenFlip();
    WaitKey();  // キー入力待ち

    End();
    DxLib_End();               // ＤＸライブラリ使用の終了処理

    return 0;              // ソフトの終了 
}