#pragma once

#include "stdafx.h"

using floatN = XMVECTOR;
using float4 = XMFLOAT4;
using float3 = XMFLOAT3;
using float2 = XMFLOAT2;
using float4x4 = XMMATRIX;

enum class VertexFormat
{
	UNDEFINED,
	POSITION,
	POSITION_TEXCOORD,
	POSITION_NORMAL,
	POSITION_NORMAL_TEXCOORD
};

inline void ThrowIfFailed(bool successCondition, const char* errorMessage)
{
	if (!successCondition)
		throw std::exception(errorMessage);
}

inline void ConvertWCharStringToCharString(const PWSTR wcString, std::shared_ptr<char[]>& cString)
{
	size_t wcFilePathLength = wcslen(wcString);

	cString = std::shared_ptr<char[]>(new char[wcFilePathLength + 1]);

	cString[wcFilePathLength] = '\0';

	WideCharToMultiByte(CP_UTF8, 0, wcString, wcFilePathLength, cString.get(), wcFilePathLength, nullptr, nullptr);
}

inline void GetFilePathFromDialog(std::string& filePath)
{
	ThrowIfFailed(SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)),
		"GetFilePathFromDialog: COM Library does not initialized!");

	ComPtr<IFileOpenDialog> fileOpenDialog;

	ThrowIfFailed(SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(fileOpenDialog.GetAddressOf()))),
		"GetFilePathFromDialog: FileOpenDialog does not created!");

	COMDLG_FILTERSPEC filterSpec[] =
	{
		{ L"Bitmap", L"*.bmp" },
	};

	fileOpenDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);

	ThrowIfFailed(SUCCEEDED(fileOpenDialog->Show(nullptr)), "GetFilePathFromDialog: Dialog window does not show!");

	ComPtr<IShellItem> shellItem;

	ThrowIfFailed(SUCCEEDED(fileOpenDialog->GetResult(shellItem.GetAddressOf())), "GetFilePathFromDialog: Result does not received!");
	
	PWSTR wcFilePath;
	
	ThrowIfFailed(SUCCEEDED(shellItem->GetDisplayName(SIGDN_FILESYSPATH, &wcFilePath)), "GetFilePathFromDialog: File path does not created!");
	
	std::shared_ptr<char[]> cFilePath;

	ConvertWCharStringToCharString(wcFilePath, cFilePath);

	filePath = cFilePath.get();

	CoTaskMemFree(wcFilePath);

	CoUninitialize();
}
