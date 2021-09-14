//
// Created by Dallin Hagman on 9/3/21.
//

#include <Lights/DirectionalLight.h>
#include <Renderable/Sphere.h>
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
    glm::dvec3 pos = visitPoint3(ctx->point3());
    std::unique_ptr<Light> light = std::make_unique<DirectionalLight>(pos, color);
    _sceneDescription->pushLight(std::move(light));
    return light;
}

antlrcpp::Any MySDFVisitor::visitAreaLight(antlrcpp::SDFParser::AreaLightContext *ctx) {
    return SDFBaseVisitor::visitAreaLight(ctx);
}

antlrcpp::Any MySDFVisitor::visitPointLight(antlrcpp::SDFParser::PointLightContext *ctx) {
    return SDFBaseVisitor::visitPointLight(ctx);
}

antlrcpp::Any MySDFVisitor::visitSphereLight(antlrcpp::SDFParser::SphereLightContext *ctx) {
    return SDFBaseVisitor::visitSphereLight(ctx);
}

antlrcpp::Any MySDFVisitor::visitMaterial(antlrcpp::SDFParser::MaterialContext *ctx) {
    int num = std::stoi(ctx->num->getText());
    glm::dvec3 kdRgb = visitRgb(ctx->kd_rgb);
    glm::dvec3 ksRgb = visitRgb(ctx->ks_rgb);
    double n = std::stod(ctx->n->getText());
    double kd = std::stod(ctx->kd->getText());
    double ks = std::stod(ctx->ks->getText());
    double kt = std::stod(ctx->kt->getText());

    auto mat = std::make_unique<Material>(kd, ks, kt, n, kdRgb, ksRgb);
    _sceneDescription->insertMaterial(num, std::move(mat));
    return mat;
}

antlrcpp::Any MySDFVisitor::visitSphere(antlrcpp::SDFParser::SphereContext *ctx) {
    glm::dvec3 origin = visitPoint3(ctx->point3());
    double radius = std::stod(ctx->radius->getText());
    int mat_num = std::stoi(ctx->mat_num->getText());

    auto& material = _sceneDescription->getMaterials().at(mat_num);
    auto sphere = std::make_unique<Sphere>(material, origin, radius);
    _sceneDescription->pushObject(std::move(sphere));
    return sphere;
}

antlrcpp::Any MySDFVisitor::visitTriangle(antlrcpp::SDFParser::TriangleContext *ctx) {
    return SDFBaseVisitor::visitTriangle(ctx);
}

antlrcpp::Any MySDFVisitor::visitPolygon(antlrcpp::SDFParser::PolygonContext *ctx) {
    return SDFBaseVisitor::visitPolygon(ctx);
}

antlrcpp::Any MySDFVisitor::visitTexSphere(antlrcpp::SDFParser::TexSphereContext *ctx) {
    return SDFBaseVisitor::visitTexSphere(ctx);
}

antlrcpp::Any MySDFVisitor::visitTexTriangle(antlrcpp::SDFParser::TexTriangleContext *ctx) {
    return SDFBaseVisitor::visitTexTriangle(ctx);
}

antlrcpp::Any MySDFVisitor::visitTexPolygon(antlrcpp::SDFParser::TexPolygonContext *ctx) {
    return SDFBaseVisitor::visitTexPolygon(ctx);
}

antlrcpp::Any MySDFVisitor::visitVertex(antlrcpp::SDFParser::VertexContext *ctx) {
    return SDFBaseVisitor::visitVertex(ctx);
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

