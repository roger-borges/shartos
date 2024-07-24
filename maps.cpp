#include "scripting.h"

//String* to char* conversion macro
char* convertToChars1(String* convert_this)
{return (char *) Marshal::StringToHGlobalAnsi(convert_this).ToPointer();}



maps::maps(String* dir_file_name)
{
	directory=new char();
	try
	{
		XmlTextReader* xmlreader = new XmlTextReader(dir_file_name);
		while(xmlreader->Read())//xmlreader->NodeType!=XmlNodeType::EndElement && xmlreader->Name!=S"worlds")
		{
			//xmlreader->Read();
			if(String::Compare(xmlreader->Name,S"dir")==0 && xmlreader->NodeType==XmlNodeType::Element)
			{
				xmlreader->Read();
				//directory=xmlreader->GetAttribute(S"location");
				directory=convertToChars1(xmlreader->Value);
			}
			else if(String::Compare(xmlreader->Name,S"map")==0 && xmlreader->NodeType==XmlNodeType::Element)
			{
				maps_list.push_back(convertToChars1(xmlreader->GetAttribute("location")));
				xmlreader->Read();
				maps_name_list.push_back(convertToChars1(xmlreader->Value));


			}
		}
	}
	catch (Exception* ex)
	{
		//Console::Write(ex->Message);Console::WriteLine(S" Load World Error");
	}
}