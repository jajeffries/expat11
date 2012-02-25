#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class XMLParser
{
public:
	XMLParser() =default;
	XMLParser(const XMLParser &other) =default;
	XMLParser(XMLParser &&other) =default;
	virtual ~XMLParser();
		
	bool Parse();
	
	typedef  std::function< bool ( const std::vector< std::string >& ) > ElementHandlerFunction;
	void AddStartElementHandler( const std::string& elementName, 
	                             const ElementHandlerFunction& startElementHandler);

private:
	std::unordered_map< std::string, std::vector<ElementHandlerFunction> > m_StartElementHandlers;

};
