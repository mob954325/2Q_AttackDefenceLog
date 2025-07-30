#pragma once
//#include "Utils/Singleton.h"
//#include "DataStorage/BaseData.h"
#include <unordered_map>
#include <string>

class NodeData
{

public:
	class NodeList
	{
	private:
		int node01 = 0;
		int node02 = 0;
		int node03 = 0;
		int node04 = 0;
		int node05 = 0;
		int node06 = 0;
		int node07 = 0;
		int node08 = 0;
		int node09 = 0;

	public:
		void SetData(std::vector<std::wstring> tmp);
		int GetData(std::wstring name);
	};

	const NodeList& GetNodeData(std::wstring ID);
	

private:
	std::unordered_map<std::wstring, NodeList> DataMap;
	/*std::unordered_map<std::wstring, NodeList*> DataMap;*/

};

