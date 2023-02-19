#ifdef _MSC_VER
#pragma once
#endif

#include <d3d11.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#pragma warning(pop)

HRESULT create_wic_texture_from_memory(ID3D11Device* d3dDevice, const uint8_t* wicData, size_t wicDataSize, ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t maxsize = 0);
HRESULT create_wic_texture_from_file(ID3D11Device* d3dDevice, const wchar_t* szFileName, ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t maxsize = 0);
HRESULT create_dds_texture_from_memory(ID3D11Device* d3dDevice, const byte* ddsData, size_t ddsDataSize, ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t maxsize = 0);