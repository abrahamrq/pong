// Oscar Abraham Rodriguez Quintanilla
// A01195653
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>  

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

    double getYPosition(){
      return (this->y_translate*2) * 4;
    }

    double getXPosition(){
      return (this->x_translate/2) * 4;
    }

    void display(){
      glPushMatrix();
      glScalef(.5, 2, 0.1);
      glTranslated(this->x_translate, y_translate, 0);
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
      if (this->raquet.getYTranslate() >= 1.5) return;
      this->raquet.setYTranslate(this->raquet.getYTranslate() + how_much);
    }

    void moveDown(double how_much){
      if (this->raquet.getYTranslate() <= -1.5) return;
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
      glScalef(0.2, 0.2, 0);
      glTranslated(this->x_translate, this->y_translate, 0);
      glColor3ub(255, 255, 255);
      glutSolidSphere(1, 20, 20);
      glPopMatrix();
    }

    void resetGame(){
      this->player_left_score = 0;
      this->player_right_score = 0;
    }

    void resetPosition(){
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

    double getYPosition(){
      return (this->y_translate / 5) * 4;
    }

    double getXPosition(){
      return (this->x_translate / 5) * 4;
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
      if (this->x_translate >= 18){
        this->direction_x = 1;
        this->player_left_score++;
        this->resetPosition();
      } else if (this->x_translate <= -18){
        this->direction_x = 0;
        this->player_right_score++;
        this->resetPosition();
      }
      if (this->y_translate >= 18){
        this->direction_y = 1;
      } else if (this->y_translate <= -18){
        this->direction_y = 0;
      }
      if (this->speed_x <= 1){
        this->speed_x += 0.1;
      }
      if (this->speed_y <= .8){
        this->speed_y += 0.1;
      }
    }
};
////////////////////////////////////////////////////////////////////////////////

bool paused = false, started = false;
Player players[2];
Ball ball;

void generateBall(){
  ball = Ball();
}

void generatePlayers(){
  players[0] = Player(0, "Player 1", -7, 0);
  players[1] = Player(0, "Player 2", 7, 0);
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

bool collide(float ball_x, float ball_y, float player_x, float player_y){
  float player_y_top = player_y + 4;
  float player_y_bottom = player_y - 4;
  return((ball_y <= player_y_top && ball_y >= player_y_bottom) && (ball_x <= -12|| ball_x >= 12));
}

bool collision(){
  float ball_y_position = ball.getYPosition();
  float ball_x_position = ball.getXPosition();
  float player1_x_position = players[0].getRaquet().getXPosition();
  float player1_y_position = players[0].getRaquet().getYPosition();
  float player2_x_position = players[1].getRaquet().getXPosition();
  float player2_y_position = players[1].getRaquet().getYPosition();
  std::cout << ball_x_position << ", " << ball_y_position << "     " << player1_x_position << ", " << player1_y_position << std::endl;
  return collide(ball_x_position, ball_x_position, player1_x_position, player1_y_position) || collide(ball_x_position, ball_x_position, player2_x_position, player2_y_position);
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

void display(){
  glPushMatrix();
  glRotatef(ball.getXTranslate() / 10, 0, 1, 0);
  glRotatef(ball.getYTranslate() / -10, 1, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  displayTable();
  displayPlayersRaquets();
  displayBall();
  glutSwapBuffers();
  glPopMatrix();
}

void specialActions(int key, int x, int y){
  switch (key) {
    case GLUT_KEY_DOWN:
      if (started && !paused){
        players[1].moveDown(.1);
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_UP:
      if (started && !paused){ 
        players[1].moveUp(.1);
        glutPostRedisplay();
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
            if (started && !paused){
              players[0].moveUp(.1);
              glutPostRedisplay();
            }
            break;
        case 's':
        case 'S':
            if (started && !paused){
              players[0].moveDown(.1);
              glutPostRedisplay();
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
  glLoadIdentity();
  gluLookAt(0, 0, 1.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void init(){
  glClearColor (0.2039, 0.6588, 0.3254, 1.0);
  glColor3f(0.0, 0.0, 0.0);
  generatePlayers();
  generateBall();
}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Pong A01195653");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardActions);
  glutSpecialFunc(specialActions);
  init();
  //glutTimerFunc(1000, myTimer,   1);
  glutMainLoop();
}