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
                                        const StartElementHandler& startElementHandler)
{
	m_StartElementHandlers[ elementName ].push_back( startElementHandler );
}

void XMLParser::AddEndElementHandler( const std::string& elementName, 
                                      const EndElementHandler& endElementHandler)
{
	m_EndElementHandlers[ elementName ].push_back( endElementHandler );
}

void XMLParser::AddValueHandler( const std::string& elementName, 
                                 const ValueHandler& valueHandler)
{
	m_ValueHandlers[ elementName ].push_back( valueHandler );
}


int main(){}
