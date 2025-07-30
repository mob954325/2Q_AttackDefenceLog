#include "NodeData.h"
#include "Utils/StringConvert.h"


void NodeData::NodeList::SetData(std::vector<std::wstring> tmp)
{
	int* members[9] = {
			&node01, &node02, &node03, &node04, &node05,
			&node06, &node07, &node08, &node09
	};

	for (size_t i = 0; i < 9 && i < tmp.size(); ++i) {
		if (tmp[i] == L"null")
		{
			*members[i] = 0;
		}
		else 
		{
			*members[i] = std::stoi(tmp[i]);
		}
	}
}

//int NodeData::NodeList::GetData(std::wstring name)
//{
//	std::string nameC = StringConvert::WstringToString(name);
//	return this->nameC;
//}


 const NodeData::NodeList& NodeData::GetNodeData(std::wstring ID)
{
	 return DataMap.at(ID);
}
