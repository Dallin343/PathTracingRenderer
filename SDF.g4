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
background: 'BACKGROUND' 'color' rgb;
ambient: 'AMBIENT' 'fac' fac=Float 'color' rgb;
camera: 'CAMERA' 'look_from' lf=point3 'look_at' la=point3 'fov' fov=point2;
directionalLight: 'DIRECTIONAL_LIGHT' 'direction' point3 'color' rgb;
areaLight: 'AREA_LIGHT' 'p1' p1=point3 'p2' p2=point3 'color' rgb;
pointLight: 'POINT_LIGHT' 'origin' point3 'color' rgb;
sphereLight: 'SPHERE_LIGHT' 'origin' point3 'radius' radius=Float 'color' rgb;
material: 'MATERIAL' 'mat_num' num=Int 'kd' kd_rgb=rgb 'ks' ks_rgb=rgb 'phong' n=Float
'kr_fac' kr=Float 'kd_fac' kd=Float 'ks_fac' ks=Float 'kt_fac' kt=Float;

sphere: 'SPHERE' 'mat_num' mat_num=Int 'origin' point3 'radius' radius=Float;
triangle: 'TRIANGLE' mat_num=Int vertex+;
polygon: 'POLYGON' mat_num=Int num_verts=Int vertex+;
texSphere: 'TEX_SPHERE' tex_num=Int point3 radius=Float;
texTriangle: 'TEX_TRIANGLE' tex_num=Int tex_vertex+;
texPolygon: 'TEX_POLYGON' tex_num=Int num_verts=Int tex_vertex+;

vertex: p=point3 nrm=point3;
tex_vertex: p=point3 nrm=point3 tex_coord=point2;
point2: x=Float y=Float | x=Int y=Int;
point3: x=Float y=Float z=Float | x=Int y=Int z=Int;
rgb: r=Float g=Float b=Float;


Float: '-' Int [.] Int | Int [.] Int;
Int: Digit+;
fragment Digit: [0-9];
Space: [ \r\t\n]+ -> skip;
