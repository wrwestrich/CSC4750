#include "Face.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//use colors to overlay DDA and Bresenham to see how well they match

Face::Face()
{
   vertices = new ListArray<Vertex>();
   size = 0;
}

Face::~Face()
{
   delete vertices;
}

void Face::addVertex(Vertex* vertex)
{
   if (size < 3)
   {
      vertices->add(size + 1, vertex);
      size++;
   }
}

Vertex* Face::getVertex(int index)
{
   return vertices->get(index);
}

void Face::render(Pixel* pix, Matrix* zBuffer, Matrix* transform, Color* mat)
{
   Vertex* v1 = getVertex(1);
   Vertex* v2 = getVertex(2);
   Vertex* v3 = getVertex(3);

   //put vertices into window coordinates (directly from local coordinates)
   v1 = v1->multiply(transform);
   v2 = v2->multiply(transform);
   v3 = v3->multiply(transform);

   //Perpective division
   v1->homogenize();
   v2->homogenize();
   v3->homogenize();

   /*
   //Set color passed down the hierarcy
   v1->setRed(mat->getRed());
   v1->setGreen(mat->getGreen());
   v1->setBlue(mat->getBlue());

   v2->setRed(mat->getRed());
   v2->setGreen(mat->getGreen());
   v2->setBlue(mat->getBlue());

   v3->setRed(mat->getRed());
   v3->setGreen(mat->getGreen());
   v3->setBlue(mat->getBlue());
   */

   //Hardcode the color values for interpolation test
   v1->setRed(1.0);        //0.12
   v1->setGreen(0.0);      //0.63
   v1->setBlue(0.0);       //0.12

   v2->setRed(0.0);        //0.39
   v2->setGreen(1.0);      //0.39
   v2->setBlue(0.0);       //0.39

   v3->setRed(0.0);        //0.44
   v3->setGreen(0.0);      //0.07
   v3->setBlue(1.0);       //0.61

   //Render using barycentric coorinates
   renderFace(pix, zBuffer, v1, v2, v3);
   
   //draw the wireframe of the triangle in blue
   //renderDDA(pix, v1, v2);
   //renderDDA(pix, v2, v3);
   //renderDDA(pix, v3, v1);

   //draw the wireframe of the triangle in red
   //renderBresenham(pix, v1, v2);
   //renderBresenham(pix, v2, v3);
   //renderBresenham(pix, v3, v1);

   delete v1;
   delete v2;
   delete v3;
}

void Face::renderFace(Pixel* pix, Matrix* zBuffer, Vertex* v1, Vertex*v2, Vertex* v3){
    
    //Calculate normal for this face
    Vector* f = v2->sub(v1);
    Vector* g = v3->sub(v1);
    Vector* normal = g->cross(f);

    //Do not render if face is facing away from camera
    if(normal->getZ() < 0.0){
        delete f;
        delete g;
        delete normal;
        return;
    }
 
    //Calculate bounding box using window as a constraint
    int xMin = round(fmax(fmin(fmin(v1->getX(), v2->getX()), v3->getX()), 0.0));
    int xMax = round(fmin(fmax(fmax(v1->getX(), v2->getX()), v3->getX()), zBuffer->getNumCols() - 1));

    int yMin = round(fmax(fmin(fmin(v1->getY(), v2->getY()), v3->getY()), 0.0));
    int yMax = round(fmin(fmax(fmax(v1->getY(), v2->getY()), v3->getY()), zBuffer->getNumRows() - 1));

    //Do not render if entire face is off screen
    if(xMax < 0 || yMax < 0 || xMin >= zBuffer->getNumCols() || yMin >= zBuffer->getNumRows()){
        delete f;
        delete g;
        delete normal;
        return;
    }

    //Normalize the normal
    Vector* temp = normal;
    normal = normal->norm();
    delete temp;

    //Calculate the color vectors
    Vector fc = Vector(v2->getRed() - v1->getRed(), v2->getGreen() - v1->getGreen(), v2->getBlue() - v1->getBlue());
    Vector gc = Vector(v3->getRed() - v1->getRed(), v3->getGreen() - v1->getGreen(), v3->getBlue() - v1->getBlue());

    //calculate steps for the algorithm
    double denom = 1.0 / ((f->getX() * g->getY()) - (f->getY() * g->getX()));
    double deltaAX = g->getY() * denom;
    double deltaBX = f->getY() * denom * -1.0;
    double deltaAY = g->getX() * denom * -1.0;
    double deltaBY = f->getX() * denom;
    double xPrime = xMin - v1->getX();
    double yPrime = yMin - v1->getY();
    double startA = ((xPrime * g->getY())-(yPrime * g->getX())) * denom;
    double startB = ((yPrime * f->getX())-(xPrime * f->getY())) * denom;

    //Draw the pixels
    for(int y = yMin; y <= yMax; ++y){

        int offset = y - yMin;
        double alpha = startA + (offset * deltaAY);
        double beta = startB + (offset * deltaBY);

        for(int x = xMin; x <= xMax; ++x){
            double sum = alpha + beta;
            

            if(alpha > 0.0 && beta > 0.0 && sum <= 1.0){

                double z = (f->getZ() * alpha) + (g->getZ() * beta) + v1->getZ();

                if(z > zBuffer->getElement(y, x) && z <= 1){

                    zBuffer->setElement(y, x, z);

                    //Interpolate the color
                    double r = (fc.getX() * alpha) + (gc.getX() * beta) + v1->getRed();
                    double g = (fc.getY() * alpha) + (gc.getY() * beta) + v1->getGreen();
                    double b = (fc.getZ() * alpha) + (gc.getZ() * beta) + v1->getBlue();

                    pix->drawPixel(x, y, Color(r, g, b));

                }
            }

            alpha += deltaAX;
            beta += deltaBX;
        }
    }

    delete f;
    delete g;
    delete normal;

}

void Face::renderBresenham(Pixel* pix, Vertex* first, Vertex* second)
{
   Color color(255.0, 0, 0);

   //vertices have been transformed to window coordinates, so just draw the appropriate pixels
   double x0 = first->getX();
   double y0 = first->getY();
   double x1 = second->getX();
   double y1 = second->getY();

   int step_x = +1;
   int step_y = +1;

   if (x0 > x1)
   {
      step_x = -1;
   }

   if (y0 > y1)
   {
      step_y = -1;
   }

   //assume the slope is a rational number, so dx and dy are integers
   double dx_temp = x1 - x0;
   double dy_temp = y1 - y0;
   int dx = static_cast<int> (dx_temp + 0.5);
   int dy = static_cast<int> (dy_temp + 0.5);
   if (dx_temp < 0) dx = static_cast<int> (dx_temp - 0.5);
   if (dy_temp < 0) dy = static_cast<int> (dy_temp - 0.5);

   if (abs(dx) >= abs(dy))  //need to determine if x will be incremeted or y will be incremented
   {
      //store the sign in dy, the numerator
      if (dx < 0)
      {
         dx = -1*dx;
         dy = -1*dy;
      }

      //slope is less than one so we will loop over x values, calculating y values
      int x_start = static_cast<int>(x0 + 0.5);
      if (x0 < 0)
      {
         x_start = static_cast<int>(x0 - 0.5);
      }

      int x_end = static_cast<int>(x1 + 0.5);
      if (x1 < 0)
      {
         x_end = static_cast<int>(x1 - 0.5);
      }

      int y_i = static_cast<int>(y0 + 0.5);
      if (y0 < 0)  //if y is negative
      {
         y_i = static_cast<int>(y0 - 0.5);
      }
 
      //set initial fraction to 0.5 (some error here) and then multiply fraction and slope through by 2*dx
      int fraction = dx;  //last thing to do is to subtract 2*dx so that the comparisons are with 0
      int m_new = 2*dy;
      int f_new = 2*dx;

      while(x_start != x_end)
      {
         pix->drawPixel(x_start, y_i, color);

         x_start = x_start + step_x;
         fraction = fraction + abs(m_new);  //I can simplify further if the slope is always positive

         if (fraction > f_new)
         {
            fraction = fraction - f_new;
            //y_i = y_i + step_x;
            y_i = y_i + step_y;
         }
/*
         else if (fraction < 0)
         {
            fraction = fraction + f_new;
            y_i = y_i - step_x;
         }
*/
      }
   }

   else
   {
      //store the sign in dx, the numerator
      if (dy < 0)
      {
         dx = -1*dx;
         dy = -1*dy;
      }

      int y_start = static_cast<int>(y0 + 0.5);
      if (y0 < 0)
      {
         y_start = static_cast<int>(y0 - 0.5);
      }

      int y_end = static_cast<int>(y1 + 0.5);
      if (y1 < 0)
      {
         y_end = static_cast<int>(y1 - 0.5);
      }

      int x_i = static_cast<int>(x0 + 0.5);
      if (x0 < 0)
      {
         x_i = static_cast<int>(x0 - 0.5);
      }
 
      //multiply fraction through by 2*dx everywhere
      int fraction = dy;
      int m_new = 2*dx;
      int f_new = 2*dy;

      while(y_start != y_end)
      {
         pix->drawPixel(x_i, y_start, color);

         y_start = y_start + step_y;
         fraction = fraction + abs(m_new);

         if (fraction > 2*dy)
         {
            fraction = fraction - f_new;
            //x_i = x_i + step_y;
            x_i = x_i + step_x;
         }
/*
         else if (fraction < 0)
         {
            fraction = fraction + f_new;
            x_i = x_i - step_y;
         }
*/
      }
   }
}

void Face::renderDDA(Pixel* pix, Vertex* first, Vertex* second)
{
   Color color(0, 0, 255.0);

   //vertices have been transformed to window coordinates, so just draw the appropriate pixels
   double x0 = first->getX();
   double y0 = first->getY();
   double x1 = second->getX();
   double y1 = second->getY();

   double m;

   int step_x = +1;
   int step_y = +1;

   if (x0 > x1)
   {
      step_x = -1;
   }

   if (y0 > y1)
   {
      step_y = -1;
   }

   m = 1000.0;
   if (fabs(x1 - x0) > 0.00001)
   {
      m = (y1 - y0)/(x1 - x0);
   }

   if (fabs(m) <= 1)  //need to determine if x will be incremeted or y will be incremented
   {
      //slope is less than one so we will loop over x values, calculating y values

      int x_start = static_cast<int>(x0 + 0.5);
      if (x0 < 0)
      {
         x_start = static_cast<int>(x0 - 0.5);
      }

      int x_end = static_cast<int>(x1 + 0.5);
      if (x1 < 0)
      {
         x_end = static_cast<int>(x1 - 0.5);
      }

      double y_intercept = y1 - m*x1;
      double y = m*x_start + y_intercept;

      int y_i = static_cast<int>(y + 0.5);
      if (y < 0)  //if y is negative
      {
         y_i = static_cast<int>(y - 0.5);
      }

      double fraction = (y - y_i) + 0.5;

      while(x_start != x_end)
      {
         pix->drawPixel(x_start, y_i, color);

         x_start = x_start + step_x;
         fraction = fraction + m;

         if (fraction > 1.0)
         {
            fraction = fraction - 1.0;
            y_i = y_i + step_x;
         }

         else if (fraction < 0.0)
         {
            fraction = fraction + 1.0;
            y_i = y_i - step_x;
         }
      }
   }

   else
   {
      //slope is greater than one so we will loop over y values, calculating x values
      m = (x1 - x0)/(y1 - y0);

      int y_start = static_cast<int>(y0 + 0.5);
      if (y0 < 0)
      {
         y_start = static_cast<int>(y0 - 0.5);
      }

      int y_end = static_cast<int>(y1 + 0.5);
      if (y1 < 0)
      {
         y_end = static_cast<int>(y1 - 0.5);
      }

      double x_intercept = x1 - m*y1;
      double x = m*y_start + x_intercept;

      int x_i = static_cast<int>(x + 0.5);
      if (x < 0)  //if x is negative
      {
         x_i = static_cast<int>(x - 0.5);
      }

      double fraction = (x - x_i) + 0.5;

      while (y_start != y_end)
      {
         pix->drawPixel(x_i, y_start, color);

         y_start = y_start + step_y;
         fraction = fraction + m;

         if (fraction > 1.0)
         {
            fraction = fraction - 1.0;
            x_i = x_i + step_y;
         }

         else if (fraction < 0.0)
         {
            fraction = fraction + 1.0;
            x_i = x_i - step_y;
         }
      }
   }
}

void Face::displayFace()
{
   for (int i = 1; i <= size; i++)
   {
      Vertex* vertex = getVertex(i);
      vertex->displayVertex();
   }
}
