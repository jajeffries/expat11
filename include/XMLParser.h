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
		XMLParser() =default;
		XMLParser(const XMLParser &other) =default;
		XMLParser(XMLParser &&other) =default;
		virtual ~XMLParser();

		bool Parse(const std::string& xml) const;

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
		std::unordered_map< std::string, std::vector<StartElementHandler> > m_StartElementHandlers;

		std::unordered_map< std::string, std::vector<EndElementHandler> > m_EndElementHandlers;
		std::vector< ValueHandler > m_ValueHandlers;
		
		const static int DEFAULT_READSIZE(50);
		int m_ReadSize = DEFAULT_READSIZE;

	};
}
#endif // XMLPARSER_H
