#include "wmi.h"
#include "util/log.h"
#include "util/va.h"
#include <comdef.h>
#include <WbemIdl.h>
#pragma comment(lib, "wbemuuid.lib")

namespace util::wmi {
	IWbemLocator* g_locator;
	IWbemServices* g_services;
	IEnumWbemClassObject* g_enumerator;

	bool load() {
		HRESULT result;

		result = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(result)) {
			LOG_ERROR(XOR("Failed to initialize service (#1)"));
			return false;
		}

		CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
		result = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&g_locator);

		if (FAILED(result)) {
			LOG_ERROR(XOR("Failed to initialize service (#2) %X"), result);
			CoUninitialize();
			return false;
		}

		result = g_locator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &g_services);
		if (FAILED(result)) {
			LOG_ERROR(XOR("Failed to initialize service (#3) %X"), result);
			g_locator->Release();
			CoUninitialize();
			return false;
		}

		result = CoSetProxyBlanket(g_services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
		if (FAILED(result)) {
			LOG_ERROR(XOR("Failed to initialize service (#4) %X"), result);
			g_services->Release();
			g_locator->Release();
			CoUninitialize();
			return false;
		}

		return true;
	}

	std::string read(std::string part, std::string property) {
		std::string output = "Error.";

		HRESULT result = g_services->ExecQuery(bstr_t("WQL"), bstr_t((std::string("SELECT * FROM ") + part).c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &g_enumerator);

		if (FAILED(result)) {
			return output;
		}

		IWbemClassObject* pclsObj = NULL;
		ULONG ret = 0;

		while (g_enumerator) {
			HRESULT hr = g_enumerator->Next(WBEM_INFINITE, 1, &pclsObj, &ret);
			if (FAILED(hr) || !ret) {
				break;
			}

			VARIANT vtProp;

			std::wstring stemp = std::wstring(property.begin(), property.end());
			LPCWSTR sw = stemp.c_str();
			hr = pclsObj->Get(sw, 0, &vtProp, 0, 0);
			if (SUCCEEDED(hr)) {
				if (vtProp.vt == VT_BSTR) {
					output = _bstr_t(vtProp.bstrVal);
				} else if (vtProp.vt == VT_I4) {
					output = std::to_string(vtProp.iVal);
				}

				VariantClear(&vtProp);
				pclsObj->Release();
				g_enumerator->Release();
			} else {
				g_enumerator->Release();
			}

			break;
		}

		return output;
	}

	void cleanup() {
		if (g_services) g_services->Release();
		if (g_locator) g_locator->Release();
		CoUninitialize();
	}
}