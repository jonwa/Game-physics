#pragma once
#include "../SF_src/Demo.h"
#include "../SF_src/DemoHandler.h"
#include "../SF_src/MyVector.h"
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
const static float BIGFLOAT=99999999;
const static float SMALLTHRESHOLD=0.001;
static float G=10;// m/s2
static float elasticy=0.5;//elasticitetskoefficient kan sättas för olika material. Från 0 (ingen studs) till 1 (helt förlustfri studs)

/*
 En enkel exempelklass som representerar en boll
 */
class Ball
{
public:
    float mR;//bollens radie
    MyVector mPos;//bollens position
    MyVector mVelocity;//bollens hastighet
    MyVector mForce;//kraften som verkar på bollen
    float mMass;//massan
    float mInvMass;//den inverterade massan
    Ball(const MyVector Pos,const MyVector Velocity,const float Mass,const float Radius)
    {
        mPos=Pos;
        mVelocity=Velocity;
        mR=Radius;
        setMass(Mass);
    }
    //behövs tydligen för att slippa varning
    virtual ~Ball()
    {
    }
    
    void setMass(const float Mass)
    {
        mMass=Mass;
        if(mMass==0)
            mInvMass=BIGFLOAT;
        else
            mInvMass=1.0/mMass;//se upp med 0-massa
    }
    
    //denna anropas för att nollställa kraften
    void clearForce()
    {
        mForce=MyVector();
    }
    //denna anropas för att lägga på krafter på bollen
    void addForce(const MyVector f)
    {
        mForce+=f;
    }
    //returnerar avståndet mellan två bollar (för framtida bruk)
    float distance(const Ball* b2)
    {
        return (mPos-b2->mPos).length();
    }
    
    virtual void handleGround()
    {
        /* Kollisionsdetektering och hantering mot mark */
        MyVector N=MyVector(0,1,0);//normalen för planet
        float vrel=N*mVelocity;
		
        if(mPos.mY <= mR && vrel<-SMALLTHRESHOLD)
		{
			MyVector newVelocity=mVelocity-N*(1+elasticy)*vrel;
            mVelocity=newVelocity;
        }
    }
    
    //uppdaterar bollens position med Euler med angiven steglängd
    virtual void update(const float DT)
    {
        MyVector dpos=mVelocity;//förändring i position är hastigheten..
        dpos*=DT;//..gånger steglängden
        mPos+=dpos;//Lägg till förändring för att få den nya positionen
        MyVector dvel=mForce*mInvMass;//förändring i hastighet är accelerationen (Newtons andra -> kraften delat med massan)...
        dvel*=DT;//gånger steglängd       
        mVelocity+=dvel;//Lägg till förändring för att få den nya hastighetet
    }
};


class BouncingBall:public Demo
{
public:
	Ball* mBall;
    
	BouncingBall()
	{
        elasticy=1;
		reset();
    }
    void reset()
    {
        mBall=new Ball(MyVector(3,2,7),MyVector(0.5,0,0),0.2,0.3);//vi lägger på en liten rörelse i x-led så att bollen studsar och rullar
        G=10;
    }
    
	void update(DemoHandler* draw)
	{
        if(draw->keyTyped('r'))
            reset();
        if(draw->keyTyped('1'))
            elasticy=1;//perfekt studsigt
        if(draw->keyTyped('0'))
            elasticy=0;//helt ostudsigt
        if(draw->keyTyped('5'))
            elasticy=0.5;//halvstudsigt
        
		mBall->clearForce();//börja med att rensa tidigare krafter
        
        //lägg sen på krafter
		mBall->addForce(MyVector(0,-G*mBall->mMass,0));//kraften som verkar på bollen är massan gånger g
        mBall->handleGround();
		//uppdatera tillståndet
        mBall->update(1.0/60);
        
        //Grafikprylar
		draw->drawPoint(mBall->mPos.toPoint(),MAGENTA,mBall->mR);
		draw->drawPlane(Point(5,0,5),Point(0,1,0),GREEN,5);
	}
    
	const virtual string getName()
	{
		return "Bouncing ball";
	}
	const virtual string getInfo()
	{
		return "This is a simple bouncing ball \nPress \'r\' to reset. \'0\' for inelastic collision, \'1\' for perfect elastic and \n\'5\' for medium elasticity (e=0.5)";
	}
};


/*
 (c)2012 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde 
 Contact me if you want to use it for other purposes.
 */