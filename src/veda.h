#pragma once

#ifdef __ve__
#error Inclusion of veda.h in device code detected! veda.h is only meant for host code, use veda_device.h instead. If you want to use VEDA data types in a shared header file, use veda_types.h.
#endif

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

//------------------------------------------------------------------------------
// Pure C interface
//------------------------------------------------------------------------------
#include "veda_enums.h"
#include "veda_types.h"
#include "veda_macros.h"
#include "veda_version.h"

#ifdef __cplusplus
#include <type_traits>
extern "C" {
#endif

VEDAresult	vedaArgsCreate			(VEDAargs* args);
VEDAresult	vedaArgsDestroy			(VEDAargs args);
VEDAresult	vedaArgsSetF32			(VEDAargs args, const int idx, const float value);
VEDAresult	vedaArgsSetF64			(VEDAargs args, const int idx, const double value);
VEDAresult	vedaArgsSetI16			(VEDAargs args, const int idx, const int16_t value);
VEDAresult	vedaArgsSetI32			(VEDAargs args, const int idx, const int32_t value);
VEDAresult	vedaArgsSetI64			(VEDAargs args, const int idx, const int64_t value);
VEDAresult	vedaArgsSetI8			(VEDAargs args, const int idx, const int8_t value);
VEDAresult	vedaArgsSetPtr			(VEDAargs args, const int idx, const VEDAdeviceptr value);
VEDAresult	vedaArgsSetVPtr			(VEDAargs args, const int idx, const VEDAdeviceptr value);
VEDAresult	vedaArgsSetHMEM			(VEDAargs args, const int idx, const void* value);
VEDAresult	vedaArgsSetStack		(VEDAargs args, const int idx, void* ptr, VEDAargs_intent intent, const size_t size);
VEDAresult	vedaArgsSetU16			(VEDAargs args, const int idx, const uint16_t value);
VEDAresult	vedaArgsSetU32			(VEDAargs args, const int idx, const uint32_t value);
VEDAresult	vedaArgsSetU64			(VEDAargs args, const int idx, const uint64_t value);
VEDAresult	vedaArgsSetU8			(VEDAargs args, const int idx, const uint8_t value);
VEDAresult	vedaCtxCreate			(VEDAcontext* pctx, int mode, VEDAdevice dev);
VEDAresult	vedaCtxDestroy			(VEDAcontext ctx);
VEDAresult	vedaCtxGet			(VEDAcontext* ctx, const VEDAdevice device);
VEDAresult	vedaCtxGetApiVersion		(VEDAcontext ctx, uint32_t* version);
VEDAresult	vedaCtxGetCurrent		(VEDAcontext* pctx);
VEDAresult	vedaCtxGetDevice		(VEDAdevice* device);
VEDAresult	vedaCtxPopCurrent		(VEDAcontext* pctx);
VEDAresult	vedaCtxPushCurrent		(VEDAcontext ctx);
VEDAresult	vedaCtxSetCurrent		(VEDAcontext ctx);
VEDAresult	vedaCtxStreamCnt		(int* cnt);
VEDAresult	vedaCtxSynchronize		(void);
VEDAresult	vedaDeviceDistance		(float* distance, VEDAdevice devA, VEDAdevice devB);
VEDAresult	vedaDeviceGet			(VEDAdevice* device, int ordinal);
VEDAresult	vedaDeviceGetAttribute		(int* pi, VEDAdevice_attribute attrib, VEDAdevice dev);
VEDAresult	vedaDeviceGetCount		(int* count);
VEDAresult	vedaDeviceGetName 		(char* name, int len, VEDAdevice dev);
VEDAresult	vedaDeviceGetPower		(float* power, VEDAdevice dev);
VEDAresult	vedaDeviceGetCurrent		(float* current, VEDAdevice dev);
VEDAresult	vedaDeviceGetVoltage		(float* voltage, VEDAdevice dev);
VEDAresult	vedaDeviceGetTemp		(float* tempC, const int coreIdx, VEDAdevice dev);
VEDAresult	vedaDeviceGetPhysicalId		(int* id, VEDAdevice dev);
VEDAresult	vedaDeviceGetAVEOId		(int* id, VEDAdevice dev);
VEDAresult	vedaDeviceGetNUMAId		(int* id, VEDAdevice dev);
VEDAresult	vedaDevicePrimaryCtxGetState	(VEDAdevice dev, uint32_t* flags, int* active);
VEDAresult	vedaDevicePrimaryCtxRelease	(VEDAdevice dev);
VEDAresult	vedaDevicePrimaryCtxReset	(VEDAdevice dev);
VEDAresult	vedaDevicePrimaryCtxRetain	(VEDAcontext* pctx, VEDAdevice dev);
VEDAresult	vedaDevicePrimaryCtxSetFlags	(VEDAdevice dev, uint32_t flags);
VEDAresult	vedaDeviceTotalMem		(size_t* bytes, VEDAdevice dev);
VEDAresult	vedaDriverGetVersion 		(const char** str);
VEDAresult	vedaExit			(void);
VEDAresult	vedaGetErrorName		(VEDAresult error, const char** pStr);
VEDAresult	vedaGetErrorString		(VEDAresult error, const char** pStr);
VEDAresult	vedaGetVersion			(const char** str);
VEDAresult	vedaInit			(uint32_t Flags);
VEDAresult	vedaLaunchHostFunc		(VEDAstream stream, VEDAhost_function fn, void* userData);
VEDAresult	vedaLaunchKernel		(VEDAfunction f, VEDAstream stream, VEDAargs);
VEDAresult	vedaLaunchKernelEx		(VEDAfunction f, VEDAstream stream, VEDAargs, const int destroyArgs);
VEDAresult	vedaMemAlloc			(VEDAdeviceptr* ptr, size_t size);
VEDAresult	vedaMemAllocAsync		(VEDAdeviceptr* ptr, size_t size, VEDAstream stream);
VEDAresult	vedaMemAllocHost		(void** pp, size_t bytesiz);
VEDAresult	vedaMemAllocPitch		(VEDAdeviceptr* ptr, size_t* pPitch, size_t WidthInBytes, size_t Height, uint32_t ElementSizeByte);
VEDAresult	vedaMemAllocPitchAsync		(VEDAdeviceptr* ptr, size_t* pPitch, size_t WidthInBytes, size_t Height, uint32_t ElementSizeByte, VEDAstream stream);
VEDAresult	vedaMemFree			(VEDAdeviceptr ptr);
VEDAresult	vedaMemFreeAsync		(VEDAdeviceptr ptr, VEDAstream stream);
VEDAresult	vedaMemFreeHost			(void* ptr);
VEDAresult	vedaMemGetAddressRange		(VEDAdeviceptr* base, size_t* size, VEDAdeviceptr ptr);
VEDAresult	vedaMemGetDevice		(VEDAdevice* dev, VEDAdeviceptr ptr);
VEDAresult	vedaMemGetInfo			(size_t* free, size_t* total);
VEDAresult	vedaMemHMEM			(void** ptr, VEDAdeviceptr vptr);
VEDAresult	vedaMemHMEMSize			(void** ptr, size_t* size, VEDAdeviceptr vptr);
VEDAresult	vedaMemPtr			(void** ptr, VEDAdeviceptr vptr);
VEDAresult	vedaMemPtrSize			(void** ptr, size_t* size, VEDAdeviceptr vptr);
VEDAresult	vedaMemReport			(void);
VEDAresult	vedaMemSize			(size_t* size, VEDAdeviceptr ptr);
VEDAresult	vedaMemcpy			(VEDAdeviceptr dst, VEDAdeviceptr src, size_t ByteCount);
VEDAresult	vedaMemcpyAsync			(VEDAdeviceptr dst, VEDAdeviceptr src, size_t ByteCount, VEDAstream hStream);
VEDAresult	vedaMemcpyDtoD			(VEDAdeviceptr dstDevice, VEDAdeviceptr srcDevice, size_t ByteCount);
VEDAresult	vedaMemcpyDtoDAsync		(VEDAdeviceptr dstDevice, VEDAdeviceptr srcDevice, size_t ByteCount, VEDAstream hStream);
VEDAresult	vedaMemcpyDtoH			(void* dstHost, VEDAdeviceptr srcDevice, size_t ByteCount);
VEDAresult	vedaMemcpyDtoHAsync		(void* dstHost, VEDAdeviceptr srcDevice, size_t ByteCount, VEDAstream hStream);
VEDAresult	vedaMemcpyHtoD			(VEDAdeviceptr dstDevice, const void* srcHost, size_t ByteCount);
VEDAresult	vedaMemcpyHtoDAsync		(VEDAdeviceptr dstDevice, const void* srcHost, size_t ByteCount, VEDAstream hStream);
VEDAresult	vedaMemsetD16			(VEDAdeviceptr dstDevice, uint16_t us, size_t N);
VEDAresult	vedaMemsetD16Async		(VEDAdeviceptr dstDevice, uint16_t us, size_t N, VEDAstream hStream);
VEDAresult	vedaMemsetD2D16			(VEDAdeviceptr dstDevice, size_t dstPitch, uint16_t us, size_t Width, size_t Height);
VEDAresult	vedaMemsetD2D16Async		(VEDAdeviceptr dstDevice, size_t dstPitch, uint16_t us, size_t Width, size_t Height, VEDAstream hStream);
VEDAresult	vedaMemsetD2D32			(VEDAdeviceptr dstDevice, size_t dstPitch, uint32_t ui, size_t Width, size_t Height);
VEDAresult	vedaMemsetD2D32Async		(VEDAdeviceptr dstDevice, size_t dstPitch, uint32_t ui, size_t Width, size_t Height, VEDAstream hStream);
VEDAresult	vedaMemsetD2D8			(VEDAdeviceptr dstDevice, size_t dstPitch, uint8_t uc, size_t Width, size_t Height);
VEDAresult	vedaMemsetD2D8Async		(VEDAdeviceptr dstDevice, size_t dstPitch, uint8_t uc, size_t Width, size_t Height, VEDAstream hStream);
VEDAresult	vedaMemsetD32			(VEDAdeviceptr dstDevice, uint32_t ui, size_t N);
VEDAresult	vedaMemsetD32Async		(VEDAdeviceptr dstDevice, uint32_t ui, size_t N, VEDAstream hStream);
VEDAresult	vedaMemsetD64			(VEDAdeviceptr dstDevice, uint64_t ui, size_t N);
VEDAresult	vedaMemsetD64Async		(VEDAdeviceptr dstDevice, uint64_t ui, size_t N, VEDAstream hStream);
VEDAresult	vedaMemsetD8			(VEDAdeviceptr dstDevice, uint8_t uc, size_t N);
VEDAresult	vedaMemsetD8Async		(VEDAdeviceptr dstDevice, uint8_t uc, size_t N, VEDAstream hStream);
VEDAresult	vedaModuleGetFunction		(VEDAfunction* hfunc, VEDAmodule hmod, const char* name);
VEDAresult	vedaModuleLoad			(VEDAmodule* module, const char* fname);
VEDAresult	vedaModuleUnload		(VEDAmodule hmod);
VEDAresult	vedaStreamAddCallback		(VEDAstream stream, VEDAstream_callback callback, void* userData, unsigned int flags);
VEDAresult	vedaStreamGetFlags		(VEDAstream hStream, uint32_t* flags);
VEDAresult	vedaStreamQuery			(VEDAstream hStream);
VEDAresult	vedaStreamSynchronize		(VEDAstream hStream);

VEDA_DEPRECATED(VEDAresult vedaMemGetRawPointer	(void** rawPtr, VEDAdeviceptr vptr));	// USE vedaMemPtr instead
VEDA_DEPRECATED(VEDAresult vedaMemGetHMEMPointer(void** hmemPtr, VEDAdeviceptr vptr));	// USE vedaMemHMEM instead

#ifdef __cplusplus
}

#include <veda_ptr.h>

//------------------------------------------------------------------------------
// Advanced C++ interface
//------------------------------------------------------------------------------
struct VEDAstack {
	void* const		ptr;
	const VEDAargs_intent	intent;
	const size_t		size;

	inline VEDAstack(void* _ptr, VEDAargs_intent _intent, size_t _size) :
		ptr(_ptr), intent(_intent), size(_size) {}
};

inline VEDAresult vedaArgsSet(VEDAargs args, const int idx, const VEDAdeviceptr value) {
	return vedaArgsSetVPtr(args, idx, value);
}

template<typename T>
inline typename std::enable_if<(sizeof(T) == 1), VEDAresult>::type vedaArgsSet(VEDAargs args, const int idx, const T value) {
	return vedaArgsSetU8(args, idx, *reinterpret_cast<const uint8_t*>(&value));
}

template<typename T>
inline typename std::enable_if<(sizeof(T) == 2), VEDAresult>::type vedaArgsSet(VEDAargs args, const int idx, const T value) {
	return vedaArgsSetU16(args, idx, *reinterpret_cast<const uint16_t*>(&value));
}

template<typename T>
inline typename std::enable_if<(sizeof(T) == 4), VEDAresult>::type vedaArgsSet(VEDAargs args, const int idx, const T value) {
	return vedaArgsSetU32(args, idx, *reinterpret_cast<const uint32_t*>(&value));
}

template<typename T>
inline typename std::enable_if<(sizeof(T) == 8), VEDAresult>::type vedaArgsSet(VEDAargs args, const int idx, const T value) {
	return vedaArgsSetU64(args, idx, *reinterpret_cast<const uint64_t*>(&value));
}

inline VEDAresult vedaArgsSet(VEDAargs args, const int idx, const VEDAstack stack) {
	return vedaArgsSetStack(args, idx, stack.ptr, stack.intent, stack.size);
}

inline VEDAresult __vedaLaunchKernel(VEDAfunction func, VEDAstream stream, VEDAargs args, const int idx) {
	return vedaLaunchKernelEx(func, stream, args, 1);
}

template<typename T, typename... Args>
inline VEDAresult __vedaLaunchKernel(VEDAfunction func, VEDAstream stream, VEDAargs args, const int idx, const T value, Args... vargs) {
	CVEDA(vedaArgsSet(args, idx, value));
	return __vedaLaunchKernel(func, stream, args, idx+1, vargs...);
}

template<typename... Args>
inline VEDAresult vedaLaunchKernel(VEDAfunction func, VEDAstream stream, Args... vargs) {
	VEDAargs args = 0;
	CVEDA(vedaArgsCreate(&args));
	return __vedaLaunchKernel(func, stream, args, 0, vargs...);
}

#endif
