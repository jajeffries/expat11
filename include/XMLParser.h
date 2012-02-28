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
		friend void ValueData(void *data, const char *characterData, int length);
		
		typedef std::function< bool ( std::vector< Attribute > ) > StartElementHandler;
		void AddStartElementHandler( const std::string& elementName, 
					     StartElementHandler startElementHandler);
		size_t StartElementHandlerCount() const;

		typedef std::function< bool ( void ) > EndElementHandler;
		void AddEndElementHandler( const std::string& elementName, 
				           EndElementHandler endElementHandler);
		size_t EndElementHandlerCount() const;

		typedef std::function< bool ( const std::string& ) > ValueHandler;
		void AddValueHandler( const std::string& elementName, ValueHandler valueHandler );
		size_t ValueHandlerCount() const;

		void SetReadSize(int readSize);
		int GetReadSize() const;
		
		void SetCurrentElement(const std::string& currentElement);
		const std::string& GetCurrentElement() const;
	private:
		typedef	std::unordered_map< std::string, std::vector<StartElementHandler> > StartHandlerMap;
	  StartHandlerMap m_StartElementHandlers;

		std::unordered_map< std::string, std::vector<EndElementHandler> > m_EndElementHandlers;
		std::unordered_map<std::string, std::vector< ValueHandler >> m_ValueHandlers;
		
		static const int DEFAULT_READSIZE; 
		int m_ReadSize;
		std::string m_CurrentElement;

	};

	void StoreAttributes(const char **attributes, std::vector<Attribute>& attributesVector)
	{
		for(const char* attr = *attributes; attr != NULL; ++attr)
		{
			attributesVector.push_back( std::make_pair<std::string, std::string>( attr, ++attr ));
		}
	}
	
	//TODO: see if I could template these instead?
	void StartElement(void *data, const char *elementName, const char **attributes)
	{
		XMLParser* pInstance = static_cast<XMLParser*>(data);
		auto handlerVectorIter = pInstance->m_StartElementHandlers.find(elementName);
		pInstance->SetCurrentElement(elementName);
		
		std::vector<Attribute> attributesVector;
		StoreAttributes(attributes, attributesVector);


		//TODO: Change this to a range based for loop in gcc 4.6 and above
		for(auto handlerIter = handlerVectorIter->second.cbegin();
		    handlerIter != handlerVectorIter->second.cend();
				++handlerIter)
		{
			if (!(*handlerIter)( attributesVector ))
			{
				//error
			}
		}

	}	

	void EndElement(void *data, const char *elementName)
	{
		XMLParser* pInstance = static_cast<XMLParser*>(data);
		auto handlerVectorIter = pInstance->m_EndElementHandlers.find(elementName);
		
		//TODO: Change this to a range based for loop in gcc 4.6 and above
		for(auto handlerIter = handlerVectorIter->second.cbegin();
		    handlerIter != handlerVectorIter->second.cend();
				++handlerIter)
		{
			if (!(*handlerIter)())
			{
				//error
			}
		}
	}
	
	void ValueData(void *data, const char *characterData, int length)
	{
		XMLParser* pInstance = static_cast<XMLParser*>(data);
		auto handlerVectorIter = pInstance->m_ValueHandlers.find(pInstance->GetCurrentElement());
		
		//TODO: Change this to a range based for loop in gcc 4.6 and above
		for(auto handlerIter = handlerVectorIter->second.cbegin();
		    handlerIter != handlerVectorIter->second.cend();
				++handlerIter)
		{
			if (!(*handlerIter)( characterData ))
			{
				//error
			}
		}
	}
}
#endif // XMLPARSER_H
