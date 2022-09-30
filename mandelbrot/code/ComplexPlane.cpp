#include<iomanip>
#include<cmath>
#include<complex>
#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_view.setCenter(Vector2f{ 0.0f, 0.0f });
    m_view.setSize(Vector2f(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio));
    m_zoomCount = 0;
    
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_view.setSize(x, -y);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_view.setSize(x, y);
}

void ComplexPlane::setCenter(Vector2f coord)
{
    m_view.setCenter(coord.x, coord.y);
    cout << "New Center: " << coord.x << " " << coord.y << endl;
}

View ComplexPlane::getView()
{
    return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
    m_mouseLocation.x = coord.x;
    m_mouseLocation.y = coord.y;
    //cout << "Mouse Location: " << m_mouseLocation.x << ", " << m_mouseLocation.y << endl;
}

void ComplexPlane::loadText(Text& text)
{
    ostringstream strstr;
    strstr << "Mandelbrot Set\nCenter: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\nCursor: (" <<
        m_mouseLocation.x << ", " << m_mouseLocation.y << ")\nLeft-click to Zoom in\nRight-click to Zoom out";
    text.setString(strstr.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    size_t count = 0;
    complex<double> k(coord.x, coord.y);
    complex<double> imaginaryTotal(0.0, 0.0);
    complex<double> MORE_THAN_TWO(-2.0, 2.0);
    while (abs(imaginaryTotal) < 2.0)
    {
        if (count < MAX_ITER)
        {
            imaginaryTotal = pow(imaginaryTotal, 2) + k;
            count++;
        }
        else
        {
            count = MAX_ITER;
            return count;
        }
    }

    return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    
    if (count == MAX_ITER)
    {
        //black
        r = 0;
        g = 0;
        b = 0;
    }

    //COLOR!!
    
    else
    {   r = 255;
        g = 0;
        b = 255;
        int increment = 255 / (MAX_ITER / 5);
        for (int i = 0; i < count; i++)
        {
            if (r > 10 && g < 245 && b == 255)
            {   
                r -= (increment + 7);
                g += (increment + 7);
            }
            //r = 8
            //g = 247
            //b = 255
            else if (r < 10 && g > 245 && b > 10)
            {
                b -= (increment + 5);
            }
            //r = 8
            //g = 247
            //b = 8
            else if (r < 245 && g > 245 && b < 10)
            {
                r += (increment + 2);
            }
            //r = 255
            //g = 247
            //b = 8
            else
            {
                g -= increment;
            }
            //r = 255
            //g = 8
            //b = 8
        }
    }
    
    //GREYSCALE
    /*
    else
    {
        r = 0;
        g = 0;
        b = 0;
        int increment = 255 / MAX_ITER;
        for (int i = 0; i < count; i++)
        {
            r += increment;
            g += increment;
            b += increment;
        }
    }
    */
    /*
    if (count < MAX_ITER&& count >= 51)
    {
        //Red  
        r = 255;
        g = 0;
        b = 0;
    }
    if (count < 51 && count >= 38)
    {
        //Yellow  
        r = 255;
        g = 255;
        b = 0;
    }
    if (count < 38 && count >= 26)
    {
        //Green
        r = 0;
        g = 255;
        b = 0;
    }
    if (count < 26 && count >= 13)
    {
        //Turquoise  
        r = 0;
        g = 255;
        b = 255;
    }
    if (count < 13 && count >= 0)
    {
        //Purple / blue 
        r = 255;
        g = 0;
        b = 255;
    }*/
}
