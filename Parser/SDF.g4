grammar SDF;

scene: attribute+;

attribute: background
    | ambient
    | camera
    | directionalLight
    | areaLight
    | pointLight
    | sphereLight
    | material
    | sphere
    | triangle
    | polygon
    | texSphere
    | texTriangle
    | texPolygon
    ;
background: 'BACKGROUND' rgb;
ambient: 'AMBIENT' Int;
camera: 'CAMERA' lf=point3 la=point3 fov=point2;
directionalLight: 'DIRECTIONAL_LIGHT' point3 rgb;
areaLight: 'AREA_LIGHT' p1=point3 p2=point3 rgb;
pointLight: 'POINT_LIGHT' point3 rgb;
sphereLight: 'SPHERE_LIGHT' point3 radius=Float rgb;
material: 'MATERIAL' num=Int kd_r=Float kd_g=Float kd_b=Float ks_r=Float ks_g=Float ks_b=Float n=Float kd=Float kt=Float;
sphere: 'SPHERE' mat_num=Int point3 radius=Float;
triangle: 'TRIANGLE' mat_num=Int vertex+;
polygon: 'POLYGON' mat_num=Int num_verts=Int vertex+;
texSphere: 'TEX_SPHERE' tex_num=Int point3 radius=Float;
texTriangle: 'TEX_TRIANGLE' tex_num=Int tex_vertex+;
texPolygon: 'TEX_POLYGON' tex_num=Int num_verts=Int tex_vertex+;

vertex: p=point3 nrm=point3;
tex_vertex: p=point3 nrm=point3 tex_coord=point2;
point2: Float Float;
point3: Float Float Float;
rgb: Int Int Int;

Float: Int [.] Int;
Int: Digit+;
fragment Digit: [0-9];
Space: [ \r\t]+ -> skip;
