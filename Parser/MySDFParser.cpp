//
// Created by Dallin Hagman on 9/6/21.
//

#include "MySDFParser.h"
#include "antlr4-runtime.h"
#include "SDFLexer.h"
#include "SDFParser.h"
#include "MySDFVisitor.h"

using namespace antlr4;
std::shared_ptr<SceneDescription> MySDFParser::parse(std::ifstream& src) {
    ANTLRInputStream input(src);
    antlrcpp::SDFLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    antlrcpp::SDFParser parser(&tokens);

    _visitor->visitScene(parser.scene());
    return _visitor->getSceneDescription();
}

MySDFParser::MySDFParser(): _visitor(std::make_unique<MySDFVisitor>()) {}
