/*This piece of code was originally from Lazy Foo' Productions
(http://lazyfoo.net/)
I edited someparts
*/

#include "LUtil.h"
#include <math.h>
#include <iostream>
using namespace std;
//The current color rendering mode
int gColorMode = 1;

//The projection scale
GLfloat gProjectionScale = 1.f;
GLfloat angle=0;
bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Move to center of the screen
    glTranslatef( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f );

    //Render quad
    if( COLOR_MODE_CYAN )
    {
        //Solid Cyan
        glBegin( GL_QUADS );
            glColor3f( 0.f, 1.f, 1.f );
            glVertex2f( -50.f, -50.f );
            glVertex2f(  50.f, -50.f );
            glVertex2f(  50.f,  50.f );
            glVertex2f( -50.f,  50.f );


        glEnd();
    }
    else
    {
        //RYGB Mix
        //angle+=M_PI*0.015;
        angle=M_PI/4;
        GLfloat s = angle;
        GLfloat size=50;
        int blur=50;
        glBegin( GL_QUADS );

            //cout<<sin(s) * -50.f<<" "<<cos(s) * 50.f<<endl;

            for(int i=blur;i>0;i--){
            s = angle;
                //glColor4f( 1.f, 1.f, 1.f,0.5f /blur );
                GLfloat z=1.f/blur;
                glColor4f( 1.f, 0.f, 0.f,z );
                glVertex2f( sin(s)*(size+i), cos(s)*(size+i) );
                s+=M_PI/2;

                glColor4f( 1.f, 1.f, 0.f ,z);
                glVertex2f( sin(s)*(size+i), cos(s) *(size+i));
                s+=M_PI/2;
                glColor4f( 0.f, 1.f, 0.f,z );
                glVertex2f( sin(s) *(size+i), cos(s)*(size+i));
                s+=M_PI/2;
                glColor4f( 0.f, 0.f, 1.f ,z );
                glVertex2f( sin(s) *(size+i),cos(s) *(size+i) );
            }

           s = angle;
            //glColor4f( 0.f, 0.f, 0.f,1.f );

            glColor3f( 1.f, 0.f, 0.f );
            glVertex2f( sin(s)*size, cos(s)*size );
            s+=M_PI/2;
            glColor3f( 1.f, 1.f, 0.f );
            glVertex2f( sin(s) * size, cos(s) *size);
            s+=M_PI/2;
            glColor3f( 0.f, 1.f, 0.f );
            glVertex2f( sin(s) * size, cos(s)* size);
            s+=M_PI/2;
            glColor3f( 0.f, 0.f, 1.f );
            glVertex2f( sin(s) * size,cos(s) * size );

        glEnd();
    }

    //Update screen
    glutSwapBuffers();
}

void handleKeys( unsigned char key, int x, int y )
{
    //If the user presses q
    if( key == 'q' )
    {
        //Toggle color mode
        if( gColorMode == COLOR_MODE_CYAN )
        {
            gColorMode = COLOR_MODE_MULTI;
        }
        else
        {
            gColorMode = COLOR_MODE_CYAN;
        }
    }
    else if( key == 'e' )
    {
        //Cycle through projection scales
        if( gProjectionScale == 1.f )
        {
            //Zoom out
            gProjectionScale = 2.f;
        }
        else if( gProjectionScale == 2.f )
        {
            //Zoom in
            gProjectionScale = 0.5f;
        }
        else if( gProjectionScale == 0.5f )
        {
            //Regular zoom
            gProjectionScale = 1.f;
        }

        //Update projection matrix
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0, SCREEN_WIDTH * gProjectionScale, SCREEN_HEIGHT * gProjectionScale, 0.0, 1.0, -1.0 );
    }
}
