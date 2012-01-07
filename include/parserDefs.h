#include <string>
#include <vector>

struct XMLAttribute
{
	std::string name;
	std::string value;
};

struct XMLElement
{
	std::string name;
	std::vector<XMLAttribute> attributes;
};