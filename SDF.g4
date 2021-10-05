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
background: 'BACKGROUND' 'Color' rgb;
ambient: 'AMBIENT' 'AmbientFactor' fac=Float 'Color' rgb;
camera: 'CAMERA' 'LookFrom' lf=point3 'LookAt' la=point3 'FieldOfView' fov=point2;
directionalLight: 'DIRECTIONAL_LIGHT' 'Direction' point3 'Color' rgb 'Intensity' intensity=Float;
areaLight: 'AREA_LIGHT'
    'Origin' origin=point3 'U' u=point3 'V' v=point3
    'Width' w=Float 'Height' h=Float 'Color' rgb 'Intensity' intensity=Float;

pointLight: 'POINT_LIGHT' 'Origin' point3 'Color' rgb 'Intensity' intensity=Float;
sphereLight: 'SPHERE_LIGHT' 'Origin' point3 'Radius' radius=Float 'Color' rgb 'Intensity' intensity=Float;
material: 'MATERIAL'
    'Index' num=Int
    'Type' (
    type='Diffuse'
        'DiffuseColor' kd_rgb=rgb
        'SpecularColor' ks_rgb=rgb
        'PhongConstant' n=Float
        'DiffuseFactor' kd=Float
        'SpecularFactor' ks=Float
        'ReflectiveFactor' kr=Float
        'GlossyFactor' kg=Float
        |
    type='Transparent'
        'ReflectiveFactor' kr=Float
        'GlossyFactor' kg=Float
        'TransmissionFactor' kt=Float
        'TranslucencyFactor' ktrans=Float
        'IndexOfRefraction' ior=Float
    );

sphere: 'SPHERE' 'MaterialNumber' mat_num=Int 'Origin' point3 'Radius' radius=Float;
triangle: 'TRIANGLE' 'MaterialNumber' mat_num=Int 'Point1' p1=point3 'Point2' p2=point3 'Point3' p3=point3;//vertex+;
polygon: 'POLYGON' mat_num=Int num_verts=Int vertex+;
texSphere: 'TEX_SPHERE' tex_num=Int point3 radius=Float;
texTriangle: 'TEX_TRIANGLE' tex_num=Int tex_vertex+;
texPolygon: 'TEX_POLYGON' tex_num=Int num_verts=Int tex_vertex+;

vertex: p=point3 nrm=point3;
tex_vertex: p=point3 nrm=point3 tex_coord=point2;
point2: x=Float y=Float | x=Int y=Int;
point3: x=Float y=Float z=Float | x=Int y=Int z=Int;
rgb: r=Float g=Float b=Float;


Float: '-' Int '.' Int | Int '.' Int;
Int: Digit+;
fragment Digit: [0-9];
Space: [ \r\t\n]+ -> skip;

Comment: '#' ~[\r\n]* '\r'? '\n' -> skip;
MultilineComment: '#-' .*? '-#' -> skip;
