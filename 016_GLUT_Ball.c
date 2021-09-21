#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>

#define M_PI		3.14159265358979323846
#define M_TAU		(2 * M_PI)

#define sectors 40
#define stripes 40
#define radius  0.9

#define secStep (2 * M_PI / sectors)
#define strStep (    M_PI / stripes)

// ========================================================================= //
// compute the red, green and blue value for a given segment of the sphere

float angR(double sector) {

  if        (sector < (1.0 / 3) * M_TAU) {
    return 3.0 * sector /M_TAU;
  } else if (sector < (2.0 / 3) * M_TAU) {
    return 1 - (3.0/M_TAU) * (sector - (M_TAU / 3.0));
  } else {
    return 0;
  }
}
float angG(double sector) {
  if        (sector < (1.0 / 3) * M_TAU) {
    return 0;
  } else if (sector < (2.0 / 3) * M_TAU) {
    return (3.0/M_TAU) * (sector -     (M_TAU / 3));
  } else {
    return 1.0 - (4.0/M_TAU) * (sector - (2.0 / 3) * M_TAU);
  }
}
float angB(double sector) {
  if        (sector < (2.0 / 3) * M_PI) {
    return 1.0 - 3.0 * sector /M_TAU;
  } else if (sector < (4.0 / 3) * M_PI) {
    return 0;
  } else {
    return (4.0/M_TAU) * (sector - (2.0 / 3) * M_TAU);
  }
}

// ------------------------------------------------------------------------- //

void renderScene(void) {
  static float angle = 0.0f;
  static float rotX, rotY, rotZ;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  angle += 0.05;

  glLoadIdentity();
  // Set the camera
  gluLookAt( 0.0f, 0.0f, 5.0f,		// eye coordinates
             0.0f, 0.0f, 0.0f,		// center coordinates
             0.0f, 1.0f, 0.0f);		// up direction

  rotX = cos(1 * angle);
  rotY = sin(1 * angle);
  rotZ = rotX * rotY;

  glRotatef(angle, rotX, rotY, rotZ);

  double  curSec = 0, curStr = 0;
  float   x, y, z = cos(strStep),
          fz = sin(strStep);

  // top of the sphere
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.f, 1.f, 1.f);

    glVertex3f(0.0f, 0.0f, radius);

    for (curSec = 0; curSec < 2 * M_PI; curSec += secStep) {
      x = cos(curSec) * fz * radius;
      y = sin(curSec) * fz * radius;

      glColor3f(
        angR(curSec) * fz,
        angG(curSec) * fz,
        angB(curSec) * fz
      );
      glVertex3f(x, y, z);
    }

    glColor3f(
        angR(curSec) * fz,
        angG(curSec) * fz,
        angB(curSec) * fz
      );
    glVertex3f(fz * radius, 0 , z);
  glEnd();

  // the top and bottom of the sphere count as stripes themselves -- start at strStep, stop at pi - step.
  for (curStr = strStep; curStr < (M_PI - strStep); curStr += strStep) {
    for (curSec = 0; curSec < M_TAU; curSec += secStep) {


      glBegin(GL_QUADS);
         z = cos(curStr),
        fz = sin(curStr);
         x = cos(curSec) * fz * radius;
         y = sin(curSec) * fz * radius;
        glColor3f(
          angR(curSec) * fz,
          angG(curSec) * fz,
          angB(curSec) * fz
        );
        glVertex3f(x, y, z);

         z = cos(curStr + strStep),
        fz = sin(curStr + strStep);
         x = cos(curSec) * fz * radius;
         y = sin(curSec) * fz * radius;
        glColor3f(
          angR(curSec) * fz,
          angG(curSec) * fz,
          angB(curSec) * fz
        );
        glVertex3f(x, y, z);

         z = cos(curStr + strStep),
        fz = sin(curStr + strStep);
         x = cos(curSec + secStep) * fz * radius;
         y = sin(curSec + secStep) * fz * radius;
        glColor3f(
          angR(curSec) * fz,
          angG(curSec) * fz,
          angB(curSec) * fz
        );
        glVertex3f(x, y, z);

         z = cos(curStr),
        fz = sin(curStr);
         x = cos(curSec + secStep) * fz * radius;
         y = sin(curSec + secStep) * fz * radius;
        glColor3f(
          angR(curSec) * fz,
          angG(curSec) * fz,
          angB(curSec) * fz
        );
        glVertex3f(x, y, z);
      glEnd();
    }
  }


  // bottom of the sphere
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);

    glVertex3f(0.0, 0.0, -radius);

     z = -cos(strStep),
    fz =  sin(strStep);

    for (curSec = 0; curSec < 2 * M_PI; curSec += secStep) {
      x = cos(curSec) * fz * radius;
      y = sin(curSec) * fz * radius;

      glColor3f(
        angR(curSec) * fz,
        angG(curSec) * fz,
        angB(curSec) * fz
      );
      glVertex3f(x, y, z);
    }

    glColor3f(
        angR(curSec) * fz,
        angG(curSec) * fz,
        angB(curSec) * fz
      );
    glVertex3f(fz * radius, 0 , z);
  glEnd();

  glutSwapBuffers();
}

// ------------------------------------------------------------------------- //

void changeSize(int w, int h) {
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (h == 0) {h = 1;}

  float ratio =  (float) w / h;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 1, 100);

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);
}

// ========================================================================= //

int main(int argc, char **argv) {

  // init GLUT and create Window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(320,320);
  glutCreateWindow("GLUT Sphere");

  // register callbacks
  glutDisplayFunc(renderScene);
  glutIdleFunc   (renderScene);
  glutReshapeFunc(changeSize );

  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}
