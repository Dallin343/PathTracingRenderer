//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_MYSDFLISTENER_H
#define CS655_MYSDFLISTENER_H

#include "generated/SDFBaseListener.h"

class MySDFListener: SDFBaseListener {
    void enterScene(SDFParser::SceneContext *context) override;

    void exitScene(SDFParser::SceneContext *context) override;

    void enterAttribute(SDFParser::AttributeContext *context) override;

    void exitAttribute(SDFParser::AttributeContext *context) override;

    void enterBackground(SDFParser::BackgroundContext *context) override;

    void exitBackground(SDFParser::BackgroundContext *context) override;

    void enterAmbient(SDFParser::AmbientContext *context) override;

    void exitAmbient(SDFParser::AmbientContext *context) override;

    void enterCamera(SDFParser::CameraContext *context) override;

    void exitCamera(SDFParser::CameraContext *context) override;

    void enterDirectionalLight(SDFParser::DirectionalLightContext *context) override;

    void exitDirectionalLight(SDFParser::DirectionalLightContext *context) override;

    void enterAreaLight(SDFParser::AreaLightContext *context) override;

    void exitAreaLight(SDFParser::AreaLightContext *context) override;

    void enterPointLight(SDFParser::PointLightContext *context) override;

    void exitPointLight(SDFParser::PointLightContext *context) override;

    void enterSphereLight(SDFParser::SphereLightContext *context) override;

    void exitSphereLight(SDFParser::SphereLightContext *context) override;

    void enterMaterial(SDFParser::MaterialContext *context) override;

    void exitMaterial(SDFParser::MaterialContext *context) override;

    void enterSphere(SDFParser::SphereContext *context) override;

    void exitSphere(SDFParser::SphereContext *context) override;

    void enterTriangle(SDFParser::TriangleContext *context) override;

    void exitTriangle(SDFParser::TriangleContext *context) override;

    void enterPolygon(SDFParser::PolygonContext *context) override;

    void exitPolygon(SDFParser::PolygonContext *context) override;

    void enterTexSphere(SDFParser::TexSphereContext *context) override;

    void exitTexSphere(SDFParser::TexSphereContext *context) override;

    void enterTexTriangle(SDFParser::TexTriangleContext *context) override;

    void exitTexTriangle(SDFParser::TexTriangleContext *context) override;

    void enterTexPolygon(SDFParser::TexPolygonContext *context) override;

    void exitTexPolygon(SDFParser::TexPolygonContext *context) override;

    void enterVertex(SDFParser::VertexContext *context) override;

    void exitVertex(SDFParser::VertexContext *context) override;

    void enterTex_vertex(SDFParser::Tex_vertexContext *context) override;

    void exitTex_vertex(SDFParser::Tex_vertexContext *context) override;

    void enterPoint2(SDFParser::Point2Context *context) override;

    void exitPoint2(SDFParser::Point2Context *context) override;

    void enterPoint3(SDFParser::Point3Context *context) override;

    void exitPoint3(SDFParser::Point3Context *context) override;

    void enterRgb(SDFParser::RgbContext *context) override;

    void exitRgb(SDFParser::RgbContext *context) override;

    void enterEveryRule(antlr4::ParserRuleContext *context) override;

    void exitEveryRule(antlr4::ParserRuleContext *context) override;

    void visitTerminal(antlr4::tree::TerminalNode *node) override;

    void visitErrorNode(antlr4::tree::ErrorNode *node) override;
};


#endif //CS655_MYSDFLISTENER_H
