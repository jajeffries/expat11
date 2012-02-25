#include "expat.h"

#include "XMLParser.h"

using namespace expat11;

XMLParser::~XMLParser(){}

bool Parse()
{
	return true;
}

void XMLParser::AddStartElementHandler( const std::string& elementName, 
                                        StartElementHandler startElementHandler)
{
	m_StartElementHandlers[ elementName ].push_back( startElementHandler );
}

size_t XMLParser::StartElementHandlerCount() const
{
	return m_StartElementHandlers.size();
}

void XMLParser::AddEndElementHandler( const std::string& elementName, 
                                      EndElementHandler endElementHandler)
{
	m_EndElementHandlers[ elementName ].push_back( endElementHandler );
}

size_t XMLParser::EndElementHandlerCount() const
{
	return m_EndElementHandlers.size();
}

void XMLParser::AddValueHandler( const std::string& elementName, 
                                 ValueHandler valueHandler)
{
	m_ValueHandlers[ elementName ].push_back( valueHandler );
}

size_t XMLParser::ValueHandlerCount() const
{
	return m_ValueHandlers.size();
}

int main(){}
