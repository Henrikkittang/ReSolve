#pragma once
#include<chrono>
#include<random>
#include<thread> 
#include<limits>

#include<glm/glm.hpp>



class Random
{
public:

    Random() = delete;

    static void      initialize(); 
    static double    getDouble(double min=0.0, double max=1.0);
    static float     getFloat(float min=0.0f, float max=1.0f);
    static glm::vec3 getFloat3(float min=0.0f, float max=1.0f);
    static int32_t   getInt(int32_t min=0, int32_t max=std::numeric_limits<int32_t>::max());  



private:   
  
    static thread_local std::mt19937                           s_generator;
    static thread_local std::uniform_real_distribution<double> s_distribution;

};


class Noise
{
public:

    Noise() = delete;

    static void initilize();
    static void destroy();
    static double noise(double x, double y, double z) ;
    static double turbulence(double x, double y, double z, int depth=7);

private:

    static double perlinLerp(glm::vec3 c[2][2][2], double u, double v, double w);
    static void permute(int* p, int n); 

private:
    static inline int s_pointCount = 256;
    static inline glm::vec3* s_randomValues = nullptr;
    static inline int* s_xperm = nullptr;
    static inline int* s_yperm = nullptr;
    static inline int* s_zperm = nullptr;
};




