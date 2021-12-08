/**************************** dll export:****************************/
#pragma  once
#ifndef DLLAPI
#define DLLAPI __declspec(dllexport)
#endif

#define MAX_PCIE_BUF_SIZE    (64)
typedef enum {
    DEV_CC_GIFA = 0,
    DEV_NI_VST,
    DEV_CY_VST,
    DEV_ALL_TYPE_NUM
}DEVICE_TYPE;

typedef enum _AllocStatus {
    ALLOC_SUCCESSFUL,
    ALLOC_INVALID_HANDLE,
    ALLOC_DEVICE_FAILURE,
} AllocStatus;

typedef struct{
    unsigned char nBusNumber;
    unsigned char nDevId;
    unsigned char nFuncId;
}DEV_LOC_INFO;

typedef struct{
    char szDeviceDesc[MAX_PCIE_BUF_SIZE];
    char szHardWareID[MAX_PCIE_BUF_SIZE];
    //char szLocationInfo[MAX_PCIE_BUF_SIZE];
    DEV_LOC_INFO devLocInfo;
}PCI_DEV_INFO,*P_PCI_DEV_INFO;

DLLAPI int __stdcall ScanS08FDevice(int nType);

DLLAPI void __stdcall InitializeGIFADevice();
DLLAPI void __stdcall ReleaseGIFADevice();

/* write data to io port */
DLLAPI void __stdcall PutIo(unsigned long Io, unsigned long  Data);
/* read data from io port */
DLLAPI unsigned long __stdcall GetIo(unsigned long Io);
/* Wait for time(ms)*/
DLLAPI void __stdcall Wait(double tms);
DLLAPI double __stdcall RdSysTime();
