#include "Stages/Header/StageManager.h"

using namespace std;

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)

StageManager* stageManager;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    stageManager->movements();

    glutSwapBuffers();
}

void redimensionada(int width, int height) 
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(esquerda, direita, bottom, top, -1, 1);

    float aspectRatio = ((float)width)/height;    
    float worldAspectRatio = ((float) direita)/ top;
    
    if (aspectRatio < worldAspectRatio) 
    {
        float h = width / worldAspectRatio;

        float y = (height - h)/2;

        glViewport(0, y, width, h);
    }
    
    else if (aspectRatio > worldAspectRatio) {
        float w = ((float)height) * worldAspectRatio;
        float x = (width - w)/2;
        glViewport(x, 0, w, height);
    } else {
        glViewport(0, 0, width, height);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Callback do evento de pressionamento de tecla (sem ser setas)
void keyboard(unsigned char key, int x, int y)
{
    /*Dependendo da tecla pressionada, um vetor sinaliza
    0 mostrando que uma tecla foi desligada, ou
    1 mostrando que uma tecla foi ligada*/
    switch (key)
    {
        case 27: //ESC
            exit(0); 
            break;
            
        case 'w': //Anda para frente
        case 'W':
            if(keys[0] == 1)
                keys[0] = 0;
            else keys[0] = 1;
            
            auxKeys[0] = 1;
            break;

        case 's': //Anda para trás
        case 'S':
            if(keys[1] == 1)
                keys[1] = 0;
            else keys[1] = 1;
            auxKeys[1] = 1;
            break;

        case 'd': // Anda para direita
        case 'D':
            if(keys[2] == 1)
                keys[2] = 0;
            else keys[2] = 1;
            break;

        case 'a': // Anda para esquerda
        case 'A':
            if(keys[3] == 1)
                keys[3] = 0;
            else keys[3] = 1;
            break;

        case ' ': // Atira 
            if(keys[4] == 0)
                keys[4] = 1;
            else keys[4] = 0;
            auxKeys[2] = 1;
            break;
    }
}

void timer(int t)
{
    stageManager->timer();

    glutPostRedisplay();
    glutTimerFunc(t, timer, t);
}

void initialize()
{
    stageManager = new StageManager();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(900, 1000);
    glutInitWindowPosition(540,0);
    glutCreateWindow("C.T.C.");

    // função de inicializção do jogo
    initialize();
    glutIgnoreKeyRepeat(1); 

    // Registra callbacks para alguns eventos
    glutDisplayFunc(display);
    glutReshapeFunc(redimensionada);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard);    
    glutTimerFunc(frames, timer, frames);

    glutMainLoop();
    return 0;
}