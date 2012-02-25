#include "expat.h"

#include "XMLParser.h"

XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
}

bool Parse()
{
	return true;
}

void XMLParser::AddStartElementHandler( const std::string& elementName, 
                                        const ElementHandlerFunction& startElementHandler)
{
	m_StartElementHandlers[ elementName ].push_back( startElementHandler );
}


int main(){}
