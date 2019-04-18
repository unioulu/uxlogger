#ifndef BUTTONPARSER_H
#define BUTTONPARSER_H

#include <vector>
#include "actionbuttondata.h"

class ButtonParser
{
public:
    ButtonParser();

    const std::vector<const ActionButtonData*> parse();
};

#endif // BUTTONPARSER_H
