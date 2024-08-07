#include"random.hpp"



void Random::initialize()
{
    std::random_device device;
    if(device.entropy() != 0)
        s_generator.seed(device());
    else
        s_generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

double Random::getDouble(double min, double max)
{
    return s_distribution(s_generator) * (max - min) + min;
}

float Random::getFloat(float min, float max)
{
    return static_cast<float>( getDouble(min, max) );
}


glm::vec3 Random::getFloat3(float min, float max)
{
    return { getFloat(min, max), getFloat(min, max) , getFloat(min, max)  }; ;
}    

int32_t Random::getInt(int32_t min, int32_t max)
{
    return static_cast<int32_t>( getDouble(min, max)  ); 
}    




void Noise::initilize() 
{

    // These does not need to be heap allocations, but they are a straight forward and should never be called
    // in a loop. I dont realy know the implications of static stack allocations.
    // Pluss its nice to be able to reinitilize with a different s_pointCount
    s_pointCount = 256;
    s_randomValues = new glm::vec3[s_pointCount];
    s_xperm = new int[s_pointCount];
    s_yperm = new int[s_pointCount];
    s_zperm = new int[s_pointCount];
  
    for (int i = 0; i < s_pointCount; ++i) 
    {
        glm::vec3 vec = Random::getFloat3();
        s_randomValues[i] = vec / glm::length(vec);
        s_xperm[i] = i;
        s_yperm[i] = i;
        s_zperm[i] = i;
    }

    permute(s_xperm, s_pointCount);
    permute(s_xperm, s_pointCount);
    permute(s_xperm, s_pointCount);

    
}

void Noise::destroy()
{
    delete[] s_randomValues;
    delete[] s_xperm;
    delete[] s_yperm;
    delete[] s_zperm;   
}


double Noise::noise(double x, double y, double z)  
{
    double u = x - floor(x);
    double v = y - floor(y);
    double w = z - floor(z);

    
    int i = static_cast<int>(floor(x));
    int j = static_cast<int>(floor(y));
    int k = static_cast<int>(floor(z));
    glm::vec3 c[2][2][2]; // 3 x 3 x 3 cube of points (glm::vec3)

    for (int di=0; di < 2; di++)
        for (int dj=0; dj < 2; dj++)
            for (int dk=0; dk < 2; dk++)
                c[di][dj][dk] = s_randomValues
                [
                    s_xperm[(i+di) & 255] ^
                    s_yperm[(j+dj) & 255] ^
                    s_zperm[(k+dk) & 255]
                ];

    return perlinLerp(c, u, v, w);
}

double Noise::turbulence(double x, double y, double z, int depth)  
{
    double acc = 0.0;
    double weight = 1.0;

    double tx = x;
    double ty = y;
    double tz = z;

    
    for (int i = 0; i < depth; i++) 
    {
        acc += weight*noise(tx, ty, tz);
        weight *= 0.5;

        tx = tx * 2;
        ty = ty * 2;
        tz = tz * 2;
    }

    return abs(acc);
}


double Noise::perlinLerp(glm::vec3 c[2][2][2], double u, double v, double w) 
{
    double uu = u*u*(3-2*u);
    double vv = v*v*(3-2*v);
    double ww = w*w*(3-2*w);
    double acc = 0.0;

    for (int i=0; i < 2; i++)
        for (int j=0; j < 2; j++)
            for (int k=0; k < 2; k++) 
            {
                glm::vec3 weight_v(u-i, v-j, w-k);
                acc += (i*uu + (1-i)*(1-uu))
                        * (j*vv + (1-j)*(1-vv))
                        * (k*ww + (1-k)*(1-ww))
                        * glm::dot(c[i][j][k], weight_v); // Might be a source for bugs
            }

    return acc;
}


void Noise::permute(int* p, int n) 
{
    for (int i = n-1; i > 0; i--) 
    {
        int target = Random::getInt(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}




