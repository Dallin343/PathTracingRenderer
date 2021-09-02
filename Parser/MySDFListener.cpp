//
// Created by Dallin Hagman on 9/2/21.
//

#include "MySDFListener.h"

void MySDFListener::enterScene(SDFParser::SceneContext *context) {
    SDFBaseListener::enterScene(context);
}

void MySDFListener::exitScene(SDFParser::SceneContext *context) {
    SDFBaseListener::exitScene(context);
}

void MySDFListener::enterAttribute(SDFParser::AttributeContext *context) {
    SDFBaseListener::enterAttribute(context);
}

void MySDFListener::exitAttribute(SDFParser::AttributeContext *context) {
    SDFBaseListener::exitAttribute(context);
}

void MySDFListener::enterBackground(SDFParser::BackgroundContext *context) {
    SDFBaseListener::enterBackground(context);
}

void MySDFListener::exitBackground(SDFParser::BackgroundContext *context) {
    SDFBaseListener::exitBackground(context);
}

void MySDFListener::enterAmbient(SDFParser::AmbientContext *context) {
    SDFBaseListener::enterAmbient(context);
}

void MySDFListener::exitAmbient(SDFParser::AmbientContext *context) {
    SDFBaseListener::exitAmbient(context);
}

void MySDFListener::enterCamera(SDFParser::CameraContext *context) {
    SDFBaseListener::enterCamera(context);
}

void MySDFListener::exitCamera(SDFParser::CameraContext *context) {
    SDFBaseListener::exitCamera(context);
}

void MySDFListener::enterDirectionalLight(SDFParser::DirectionalLightContext *context) {
    SDFBaseListener::enterDirectionalLight(context);
}

void MySDFListener::exitDirectionalLight(SDFParser::DirectionalLightContext *context) {
    SDFBaseListener::exitDirectionalLight(context);
}

void MySDFListener::enterAreaLight(SDFParser::AreaLightContext *context) {
    SDFBaseListener::enterAreaLight(context);
}

void MySDFListener::exitAreaLight(SDFParser::AreaLightContext *context) {
    SDFBaseListener::exitAreaLight(context);
}

void MySDFListener::enterPointLight(SDFParser::PointLightContext *context) {
    SDFBaseListener::enterPointLight(context);
}

void MySDFListener::exitPointLight(SDFParser::PointLightContext *context) {
    SDFBaseListener::exitPointLight(context);
}

void MySDFListener::enterSphereLight(SDFParser::SphereLightContext *context) {
    SDFBaseListener::enterSphereLight(context);
}

void MySDFListener::exitSphereLight(SDFParser::SphereLightContext *context) {
    SDFBaseListener::exitSphereLight(context);
}

void MySDFListener::enterMaterial(SDFParser::MaterialContext *context) {
    SDFBaseListener::enterMaterial(context);
}

void MySDFListener::exitMaterial(SDFParser::MaterialContext *context) {
    SDFBaseListener::exitMaterial(context);
}

void MySDFListener::enterSphere(SDFParser::SphereContext *context) {
    SDFBaseListener::enterSphere(context);
}

void MySDFListener::exitSphere(SDFParser::SphereContext *context) {
    SDFBaseListener::exitSphere(context);
}

void MySDFListener::enterTriangle(SDFParser::TriangleContext *context) {
    SDFBaseListener::enterTriangle(context);
}

void MySDFListener::exitTriangle(SDFParser::TriangleContext *context) {
    SDFBaseListener::exitTriangle(context);
}

void MySDFListener::enterPolygon(SDFParser::PolygonContext *context) {
    SDFBaseListener::enterPolygon(context);
}

void MySDFListener::exitPolygon(SDFParser::PolygonContext *context) {
    SDFBaseListener::exitPolygon(context);
}

void MySDFListener::enterTexSphere(SDFParser::TexSphereContext *context) {
    SDFBaseListener::enterTexSphere(context);
}

void MySDFListener::exitTexSphere(SDFParser::TexSphereContext *context) {
    SDFBaseListener::exitTexSphere(context);
}

void MySDFListener::enterTexTriangle(SDFParser::TexTriangleContext *context) {
    SDFBaseListener::enterTexTriangle(context);
}

void MySDFListener::exitTexTriangle(SDFParser::TexTriangleContext *context) {
    SDFBaseListener::exitTexTriangle(context);
}

void MySDFListener::enterTexPolygon(SDFParser::TexPolygonContext *context) {
    SDFBaseListener::enterTexPolygon(context);
}

void MySDFListener::exitTexPolygon(SDFParser::TexPolygonContext *context) {
    SDFBaseListener::exitTexPolygon(context);
}

void MySDFListener::enterVertex(SDFParser::VertexContext *context) {
    SDFBaseListener::enterVertex(context);
}

void MySDFListener::exitVertex(SDFParser::VertexContext *context) {
    SDFBaseListener::exitVertex(context);
}

void MySDFListener::enterTex_vertex(SDFParser::Tex_vertexContext *context) {
    SDFBaseListener::enterTex_vertex(context);
}

void MySDFListener::exitTex_vertex(SDFParser::Tex_vertexContext *context) {
    SDFBaseListener::exitTex_vertex(context);
}

void MySDFListener::enterPoint2(SDFParser::Point2Context *context) {
    SDFBaseListener::enterPoint2(context);
}

void MySDFListener::exitPoint2(SDFParser::Point2Context *context) {
    SDFBaseListener::exitPoint2(context);
}

void MySDFListener::enterPoint3(SDFParser::Point3Context *context) {
    SDFBaseListener::enterPoint3(context);
}

void MySDFListener::exitPoint3(SDFParser::Point3Context *context) {
    SDFBaseListener::exitPoint3(context);
}

void MySDFListener::enterRgb(SDFParser::RgbContext *context) {
    SDFBaseListener::enterRgb(context);
}

void MySDFListener::exitRgb(SDFParser::RgbContext *context) {
    SDFBaseListener::exitRgb(context);
}

void MySDFListener::enterEveryRule(antlr4::ParserRuleContext *context) {
    SDFBaseListener::enterEveryRule(context);
}

void MySDFListener::exitEveryRule(antlr4::ParserRuleContext *context) {
    SDFBaseListener::exitEveryRule(context);
}

void MySDFListener::visitTerminal(antlr4::tree::TerminalNode *node) {
    SDFBaseListener::visitTerminal(node);
}

void MySDFListener::visitErrorNode(antlr4::tree::ErrorNode *node) {
    SDFBaseListener::visitErrorNode(node);
}
