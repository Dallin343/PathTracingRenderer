//
// Created by Dallin Hagman on 9/3/21.
//

#ifndef CS655_MYSDFVISITOR_H
#define CS655_MYSDFVISITOR_H

#include <SDFBaseVisitor.h>
#include "Scene/SceneDescription.h"

class MySDFVisitor: antlrcpp::SDFBaseVisitor {
private:
    std::unique_ptr<SceneDescription> _sceneDescription;
public:
    MySDFVisitor();

    std::unique_ptr<SceneDescription> takeSceneDescription();

    antlrcpp::Any visitScene(antlrcpp::SDFParser::SceneContext *ctx) override;

    antlrcpp::Any visitAttribute(antlrcpp::SDFParser::AttributeContext *ctx) override;

    antlrcpp::Any visitBackground(antlrcpp::SDFParser::BackgroundContext *ctx) override;

    antlrcpp::Any visitAmbient(antlrcpp::SDFParser::AmbientContext *ctx) override;

    antlrcpp::Any visitCamera(antlrcpp::SDFParser::CameraContext *ctx) override;

    antlrcpp::Any visitDirectionalLight(antlrcpp::SDFParser::DirectionalLightContext *ctx) override;

    antlrcpp::Any visitAreaLight(antlrcpp::SDFParser::AreaLightContext *ctx) override;

    antlrcpp::Any visitPointLight(antlrcpp::SDFParser::PointLightContext *ctx) override;

    antlrcpp::Any visitSphereLight(antlrcpp::SDFParser::SphereLightContext *ctx) override;

    antlrcpp::Any visitMaterial(antlrcpp::SDFParser::MaterialContext *ctx) override;

    antlrcpp::Any visitSphere(antlrcpp::SDFParser::SphereContext *ctx) override;

    antlrcpp::Any visitTriangle(antlrcpp::SDFParser::TriangleContext *ctx) override;

    antlrcpp::Any visitPolygon(antlrcpp::SDFParser::PolygonContext *ctx) override;

    antlrcpp::Any visitTexTriangle(antlrcpp::SDFParser::TexTriangleContext *ctx) override;

    antlrcpp::Any visitTexPolygon(antlrcpp::SDFParser::TexPolygonContext *ctx) override;

    antlrcpp::Any visitVertex(antlrcpp::SDFParser::VertexContext *ctx) override;

    antlrcpp::Any visitTex_vertex(antlrcpp::SDFParser::Tex_vertexContext *ctx) override;

    antlrcpp::Any visitPoint2(antlrcpp::SDFParser::Point2Context *ctx) override;

    antlrcpp::Any visitPoint3(antlrcpp::SDFParser::Point3Context *ctx) override;

    antlrcpp::Any visitRgb(antlrcpp::SDFParser::RgbContext *ctx) override;
};


#endif //CS655_MYSDFVISITOR_H
