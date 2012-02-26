#include "expat.h"

#include "XMLParser.h"

using namespace expat11;

const int DEFAULT_READSIZE = 50;

XMLParser::XMLParser()
:m_ReadSize(DEFAULT_READSIZE)
{
}

XMLParser::~XMLParser()
{
}

bool XMLParser::Parse( const std::string& xml )
{
	XML_Parser parser = XML_ParserCreate(NULL);
	int depth = 0;
	XML_SetUserData(parser, &depth);
	XML_SetElementHandler(parser, &StartElement, &EndElement);
	
	int finished = 0;
	char buf[m_ReadSize];
	int length = 0;
	while( !finished )
	{
		if ( !XML_Parse(parser, buf, length, finished ) )
		{

		}

	}
	XML_ParserFree(parser);
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

void XMLParser::AddValueHandler( ValueHandler valueHandler )
{
	m_ValueHandlers.push_back( valueHandler );
}

size_t XMLParser::ValueHandlerCount() const
{
	return m_ValueHandlers.size();
}

void XMLParser::SetReadSize( int readSize )
{
	m_ReadSize = readSize;
}

int XMLParser::GetReadSize() const
{
	return m_ReadSize;
}
