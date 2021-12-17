#pragma once

extern "C" bool __declspec(dllexport) InitExcelOLE();
extern "C" void __declspec(dllexport) ReleaseExcelOLE();

extern "C" bool __declspec(dllexport) OpenExcel(const char* fileName);
extern "C" void __declspec(dllexport) CloseExcel();

extern "C" bool __declspec(dllexport) LoadSheetByIndex(long sheetIndex);
extern "C" bool __declspec(dllexport) LoadSheetByName(char *sheetName);

extern "C" __declspec(dllexport) int GetRowCount();
extern "C" __declspec(dllexport) int GetColumnCount();

extern "C" __declspec(dllexport) char* GetCellString(long iRow, long iColumn);
extern "C" __declspec(dllexport) int GetCellInt(long iRow, long iColumn);
extern "C" __declspec(dllexport) double GetCellDouble(long iRow, long iColumn);
	
