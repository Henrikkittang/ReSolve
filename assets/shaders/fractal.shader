#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

void main() 
{
    gl_Position = position;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform dvec2 uCenter;
uniform double uScale;
uniform int umaxIterations;
uniform vec2 uResolution;

vec3 interpolateColor(float t)
{
    vec3 color1 = vec3(0.8, 0.3, 0.1);
    vec3 color2 = vec3(0.1, 0.8, 0.8);
    vec3 color3 = vec3(0.8, 0.8, 0.1);
    vec3 color4 = vec3(0.0, 0.0, 0.0);

    if (t < 0.33)
        return mix(color1, color2, t * 3.0);
    else if (t < 0.66)
        return mix(color2, color3, (t - 0.33) * 3.0);
    else
        return mix(color3, color4, (t - 0.66) * 3.0);
}

void main()
{
    // Use double for initial high-precision mapping
    dvec2 pixelPos = dvec2(gl_FragCoord.xy);
    dvec2 offset = (pixelPos - dvec2(uResolution) * 0.5) * uScale;
    dvec2 dC = uCenter + offset;

    // Convert to float for main loop
    vec2 c = vec2(dC);
    vec2 z = c;

    int i;
    for (i = 0; i < umaxIterations; ++i)
    {
        float x = z.x;
        float y = z.y;

        if (x * x + y * y > 4.0) break;

        z = vec2(x * x - y * y, 2.0 * x * y) + c;
    }

    // Smooth iteration
    float smoothIter = float(i);
    if (i < umaxIterations)
    {
        float mag2 = dot(z, z);
        float log_zn = log(mag2) / 2.0;
        float nu = log(log_zn / log(2.0)) / log(2.0);
        smoothIter = float(i) + 1.0 - nu;
    }

    float t = smoothIter / float(umaxIterations);
    vec3 finalColor = interpolateColor(t);
    color = vec4(finalColor, 1.0);
}
