//
// Created by Dallin Hagman on 9/3/21.
//

#include <Lights/DirectionalLight.h>
#include <Renderable/Sphere.h>
#include <Lights/PointLight.h>
#include <Renderable/Triangle.h>
#include <Lights/AreaLight.h>
#include "Material/TextureLoader.h"
#include "MySDFVisitor.h"

antlrcpp::Any MySDFVisitor::visitScene(antlrcpp::SDFParser::SceneContext *ctx) {
    return SDFBaseVisitor::visitScene(ctx);
}

antlrcpp::Any MySDFVisitor::visitAttribute(antlrcpp::SDFParser::AttributeContext *ctx) {
    return SDFBaseVisitor::visitAttribute(ctx);
}

antlrcpp::Any MySDFVisitor::visitBackground(antlrcpp::SDFParser::BackgroundContext *ctx) {
    glm::dvec3 color = visitRgb(ctx->rgb());
    _sceneDescription->setBackground(color);
    return color;
}

antlrcpp::Any MySDFVisitor::visitAmbient(antlrcpp::SDFParser::AmbientContext *ctx) {
    double fac = std::stod(ctx->fac->getText());
    glm::dvec3 color = visitRgb(ctx->rgb());
    _sceneDescription->setAmbientFac(fac);
    _sceneDescription->setAmbientColor(color);
    return color;
}

antlrcpp::Any MySDFVisitor::visitCamera(antlrcpp::SDFParser::CameraContext *ctx) {
    glm::dvec2 fov = visitPoint2(ctx->fov);
    glm::dvec3 lookFrom = visitPoint3(ctx->lf);
    glm::dvec3 lookAt = visitPoint3(ctx->la);

    auto camera = std::make_unique<Camera>(lookFrom, lookAt, fov);
    _sceneDescription->setCamera(std::move(camera));
    return camera;
}

antlrcpp::Any MySDFVisitor::visitDirectionalLight(antlrcpp::SDFParser::DirectionalLightContext *ctx) {
    glm::dvec3 color = visitRgb(ctx->rgb());
    glm::dvec3 dir = visitPoint3(ctx->point3());
    double intensity = std::stod(ctx->intensity->getText());
    std::unique_ptr<Light> light = std::make_unique<DirectionalLight>(glm::normalize(dir), color, intensity);
    _sceneDescription->pushLight(std::move(light));

    return light;
}

antlrcpp::Any MySDFVisitor::visitAreaLight(antlrcpp::SDFParser::AreaLightContext *ctx) {
    glm::dvec3 origin = visitPoint3(ctx->origin);
    glm::dvec3 u = visitPoint3(ctx->u);
    glm::dvec3 v = visitPoint3(ctx->v);
    double width = std::stod(ctx->w->getText());
    double height = std::stod(ctx->h->getText());
    glm::dvec3 color = visitRgb(ctx->rgb());
    double intensity = std::stod(ctx->intensity->getText());
    std::unique_ptr<Light> light = std::make_unique<AreaLight>(origin, u, v, width, height, color, intensity);
    _sceneDescription->pushLight(std::move(light));
    return light;
}

antlrcpp::Any MySDFVisitor::visitPointLight(antlrcpp::SDFParser::PointLightContext *ctx) {
    glm::dvec3 color = visitRgb(ctx->rgb());
    glm::dvec3 origin = visitPoint3(ctx->point3());
    double intensity = std::stod(ctx->intensity->getText());
    std::unique_ptr<Light> light = std::make_unique<PointLight>(origin, color, intensity);
    _sceneDescription->pushLight(std::move(light));
    return light;
}

antlrcpp::Any MySDFVisitor::visitSphereLight(antlrcpp::SDFParser::SphereLightContext *ctx) {
    return SDFBaseVisitor::visitSphereLight(ctx);
}

antlrcpp::Any MySDFVisitor::visitMaterial(antlrcpp::SDFParser::MaterialContext *ctx) {
    std::string type = ctx->type->getText();
    int num = std::stoi(ctx->num->getText());
    if (type == "Diffuse") {
        glm::dvec3 kdRgb = visitRgb(ctx->kd_rgb);
        glm::dvec3 ksRgb = visitRgb(ctx->ks_rgb);
        double n = std::stod(ctx->n->getText());
        double kd = std::stod(ctx->kd->getText());
        double ks = std::stod(ctx->ks->getText());
        double kr = std::stod(ctx->kr->getText());
        double kg = std::stod(ctx->kg->getText());
        auto mat = std::make_unique<Material>(kd, ks, kr, kg, n, kdRgb, ksRgb);
        _sceneDescription->insertMaterial(num, std::move(mat));
    } else if (type == "Transparent") {
        double kr = std::stod(ctx->kr->getText());
        double kg = std::stod(ctx->kg->getText());
        double kt = std::stod(ctx->kt->getText());
        double ktrans = std::stod(ctx->ktrans->getText());
        double ior = std::stod(ctx->ior->getText());
        auto mat = std::make_unique<Material>(kr, kg, kt, ktrans, ior);
        _sceneDescription->insertMaterial(num, std::move(mat));
    } else if (type == "Textured") {
        int texNum = std::stoi(ctx->tex_num->getText());
        auto& tex = _sceneDescription->getTextures().at(texNum);

        if (ctx->ks_rgb) {
            glm::dvec3 ksRgb = visitRgb(ctx->ks_rgb);
            double n = std::stod(ctx->n->getText());
            double kd = std::stod(ctx->kd->getText());
            double ks = std::stod(ctx->ks->getText());
            double kr = std::stod(ctx->kr->getText());
            double kg = std::stod(ctx->kg->getText());
            auto mat = std::make_unique<Material>(tex.get(), kd, ks, kr, kg, n, ksRgb);
            _sceneDescription->insertMaterial(num, std::move(mat));
        } else {
            auto mat = std::make_unique<Material>(tex.get());
            _sceneDescription->insertMaterial(num, std::move(mat));
        }
    }

    return num;
}

antlrcpp::Any MySDFVisitor::visitTexture(antlrcpp::SDFParser::TextureContext *ctx) {
    int texNum = std::stoi(ctx->tex_num->getText());
    std::string filePath = ctx->file->getText();

    std::unique_ptr<Texture> texture = TextureLoader::loadFromFile(filePath);
    _sceneDescription->insertTexture(texNum, std::move(texture));

    return texture;
}

antlrcpp::Any MySDFVisitor::visitSphere(antlrcpp::SDFParser::SphereContext *ctx) {
    glm::dvec3 origin = visitPoint3(ctx->origin);
    glm::dvec3 up = visitPoint3(ctx->up);
    glm::dvec3 right = visitPoint3(ctx->right);
    double radius = std::stod(ctx->radius->getText());
    int mat_num = std::stoi(ctx->mat_num->getText());

    auto& material = _sceneDescription->getMaterials().at(mat_num);
    auto sphere = std::make_unique<Sphere>(material, origin, radius, up, right);
    _sceneDescription->pushObject(std::move(sphere));
    return sphere;
}

antlrcpp::Any MySDFVisitor::visitTriangle(antlrcpp::SDFParser::TriangleContext *ctx) {
    int mat_num = std::stoi(ctx->mat_num->getText());
    glm::dvec3 p1 = visitPoint3(ctx->p1);
    glm::dvec3 p2 = visitPoint3(ctx->p2);
    glm::dvec3 p3 = visitPoint3(ctx->p3);

    auto& material = _sceneDescription->getMaterials().at(mat_num);
    auto triangle = std::make_unique<Triangle>(material, p1, p2, p3);
    _sceneDescription->pushObject(std::move(triangle));
    return triangle;
}

antlrcpp::Any MySDFVisitor::visitPolygon(antlrcpp::SDFParser::PolygonContext *ctx) {
    return SDFBaseVisitor::visitPolygon(ctx);
}

antlrcpp::Any MySDFVisitor::visitTexTriangle(antlrcpp::SDFParser::TexTriangleContext *ctx) {
    int mat_num = std::stoi(ctx->mat_num->getText());
    glm::dvec3 p1 = visitPoint3(ctx->p1);
    glm::dvec2 uv1 = visitPoint2(ctx->tex_coord1);
    glm::dvec3 p2 = visitPoint3(ctx->p2);
    glm::dvec2 uv2 = visitPoint2(ctx->tex_coord2);
    glm::dvec3 p3 = visitPoint3(ctx->p3);
    glm::dvec2 uv3 = visitPoint2(ctx->tex_coord3);

    auto& material = _sceneDescription->getMaterials().at(mat_num);
    auto triangle = std::make_unique<Triangle>(material, p1, uv1, p2, uv2, p3, uv3);
    _sceneDescription->pushObject(std::move(triangle));
    return triangle;
}

antlrcpp::Any MySDFVisitor::visitTexPolygon(antlrcpp::SDFParser::TexPolygonContext *ctx) {
    return SDFBaseVisitor::visitTexPolygon(ctx);
}

antlrcpp::Any MySDFVisitor::visitVertex(antlrcpp::SDFParser::VertexContext *ctx) {
    glm::dvec3 point = visitPoint3(ctx->p);
    glm::dvec3 nrm = visitPoint3(ctx->nrm);
    return std::make_pair(point, nrm);
}

antlrcpp::Any MySDFVisitor::visitTex_vertex(antlrcpp::SDFParser::Tex_vertexContext *ctx) {
    glm::dvec3 p = visitPoint3(ctx->p);
    glm::dvec3 nrm = visitPoint3(ctx->nrm);
    glm::ivec3 texCoord = visitPoint2(ctx->tex_coord);
    return SDFBaseVisitor::visitTex_vertex(ctx);
}

antlrcpp::Any MySDFVisitor::visitPoint2(antlrcpp::SDFParser::Point2Context *ctx) {
    double x = std::stod(ctx->x->getText());
    double y = std::stod(ctx->y->getText());
    return glm::dvec2(x, y);
}

antlrcpp::Any MySDFVisitor::visitPoint3(antlrcpp::SDFParser::Point3Context *ctx) {
    double x = std::stod(ctx->x->getText());
    double y = std::stod(ctx->y->getText());
    double z = std::stod(ctx->z->getText());
    return glm::dvec3(x, y, z);
}

antlrcpp::Any MySDFVisitor::visitRgb(antlrcpp::SDFParser::RgbContext *ctx) {
    double r = std::stod(ctx->r->getText());
    double g = std::stod(ctx->g->getText());
    double b = std::stod(ctx->b->getText());
    return glm::dvec3(r, g, b);
}

std::unique_ptr<SceneDescription> MySDFVisitor::takeSceneDescription() {
    return std::move(_sceneDescription);
}

MySDFVisitor::MySDFVisitor(): _sceneDescription(std::make_unique<SceneDescription>()) {}


