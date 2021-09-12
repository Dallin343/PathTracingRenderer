//
// Created by Dallin Hagman on 9/6/21.
//

#ifndef CS655_MYSDFPARSER_H
#define CS655_MYSDFPARSER_H

#include <SDFParser.h>
#include "Scene/SceneDescription.h"
#include "MySDFVisitor.h"

class MySDFParser {
private:
    std::unique_ptr<MySDFVisitor> _visitor;
public:
    MySDFParser();

    std::shared_ptr<SceneDescription> parse(std::ifstream& src);

};


#endif //CS655_MYSDFPARSER_H
