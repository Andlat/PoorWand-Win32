# PoorWand


# Model File format

joint        => j (joint matrice 4x4) [parent]
joint group  => g [vector2(joint index, weight)] ... #Total weight must be 1 per group
vertex       => v (vector coords vec3) [g joint group index]
:
j mat4
j mat4 0
j mat4 1
j mat4 1
g vec2jw vec2jw vec2jw
g vec2jw vec2jw vec2jw
v vec3 g
v vec3 g
v vec3 g
