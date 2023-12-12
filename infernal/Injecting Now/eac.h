//#define DllExport extern "C" __declspec( dllexport )
//
//struct eac_info
//{
//    uint32_t entry;
//    uint32_t cheat_base;
//};
//
//namespace eac
//{
//    inline uint64_t base;
//    inline uint64_t entry;
//};
//
////#pragma section(".gay")
////DllExport __declspec(allocate(".gay")) eac_info eac_data;
////inline eac_info eac_data;
//
//#pragma section(".text")
//DllExport __declspec(allocate(".text")) eac_info eac_data;
//inline eac_info eac_data;