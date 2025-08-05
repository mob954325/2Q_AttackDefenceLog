#pragma once
#include "Datas/SoundDatas.h"
#include "Utils/StringConvert.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

/*
// 25.08.05 | 작성자 : 김정현
csv에 , 를 기준으로 끊어서 저장
\"\" 와 같은 불필요한 값을 읽었을때 SetData에서 제거하는 함수 구현으로 제거 ( LoadCSV는 CSV파일을 정말 읽기만해서 던져주는 역할 )
int 매개변수(스킵할 줄수)를 던져줘서 몇번째줄 부터 읽도록 할 수 있음
*/
template<typename T >
struct LoadCSV
{
	static void SetCSV(const std::wstring& path, std::vector<T>& outList, int skipLine = 1) {
		std::ifstream file(path);
		if (!file.is_open()) {
			std::wcerr << "파일 열기 실패: " << path << std::endl;
			return;
		}

		std::string line;
		int countLine = 0;


		while (std::getline(file, line)) {
			if (countLine++ < skipLine) continue;

			std::wstring wline = StringConvert::UTF8ToWString(line);
			std::wstringstream ss(wline);
			std::wstring cell;
			std::vector<std::wstring> row;

			while (std::getline(ss, cell, L',')) 
			{
				row.push_back(cell);
			}

			T tmpData;
			tmpData.SetData(row);
			outList.push_back(tmpData);
		}

		file.close();
	}
};