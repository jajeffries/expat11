#pragma once
#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace expat11
{

	typedef std::pair<std::string, std::string> Attribute;
	class XMLParser
	{
	public:
		XMLParser();
		XMLParser(const XMLParser &other) =default;
		XMLParser(XMLParser &&other) =default;
		virtual ~XMLParser();

		bool Parse(const std::string& xml) ;
		
		friend void StartElement(void *data, const char *elementName, const char **attributes);
		friend void EndElement(void *data, const char *elelemntName);

		typedef std::function< bool ( const std::vector< Attribute >& ) > StartElementHandler;
		void AddStartElementHandler( const std::string& elementName, 
					     StartElementHandler startElementHandler);
		size_t StartElementHandlerCount() const;

		typedef std::function< bool ( const std::vector< Attribute >& ) > EndElementHandler;
		void AddEndElementHandler( const std::string& elementName, 
				           EndElementHandler endElementHandler);
		size_t EndElementHandlerCount() const;

		typedef std::function< bool ( const std::string& ) > ValueHandler;
		void AddValueHandler( ValueHandler valueHandler );
		size_t ValueHandlerCount() const;

		void SetReadSize(int readSize);
		int GetReadSize() const;

	private:
		typedef	std::unordered_map< std::string, std::vector<StartElementHandler> > StartHandlerMap;
	  StartHandlerMap m_StartElementHandlers;

		std::unordered_map< std::string, std::vector<EndElementHandler> > m_EndElementHandlers;
		std::vector< ValueHandler > m_ValueHandlers;
		
		static const int DEFAULT_READSIZE; 
		int m_ReadSize;

	};

	void StoreAttributes(const char **attributes, std::vector<Attribute>& attributesVector)
	{
		for(const char* attr = *attributes; attr != NULL; ++attr)
		{
			
		}
	}

	void StartElement(void *data, const char *elementName, const char **attributes)
	{
		std::string element(elementName);
		
		std::vector<Attribute> attributesVector;
		StoreAttributes(attributes, attributesVector);

		XMLParser* pInstance = static_cast<XMLParser*>(data);
		auto handlerVectorIter = pInstance->m_StartElementHandlers.find(elementName);
		
		//TODO: Change this to arange based for loop in gcc 4.6 and above
		for(auto handlerIter = handlerVectorIter->second.cbegin();
		    handlerIter != handlerVectorIter->second.cend();
				++handlerIter)
		{
			if (!(*handlerIter)(element, attributesVector) )
			{
				//error
			}
		}

	}	

	void EndElement(void *data, const char *elementName)
	{

	}
}
#endif // XMLPARSER_H
