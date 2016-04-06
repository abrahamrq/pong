// Oscar Abraham Rodriguez Quintanilla
// A01195653
// Tania Garrido Salido
// A01138941
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "imageloader.h"
#include "Sound.h"


Sound die = Sound("/Users/taniagarridosalido/Dropbox/ITESM-ITC Decimo Semestre/Graficas/pong/pong_examen/pong_examen/sounds/die.wav");

///////////////////////////////////CLASSES//////////////////////////////////////
class Raquet{
  private:
    double x_translate;
    double y_translate;
    
  public:
    Raquet(){
      x_translate = 0;
      y_translate = 0;
    }
    
    Raquet(double x_translate, double y_translate){
      this->x_translate = x_translate;
      this->y_translate = y_translate;
    }
    
    double getXTranslate() { return this->x_translate; }
    void setXTranslate(double x_translate) { this->x_translate = x_translate; }
    double getYTranslate() { return this->y_translate; }
    void setYTranslate(double y_translate) { this->y_translate = y_translate; }
        
    void display(){
      glPushMatrix();
      glTranslated(this->x_translate, y_translate, 0);
      glScalef(.3, 2, 0.1);
      glColor3ub(0, 0, 0);
      glutSolidCube(1);
      glColor3ub(255, 0, 0);
      glLineWidth(1);
      glutWireCube(1);
      glPopMatrix();
    }
};

class Player{
  private:
    Raquet raquet;
    int score;
    std::string name;
    
  public:
    Player(){
      raquet = Raquet();
      score = 0;
      name = "";
    }
    
    Player(int score, std::string name, double x_translate, double y_translate){
      this->raquet = Raquet(x_translate, y_translate);
      this->score = score;
      this->name = name;
    }
    
    int getScore() { return this->score; }
    void setScore(int score) { this->score = score; }
    std::string getName() {return this->name; }
    void setName(std::string name) {this->name = name; }
    Raquet getRaquet() { return this->raquet; }
    
    void moveUp(double how_much){
      if (this->raquet.getYTranslate() >= 3) return;
      this->raquet.setYTranslate(this->raquet.getYTranslate() + how_much);
    }
    
    void moveDown(double how_much){
      if (this->raquet.getYTranslate() <= -3) return;
      this->raquet.setYTranslate(this->raquet.getYTranslate() - how_much);
    }
};

class Ball{
  private:
    double x_translate;
    double y_translate;
    double speed_x;
    double speed_y;
    int direction_x;
    int direction_y;
    int player_left_score;
    int player_right_score;
    
  public:
    Ball(){
      x_translate = 0;
      y_translate = 0;
      speed_x = .01;
      speed_y = 0;
      direction_x = 0;
      direction_y = 0;
      player_left_score = 0;
      player_right_score = 0;
    }
    
    Ball(double x_translate, double y_translate, double speed_x, double speed_y, int direction_x, int direction_y, int player_left_score, int player_right_score){
      this->x_translate = x_translate;
      this->y_translate = y_translate;
      this->speed_x = speed_x;
      this->speed_x = speed_y;
      this->direction_x = direction_x;
      this->direction_y = direction_y;
      this->player_right_score = player_right_score;
      this->player_left_score = player_left_score;
    }
    
    double getXTranslate() { return this->x_translate; }
    void setXTranslate(double x_translate) { this->x_translate = x_translate; }
    double getYTranslate() { return this->y_translate; }
    void setYTranslate(double y_translate) { this->y_translate = y_translate; }
    double getSpeedX() { return this->speed_x; }
    void setSpeedX(double speed_x) { this->speed_x = speed_x; }
    double getSpeedY() { return this->speed_y; }
    void setSpeedY(double speed_y) { this->speed_y = speed_y; }
    int getDirectionX() { return this->direction_x; }
    void setDirectionX(int direction_x) { this->direction_x = direction_x; }
    int getDirectionY() { return this->direction_y; }
    void setDirectionY(int direction_y) { this->direction_y = direction_y; }
    int getPlayerLeftScore() { return this->player_left_score; }
    void setPlayerLeftScore(int player_left_score) { this->player_left_score = player_left_score; }
    int getPlayerRightScore() { return this->player_right_score; }
    void setPlayerRightScore(int player_right_score) { this->player_right_score = player_right_score; }
    
    void display(){
      glPushMatrix();
      glTranslated(this->x_translate, this->y_translate, 0);
      glScalef(0.2, 0.2, 0);
      glColor3ub(255, 255, 255);
      glutSolidSphere(1, 20, 20);
      glPopMatrix();
    }
    
    void resetGame(){
      this->player_left_score = 0;
      this->player_right_score = 0;
    }
    
    void resetPosition(){
      die.PlaySound();
      this->x_translate = 0;
      this->y_translate = 0;
      this->speed_x = .01;
      this->speed_y = 0;
    }
    
    void displayScore(){
      std::ostringstream buffer;
      buffer << this->player_left_score;
      std::string player_left_score_string = buffer.str();
      glColor3ub(255, 255, 255);
      glRasterPos2f(-2, 3);
      for(int k = 0; k < player_left_score_string.size(); k++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, player_left_score_string[k]);
      }
      std::ostringstream buffer2;
      buffer2 << this->player_right_score;
      std::string player_right_score_string = buffer2.str();
      glColor3ub(255, 255, 255);
      glRasterPos2f(2, 3);
      for(int k = 0; k < player_right_score_string.size(); k++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, player_right_score_string[k]);
      }
    }
    
    void move(){
      if (this->direction_x == 0){
        this->x_translate += this->speed_x;
      } else {
        this->x_translate -= this->speed_x;
      }
      if (this->direction_y == 0){
        this->y_translate += this->speed_y;
      } else {
        this->y_translate -= this->speed_y;
      }
      if (this->x_translate >= 4){
        this->direction_x = 1;
        this->player_left_score++;
        this->resetPosition();
      } else if (this->x_translate <= -4){
        this->direction_x = 0;
        this->player_right_score++;
        this->resetPosition();
      }
      if (this->y_translate >= 4){
        this->direction_y = 1;
      } else if (this->y_translate <= -4){
        this->direction_y = 0;
      }
      if (this->speed_x <= .2){
        this->speed_x += 0.01;
      }
      if (this->speed_y <= .2){
        this->speed_y += 0.01;
      }
    }
};
////////////////////////////////////////////////////////////////////////////////

bool inicio = true;
bool paused = false, started = false;
Player players[2];
Ball ball;
std::string fullPath = __FILE__;
const int TEXTURE_COUNT=7;
static GLuint texName[TEXTURE_COUNT];
float vertical = 0.0;

////////////////////////////////////////////////////////////////////////////////

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: //Escape key
            exit(0);
    }
}

//le borramos el exceso para solo obtener el Path padre
void getParentPath()
{
    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
        fullPath.erase(i,1);
    }
}
//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Filtros de ampliacion y redución con cálculo mas cercano no es tan bueno pero es rápido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    //Filtros de ampliacion y redución con cálculo lineal es mejo pero son más calculos
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}



void initRendering()
{
    //Declaración del objeto Image
    Image* image;
    GLuint i=0;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture
    char  ruta[200];
    sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/burger.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/pasto.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/inicio1.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/inicio2.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
     sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/Fondo.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/RaquetaNino.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    sprintf(ruta,"%s%s", fullPath.c_str() , "texturas/RaquetaNina.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
   
    delete image;
}

void generateBall(){
  ball = Ball();
}

void generatePlayers(){
  players[0] = Player(0, "Player 1", -3.5, 0);
  players[1] = Player(0, "Player 2", 3.5, 0);
}

void displayPlayersRaquets(){
  for (int i = 0; i < 2; i++){
    players[i].getRaquet().display();
  }
}

void displayTable(){
  glLineWidth(3);
  glColor3ub(0, 0, 0);
  glBegin(GL_LINES);
  
  glVertex2d(0, -4);
  glVertex2d(0, 4);
  
  glVertex2d(-4, 0);
  glVertex2d(4, 0);
  glEnd();
  
  glPushMatrix();
  glScalef(8, 8, 0.1);
  glColor3ub(0, 0, 0);
  glLineWidth(3);
  glutWireCube(1);
  glPopMatrix();
}

bool collide(float ball_x, float ball_y, float player_x, float player_y, int player){
  if (player == ball.getDirectionX()){
    return false;
  }
  float ball_x_left = ball_x - (1 * .2);
  float ball_x_right = ball_x + (1 * .2);
  float ball_y_down = ball_y - (1 * .2);
  float ball_y_top = ball_y + (1 * .2);
  float player_x_left = player_x - (1 * .3);
  float player_x_right = player_x + (1 * .3);
  float player_y_down = player_y - (1 * .3);
  float player_y_top = player_y + (1 * .3);
  // std::cout << "ball: " << ball_x_left << ", " << ball_x_right << ", " << ball_y_down << ", " << ball_y_top << "player: " << player_x_left << ", " << player_x_right << ", " << player_y_down << ", " << player_y_top << std::endl;
  bool col = ((ball_y_top >= player_y_down && ball_y_down <= player_y_top) && (ball_x_right >= player_x_left && ball_x_left <= player_x_right));
  if (col){
    // ping.PlaySound();
  }
  return col;
}

bool collision(){
  float ball_y_position = ball.getYTranslate();
  float ball_x_position = ball.getXTranslate();
  float player1_x_position = players[0].getRaquet().getXTranslate();
  float player1_y_position = players[0].getRaquet().getYTranslate();
  float player2_x_position = players[1].getRaquet().getXTranslate();
  float player2_y_position = players[1].getRaquet().getYTranslate();
  return collide(ball_x_position, ball_y_position, player1_x_position, player1_y_position, 0) || collide(ball_x_position, ball_y_position, player2_x_position, player2_y_position, 1);
}

void displayBall(){
  if (collision()){
    if (ball.getDirectionX() == 0){
      ball.setDirectionX(1);
    } else {
      ball.setDirectionX(0);
    }
  }
  ball.display();
  ball.displayScore();
}

void displayHome(){
    glBindTexture(GL_TEXTURE_2D, texName[4]);
    glBegin(GL_QUADS);
    //Asignar la coordenada de textura 0,0 al vertice
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-5.0f, -5.0f, 0);
    //Asignar la coordenada de textura 1,0 al vertice
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(5.0f, -5.0f, 0);
    //Asignar la coordenada de textura 1,1 al vertice
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(5.0f, 5.0f, 0);
    //Asignar la coordenada de textura 0,1 al vertice
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-5.0f, 5.0f, 0);
    glEnd();
}

void displayInicio(){
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    glBegin(GL_QUADS);
    //Asignar la coordenada de textura 0,0 al vertice
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.0f, -3.0f, 0);
    //Asignar la coordenada de textura 1,0 al vertice
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(3.0f, -3.0f, 0);
    //Asignar la coordenada de textura 1,1 al vertice
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(3.0f, -1.0f, 0);
    //Asignar la coordenada de textura 0,1 al vertice
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-3.0f, -1.0f, 0);
    glEnd();
}

void displayInicio2(){
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glBegin(GL_QUADS);
    //Asignar la coordenada de textura 0,0 al vertice
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.0f, -3.0f, 0);
    //Asignar la coordenada de textura 1,0 al vertice
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(3.0f, -3.0f, 0);
    //Asignar la coordenada de textura 1,1 al vertice
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(3.0f, -1.0f, 0);
    //Asignar la coordenada de textura 0,1 al vertice
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-3.0f, -1.0f, 0);
    glEnd();
}

void display(){
  glPushMatrix();
  glRotatef(ball.getXTranslate() / 10, 0, 1, 0);
  // glRotatef(ball.getYTranslate() / -10, 1, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  if (!started){
    displayHome();
      if (inicio){
        displayInicio();
      }
      else{
          displayInicio2();
      }
  } else {
    glRotatef(vertical, 0.0, 0.0, 1.0);
    displayTable();
    displayPlayersRaquets();
    displayBall();
  }
  glutSwapBuffers();
  glPopMatrix();
}

void specialActions(int key, int x, int y){
  switch (key) {
    case GLUT_KEY_DOWN:
      if (vertical == 0){
        if (started && !paused){
          players[1].moveDown(.2);
          glutPostRedisplay();
        }
      }
      break;
    case GLUT_KEY_UP:
      if (vertical == 0){
        if (started && !paused){
          players[1].moveUp(.2);
          glutPostRedisplay();
        }
      }
      break;
    case GLUT_KEY_LEFT:
      if (vertical == 90){
        if (started && !paused){
          players[1].moveUp(.2);
          glutPostRedisplay();
        }
      }
      break;
    case GLUT_KEY_RIGHT:
      if (vertical == 90){
        if (started && !paused){
          players[1].moveDown(.2);
          glutPostRedisplay();
        }
      }
      break;
  }
}

void play_game(int value){
  glutPostRedisplay();
  if (started) {
    ball.move();
  }
  if (!paused){
    glutTimerFunc(100, play_game, 0);
  }
}

void passiveMotion(int x, int y){
    if ((x < 420 && x > 80) && ( y > 310 && y < 420) ) {
        if (inicio){
            inicio = !inicio;
        }
    } else {
        if (!inicio){
            inicio =! inicio;
        }
    }
    glutPostRedisplay();
}

void myMouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if ((x < 420 && x > 80) && ( y > 310 && y < 420) ) {
            if (!started){
                started = true;
                glutTimerFunc(100, play_game, 0);
            }
        }
    }
}

void keyboardActions(unsigned char theKey, int mouseX, int mouseY){
  switch (theKey){
    case 'i':
    case 'I':
      started = true;
      glutTimerFunc(100, play_game, 0);
      break;
    case 'r':
    case 'R':
      ball.resetPosition();
      ball.resetGame();
      started = false;
      paused = false;
      break;
    case 'p':
    case 'P':
      if (started){
        if (paused){
          glutTimerFunc(100, play_game, 0);
        }
        paused = !paused;
      }
      break;
    case 'w':
    case 'W':
      if (vertical == 0) {
        if (started && !paused){
          players[0].moveUp(.2);
          glutPostRedisplay();
        }
      }
      break;
    case 's':
    case 'S':
      if (vertical == 0) {
        if (started && !paused){
          players[0].moveDown(.2);
          glutPostRedisplay();
        }
      }
      break;
    case 'a':
    case 'A':
      if (vertical == 90) {
        if (started && !paused){
          players[0].moveUp(.2);
          glutPostRedisplay();
        }
      }
      break;
    case 'd':
    case 'D':
      if (vertical == 90) {
        if (started && !paused){
          players[0].moveDown(.2);
          glutPostRedisplay();
        }
      }
      break;
    case 'c':
    case 'C':
      if (vertical == 0){
        vertical = 90;
      } else {
        vertical = 0;
      }
      break;
    case 27:
      exit(0);
      break;
    default:
      break;// do nothing
  }
  glutPostRedisplay();
}

void reshape(int w, int h){
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(-4.0, 4.0, -4.0, 4.0, 1.0, 4.0);
  glFrustum(-4.0, 4.0, -4.0, 4.0, 1.0, 4.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0, 0, 1.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
}

void init(){
  glClearColor(0.2039, 0.6588, 0.3254, 1.0);
  glColor3f(0.0, 0.0, 0.0);
  generatePlayers();
  generateBall();
}

void timer(int value)
{
    glutPostRedisplay();
    // glutTimerFunc(1000,timer,0);
}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0);
  getParentPath();
  glutCreateWindow("Pong A01195653 - A01138941");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardActions);
  glutSpecialFunc(specialActions);
  glutPassiveMotionFunc(passiveMotion);
  glutMouseFunc(myMouseButton);
  init();
  initRendering();
  glutTimerFunc(1000,timer,0);
  glutMainLoop();
}


////////////////////////////IMAGE///////////////////////////////////////////////

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{
    
}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }
        
        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }
        
        T* get() const
        {
            return array;
        }
        
        T &operator*() const
        {
            return *array;
        }
        
        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        T* operator->() const
        {
            return array;
        }
        
        T* release()
        {
            isReleased = true;
            return array;
        }
        
        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }
        
        T* operator+(int i)
        {
            return array + i;
        }
        
        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}

////////////////////////////////////////////////////////////////////////////////