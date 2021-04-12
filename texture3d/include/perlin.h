/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   perlin.h
 * Author: aleksander
 *
 * Created on December 26, 2020, 7:20 AM
 * https://web.archive.org/web/20160510013854/http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
 */



#ifndef PERLIN_H
#define PERLIN_H

const float persistence = 1.0f/2.0f;
const int numberOctaves = 1;


float cosine_interpolate(float a, float b, float x)
{
    float ft = x * 3.1415927f;
    float f = (1.0f -  cos(ft)) * 0.5f;
    
    float ret = a * (1.0f - f) + b * f;
    return ret;
}

float noise_1(int x)
{
    x = (x << 13) ^ x;
    float ret =  1.0f - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f;
    return ret;
}



float smoothedNoise_1(float x)
{
    int noiseInt = static_cast<int>(x);
    float ret = noise_1(noiseInt) + noise_1(noiseInt - 1) / 4.0f + noise_1(noiseInt + 1)/4.0f;
    return ret;
}

float interpolatedNoise_1(float x)
{
    int integer_X    = static_cast<int>(x);
    float fractional_X = x - integer_X;

     float v1 = smoothedNoise_1(integer_X);
     float v2 = smoothedNoise_1(integer_X + 1);

     float ret = cosine_interpolate(v1 , v2 , fractional_X);
     
     return ret;
}

float perlinNoise_1(float x)
{
    float total = 0.0f;

    for (int ii = 0; ii < numberOctaves; ii++)
    {
        int frequency = 1;
        int amplitude = 1;
        
        for (int j = 0; j < ii; j++)
        {
            frequency *= 2;
            amplitude *= persistence;
            
        }
        
        total = total + interpolatedNoise_1(x * frequency) * amplitude;
    }

    return total;
}

float noise_2(int x, int y)
{
    int n = x + y * 57.0f;
    n = (n << 13) ^ n;
    float ret =  1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f;
    return ret;
}

float smoothNoise_2(float x, float y)
{
    float corners = ( noise_2(x-1, y-1)+noise_2(x+1, y-1)+noise_2(x-1, y+1)+noise_2(x+1, y+1) ) / 16.0;
    float sides   = ( noise_2(x-1, y)  +noise_2(x+1, y)  +noise_2(x, y-1)  +noise_2(x, y+1) ) /  8.0f;
    float center  =  noise_2(x, y) / 4.0f;

    float ret = corners + sides + center;
    return ret;
}


float interpolatedNoise_2(float x, float y)
{

      int integer_X    = int(x);
      float fractional_X = x - integer_X;

      int integer_Y    = int(y);
      float fractional_Y = y - integer_Y;

      float v1 = smoothNoise_2(integer_X,     integer_Y);
      float v2 = smoothNoise_2(integer_X + 1, integer_Y);
      float v3 = smoothNoise_2(integer_X,     integer_Y + 1);
      float v4 = smoothNoise_2(integer_X + 1, integer_Y + 1);

      float i1 = cosine_interpolate(v1 , v2 , fractional_X);
      float i2 = cosine_interpolate(v3 , v4 , fractional_X);

      float ret =  cosine_interpolate(i1 , i2 , fractional_Y);
      return ret;

}

float perlinNoise_2(float x, float y)
{
    float total = 0.0f;

    for (int ii = 0; ii < numberOctaves; ii++)
    {
        int frequency = 1;
        int amplitude = 1;
        
        for (int j = 0; j < ii; j++)
        {
            frequency *= 2;
            amplitude *= persistence;
            
        }
        
        total = total + interpolatedNoise_2(x * frequency, y * frequency) * amplitude;
    }

    return total;
}

float linear_interpolate(float a, float b, float x)
{
    float ret = a * (1.0f - x) + b * x;
    return ret;
}

//v0 - point before a
//v1 - a
//v2 - b
//v3 - point after b

float cubic_inerpolate(float v0, float v1, float v2, float v3, float x)
{
    float P = (v3 - v2) - (v0 - v1);
    float Q = (v0 - v1) - P;
    float R = v2 - v0;
    float S = v1;

    float ret = P * x * x * x + Q * x * x + R * x + S;
    
    return ret;
}



#endif /* PERLIN_H */

