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

uniform float uZoom;            
uniform vec2 uPan;              
uniform int maxIterations;              


dvec3 interpolateColor(double t)
{
    dvec3 color1 = dvec3(0.8, 0.3, 0.1);  // Yellow
    dvec3 color2 = dvec3(0.1, 0.8, 0.8);  // Cyan
    dvec3 color3 = dvec3(0.8, 0.8, 0.1);  // Yellow
    dvec3 color4 = dvec3(0.0, 0.0, 0.0);  // Red
    
    // Interpolate between color1 and color2, then color2 and color3, etc.
    if (t < 0.33)
        return mix(color1, color2, t * 3.0);  // Interpolate from blue to cyan
    else if (t < 0.66)
        return mix(color2, color3, (t - 0.33) * 3.0);  // Interpolate from cyan to yellow
    else
        return mix(color3, color4, (t - 0.66) * 3.0);  // Interpolate from yellow to red
}

void main()
{
    double x0 = 1.235 * ((gl_FragCoord.x / 960.0) * 2.0 - 1.0) * uZoom  - uPan.x  - 0.765; 
    double y0 = 1.120 * ((gl_FragCoord.y / 540.0) * 2.0 - 1.0) * uZoom  - uPan.y ;        

    double xn = x0;
    double yn = y0;


    double xn2, yn2, xt;

    int iterations = 0;
    for(iterations = 0; iterations < maxIterations; iterations++)
    {
        xn2 = xn*xn;
        yn2 = yn*yn;

        if( xn2 + yn2 >= 4.0f )
            break;

        xt = xn2 - yn2 + x0;
        yn = 2*xn*yn + y0;
        xn = xt;        
    }

    dvec3 finalColor = interpolateColor(double(iterations) / double(maxIterations));
    color = vec4(finalColor, 1.0);
} 