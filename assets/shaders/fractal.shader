#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

void main() {
    gl_Position = position;
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform float uZoom;            
uniform vec2 uPan;              
uniform int maxIterations;              

// Optimized interpolateColor using float and vec3
vec3 interpolateColor(float t) {
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
    // Avoid using double precision — float is enough
    float normX = ((gl_FragCoord.x / 960.0) * 2.0 - 1.0);
    float normY = ((gl_FragCoord.y / 540.0) * 2.0 - 1.0);

    float x0 = 1.235 * normX * uZoom - uPan.x - 0.765;
    float y0 = 1.120 * normY * uZoom - uPan.y;

    float xn = x0;
    float yn = y0;

    float xn2, yn2, xt;
    int i;
    for (i = 0; i < maxIterations; ++i)
    {
        xn2 = xn * xn;
        yn2 = yn * yn;

        if (xn2 + yn2 >= 4.0)
            break;

        xt = xn2 - yn2 + x0;
        yn = 2.0 * xn * yn + y0;
        xn = xt;
    }

    float normIter = float(i) / float(maxIterations);
    vec3 finalColor = interpolateColor(normIter);
    color = vec4(finalColor, 1.0);
}
