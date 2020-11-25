/**************************
 * Includes
 *
 **************************/

#include<string.h>
#include <windows.h>
#include <gl/gl.h>
#include<math.h>

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 256, 256,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            int frame = 1;
            while(frame++ < 500)
            {
                glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
                glClear (GL_COLOR_BUFFER_BIT);
                
                // Layer 1 -base
                // upper sky
                glPushMatrix ();
                glTranslatef(0, 0, 0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                
                float mm = 255;
                glBegin(GL_QUADS);       
                glColor3f(69/mm,179/mm,224/mm); glVertex2f(-1.0f,1.0f);
                glColor3f(201/mm,233/mm,246/mm); glVertex2f(-1.0f,0.00f);
                glColor3f(201/mm,233/mm,246/mm); glVertex2f(1.0f,0.00f);
                glColor3f(69/mm,179/mm,224/mm); glVertex2f(1.0f,1.00f);
                glEnd();

                // lower water 
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glBegin(GL_QUADS);            
                glColor3f(12/mm,164/mm,255/mm);  glVertex2f(-1.0f,-1.0f);
                glColor3f(0/mm,71/mm,114/mm); glVertex2f(-1.0f,0.00f);
                glColor3f(0/mm,71/mm,114/mm); glVertex2f(1.0f,0.00f);
                glColor3f(12/mm,164/mm,255/mm);  glVertex2f(1.0f,-1.00f);
                glEnd();

                // Layer 2 -sun
                //sun
                int i;
                int triangleAmount = 200; 
                double PI =3.1415;
                GLfloat radius = 0.25f; 
                GLfloat twicePi = 2*PI;
                float x=0,y=0;
                glColor3ub(253, 170 + 0.1*frame, 19);
                glBegin(GL_TRIANGLE_FAN);

                //glVertex2f(x, y); // center of circle
                for(i = 0; i <= triangleAmount;i++) { 
                glVertex2f((radius * cos(i *  twicePi / triangleAmount)) - 0.167 , (radius * sin(i * twicePi / triangleAmount))+(frame*0.001) + radius );
                }
                glEnd();

                // layer 3 - mountain
                // left mountain
                glBegin (GL_TRIANGLES);
                glColor3f (0.0f, 0.4f, 0.4f);   glVertex2f (-1.0f, 0.0f);
                glColor3f (1.0f, 0.4f + 0.001*frame, 0.4f);   glVertex2f (-0.5f, 0.75f); //
                glColor3f (1.0f, 0.8f, 0.4f);   glVertex2f (0.0f, 0.0f);  //
                glEnd ();
                //right mountain
                glBegin (GL_TRIANGLES);
                glColor3f (1.0f, 0.8f, 0.4f);   glVertex2f (-0.5f, 0.0f); //
                glColor3f (1.0f, 0.4f + 0.001*frame, 0.4f);   glVertex2f (0.35f, 0.75f); //
                glColor3f (0.0f, 0.4f, 0.4f);   glVertex2f (1.0f, 0.0f);  
                glEnd ();

                //layer 4 - boat

                //front boat
                // boat semi-circle
                x=0,y=0;
                glColor3ub(202, 164, 114);
                glBegin(GL_TRIANGLE_FAN);

                    //glVertex2f(x, y); // center of circle
                for(i = 100; i <= triangleAmount;i++) { 
                glVertex2f((radius * cos(i *  twicePi / triangleAmount)) - 0.5 + 0.0015*frame , (radius * sin(i * twicePi / triangleAmount)) - 0.5 );
                }
                glEnd();

                // man torso - quad
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glColor3ub(172,122,194);
                glBegin(GL_QUADS);            
                glVertex2f( -0.50 + 0.0015*frame , -0.5f);
                glVertex2f( -0.50 + 0.0015*frame , -0.30f);
                glVertex2f( -0.30 + 0.0015*frame , -0.5f);
                glVertex2f( -0.30 + 0.0015*frame , -0.30f);
                glEnd();

                //person - head
                
                x=0,y=0;
                glColor3ub(214, 134, 102);
                glBegin(GL_TRIANGLE_FAN);
                radius = radius*0.3;
                    //glVertex2f(x, y); // center of circle
                for(i = 0; i <= triangleAmount;i++) { 
                glVertex2f((radius * cos(i *  twicePi / triangleAmount)) - 0.4 + 0.0015*frame , (radius * sin(i * twicePi / triangleAmount)) - 0.25 );
                }
                glEnd();

                


                glPopMatrix ();
                SwapBuffers (hDC);
                Sleep (2);
            }
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
