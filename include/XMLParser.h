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
	
	typedef  std::function< bool ( const std::vector< std::string >& ) > StartElementHandler;
	void AddStartElementHandler( const std::string& elementName, 
	                             const StartElementHandler& startElementHandler);
	
	typedef  std::function< bool ( const std::vector< std::string >& ) > EndElementHandler;
	void AddEndElementHandler( const std::string& elementName, 
	                           const EndElementHandler& endElementHandler);
	
	typedef  std::function< bool ( const std::string& ) > ValueHandler;
	void AddValueHandler( const std::string& elementName, 
	                      const ValueHandler& valueHandler);



private:
	std::unordered_map< std::string, std::vector<StartElementHandler> > m_StartElementHandlers;
	
	std::unordered_map< std::string, std::vector<EndElementHandler> > m_EndElementHandlers;
	std::unordered_map< std::string, std::vector<ValueHandler> > m_ValueHandlers;
	

};
