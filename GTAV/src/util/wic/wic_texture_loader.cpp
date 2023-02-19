#include <dxgiformat.h>
#include <assert.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <wincodec.h>
#pragma warning(pop)

#include <memory>

#include "wic_texture_loader.h"

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && !defined(DXGI_1_2_FORMATS)
#define DXGI_1_2_FORMATS
#endif

//---------------------------------------------------------------------------------
template<class T> class ScopedObject
{
public:
    explicit ScopedObject( T *p = 0 ) : _pointer(p) {}
    ~ScopedObject()
    {
        if ( _pointer )
        {
            _pointer->Release();
            _pointer = nullptr;
        }
    }

    bool IsNull() const { return (!_pointer); }

    T& operator*() { return *_pointer; }
    T* operator->() { return _pointer; }
    T** operator&() { return &_pointer; }

    void Reset(T *p = 0) { if ( _pointer ) { _pointer->Release(); } _pointer = p; }

    T* Get() const { return _pointer; }

private:
    ScopedObject(const ScopedObject&);
    ScopedObject& operator=(const ScopedObject&);
        
    T* _pointer;
};

//-------------------------------------------------------------------------------------
// WIC Pixel Format Translation Data
//-------------------------------------------------------------------------------------
struct WICTranslate
{
    GUID                wic;
    DXGI_FORMAT         format;
};

static WICTranslate g_WICFormats[] = 
{
    { GUID_WICPixelFormat128bppRGBAFloat,       DXGI_FORMAT_R32G32B32A32_FLOAT },

    { GUID_WICPixelFormat64bppRGBAHalf,         DXGI_FORMAT_R16G16B16A16_FLOAT },
    { GUID_WICPixelFormat64bppRGBA,             DXGI_FORMAT_R16G16B16A16_UNORM },

    { GUID_WICPixelFormat32bppRGBA,             DXGI_FORMAT_R8G8B8A8_UNORM },
    { GUID_WICPixelFormat32bppBGRA,             DXGI_FORMAT_B8G8R8A8_UNORM }, // DXGI 1.1
    { GUID_WICPixelFormat32bppBGR,              DXGI_FORMAT_B8G8R8X8_UNORM }, // DXGI 1.1

    { GUID_WICPixelFormat32bppRGBA1010102XR,    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM }, // DXGI 1.1
    { GUID_WICPixelFormat32bppRGBA1010102,      DXGI_FORMAT_R10G10B10A2_UNORM },
    { GUID_WICPixelFormat32bppRGBE,             DXGI_FORMAT_R9G9B9E5_SHAREDEXP },

#ifdef DXGI_1_2_FORMATS

    { GUID_WICPixelFormat16bppBGRA5551,         DXGI_FORMAT_B5G5R5A1_UNORM },
    { GUID_WICPixelFormat16bppBGR565,           DXGI_FORMAT_B5G6R5_UNORM },

#endif // DXGI_1_2_FORMATS

    { GUID_WICPixelFormat32bppGrayFloat,        DXGI_FORMAT_R32_FLOAT },
    { GUID_WICPixelFormat16bppGrayHalf,         DXGI_FORMAT_R16_FLOAT },
    { GUID_WICPixelFormat16bppGray,             DXGI_FORMAT_R16_UNORM },
    { GUID_WICPixelFormat8bppGray,              DXGI_FORMAT_R8_UNORM },

    { GUID_WICPixelFormat8bppAlpha,             DXGI_FORMAT_A8_UNORM },

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
    { GUID_WICPixelFormat96bppRGBFloat,         DXGI_FORMAT_R32G32B32_FLOAT },
#endif
};

//-------------------------------------------------------------------------------------
// WIC Pixel Format nearest conversion table
//-------------------------------------------------------------------------------------

struct WICConvert
{
    GUID        source;
    GUID        target;
};

static WICConvert g_WICConvert[] = 
{
    // Note target GUID in this conversion table must be one of those directly supported formats (above).

    { GUID_WICPixelFormatBlackWhite,            GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM

    { GUID_WICPixelFormat1bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat2bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat4bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat8bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 

    { GUID_WICPixelFormat2bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 
    { GUID_WICPixelFormat4bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 

    { GUID_WICPixelFormat16bppGrayFixedPoint,   GUID_WICPixelFormat16bppGrayHalf }, // DXGI_FORMAT_R16_FLOAT 
    { GUID_WICPixelFormat32bppGrayFixedPoint,   GUID_WICPixelFormat32bppGrayFloat }, // DXGI_FORMAT_R32_FLOAT 

#ifdef DXGI_1_2_FORMATS

    { GUID_WICPixelFormat16bppBGR555,           GUID_WICPixelFormat16bppBGRA5551 }, // DXGI_FORMAT_B5G5R5A1_UNORM

#else

    { GUID_WICPixelFormat16bppBGR555,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
    { GUID_WICPixelFormat16bppBGRA5551,         GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
    { GUID_WICPixelFormat16bppBGR565,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM

#endif // DXGI_1_2_FORMATS

    { GUID_WICPixelFormat32bppBGR101010,        GUID_WICPixelFormat32bppRGBA1010102 }, // DXGI_FORMAT_R10G10B10A2_UNORM

    { GUID_WICPixelFormat24bppBGR,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat24bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat32bppPBGRA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat32bppPRGBA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 

    { GUID_WICPixelFormat48bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat48bppBGR,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat64bppBGRA,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat64bppPRGBA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat64bppPBGRA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM

    { GUID_WICPixelFormat48bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
    { GUID_WICPixelFormat48bppBGRFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
    { GUID_WICPixelFormat64bppRGBAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
    { GUID_WICPixelFormat64bppBGRAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
    { GUID_WICPixelFormat64bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
    { GUID_WICPixelFormat64bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
    { GUID_WICPixelFormat48bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 

    { GUID_WICPixelFormat96bppRGBFixedPoint,    GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
    { GUID_WICPixelFormat128bppPRGBAFloat,      GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
    { GUID_WICPixelFormat128bppRGBFloat,        GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
    { GUID_WICPixelFormat128bppRGBAFixedPoint,  GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
    { GUID_WICPixelFormat128bppRGBFixedPoint,   GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 

    { GUID_WICPixelFormat32bppCMYK,             GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat64bppCMYK,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat40bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat80bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
    { GUID_WICPixelFormat32bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
    { GUID_WICPixelFormat64bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
    { GUID_WICPixelFormat64bppPRGBAHalf,        GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
#endif

    // We don't support n-channel formats
};

//--------------------------------------------------------------------------------------
static IWICImagingFactory* _GetWIC()
{
    static IWICImagingFactory* s_Factory = nullptr;

    if ( s_Factory )
        return s_Factory;

    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(IWICImagingFactory),
        (LPVOID*)&s_Factory
        );

    if ( FAILED(hr) )
    {
        s_Factory = nullptr;
        return nullptr;
    }

    return s_Factory;
}

//---------------------------------------------------------------------------------
static DXGI_FORMAT _WICToDXGI( const GUID& guid )
{
    for( size_t i=0; i < _countof(g_WICFormats); ++i )
    {
        if ( memcmp( &g_WICFormats[i].wic, &guid, sizeof(GUID) ) == 0 )
            return g_WICFormats[i].format;
    }

    return DXGI_FORMAT_UNKNOWN;
}

//---------------------------------------------------------------------------------
static size_t _WICBitsPerPixel( REFGUID targetGuid )
{
    IWICImagingFactory* pWIC = _GetWIC();
    if ( !pWIC )
        return 0;
 
    ScopedObject<IWICComponentInfo> cinfo;
    if ( FAILED( pWIC->CreateComponentInfo( targetGuid, &cinfo ) ) )
        return 0;

    WICComponentType type;
    if ( FAILED( cinfo->GetComponentType( &type ) ) )
        return 0;

    if ( type != WICPixelFormat )
        return 0;

    ScopedObject<IWICPixelFormatInfo> pfinfo;
    if ( FAILED( cinfo->QueryInterface( __uuidof(IWICPixelFormatInfo), reinterpret_cast<void**>( &pfinfo )  ) ) )
        return 0;

    UINT bpp;
    if ( FAILED( pfinfo->GetBitsPerPixel( &bpp ) ) )
        return 0;

    return bpp;
}

//---------------------------------------------------------------------------------
static HRESULT CreateTextureFromWIC( _In_ ID3D11Device* d3dDevice,
                                     _In_opt_ ID3D11DeviceContext* d3dContext,
                                     _In_ IWICBitmapFrameDecode *frame,
                                     _Out_opt_ ID3D11Resource** texture,
                                     _Out_opt_ ID3D11ShaderResourceView** textureView,
                                     _In_ size_t maxsize )
{
    UINT width, height;
    HRESULT hr = frame->GetSize( &width, &height );
    if ( FAILED(hr) )
        return hr;

    if ( !maxsize )
    {
        // This is a bit conservative because the hardware could support larger textures than
        // the Feature Level defined minimums, but doing it this way is much easier and more
        // performant for WIC than the 'fail and retry' model used by DDSTextureLoader

        switch( d3dDevice->GetFeatureLevel() )
        {
            case D3D_FEATURE_LEVEL_9_1:
            case D3D_FEATURE_LEVEL_9_2:
                maxsize = 2048 /*D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION*/;
                break;

            case D3D_FEATURE_LEVEL_9_3:
                maxsize = 4096 /*D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION*/;
                break;

            case D3D_FEATURE_LEVEL_10_0:
            case D3D_FEATURE_LEVEL_10_1:
                maxsize = 8192 /*D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION*/;
                break;

            default:
                maxsize = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
                break;
        }
    }

    UINT twidth, theight;
    if ( width > maxsize || height > maxsize )
    {
        float ar = static_cast<float>(height) / static_cast<float>(width);
        if ( width > height )
        {
            twidth = static_cast<UINT>( maxsize );
            theight = static_cast<UINT>( static_cast<float>(maxsize) * ar );
        }
        else
        {
            theight = static_cast<UINT>( maxsize );
            twidth = static_cast<UINT>( static_cast<float>(maxsize) / ar );
        }
    }
    else
    {
        twidth = width;
        theight = height;
    }

    // Determine format
    WICPixelFormatGUID pixelFormat;
    hr = frame->GetPixelFormat( &pixelFormat );
    if ( FAILED(hr) )
        return hr;

    WICPixelFormatGUID convertGUID;
    memcpy( &convertGUID, &pixelFormat, sizeof(WICPixelFormatGUID) );

    size_t bpp = 0;

    DXGI_FORMAT format = _WICToDXGI( pixelFormat );
    if ( format == DXGI_FORMAT_UNKNOWN )
    {
        for( size_t i=0; i < _countof(g_WICConvert); ++i )
        {
            if ( memcmp( &g_WICConvert[i].source, &pixelFormat, sizeof(WICPixelFormatGUID) ) == 0 )
            {
                memcpy( &convertGUID, &g_WICConvert[i].target, sizeof(WICPixelFormatGUID) );

                format = _WICToDXGI( g_WICConvert[i].target );
                bpp = _WICBitsPerPixel( convertGUID );
                break;
            }
        }

        if ( format == DXGI_FORMAT_UNKNOWN )
            return HRESULT_FROM_WIN32( ERROR_NOT_SUPPORTED );
    }
    else
    {
        bpp = _WICBitsPerPixel( pixelFormat );
    }

    if ( !bpp )
        return E_FAIL;

    // Verify our target format is supported by the current device
    // (handles WDDM 1.0 or WDDM 1.1 device driver cases as well as DirectX 11.0 Runtime without 16bpp format support)
    UINT support = 0;
    hr = d3dDevice->CheckFormatSupport( format, &support );
    if ( FAILED(hr) || !(support & D3D11_FORMAT_SUPPORT_TEXTURE2D) )
    {
        // Fallback to RGBA 32-bit format which is supported by all devices
        memcpy( &convertGUID, &GUID_WICPixelFormat32bppRGBA, sizeof(WICPixelFormatGUID) );
        format = DXGI_FORMAT_R8G8B8A8_UNORM;
        bpp = 32;
    }

    // Allocate temporary memory for image
    size_t rowPitch = ( twidth * bpp + 7 ) / 8;
    size_t imageSize = rowPitch * theight;

    std::unique_ptr<uint8_t[]> temp( new uint8_t[ imageSize ] );

    // Load image data
    if ( memcmp( &convertGUID, &pixelFormat, sizeof(GUID) ) == 0
         && twidth == width
         && theight == height )
    {
        // No format conversion or resize needed
        hr = frame->CopyPixels( 0, static_cast<UINT>( rowPitch ), static_cast<UINT>( imageSize ), temp.get() );  
        if ( FAILED(hr) )
            return hr;
    }
    else if ( twidth != width || theight != height )
    {
        // Resize
        IWICImagingFactory* pWIC = _GetWIC();
        if ( !pWIC )
            return E_NOINTERFACE;

        ScopedObject<IWICBitmapScaler> scaler;
        hr = pWIC->CreateBitmapScaler( &scaler );
        if ( FAILED(hr) )
            return hr;

        hr = scaler->Initialize( frame, twidth, theight, WICBitmapInterpolationModeFant );
        if ( FAILED(hr) )
            return hr;

        WICPixelFormatGUID pfScaler;
        hr = scaler->GetPixelFormat( &pfScaler );
        if ( FAILED(hr) )
            return hr;

        if ( memcmp( &convertGUID, &pfScaler, sizeof(GUID) ) == 0 )
        {
            // No format conversion needed
            hr = scaler->CopyPixels( 0, static_cast<UINT>( rowPitch ), static_cast<UINT>( imageSize ), temp.get() );  
            if ( FAILED(hr) )
                return hr;
        }
        else
        {
            ScopedObject<IWICFormatConverter> FC;
            hr = pWIC->CreateFormatConverter( &FC );
            if ( FAILED(hr) )
                return hr;

            hr = FC->Initialize( scaler.Get(), convertGUID, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom );
            if ( FAILED(hr) )
                return hr;

            hr = FC->CopyPixels( 0, static_cast<UINT>( rowPitch ), static_cast<UINT>( imageSize ), temp.get() );  
            if ( FAILED(hr) )
                return hr;
        }
    }
    else
    {
        // Format conversion but no resize
        IWICImagingFactory* pWIC = _GetWIC();
        if ( !pWIC )
            return E_NOINTERFACE;

        ScopedObject<IWICFormatConverter> FC;
        hr = pWIC->CreateFormatConverter( &FC );
        if ( FAILED(hr) )
            return hr;

        hr = FC->Initialize( frame, convertGUID, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom );
        if ( FAILED(hr) )
            return hr;

        hr = FC->CopyPixels( 0, static_cast<UINT>( rowPitch ), static_cast<UINT>( imageSize ), temp.get() );  
        if ( FAILED(hr) )
            return hr;
    }

    // See if format is supported for auto-gen mipmaps (varies by feature level)
    bool autogen = false;
    if ( d3dContext != 0 && textureView != 0 ) // Must have context and shader-view to auto generate mipmaps
    {
        UINT fmtSupport = 0;
        hr = d3dDevice->CheckFormatSupport( format, &fmtSupport );
        if ( SUCCEEDED(hr) && ( fmtSupport & D3D11_FORMAT_SUPPORT_MIP_AUTOGEN ) )
        {
            autogen = true;
        }
    }

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    desc.Width = twidth;
    desc.Height = theight;
    desc.MipLevels = (autogen) ? 0 : 1;
    desc.ArraySize = 1;
    desc.Format = format;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = (autogen) ? (D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET) : (D3D11_BIND_SHADER_RESOURCE);
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = (autogen) ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

    D3D11_SUBRESOURCE_DATA initData;
    initData.pSysMem = temp.get();
    initData.SysMemPitch = static_cast<UINT>( rowPitch );
    initData.SysMemSlicePitch = static_cast<UINT>( imageSize );

    ID3D11Texture2D* tex = nullptr;
    hr = d3dDevice->CreateTexture2D( &desc, (autogen) ? nullptr : &initData, &tex );
    if ( SUCCEEDED(hr) && tex != 0 )
    {
        if (textureView != 0)
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
            memset( &SRVDesc, 0, sizeof( SRVDesc ) );
            SRVDesc.Format = format;
            SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            SRVDesc.Texture2D.MipLevels = (autogen) ? -1 : 1;

            hr = d3dDevice->CreateShaderResourceView( tex, &SRVDesc, textureView );
            if ( FAILED(hr) )
            {
                tex->Release();
                return hr;
            }

            if ( autogen )
            {
                d3dContext->UpdateSubresource( tex, 0, nullptr, temp.get(), static_cast<UINT>(rowPitch), static_cast<UINT>(imageSize) );
                d3dContext->GenerateMips( *textureView );
            }
        }

        if (texture != 0)
        {
            *texture = tex;
        }
        else
        {
#if defined(_DEBUG) || defined(PROFILE)
            tex->SetPrivateData( WKPDID_D3DDebugObjectName,
                                 sizeof("WICTextureLoader")-1,
                                 "WICTextureLoader"
                               );
#endif
            tex->Release();
        }
    }

    return hr;
}

//--------------------------------------------------------------------------------------
HRESULT create_wic_texture_from_memory( _In_ ID3D11Device* d3dDevice,
                                    _In_bytecount_(wicDataSize) const uint8_t* wicData,
                                    _In_ size_t wicDataSize,
                                    _Out_opt_ ID3D11Resource** texture,
                                    _Out_opt_ ID3D11ShaderResourceView** textureView,
                                    _In_ size_t maxsize
                                  )
{
    if (!d3dDevice || !wicData || (!texture && !textureView))
    {
        return E_INVALIDARG;
    }

    ID3D11DeviceContext* d3dContext;
    d3dDevice->GetImmediateContext(&d3dContext);

    if ( !wicDataSize )
    {
        return E_FAIL;
    }

#ifdef _M_AMD64
    if ( wicDataSize > 0xFFFFFFFF )
        return HRESULT_FROM_WIN32( ERROR_FILE_TOO_LARGE );
#endif

    IWICImagingFactory* pWIC = _GetWIC();
    if ( !pWIC )
        return E_NOINTERFACE;

    // Create input stream for memory
    ScopedObject<IWICStream> stream;
    HRESULT hr = pWIC->CreateStream( &stream );
    if ( FAILED(hr) )
        return hr;

    hr = stream->InitializeFromMemory( const_cast<uint8_t*>( wicData ), static_cast<DWORD>( wicDataSize ) );
    if ( FAILED(hr) )
        return hr;

    // Initialize WIC
    ScopedObject<IWICBitmapDecoder> decoder;
    hr = pWIC->CreateDecoderFromStream( stream.Get(), 0, WICDecodeMetadataCacheOnDemand, &decoder );
    if ( FAILED(hr) )
        return hr;

    ScopedObject<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame( 0, &frame );
    if ( FAILED(hr) )
        return hr;

    hr = CreateTextureFromWIC( d3dDevice, d3dContext, frame.Get(), texture, textureView, maxsize );
    if ( FAILED(hr)) 
        return hr;

#if defined(_DEBUG) || defined(PROFILE)
    if (texture != 0 && *texture != 0)
    {
        (*texture)->SetPrivateData( WKPDID_D3DDebugObjectName,
                                    sizeof("WICTextureLoader")-1,
                                    "WICTextureLoader"
                                  );
    }

    if (textureView != 0 && *textureView != 0)
    {
        (*textureView)->SetPrivateData( WKPDID_D3DDebugObjectName,
                                        sizeof("WICTextureLoader")-1,
                                        "WICTextureLoader"
                                      );
    }
#endif

    return hr;
}

//--------------------------------------------------------------------------------------
HRESULT create_wic_texture_from_file( _In_ ID3D11Device* d3dDevice,
                                  _In_z_ const wchar_t* fileName,
                                  _Out_opt_ ID3D11Resource** texture,
                                  _Out_opt_ ID3D11ShaderResourceView** textureView,
                                  _In_ size_t maxsize )
{
    if (!d3dDevice || !fileName || (!texture && !textureView))
    {
        return E_INVALIDARG;
    }

    ID3D11DeviceContext* d3dContext;
    d3dDevice->GetImmediateContext(&d3dContext);

    IWICImagingFactory* pWIC = _GetWIC();
    if ( !pWIC )
        return E_NOINTERFACE;

    // Initialize WIC
    ScopedObject<IWICBitmapDecoder> decoder;
    HRESULT hr = pWIC->CreateDecoderFromFilename( fileName, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder );
    if ( FAILED(hr) )
        return hr;

    ScopedObject<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame( 0, &frame );
    if ( FAILED(hr) )
        return hr;

    hr = CreateTextureFromWIC( d3dDevice, d3dContext, frame.Get(), texture, textureView, maxsize );
    if ( FAILED(hr)) 
        return hr;

#if defined(_DEBUG) || defined(PROFILE)
    if (texture != 0 || textureView != 0)
    {
        CHAR strFileA[MAX_PATH];
        WideCharToMultiByte( CP_ACP,
                             WC_NO_BEST_FIT_CHARS,
                             fileName,
                             -1,
                             strFileA,
                             MAX_PATH,
                             nullptr,
                             FALSE
                           );
        const CHAR* pstrName = strrchr( strFileA, '\\' );
        if (!pstrName)
        {
            pstrName = strFileA;
        }
        else
        {
            pstrName++;
        }

        if (texture != 0 && *texture != 0)
        {
            (*texture)->SetPrivateData( WKPDID_D3DDebugObjectName,
                                        static_cast<UINT>( strnlen_s(pstrName, MAX_PATH) ),
                                        pstrName
                                      );
        }

        if (textureView != 0 && *textureView != 0 )
        {
            (*textureView)->SetPrivateData( WKPDID_D3DDebugObjectName,
                                            static_cast<UINT>( strnlen_s(pstrName, MAX_PATH) ),
                                            pstrName
                                          );
        }
    }
#endif

    return hr;
}

//--------------------------------------------------------------------------------------
// Macros
//--------------------------------------------------------------------------------------
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((uint32_t)(byte)(ch0) | ((uint32_t)(byte)(ch1) << 8) |       \
                ((uint32_t)(byte)(ch2) << 16) | ((uint32_t)(byte)(ch3) << 24))
#endif /* defined(MAKEFOURCC) */

//--------------------------------------------------------------------------------------
// DDS file structure definitions
//
// See DDS.h in the 'Texconv' sample and the 'DirectXTex' library.
//--------------------------------------------------------------------------------------
#pragma pack(push, 1)

#define DDS_MAGIC 0x20534444 // "DDS "

struct DDS_PIXELFORMAT {
    uint32_t  size;
    uint32_t  flags;
    uint32_t  fourCC;
    uint32_t  RGBBitCount;
    uint32_t  RBitMask;
    uint32_t  GBitMask;
    uint32_t  BBitMask;
    uint32_t  ABitMask;
};

#define DDS_FOURCC      0x00000004  // DDPF_FOURCC
#define DDS_RGB         0x00000040  // DDPF_RGB
#define DDS_RGBA        0x00000041  // DDPF_RGB | DDPF_ALPHAPIXELS
#define DDS_LUMINANCE   0x00020000  // DDPF_LUMINANCE
#define DDS_LUMINANCEA  0x00020001  // DDPF_LUMINANCE | DDPF_ALPHAPIXELS
#define DDS_ALPHA       0x00000002  // DDPF_ALPHA
#define DDS_PAL8        0x00000020  // DDPF_PALETTEINDEXED8

#define DDS_HEADER_FLAGS_TEXTURE        0x00001007  // DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT
#define DDS_HEADER_FLAGS_MIPMAP         0x00020000  // DDSD_MIPMAPCOUNT
#define DDS_HEADER_FLAGS_VOLUME         0x00800000  // DDSD_DEPTH
#define DDS_HEADER_FLAGS_PITCH          0x00000008  // DDSD_PITCH
#define DDS_HEADER_FLAGS_LINEARSIZE     0x00080000  // DDSD_LINEARSIZE

#define DDS_HEIGHT 0x00000002 // DDSD_HEIGHT
#define DDS_WIDTH  0x00000004 // DDSD_WIDTH

#define DDS_SURFACE_FLAGS_TEXTURE 0x00001000 // DDSCAPS_TEXTURE
#define DDS_SURFACE_FLAGS_MIPMAP  0x00400008 // DDSCAPS_COMPLEX | DDSCAPS_MIPMAP
#define DDS_SURFACE_FLAGS_CUBEMAP 0x00000008 // DDSCAPS_COMPLEX

#define DDS_CUBEMAP_POSITIVEX 0x00000600 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX
#define DDS_CUBEMAP_NEGATIVEX 0x00000a00 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEX
#define DDS_CUBEMAP_POSITIVEY 0x00001200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEY
#define DDS_CUBEMAP_NEGATIVEY 0x00002200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEY
#define DDS_CUBEMAP_POSITIVEZ 0x00004200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEZ
#define DDS_CUBEMAP_NEGATIVEZ 0x00008200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEZ

#define DDS_CUBEMAP_ALLFACES (DDS_CUBEMAP_POSITIVEX | DDS_CUBEMAP_NEGATIVEX |\
                              DDS_CUBEMAP_POSITIVEY | DDS_CUBEMAP_NEGATIVEY |\
                              DDS_CUBEMAP_POSITIVEZ | DDS_CUBEMAP_NEGATIVEZ)

#define DDS_CUBEMAP 0x00000200 // DDSCAPS2_CUBEMAP

#define DDS_FLAGS_VOLUME 0x00200000 // DDSCAPS2_VOLUME

typedef struct {
    uint32_t          size;
    uint32_t          flags;
    uint32_t          height;
    uint32_t          width;
    uint32_t          pitchOrLinearSize;
    uint32_t          depth; // only if DDS_HEADER_FLAGS_VOLUME is set in flags
    uint32_t          mipMapCount;
    uint32_t          reserved1[11];
    DDS_PIXELFORMAT ddspf;
    uint32_t          caps;
    uint32_t          caps2;
    uint32_t          caps3;
    uint32_t          caps4;
    uint32_t          reserved2;
} DDS_HEADER;

typedef struct {
    DXGI_FORMAT dxgiFormat;
    uint32_t      resourceDimension;
    uint32_t      miscFlag; // See D3D11_RESOURCE_MISC_FLAG
    uint32_t      arraySize;
    uint32_t      reserved;
} DDS_HEADER_DXT10;

#pragma pack(pop)

//--------------------------------------------------------------------------------------
// Return the BPP for a particular format.
//--------------------------------------------------------------------------------------
static size_t BitsPerPixel(_In_ DXGI_FORMAT fmt) {
    switch (fmt) {
        case DXGI_FORMAT_R32G32B32A32_TYPELESS:
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
        case DXGI_FORMAT_R32G32B32A32_UINT:
        case DXGI_FORMAT_R32G32B32A32_SINT:
            return 128;

        case DXGI_FORMAT_R32G32B32_TYPELESS:
        case DXGI_FORMAT_R32G32B32_FLOAT:
        case DXGI_FORMAT_R32G32B32_UINT:
        case DXGI_FORMAT_R32G32B32_SINT:
            return 96;

        case DXGI_FORMAT_R16G16B16A16_TYPELESS:
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
        case DXGI_FORMAT_R16G16B16A16_UNORM:
        case DXGI_FORMAT_R16G16B16A16_UINT:
        case DXGI_FORMAT_R16G16B16A16_SNORM:
        case DXGI_FORMAT_R16G16B16A16_SINT:
        case DXGI_FORMAT_R32G32_TYPELESS:
        case DXGI_FORMAT_R32G32_FLOAT:
        case DXGI_FORMAT_R32G32_UINT:
        case DXGI_FORMAT_R32G32_SINT:
        case DXGI_FORMAT_R32G8X24_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
            return 64;

        case DXGI_FORMAT_R10G10B10A2_TYPELESS:
        case DXGI_FORMAT_R10G10B10A2_UNORM:
        case DXGI_FORMAT_R10G10B10A2_UINT:
        case DXGI_FORMAT_R11G11B10_FLOAT:
        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        case DXGI_FORMAT_R8G8B8A8_UINT:
        case DXGI_FORMAT_R8G8B8A8_SNORM:
        case DXGI_FORMAT_R8G8B8A8_SINT:
        case DXGI_FORMAT_R16G16_TYPELESS:
        case DXGI_FORMAT_R16G16_FLOAT:
        case DXGI_FORMAT_R16G16_UNORM:
        case DXGI_FORMAT_R16G16_UINT:
        case DXGI_FORMAT_R16G16_SNORM:
        case DXGI_FORMAT_R16G16_SINT:
        case DXGI_FORMAT_R32_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT:
        case DXGI_FORMAT_R32_FLOAT:
        case DXGI_FORMAT_R32_UINT:
        case DXGI_FORMAT_R32_SINT:
        case DXGI_FORMAT_R24G8_TYPELESS:
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        case DXGI_FORMAT_R8G8_B8G8_UNORM:
        case DXGI_FORMAT_G8R8_G8B8_UNORM:
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        case DXGI_FORMAT_B8G8R8X8_UNORM:
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        case DXGI_FORMAT_B8G8R8A8_TYPELESS:
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8X8_TYPELESS:
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            return 32;

        case DXGI_FORMAT_R8G8_TYPELESS:
        case DXGI_FORMAT_R8G8_UNORM:
        case DXGI_FORMAT_R8G8_UINT:
        case DXGI_FORMAT_R8G8_SNORM:
        case DXGI_FORMAT_R8G8_SINT:
        case DXGI_FORMAT_R16_TYPELESS:
        case DXGI_FORMAT_R16_FLOAT:
        case DXGI_FORMAT_D16_UNORM:
        case DXGI_FORMAT_R16_UNORM:
        case DXGI_FORMAT_R16_UINT:
        case DXGI_FORMAT_R16_SNORM:
        case DXGI_FORMAT_R16_SINT:
        case DXGI_FORMAT_B5G6R5_UNORM:
        case DXGI_FORMAT_B5G5R5A1_UNORM:
        case DXGI_FORMAT_B4G4R4A4_UNORM:
            return 16;

        case DXGI_FORMAT_R8_TYPELESS:
        case DXGI_FORMAT_R8_UNORM:
        case DXGI_FORMAT_R8_UINT:
        case DXGI_FORMAT_R8_SNORM:
        case DXGI_FORMAT_R8_SINT:
        case DXGI_FORMAT_A8_UNORM:
            return 8;

        case DXGI_FORMAT_R1_UNORM:
            return 1;

        case DXGI_FORMAT_BC1_TYPELESS:
        case DXGI_FORMAT_BC1_UNORM:
        case DXGI_FORMAT_BC1_UNORM_SRGB:
        case DXGI_FORMAT_BC4_TYPELESS:
        case DXGI_FORMAT_BC4_UNORM:
        case DXGI_FORMAT_BC4_SNORM:
            return 4;

        case DXGI_FORMAT_BC2_TYPELESS:
        case DXGI_FORMAT_BC2_UNORM:
        case DXGI_FORMAT_BC2_UNORM_SRGB:
        case DXGI_FORMAT_BC3_TYPELESS:
        case DXGI_FORMAT_BC3_UNORM:
        case DXGI_FORMAT_BC3_UNORM_SRGB:
        case DXGI_FORMAT_BC5_TYPELESS:
        case DXGI_FORMAT_BC5_UNORM:
        case DXGI_FORMAT_BC5_SNORM:
        case DXGI_FORMAT_BC6H_TYPELESS:
        case DXGI_FORMAT_BC6H_UF16:
        case DXGI_FORMAT_BC6H_SF16:
        case DXGI_FORMAT_BC7_TYPELESS:
        case DXGI_FORMAT_BC7_UNORM:
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            return 8;

        default:
            return 0;
    }
}


//--------------------------------------------------------------------------------------
// Get surface information for a particular format.
//--------------------------------------------------------------------------------------
static void GetSurfaceInfo(
    _In_ size_t width,
    _In_ size_t height,
    _In_ DXGI_FORMAT fmt,
    _Out_opt_ size_t* outNumBytes,
    _Out_opt_ size_t* outRowBytes,
    _Out_opt_ size_t* outNumRows
) {
    size_t numBytes = 0;
    size_t rowBytes = 0;
    size_t numRows = 0;

    bool bc = false;
    bool packed = false;
    size_t bcnumBytesPerBlock = 0;
    switch (fmt) {
        case DXGI_FORMAT_BC1_TYPELESS:
        case DXGI_FORMAT_BC1_UNORM:
        case DXGI_FORMAT_BC1_UNORM_SRGB:
        case DXGI_FORMAT_BC4_TYPELESS:
        case DXGI_FORMAT_BC4_UNORM:
        case DXGI_FORMAT_BC4_SNORM:
            bc = true;
            bcnumBytesPerBlock = 8;
            break;

        case DXGI_FORMAT_BC2_TYPELESS:
        case DXGI_FORMAT_BC2_UNORM:
        case DXGI_FORMAT_BC2_UNORM_SRGB:
        case DXGI_FORMAT_BC3_TYPELESS:
        case DXGI_FORMAT_BC3_UNORM:
        case DXGI_FORMAT_BC3_UNORM_SRGB:
        case DXGI_FORMAT_BC5_TYPELESS:
        case DXGI_FORMAT_BC5_UNORM:
        case DXGI_FORMAT_BC5_SNORM:
        case DXGI_FORMAT_BC6H_TYPELESS:
        case DXGI_FORMAT_BC6H_UF16:
        case DXGI_FORMAT_BC6H_SF16:
        case DXGI_FORMAT_BC7_TYPELESS:
        case DXGI_FORMAT_BC7_UNORM:
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            bc = true;
            bcnumBytesPerBlock = 16;
            break;

        case DXGI_FORMAT_R8G8_B8G8_UNORM:
        case DXGI_FORMAT_G8R8_G8B8_UNORM:
            packed = true;
            break;
    }

    if (bc) {
        size_t numBlocksWide = 0;
        if (width > 0) {
            numBlocksWide = max(1, (width + 3) / 4);
        }
        size_t numBlocksHigh = 0;
        if (height > 0) {
            numBlocksHigh = max(1, (height + 3) / 4);
        }
        rowBytes = numBlocksWide * bcnumBytesPerBlock;
        numRows = numBlocksHigh;
    } else if (packed) {
        rowBytes = ((width + 1) >> 1) * 4;
        numRows = height;
    } else {
        size_t bpp = BitsPerPixel(fmt);
        rowBytes = (width * bpp + 7) / 8; // Round up to the nearest byte.
        numRows = height;
    }

    numBytes = rowBytes * numRows;
    if (outNumBytes) {
        *outNumBytes = numBytes;
    }
    if (outRowBytes) {
        *outRowBytes = rowBytes;
    }
    if (outNumRows) {
        *outNumRows = numRows;
    }
}


//--------------------------------------------------------------------------------------
#define ISBITMASK(r, g, b, a) (ddpf.RBitMask == r && ddpf.GBitMask == g && ddpf.BBitMask == b && ddpf.ABitMask == a)

static DXGI_FORMAT GetDXGIFormat(const DDS_PIXELFORMAT& ddpf) {
    if (ddpf.flags & DDS_RGB) {
        // Note that sRGB formats are written using the "DX10" extended header.

        switch (ddpf.RGBBitCount) {
            case 32:
                if (ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000)) {
                    return DXGI_FORMAT_R8G8B8A8_UNORM;
                }

                if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000)) {
                    return DXGI_FORMAT_B8G8R8A8_UNORM;
                }

                if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000)) {
                    return DXGI_FORMAT_B8G8R8X8_UNORM;
                }

                // No DXGI format maps to ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000) aka D3DFMT_X8B8G8R8

                // Note that many common DDS reader/writers (including D3DX) swap the
                // the RED/BLUE masks for 10:10:10:2 formats. We assumme
                // below that the 'backwards' header mask is being used since it is most
                // likely written by D3DX. The more robust solution is to use the 'DX10'
                // header extension and specify the DXGI_FORMAT_R10G10B10A2_UNORM format directly

                // For 'correct' writers, this should be 0x000003ff, 0x000ffc00, 0x3ff00000 for RGB data
                if (ISBITMASK(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000)) {
                    return DXGI_FORMAT_R10G10B10A2_UNORM;
                }

                // No DXGI format maps to ISBITMASK(0x000003ff, 0x000ffc00, 0x3ff00000, 0xc0000000) aka D3DFMT_A2R10G10B10

                if (ISBITMASK(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000)) {
                    return DXGI_FORMAT_R16G16_UNORM;
                }

                if (ISBITMASK(0xffffffff, 0x00000000, 0x00000000, 0x00000000)) {
                    // Only 32-bit color channel format in D3D9 was R32F.
                    return DXGI_FORMAT_R32_FLOAT; // D3DX writes this out as a FourCC of 114.
                }
                break;

            case 24:
                // No 24bpp DXGI formats aka D3DFMT_R8G8B8
                break;

            case 16:
                if (ISBITMASK(0x7c00, 0x03e0, 0x001f, 0x8000)) {
                    return DXGI_FORMAT_B5G5R5A1_UNORM;
                }
                if (ISBITMASK(0xf800, 0x07e0, 0x001f, 0x0000)) {
                    return DXGI_FORMAT_B5G6R5_UNORM;
                }

                // No DXGI format maps to ISBITMASK(0x7c00, 0x03e0, 0x001f, 0x0000) aka D3DFMT_X1R5G5B5.
                if (ISBITMASK(0x0f00, 0x00f0, 0x000f, 0xf000)) {
                    return DXGI_FORMAT_B4G4R4A4_UNORM;
                }

                // No DXGI format maps to ISBITMASK(0x0f00, 0x00f0, 0x000f, 0x0000) aka D3DFMT_X4R4G4B4.

                // No 3:3:2, 3:3:2:8, or paletted DXGI formats aka D3DFMT_A8R3G3B2, D3DFMT_R3G3B2, D3DFMT_P8, D3DFMT_A8P8, etc.
                break;
        }
    } else if (ddpf.flags & DDS_LUMINANCE) {
        if (8 == ddpf.RGBBitCount) {
            if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x00000000)) {
                return DXGI_FORMAT_R8_UNORM; // D3DX10/11 writes this out as DX10 extension
            }

            // No DXGI format maps to ISBITMASK(0x0f, 0x00, 0x00, 0xf0) aka D3DFMT_A4L4.
        }

        if (16 == ddpf.RGBBitCount) {
            if (ISBITMASK(0x0000ffff, 0x00000000, 0x00000000, 0x00000000)) {
                return DXGI_FORMAT_R16_UNORM; // D3DX10/11 writes this out as DX10 extension.
            }
            if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x0000ff00)) {
                return DXGI_FORMAT_R8G8_UNORM; // D3DX10/11 writes this out as DX10 extension.
            }
        }
    } else if (ddpf.flags & DDS_ALPHA) {
        if (8 == ddpf.RGBBitCount) {
            return DXGI_FORMAT_A8_UNORM;
        }
    } else if (ddpf.flags & DDS_FOURCC) {
        if (MAKEFOURCC('D', 'X', 'T', '1') == ddpf.fourCC) {
            return DXGI_FORMAT_BC1_UNORM;
        }
        if (MAKEFOURCC('D', 'X', 'T', '3') == ddpf.fourCC) {
            return DXGI_FORMAT_BC2_UNORM;
        }
        if (MAKEFOURCC('D', 'X', 'T', '5') == ddpf.fourCC) {
            return DXGI_FORMAT_BC3_UNORM;
        }

        // While pre-mulitplied alpha isn't directly supported by the DXGI formats,
        // they are basically the same as these BC formats so they can be mapped
        if (MAKEFOURCC('D', 'X', 'T', '2') == ddpf.fourCC) {
            return DXGI_FORMAT_BC2_UNORM;
        }
        if (MAKEFOURCC('D', 'X', 'T', '4') == ddpf.fourCC) {
            return DXGI_FORMAT_BC3_UNORM;
        }

        if (MAKEFOURCC('A', 'T', 'I', '1') == ddpf.fourCC) {
            return DXGI_FORMAT_BC4_UNORM;
        }
        if (MAKEFOURCC('B', 'C', '4', 'U') == ddpf.fourCC) {
            return DXGI_FORMAT_BC4_UNORM;
        }
        if (MAKEFOURCC('B', 'C', '4', 'S') == ddpf.fourCC) {
            return DXGI_FORMAT_BC4_SNORM;
        }

        if (MAKEFOURCC('A', 'T', 'I', '2') == ddpf.fourCC) {
            return DXGI_FORMAT_BC5_UNORM;
        }
        if (MAKEFOURCC('B', 'C', '5', 'U') == ddpf.fourCC) {
            return DXGI_FORMAT_BC5_UNORM;
        }
        if (MAKEFOURCC('B', 'C', '5', 'S') == ddpf.fourCC) {
            return DXGI_FORMAT_BC5_SNORM;
        }

        // BC6H and BC7 are written using the "DX10" extended header

        if (MAKEFOURCC('R', 'G', 'B', 'G') == ddpf.fourCC) {
            return DXGI_FORMAT_R8G8_B8G8_UNORM;
        }
        if (MAKEFOURCC('G', 'R', 'G', 'B') == ddpf.fourCC) {
            return DXGI_FORMAT_G8R8_G8B8_UNORM;
        }

        // Check for D3DFORMAT enums being set here.
        switch (ddpf.fourCC) {
            case 36: // D3DFMT_A16B16G16R16
                return DXGI_FORMAT_R16G16B16A16_UNORM;

            case 110: // D3DFMT_Q16W16V16U16
                return DXGI_FORMAT_R16G16B16A16_SNORM;

            case 111: // D3DFMT_R16F
                return DXGI_FORMAT_R16_FLOAT;

            case 112: // D3DFMT_G16R16F
                return DXGI_FORMAT_R16G16_FLOAT;

            case 113: // D3DFMT_A16B16G16R16F
                return DXGI_FORMAT_R16G16B16A16_FLOAT;

            case 114: // D3DFMT_R32F
                return DXGI_FORMAT_R32_FLOAT;

            case 115: // D3DFMT_G32R32F
                return DXGI_FORMAT_R32G32_FLOAT;

            case 116: // D3DFMT_A32B32G32R32F
                return DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
    }

    return DXGI_FORMAT_UNKNOWN;
}


//--------------------------------------------------------------------------------------
static void FillInitData(
    _In_ size_t width,
    _In_ size_t height,
    _In_ size_t depth,
    _In_ size_t mipCount,
    _In_ size_t arraySize,
    _In_ DXGI_FORMAT format,
    _In_ size_t maxsize,
    _In_ size_t bitSize,
    _In_reads_bytes_(bitSize) const byte* bitData,
    _Out_ size_t& twidth,
    _Out_ size_t& theight,
    _Out_ size_t& tdepth,
    _Out_ size_t& skipMip,
    _Out_writes_(mipCount* arraySize) D3D11_SUBRESOURCE_DATA* initData
) {
    if (!bitData || !initData) {
        return;
    }

    skipMip = 0;
    twidth = 0;
    theight = 0;
    tdepth = 0;

    size_t NumBytes = 0;
    size_t RowBytes = 0;
    size_t NumRows = 0;
    const byte* pSrcBits = bitData;
    const byte* pEndBits = bitData + bitSize;

    size_t index = 0;
    for (size_t j = 0; j < arraySize; j++) {
        size_t w = width;
        size_t h = height;
        size_t d = depth;
        for (size_t i = 0; i < mipCount; i++) {
            GetSurfaceInfo(w, h, format, &NumBytes, &RowBytes, &NumRows);

            if ((mipCount <= 1) || !maxsize || (w <= maxsize && h <= maxsize && d <= maxsize)) {
                if (!twidth) {
                    twidth = w;
                    theight = h;
                    tdepth = d;
                }

                initData[index].pSysMem = (const void*)pSrcBits;
                initData[index].SysMemPitch = static_cast<UINT>(RowBytes);
                initData[index].SysMemSlicePitch = static_cast<UINT>(NumBytes);
                ++index;
            } else {
                ++skipMip;
            }

            if (pSrcBits + (NumBytes * d) > pEndBits) {
                return;
            }

            pSrcBits += NumBytes * d;

            w = w >> 1;
            h = h >> 1;
            d = d >> 1;
            if (w == 0) {
                w = 1;
            }
            if (h == 0) {
                h = 1;
            }
            if (d == 0) {
                d = 1;
            }
        }
    }

    if (!index) {
        return;
    }
}


//--------------------------------------------------------------------------------------
static HRESULT CreateD3DResources(
    _In_ ID3D11Device* d3dDevice,
    _In_ uint32_t resDim,
    _In_ size_t width,
    _In_ size_t height,
    _In_ size_t depth,
    _In_ size_t mipCount,
    _In_ size_t arraySize,
    _In_ DXGI_FORMAT format,
    _In_ bool isCubeMap,
    _In_reads_(mipCount* arraySize) D3D11_SUBRESOURCE_DATA* initData,
    _Out_opt_ ID3D11Resource** texture,
    _Out_opt_ ID3D11ShaderResourceView** textureView
) {
    if (!d3dDevice || !initData) {
        return E_INVALIDARG;
    }

    HRESULT hr = E_FAIL;

    switch (resDim) {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
        {
            D3D11_TEXTURE1D_DESC desc;
            desc.Width = static_cast<UINT>(width);
            desc.MipLevels = static_cast<UINT>(mipCount);
            desc.ArraySize = static_cast<UINT>(arraySize);
            desc.Format = format;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = 0;

            ID3D11Texture1D* tex = nullptr;
            hr = d3dDevice->CreateTexture1D(&desc, initData, &tex);

            if (SUCCEEDED(hr) && tex != 0) {
                if (textureView != 0) {
                    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
                    memset(&SRVDesc, 0, sizeof(SRVDesc));
                    SRVDesc.Format = format;

                    if (arraySize > 1) {
                        SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE1DARRAY;
                        SRVDesc.Texture1DArray.MipLevels = desc.MipLevels;
                        SRVDesc.Texture1DArray.ArraySize = static_cast<UINT>(arraySize);
                    } else {
                        SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE1D;
                        SRVDesc.Texture1D.MipLevels = desc.MipLevels;
                    }

                    hr = d3dDevice->CreateShaderResourceView(tex, &SRVDesc, textureView);

                    if (FAILED(hr)) {
                        tex->Release();
                        return hr;
                    }
                }

                if (texture != 0) {
                    *texture = tex;
                } else {
                    tex->Release();
                }
            }
        }
        break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
        {
            D3D11_TEXTURE2D_DESC desc;
            desc.Width = static_cast<UINT>(width);
            desc.Height = static_cast<UINT>(height);
            desc.MipLevels = static_cast<UINT>(mipCount);
            desc.ArraySize = static_cast<UINT>(arraySize);
            desc.Format = format;
            desc.SampleDesc.Count = 1;
            desc.SampleDesc.Quality = 0;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = (isCubeMap) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;

            ID3D11Texture2D* tex = nullptr;
            hr = d3dDevice->CreateTexture2D(&desc, initData, &tex);

            if (SUCCEEDED(hr) && tex != 0) {
                if (textureView != 0) {
                    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
                    memset(&SRVDesc, 0, sizeof(SRVDesc));
                    SRVDesc.Format = format;

                    if (isCubeMap) {
                        if (arraySize > 6) {
                            SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBEARRAY;
                            SRVDesc.TextureCubeArray.MipLevels = desc.MipLevels;

                            // Earlier, we set arraySize to (NumCubes * 6).
                            SRVDesc.TextureCubeArray.NumCubes = static_cast<UINT>(arraySize / 6);
                        } else {
                            SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
                            SRVDesc.TextureCube.MipLevels = desc.MipLevels;
                        }
                    } else if (arraySize > 1) {
                        SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DARRAY;
                        SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
                        SRVDesc.Texture2DArray.ArraySize = static_cast<UINT>(arraySize);
                    } else {
                        SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
                        SRVDesc.Texture2D.MipLevels = desc.MipLevels;
                    }

                    hr = d3dDevice->CreateShaderResourceView(tex, &SRVDesc, textureView);

                    if (FAILED(hr)) {
                        tex->Release();
                        return hr;
                    }
                }

                if (texture != 0) {
                    *texture = tex;
                } else {
                    tex->Release();
                }
            }
        }
        break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
        {
            D3D11_TEXTURE3D_DESC desc;
            desc.Width = static_cast<UINT>(width);
            desc.Height = static_cast<UINT>(height);
            desc.Depth = static_cast<UINT>(depth);
            desc.MipLevels = static_cast<UINT>(mipCount);
            desc.Format = format;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = 0;

            ID3D11Texture3D* tex = nullptr;
            hr = d3dDevice->CreateTexture3D(&desc, initData, &tex);

            if (SUCCEEDED(hr) && tex != 0) {
                if (textureView != 0) {
                    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
                    memset(&SRVDesc, 0, sizeof(SRVDesc));
                    SRVDesc.Format = format;
                    SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE3D;
                    SRVDesc.Texture3D.MipLevels = desc.MipLevels;

                    hr = d3dDevice->CreateShaderResourceView(tex, &SRVDesc, textureView);

                    if (FAILED(hr)) {
                        tex->Release();
                        return hr;
                    }
                }

                if (texture != 0) {
                    *texture = tex;
                } else {
                    tex->Release();
                }
            }
        }
        break;
    }

    return hr;
}


//--------------------------------------------------------------------------------------
static void CreateTextureFromDDS(
    _In_ ID3D11Device* d3dDevice,
    _In_ const DDS_HEADER* header,
    _In_reads_bytes_(bitSize) const byte* bitData,
    _In_ size_t bitSize,
    _Out_opt_ ID3D11Resource** texture,
    _Out_opt_ ID3D11ShaderResourceView** textureView,
    _In_ size_t maxsize
) {
    HRESULT hr = S_OK;

    size_t width = header->width;
    size_t height = header->height;
    size_t depth = header->depth;

    uint32_t resDim = D3D11_RESOURCE_DIMENSION_UNKNOWN;
    size_t arraySize = 1;
    DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
    bool isCubeMap = false;

    size_t mipCount = header->mipMapCount;
    if (0 == mipCount) {
        mipCount = 1;
    }

    if ((header->ddspf.flags & DDS_FOURCC) &&
        (MAKEFOURCC('D', 'X', '1', '0') == header->ddspf.fourCC)) {
        const DDS_HEADER_DXT10* d3d10ext = reinterpret_cast<const DDS_HEADER_DXT10*>((const char*)header + sizeof(DDS_HEADER));

        arraySize = d3d10ext->arraySize;
        if (arraySize == 0) {
            return;
        }

        if (BitsPerPixel(d3d10ext->dxgiFormat) == 0) {
            return;
        }

        format = d3d10ext->dxgiFormat;

        switch (d3d10ext->resourceDimension) {
            case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
                // D3DX writes 1D textures with a fixed Height of 1.
                if ((header->flags & DDS_HEIGHT) && height != 1) {
                    return;
                }
                height = depth = 1;
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
                if (d3d10ext->miscFlag & D3D11_RESOURCE_MISC_TEXTURECUBE) {
                    arraySize *= 6;
                    isCubeMap = true;
                }
                depth = 1;
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
                if (!(header->flags & DDS_HEADER_FLAGS_VOLUME)) {
                    return;
                }

                if (arraySize > 1) {
                    return;
                }
                break;

            default:
                return;
        }

        resDim = d3d10ext->resourceDimension;
    } else {
        format = GetDXGIFormat(header->ddspf);

        if (format == DXGI_FORMAT_UNKNOWN) {
            return;
        }

        if (header->flags & DDS_HEADER_FLAGS_VOLUME) {
            resDim = D3D11_RESOURCE_DIMENSION_TEXTURE3D;
        } else {
            if (header->caps2 & DDS_CUBEMAP) {
                // We require all six faces to be defined.
                if ((header->caps2 & DDS_CUBEMAP_ALLFACES) != DDS_CUBEMAP_ALLFACES) {
                    return;
                }

                arraySize = 6;
                isCubeMap = true;
            }

            depth = 1;
            resDim = D3D11_RESOURCE_DIMENSION_TEXTURE2D;

            // Note there's no way for a legacy Direct3D 9 DDS to express a '1D' texture.
        }
    }

    // Bound sizes (For security purposes, we don't trust DDS file metadata larger than the D3D 11.x hardware requirements.)
    if (mipCount > D3D11_REQ_MIP_LEVELS) {
        return;
    }

    switch (resDim) {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            if ((arraySize > D3D11_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION) ||
                (width > D3D11_REQ_TEXTURE1D_U_DIMENSION)) {
                return;
            }
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            if (isCubeMap) {
                // This is the right bound because we set arraySize to (NumCubes*6) above.
                if ((arraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) ||
                    (width > D3D11_REQ_TEXTURECUBE_DIMENSION) ||
                    (height > D3D11_REQ_TEXTURECUBE_DIMENSION)) {
                    return;
                }
            } else if ((arraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) ||
                (width > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION) ||
                (height > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)) {
                return;
            }
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            if ((arraySize > 1) ||
                (width > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) ||
                (height > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) ||
                (depth > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION)) {
                return;
            }
            break;
    }

    // Create the texture.
    std::unique_ptr<D3D11_SUBRESOURCE_DATA> initData(new D3D11_SUBRESOURCE_DATA[mipCount * arraySize]);

    size_t skipMip = 0;
    size_t twidth = 0;
    size_t theight = 0;
    size_t tdepth = 0;
    FillInitData(width, height, depth, mipCount, arraySize, format, maxsize, bitSize, bitData, twidth, theight, tdepth, skipMip, initData.get());

    hr = CreateD3DResources(d3dDevice, resDim, twidth, theight, tdepth, mipCount - skipMip, arraySize, format, isCubeMap, initData.get(), texture, textureView);

    if (FAILED(hr) && !maxsize && (mipCount > 1)) {
        // Retry with a maxsize determined by feature level.
        switch (d3dDevice->GetFeatureLevel()) {
            case D3D_FEATURE_LEVEL_9_1:
            case D3D_FEATURE_LEVEL_9_2:
                if (isCubeMap) {
                    maxsize = D3D_FL9_1_REQ_TEXTURECUBE_DIMENSION;
                } else {
                    maxsize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
                        ? D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
                        : D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION;
                }
                break;

            case D3D_FEATURE_LEVEL_9_3:
                maxsize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
                    ? D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
                    : D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION;
                break;

            default: // D3D_FEATURE_LEVEL_10_0 & D3D_FEATURE_LEVEL_10_1
                maxsize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
                    ? D3D10_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
                    : D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION;
                break;
        }

        FillInitData(width, height, depth, mipCount, arraySize, format, maxsize, bitSize, bitData, twidth, theight, tdepth, skipMip, initData.get());

        hr = CreateD3DResources(d3dDevice, resDim, twidth, theight, tdepth, mipCount - skipMip, arraySize, format, isCubeMap, initData.get(), texture, textureView);
    }
}

HRESULT create_dds_texture_from_memory(ID3D11Device* d3dDevice, const byte* ddsData, size_t ddsDataSize, ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t maxsize) {
    if (!d3dDevice || !ddsData || (!texture && !textureView)) {
        return E_NOINTERFACE;
    }

    // Validate DDS file in memory.
    if (ddsDataSize < (sizeof(uint32_t) + sizeof(DDS_HEADER))) {
        return E_NOINTERFACE;
    }

    uint32_t dwMagicNumber = *(const uint32_t*)(ddsData);
    if (dwMagicNumber != DDS_MAGIC) {
        return E_NOINTERFACE;
    }

    const DDS_HEADER* header = reinterpret_cast<const DDS_HEADER*>(ddsData + sizeof(uint32_t));

    // Verify the header to validate the DDS file.
    if (header->size != sizeof(DDS_HEADER) ||
        header->ddspf.size != sizeof(DDS_PIXELFORMAT)) {
        return E_NOINTERFACE;
    }

    // Check for the DX10 extension.
    bool bDXT10Header = false;
    if ((header->ddspf.flags & DDS_FOURCC) &&
        (MAKEFOURCC('D', 'X', '1', '0') == header->ddspf.fourCC)) {
        // Must be long enough for both headers and magic value
        if (ddsDataSize < (sizeof(DDS_HEADER) + sizeof(uint32_t) + sizeof(DDS_HEADER_DXT10))) {
            return E_NOINTERFACE;
        }

        bDXT10Header = true;
    }

    ptrdiff_t offset = sizeof(uint32_t) + sizeof(DDS_HEADER) + (bDXT10Header ? sizeof(DDS_HEADER_DXT10) : 0);

    CreateTextureFromDDS(d3dDevice, header, ddsData + offset, ddsDataSize - offset, texture, textureView, maxsize);
    return ERROR_SUCCESS;
}