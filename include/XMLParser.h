#include "expat.h"

#include "parserDefs.h"

class XMLParser
{
public:
	XMLParser() =default;
	XMLParser(const XMLParser &other) =default;
	virtual ~XMLParser();
		
	bool Parse();
	
	/*typedef ElementHandlerFunction (bool (XMLParser::*(const &&XMLElement))) ;
	
	bool AddStartElementHandler(std::string elementName, ElementHandlerFunction&& func);
	bool RemoveStartElementHandler(std::string elementName);
	
	bool AddEndElementHandler(std::string elementName, ElementHandlerFunction&& func);
	bool RemoveEndElementHandler(std::string elementName);
	
	AddCharacterDataHandler(std::string elementName, CharacterDataHandlerFunction&& func);
	AddCharacterDataHandler(std::string elementName);*/
};