// EsteidShlExt.cpp : Implementation of CEsteidShlExt

#include "stdafx.h"
#include "EsteidShlExt.h"


CEsteidShlExt::CEsteidShlExt()
{
	m_DigidocBmp = LoadBitmap(_AtlBaseModule.GetModuleInstance(),
	                           MAKEINTRESOURCE(IDB_DIGIDOCBMP));
}

CEsteidShlExt::~CEsteidShlExt()
{
	DeleteObject(m_DigidocBmp);
}

STDMETHODIMP CEsteidShlExt::Initialize(
	LPCITEMIDLIST /* pidlFolder */, LPDATAOBJECT pDataObj, HKEY /* hProgID */)
{
	FORMATETC fmt = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	m_Files.clear();

	// Look for CF_HDROP data in the data object.
	if (FAILED(pDataObj->GetData(&fmt, &stg))) {
		// Nope! Return an "invalid argument" error back to Explorer.
		return E_INVALIDARG;
	}

	// Get a pointer to the actual data.
	HDROP hDrop = HDROP(GlobalLock(stg.hGlobal));
	if (!hDrop) {
		ReleaseStgMedium(&stg);
		return E_INVALIDARG;
	}

	// Sanity check - make sure there is at least one filename.
	UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
	if (nFiles == 0) {
		GlobalUnlock(stg.hGlobal);
		ReleaseStgMedium(&stg);
		return E_INVALIDARG;
	}

	for (UINT i = 0; i < nFiles; i++) {
		// Get path length in chars
		UINT len = DragQueryFile(hDrop, i, nullptr, 0);
		if (len == 0 || len >= MAX_PATH)
			continue;

		// Get the name of the file
		TCHAR szFile[MAX_PATH];
		if (DragQueryFile(hDrop, i, szFile, len+1) == 0)
			continue;

		tstring str = tstring(szFile);
		if (str.empty())
			continue;

		m_Files.push_back(str);
	}

	GlobalUnlock(stg.hGlobal);
	ReleaseStgMedium(&stg);

	// Don't show menu if no items were found
	return m_Files.empty() ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CEsteidShlExt::QueryContextMenu(
	HMENU hmenu, UINT uMenuIndex, UINT uidFirstCmd,
	UINT /* uidLastCmd */, UINT uFlags)
{
	// If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
	if (uFlags & CMF_DEFAULTONLY)
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);

	PCTCH sign = _T("Sign digitally");
	PCTCH encrypt = _T("Encrypt");
	switch (PRIMARYLANGID(GetUserDefaultUILanguage()))
	{
	case LANG_ESTONIAN:
		sign = _T("Allkirjasta digitaalselt");
		encrypt = _T("Krüpteeri");
		break;
	case LANG_RUSSIAN:
		sign = _T("Подписать дигитально");
		encrypt = _T("Зашифровать");
		break;
	default: break;
	}

	InsertMenu(hmenu, uMenuIndex, MF_STRING | MF_BYPOSITION, uidFirstCmd, sign);
	if (m_DigidocBmp)
		SetMenuItemBitmaps(hmenu, uMenuIndex, MF_BYPOSITION, m_DigidocBmp, nullptr);
	InsertMenu(hmenu, uMenuIndex + MENU_ENCRYPT, MF_STRING | MF_BYPOSITION, uidFirstCmd + MENU_ENCRYPT, encrypt);
	if (m_DigidocBmp)
		SetMenuItemBitmaps(hmenu, uMenuIndex + MENU_ENCRYPT, MF_BYPOSITION, m_DigidocBmp, nullptr);

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 2);
}

STDMETHODIMP CEsteidShlExt::GetCommandString(
	UINT_PTR idCmd, UINT uFlags, UINT * /* pwReserved */, LPSTR pszName, UINT cchMax)
{
	USES_CONVERSION;

	// Check idCmd, it must be 0 or 1 since we have only two menu items.
	if (idCmd > MENU_ENCRYPT)
		return E_INVALIDARG;

	// If Explorer is asking for a help string, copy our string into the
	// supplied buffer.
	if (uFlags & GCS_HELPTEXT) {
		LPCTSTR szText = idCmd == MENU_SIGN ? _T("Allkirjasta valitud failid digitaalselt") : _T("Krüpteeri valitud failid");

		if (uFlags & GCS_UNICODE) {
			// We need to cast pszName to a Unicode string, and then use the
			// Unicode string copy API.
			lstrcpynW(LPWSTR(pszName), T2CW(szText), int(cchMax));
		} else {
			// Use the ANSI string copy API to return the help string.
			lstrcpynA(pszName, T2CA(szText), int(cchMax));
		}

		return S_OK;
	}

	return E_INVALIDARG;
}

bool WINAPI CEsteidShlExt::FindRegistryInstallPath(tstring* path)
{
	static PCTCH IDCARD_REGKEY = _T("SOFTWARE\\RIA\\Open-EID");
	static PCTCH IDCARD_REGVALUE = _T("Installed");
	HKEY hkey;
	DWORD dwSize = MAX_PATH * sizeof(TCHAR);
	TCHAR szInstalldir[MAX_PATH];
	LSTATUS dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, IDCARD_REGKEY, 0, KEY_QUERY_VALUE, &hkey);
	if (dwRet == ERROR_SUCCESS) {
		dwRet = RegQueryValueEx(hkey, IDCARD_REGVALUE, nullptr, nullptr, LPBYTE(szInstalldir), &dwSize);
		RegCloseKey(hkey);
		*path = tstring(szInstalldir);
		return true;
	}
	dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, IDCARD_REGKEY, 0, KEY_QUERY_VALUE, &hkey);
	if (dwRet == ERROR_SUCCESS) {
		RegCloseKey(hkey);
		*path = tstring(szInstalldir);
		return true;
	}
	return false;
}

STDMETHODIMP CEsteidShlExt::ExecuteDigidocclient(LPCMINVOKECOMMANDINFO /* pCmdInfo */, bool crypto)
{
	if (m_Files.empty())
		return E_INVALIDARG;

	tstring path(MAX_PATH, 0);
	tstring command(MAX_PATH, 0);

	// Read the location of the installation from registry
	if (!FindRegistryInstallPath(&path)) {
		// .. and fall back to directory where shellext resides if not found from registry 
		GetModuleFileName(_AtlBaseModule.m_hInst, &path[0], MAX_PATH);
		path.resize(path.find_last_of(_T('\\')) + 1);
	}

	// First try with DigiDoc4 Client and then with DigiDoc3
	for(auto program : {_T("qdigidoc4.exe"), _T("qdigidocclient.exe")})
	{
		command = path + program;
		if(PathFileExists(command.c_str()) == 1)
			break;

		// Replace "c:\Program Files\" with "c:\Program Files (x86)\"
		command.insert(16, _T(" (x86)"));
		if(PathFileExists(command.c_str()) == 1)
			break;
	}

	// Construct command line arguments to pass to qdigidocclient.exe
	tstring parameters = crypto ? _T("\"-crypto\" ") : _T("\"-sign\" ");
	for (const tstring &file: m_Files)
		parameters += _T("\"") + file + _T("\" ");

	SHELLEXECUTEINFO  seInfo = { sizeof(SHELLEXECUTEINFO) };
	seInfo.lpFile       = command.c_str();
	seInfo.lpParameters = parameters.c_str();
	seInfo.nShow        = SW_SHOW;
	return ShellExecuteEx(&seInfo) ? S_OK : S_FALSE;
}

STDMETHODIMP CEsteidShlExt::InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo)
{
	// If lpVerb really points to a string, ignore this function call and bail out.
	if (HIWORD(pCmdInfo->lpVerb) != 0)
		return E_INVALIDARG;

	// Get the command index - the valid ones are 0 and 1.
	switch (LOWORD(pCmdInfo->lpVerb)) {
	case MENU_SIGN:
		return ExecuteDigidocclient(pCmdInfo);
	case MENU_ENCRYPT:
		return ExecuteDigidocclient(pCmdInfo, true);
	default:
		return E_INVALIDARG;
	}
}
