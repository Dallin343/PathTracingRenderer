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
    | texture
    | sphere
    | triangle
    | polygon
    | texTriangle
    | texPolygon
    ;
background: 'Background' 'Color' rgb;
ambient: 'Ambient' 'AmbientFactor' fac=Float 'Color' rgb;
camera: 'Camera' 'LookFrom' lf=point3 'LookAt' la=point3 'FieldOfView' fov=point2;
directionalLight: 'DirectionalLight' 'Direction' point3 'Color' rgb 'Intensity' intensity=Float;
areaLight: 'AreaLight'
    'Origin' origin=point3 'U' u=point3 'V' v=point3
    'Width' w=Float 'Height' h=Float 'Color' rgb 'Intensity' intensity=Float;

pointLight: 'PointLight' 'Origin' point3 'Color' rgb 'Intensity' intensity=Float;
sphereLight: 'SphereLight' 'Origin' point3 'Radius' radius=Float 'Color' rgb 'Intensity' intensity=Float;

texture: 'Texture' 'Index' tex_num=Int 'File' file=Filepath;

material: 'Material'
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
        |
    type='Textured'
        'TextureNumber' tex_num=Int
//        'SpecularColor' ks_rgb=rgb
//        'PhongConstant' n=Float
//        'DiffuseFactor' kd=Float
//        'SpecularFactor' ks=Float
//        'ReflectiveFactor' kr=Float
//        'GlossyFactor' kg=Float
    );

sphere: 'Sphere' 'MaterialNumber' mat_num=Int 'Origin' origin=point3 'Up' up=point3 'Right' right=point3 'Radius' radius=Float;
triangle: 'Triangle' 'MaterialNumber' mat_num=Int 'Point1' p1=point3 'Point2' p2=point3 'Point3' p3=point3;
polygon: 'Polygon' 'MaterialNumber' mat_num=Int num_verts=Int vertex+;
texTriangle: 'TexTriangle' 'MaterialNumber' mat_num=Int tex_vertex+;
texPolygon: 'TexPolygon' tex_num=Int num_verts=Int tex_vertex+;

vertex: p=point3 nrm=point3;
tex_vertex: p=point3 nrm=point3 tex_coord=point2;
point2: x=Float y=Float | x=Int y=Int;
point3: x=Float y=Float z=Float | x=Int y=Int z=Int;
rgb: r=Float g=Float b=Float;


Float: '-' Int '.' Int | Int '.' Int;
Int: Digit+;
fragment Digit: [0-9];
Space: [ \r\t\n]+ -> skip;
Filepath: ('/'[^/ ]*)+'/'?;

Comment: '#' ~[\r\n]* '\r'? '\n' -> skip;
MultilineComment: '#-' .*? '-#' -> skip;
