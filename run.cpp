#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>
using namespace std;


GLuint texg=0,textureGround1,textureGround2,textureRoof;
float x=0.0f,y=0.0f,z=-20000.0f,r=0.0f;
float speedX=1.5,speedY=5.0,speedZ=2.0;
float stateMoveX = 0.0f, stateMoveZ = 0.0f, stateMoveY=0.0f;

float angleZ = 0.0f,angleY = 0.0f, angleX=-5.0f;
float stateAngleZ = 0.0f,stateAngleX=0.0f ,stateAngleY=0.0f;
float rot_angleZ = 0.15,rot_angleX=0.05,rot_angleY=0.005;

int topview=0,k=0,drop=0,m,sm1,sm2,sm3;
int housedest1=0,housedest2=0,housedest3=0;

struct Bomb{
    float xb=0,yb=0,zb=0;
    int alive=0;
};


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,ar,0.1,150000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void computePos(float stateMoveZ,float stateMoveX,float stateMoveY,float stateAngleZ,float stateAngleX) {
    
    z += stateMoveZ * speedZ;
    x += stateMoveX * speedX;
    y += stateMoveY * speedY;
    if(y<=-30*50)y=-30*50;

    if(!stateMoveX){     //bringing back rotation about z-axis to normal 
        if(angleZ!=0) 
            if( angleZ>0) angleZ-=0.1;
            else angleZ+=0.1; 
    }
    if(!stateMoveY){         //bringing back rotation about x-axis to normal 
        if(angleX!=-5) 
            if( angleX>-5) angleX-=0.1;
            else angleX+=0.1; 
    }

    angleZ += rot_angleZ * stateAngleZ;
    if(abs(angleZ)>60)  angleZ > 0 ? angleZ=60 :angleZ=-60;

    angleX += rot_angleX * stateAngleX;
    if(abs(angleX)>45)  angleX > 0 ? angleX=45 :angleX=-45;

}

void computeDir(float stateAngleY) {

    angleY += stateAngleY * rot_angleY;
    if(abs(angleY)>=360) angleY>=0? angleY-=360.0 : angleY+=360.0;
}

void drawJet(){
   
    glEnable(GL_DEPTH_TEST); 

    GLfloat ambient[] = { 0.5, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.7, 0.3, 0.3, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 

    GLfloat mat_emission[] = {0.4, 0.4, 0.4, 0.0};     

    GLfloat mat_diffuse[] = { 1.0, 0.8, 0.8, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100.0 };

    //cockpit
    glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
            glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
            glTranslated(0.0,1.5,2.0);
            glScaled(0.8,0.9,1.5);
            glutSolidSphere(2,20,20); 
        glPopAttrib();
    glPopMatrix();
   
    glPushAttrib(GL_ALL_ATTRIB_BITS); 
    
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient); 
    
        // Main body        
        glPushMatrix();
            glScaled(0.5,0.45,3.0 );
            glutSolidSphere(5,50,50);
        glPopMatrix(); 

        //nose
        glPushMatrix();
            glTranslated(0,0,10);
            glutSolidCone(1.5,10,50,50);
        glPopMatrix();

        //tail end
        glPushMatrix();
            glTranslated(0,0,-15.0);
            glutSolidCone(1.2,5,50,50);    
        glPopMatrix();

        //tail fin
        glPushMatrix();
            glColor3f(1.0,1.0,0.0);
            glTranslated(0,2,-10);
            glScaled(0.7,3.5,4);
            glRotated(-90,0.0,1.0,0);
            glutSolidTetrahedron();
            glEnd();
        glPopMatrix(); 

        //weapon left 1
        glPushMatrix();
            glTranslated(6,0,-3);
            glScaled(0.3,0.3,0.2);

            glPushMatrix();  
                glTranslated(0,0,0);
                glScaled(0.5,0.45,3.0 );
                glutSolidSphere(5,50,50);
            glPopMatrix();    

            glPushMatrix();
                glTranslated(0,0,11);
                glutSolidCone(1.5,10,50,50);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0,0,-15.0);
                glutSolidCone(1.5,5,50,50);
            glPopMatrix();

        glPopMatrix();

        //weapon left 2
        glPushMatrix();
            glTranslated(11,0,-3);
            glScaled(0.25,0.25,0.2);

            glPushMatrix();  
                glTranslated(0,0,0);
                glScaled(0.5,0.45,3.0 );
                glutSolidSphere(5,50,50);
            glPopMatrix();    
                                
            glPushMatrix();
                glTranslated(0,0,11);
                glutSolidCone(1.5,10,50,50);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0,0,-15.0);
                glutSolidCone(1.5,5,50,50);
            glPopMatrix();

        glPopMatrix();


        ///weapon right 1
        glPushMatrix();
            glTranslated(-6,0,-3);
            glScaled(0.3,0.3,0.2);

            glPushMatrix();  
                glTranslated(0,0,0);
                glScaled(0.5,0.45,3.0 );
                glutSolidSphere(5,50,50);
            glPopMatrix();    
        
            glPushMatrix();
                glTranslated(0,0,11);
                glutSolidCone(1.5,10,50,50);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0,0,-15.0);
                glutSolidCone(1.5,5,50,50);
            glPopMatrix();

        glPopMatrix();

        //weapon right 2
        glPushMatrix();
            glTranslated(-11,0,-3);
            glScaled(0.25,0.25,0.2);

            glPushMatrix();  
                glTranslated(0,0,0);
                glScaled(0.5,0.45,3.0 );
                glutSolidSphere(5,50,50);
            glPopMatrix();    
        
            glPushMatrix();
                glTranslated(0,0,11);
                glutSolidCone(1.5,10,50,50);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0,0,-15.0);
                glutSolidCone(1.5,5,50,50);
            glPopMatrix();

        glPopMatrix();

        //wings  
        glPushMatrix();
            glTranslated(0,1,-6);
            glScaled(9,0.2,2);
            glutSolidCone(2.0,6.0,50,50);
        glPopMatrix(); 

    glPopAttrib();
}
void drawGround(){
    glPushMatrix();
            
            //------------textured ground----------------

            glPushAttrib(GL_ALL_ATTRIB_BITS);
            
                glEnable(GL_TEXTURE_2D);    
                if(texg==0)
                glBindTexture(GL_TEXTURE_2D, textureGround1);
                else
                 glBindTexture(GL_TEXTURE_2D, textureGround2);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
                glTranslated(0,-1500,0);
                glScaled(100,50,100);
                
        
                glBegin(GL_QUADS);
                    glTexCoord3f(-50,50,1);  glVertex3f(500,0,500);
                    glTexCoord3f(50,50,1);  glVertex3f(-500,0,500);
                    glTexCoord3f(50,0.0,1);  glVertex3f(-500,0,-500);
                    glTexCoord3f(-50,0.0,1);  glVertex3f(500,0,-500);
                glEnd();

                glDisable(GL_TEXTURE_2D);
                
            glPopAttrib();

    glPopMatrix();    
}
void drawRoof(){

    glPushAttrib(GL_ALL_ATTRIB_BITS);
      glEnable(GL_TEXTURE_2D);    

                glBindTexture(GL_TEXTURE_2D, textureRoof);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
            //roof left
            glPushMatrix();
            glTranslated(15,17,0);
            glRotated(-32,0,0,1);
            glBegin(GL_QUADS);
                glTexCoord3f(0,0,1);     glVertex3f(50.0f, 50.0f, -50.0f);
                glTexCoord3f(1,0,1);     glVertex3f(-50.0f, 50.0f, -50.0f);
                glTexCoord3f(1,1,1);     glVertex3f(-50.0f, 50.0f, 50.0f);
                glTexCoord3f(0,1,1);     glVertex3f(50.0f, 50.0f, 50.0f);
            glEnd();
            glPopMatrix();

            //roof right
            glPushMatrix();
            glTranslated(-15,17,0);
            glRotated(32,0,0,1);
            glBegin(GL_QUADS);
                glTexCoord3f(0,0,1);     glVertex3f(50.0f, 50.0f, -50.0f);
                glTexCoord3f(1,0,1);     glVertex3f(-50.0f, 50.0f, -50.0f);
                glTexCoord3f(1,1,1);     glVertex3f(-50.0f, 50.0f, 50.0f);
                glTexCoord3f(0,1,1);     glVertex3f(50.0f, 50.0f, 50.0f);
            glEnd();
            glPopMatrix();

            glDisable(GL_TEXTURE_2D);
glPopAttrib();

}
void drawHouse(){
        
        //house1
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
            if(housedest1) glColor3f(0.05,0.05,0.05);
            else glColor3f(0.6,0.6,0.6);
            glTranslated(0,-1500,100);
            glScaled(10,5,10);
            glutSolidCube(100);
            drawRoof();
        glPopAttrib();
        glPopMatrix();

        //house2
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
            if(housedest2) glColor3f(0.05,0.05,0.05);
            else glColor3f(0.7,0.7,0.7);
            glTranslated(1500,-1500,1000);
            glRotated(90,0,1,0);
            glScaled(10,5,10);
            glutSolidCube(100);
            drawRoof();
        glPopAttrib();
        glPopMatrix();

        //house 3
        if(housedest3) glColor3f(0.05,0.05,0.05);
        else glColor3f(0.7,0.8,0.7);
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
            glTranslated(-1500,-1500,1000);
            glScaled(10,5,10);
            glEnable(GL_TEXTURE_2D);    

                glBindTexture(GL_TEXTURE_2D, textureRoof);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
            glBegin(GL_QUADS);
                glTexCoord3f(0,0,1);     glVertex3f(60.0f, 60.0f, -60.0f);
                glTexCoord3f(1,0,1);     glVertex3f(-60.0f, 60.0f, -60.0f);
                glTexCoord3f(1,1,1);     glVertex3f(-60.0f, 60.0f, 60.0f);
                glTexCoord3f(0,1,1);     glVertex3f(60.0f, 60.0f, 60.0f);
            glEnd(); 
            
            glDisable(GL_TEXTURE_2D);
            glutSolidCube(100);   
        glPopAttrib();
        glPopMatrix();

       
}

Bomb b[10];
int i=0,j=0;

void drawBomb(){
        if(b[j].alive==1){
        glPushAttrib(GL_ALL_ATTRIB_BITS);    
        glPushMatrix();
            glTranslated(b[j].xb,b[j].yb,b[j].zb+20);
            glScaled(10,10,9);
            glColor3f(1,1,0.5);    
            glPushMatrix();  
                glTranslated(0,0,0);
                glScaled(0.5,0.45,3.0 );
                glutSolidSphere(5,50,50);
            glPopMatrix();    
        
            glPushMatrix();
                glTranslated(0,0,11);
                glutSolidCone(1.5,10,50,50);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0,0,-15.0);
                glutSolidCone(1.5,5,50,50);
            glPopMatrix();
        glPopMatrix();
        glPopAttrib();
        b[i].yb-=3;
        b[i].zb+=6;

        if(b[j].alive){
            if((b[j].xb>-500 && b[j].xb<500) && (b[j].yb<=500) && (b[j].zb>-500 && b[j].zb<=500))
                housedest1=1;
            if((b[j].xb>1000 && b[j].xb<2000) && (b[j].yb<=500) && (b[j].zb>500 && b[j].zb<=1500))
                housedest2=1; 
            if((b[j].xb>-2000 && b[j].xb<-1000) && (b[j].yb<=500) && (b[j].zb>500 && b[j].zb<=1500))
                housedest3=1;       
        }
        if(b[j].yb<-1500 ) b[j].alive=0;
    }    
}
void renderScene()
{
     if(stateAngleY)
            computeDir(stateAngleY);        

    if (stateMoveX || stateMoveZ || stateMoveY || stateAngleZ || stateAngleX)
		    computePos(stateMoveZ, stateMoveX, stateMoveY, stateAngleZ, stateAngleX);
          
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.6,0.6,1.0,1.0);

    

    glPushMatrix();
        if(topview){
             gluLookAt(x,y+100,z,
                  x,y+10,z+30,
                  0.0,1.0,0.0);     
        }
        else{
            gluLookAt(x,y+10,z,
                    x,y+10,z+30,
                    0.0,1.0,0.0);
        }

        //---------------------- ground and targets------------------------------------
    
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
            glTranslated(-x,-y,-z);
            glRotatef(angleY*20,0,1,0); 
            glTranslated(x,y,z);
            drawGround();
            glPushMatrix();
            drawHouse();
            glPopMatrix();
        glPopAttrib();    
        glPopMatrix();
       
        //--------------------aircraft---------------
    
        glPushMatrix();
        glTranslated(x,y,z+25);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
            glScaled(0.5,0.5,0.5);
            glRotatef(angleZ,0,0,1);  
            glRotatef(angleX,1,0,0);            
            drawJet();
        glPopAttrib();
        glPopMatrix(); 

    if(drop && i<10){

        b[i].xb=x;
        b[i].yb=y-20;
        b[i].zb=z+20;
        b[i].alive=1;
    } 

    drawBomb();

    glPopMatrix();
       
    glutSwapBuffers();
}

void pressDirKey(int key, int xx, int yy) {

	switch (key) {

		case GLUT_KEY_UP : stateMoveZ = 1; 
                           break;

		case GLUT_KEY_DOWN :stateMoveZ = -1;
                            break;

        case GLUT_KEY_LEFT: stateMoveX = 1; 
                            stateAngleZ = -1;
                            break;
                            
        case GLUT_KEY_RIGHT:stateMoveX = -1;
                            stateAngleZ=1; 
                            break;
                                   
	}
}

void releaseDirKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : stateMoveZ=0;  
                             break;
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_LEFT: stateMoveX = 0; 
                            stateAngleZ = 0;
                            break;                        
    }
}

void pressAlphaKey(unsigned char key,int x,int y){
    switch (key)
    {
    case 'w' : stateMoveY= 0.5;
               stateAngleX=-1; 
               break; 
    case 's' : stateMoveY=-0.5;
               stateAngleX=1;
               break;
    case 'a' : stateAngleY=-1;
                break;    
    case 'd' : stateAngleY=1;
                break;           
    case 'x' : topview=1;
                break;  
    case 'z' : topview=0; //k=0;
                break; 
    case 'q' : drop=1;                                   

    }
    

}

void releaseAlphaKey(unsigned char key ,int x,int y){
        switch(key){
            case 's':
            case 'w': stateMoveY=0;
                      stateAngleX=0; 
                      break;
            case 'd' :         
            case 'a' : stateAngleY=0;
                       break;
            case 'q' : drop=0;                          
        }
}


GLuint loadTex(const char* texname)
{
    GLuint texture = SOIL_load_OGL_texture
                (
                    texname,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT

                );

    if( 0 == texture )
    {
        printf( "texture loading error '" );
    }
    return texture;
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST | GL_DOUBLE | GL_RGBA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,0.1,150000);
    textureGround1 = loadTex("./textures/grass_1.png");
    textureGround2 = loadTex("./textures/desert2.jpg");
    textureRoof =loadTex("./textures/roof.png");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void menu(int n){
    switch(n){
        case 1:topview=1;
                break;
        case 2:topview=0;
                break;
        case 3:if(speedZ<15)speedZ+=3;
                break;
        case 4:if(speedZ>0.5)speedZ-=3;
                break;
        case 5:texg=1;
                break;
        case 6: texg=0;
                break;              
        case 7:exit(0);
                break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(900,600);
    glutCreateWindow("AIR SURGICAL STRIKE SIMULATION");
    Initialize();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(resize);
    glutSpecialFunc(pressDirKey);
    glutKeyboardFunc(pressAlphaKey);
    glutSpecialUpFunc(releaseDirKey);
    glutKeyboardUpFunc(releaseAlphaKey);
	
    sm1=glutCreateMenu(menu);
    glutAddMenuEntry("Topview",1);
    glutAddMenuEntry("Normalview",2);
    sm2=glutCreateMenu(menu);
    glutAddMenuEntry("Increase",3);
    glutAddMenuEntry("Decreaase",4);
    sm3=glutCreateMenu(menu);
    glutAddMenuEntry("Desert",5);
    glutAddMenuEntry("Plain",6);
    m=glutCreateMenu(menu);
    glutAddSubMenu("terrain",sm3);
    glutAddSubMenu("speed",sm2);
    glutAddSubMenu("view",sm1);
    glutAddMenuEntry("quit",7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
