_Pragma("once");
#include <libusb-1.0/libusb.h>
#include <map>

#if defined(_WIN32) && defined(_MSC_VER)
    #ifdef ZEROPACKAGE_BUILDING
        #define PACKAGE_DLL __declspec(dllexport)
    #else
        #define PACKAGE_DLL __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define PACKAGE_DLL __attribute__((visibility("default")))
#else
    #define PACKAGE_DLL
#endif

class PACKAGE_DLL UsbManager
{
public:
    explicit(true) UsbManager();

    ~UsbManager() noexcept;

public:
    auto devicesList() noexcept -> std::map<u_int, u_int>;

private:
    auto init() noexcept -> void;

private:
    libusb_context* m_usbContext{nullptr};
    libusb_device** m_devices{};
};
