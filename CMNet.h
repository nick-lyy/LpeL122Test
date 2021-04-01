#ifndef __MNET_H__
#define __MNET_H__

#include "type_def.h"

////////////////////////////////////////////////////////////////////////////////
//                                Error Code                                  //
////////////////////////////////////////////////////////////////////////////////
#define ERR_NoError                            0
#define ERR_MNET_Ring_Used                    -1
#define ERR_Invalid_Ring                      -2
#define ERR_Invalid_Slave                     -3
#define ERR_Invalid_Hardware                  -4
#define ERR_Invalid_Sync_Object               -5
#define ERR_RingCommunicationError            -8
#define ERR_RingCommunicationTimeOut          -9
#define ERR_DataFifoFull                     -10
#define ERR_DataCommunicationFailed          -11
#define ERR_InvalidMaxVel                    -16
#define ERR_ObsoleteFunction                 -34
#define ERR_G94_RECEIVE_TimeOut              -36
#define ERR_G94_CPURead                      -37
#define ERR_G94_MsgCommunication             -38
#define ERR_G94_MsgSize                      -39
#define ERR_G94_CommTimeOut                  -40
#define ERR_InvalidAxisNo                    -50
#define ERR_InvalidParameter_1               -51
#define ERR_InvalidParameter_2               -52
#define ERR_InvalidParameter_3               -53
#define ERR_InvalidParameter_4               -54
#define ERR_InvalidParameter_5               -55
#define ERR_InvalidParameter_6               -56
#define ERR_InvalidParameter_7               -57
#define ERR_InvalidParameter_8               -58
#define ERR_InvalidParameter_9               -59
#define ERR_InvalidParameter_10              -60
#define ERR_InvalidParameter_11              -61
#define ERR_InvalidParameter_12              -62
#define ERR_InvalidParameter_13              -63
#define ERR_FailGetDeviceTable               -74
#define ERR_NoDeviceFound                    -75
#define ERR_SlowDownPointError              -101
#define ERR_M1A_InvalidCheckCode            -103
#define ERR_M1A_NotInitializedYet           -105
#define ERR_AI8_RegisterWriteFail           -111
#define ERR_AI8_RegisterReadFail            -112
#define ERR_AI8_DeviceTypeNotCorrect        -113
#define ERR_AI8_IncorrectChannelNo          -114
#define ERR_AI8_IncorrectValueOfGain        -115
#define ERR_AI8_DeviceNotEnable             -116
#define ERR_AI8_ChannelNotEnable            -117
#define ERR_AI8_MOSI_Busy                   -118
#define ERR_AI8_MISO_Busy                   -119
#define ERR_AI8_Read_EEPROM                 -120
#define ERR_AI8_AdjustFail                  -121
#define ERR_AO4_RegisterWriteFail           -131
#define ERR_AO4_RegisterReadFail            -132
#define ERR_AO4_RegisterReadTimeout         -133
#define ERR_AO4_DeviceTypeNotCorrect        -134
#define ERR_AO4_ChannelNoNotCorrect         -135
#define ERR_AO4_OutputValueNotCorrect       -136
#define ERR_AO4_CoarseGainValueNotCorrect   -137
#define ERR_AO4_FineGainValueNotCorrect     -138
#define ERR_AO4_OffsetValueNotCorrect       -139
#define ERR_AO4_OutputVoltageNotCorrect     -140
#define ERR_AO4_FlashReadFail               -141
#define ERR_AO4_FlashWriteFail              -142
#define ERR_AO4_FlashEraseFail              -143
#define ERR_FunctionNotSupport              -151
#define ERR_InvalidDeviceType               -152
#define ERR_GetDLLPath                      -170
#define ERR_GetDLLVersion                   -171
#define ERR_LoadFileFailed                  -172
#define ERR_AutoCmpSetFifoFailed            -173
#define ERR_InvalidOperation                -174
#define ERR_OperationFailed                 -175

////////////////////////////////////////////////////////////////////////////////
//                           Slave Type Definition                            //
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    // Axis
    G9103_M1X1 = 0xA2,
    G9003_M1X1 = 0xA3,
    G9004_M304T = 0xA8,
    G9004_M4A2 = 0xA9,
    // DIO (32 In/Out)
    G9002_Q32 = 0xB0,
    G9002_I16Q16 = 0xB2,
    G9002_I32 = 0xB4,
    // DIO (64 In/Out)
    G9004_I64 = 0xBC,
    G9004_I32Q32 = 0xBD,
    G9004_Q64 = 0xBE,
    // DIO (96 In/Out)
    G9004_I96 = 0xB5,
    G9004_I80Q16 = 0xB6,
    G9004_I64Q32 = 0xB7,
    G9004_I48Q48 = 0xB8,
    G9004_I32Q64 = 0xB9,
    G9004_I16Q80 = 0xBA,
    G9004_Q96 = 0xBB,
    // DIO (16 In/Out)
    G9102_I16 = 0xC0,
    G9102_I8Q8 = 0xC4,
    G9102_Q16 = 0xC7,
    G9205_I16 = 0xC8,
    G9205_I8Q8 = 0xCC,
    G9205_Q16 = 0xCF,
    // Misc.
    G9004_A104 = 0xD0,  // 106-A104
    G9004_A180 = 0xD1,  // 106-A180
    G9004_P144 = 0xD2,  // 108-P144
    G9004_C144 = 0xD3,  // 108-C144
    G9004_C144F = 0xD6, // 108-C144F
    G9004_A222 = 0xD4,  // 108-A222
    G9004_A204 = 0xD5,  // 108-A204
    G9004_A322 = 0xD7,  // 108-A322
    G9004_MSG = 0xE0,
    G9004_UNKNOWN = 0xFF,
} ESlaveType;

////////////////////////////////////////////////////////////////////////////////
//                            Function Declaration                            //
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
    //
    I16 PASCAL _mnet_open(void);
    I16 PASCAL _mnet_close(void);
    //
    // Ring Operation
    I16 PASCAL _mnet_reset_ring(U16 RingNo);
    I16 PASCAL _mnet_start_ring(U16 RingNo);
    I16 PASCAL _mnet_stop_ring(U16 RingNo);
    I16 PASCAL _mnet_set_ring_config(U16 RingNo, U16 BaudRate);
    I16 PASCAL _mnet_get_ring_count(U16 *Count);
    //
    // Slaves
    I16 PASCAL _mnet_get_ring_active_table(U16 RingNo, U32 *DevTable);
    I16 PASCAL _mnet_get_slave_type(U16 RingNo, U16 SlaveIP, U8 *SlaveType);
    I16 PASCAL _mnet_get_msg_slave_type(U16 RingNo, U16 SlaveIP, U16 *Type);
    //
    // Communication Status & Error
    I16 PASCAL _mnet_get_ring_status(U16 RingNo, U16 *Status);
    I16 PASCAL _mnet_get_com_status(U16 RingNo);
    I16 PASCAL _mnet_get_ring_error_counter(U16 RingNo, U16 *ErrCount);
    I16 PASCAL _mnet_reset_ring_error_counter(U16 RingNo);
    I16 PASCAL _mnet_get_communication_error_flag(U16 RingNo, U16 SlaveIP, U8 *IsError);
    I16 PASCAL _mnet_reset_communication_error_flag(U16 RingNo, U16 SlaveIP);
    I16 PASCAL _mnet_get_communication_error_table(U16 RingNo, U32 ErrTable[2]);
    I16 PASCAL _mnet_reset_communication_error_table(U16 RingNo);
    I16 PASCAL _mnet_set_io_error_check(U16 RingNo, U8 Enabled);
    //
    // Digital I/O Slave
    I16 PASCAL _mnet_io_input(U16 RingNo, U16 SlaveIP, U8 PortNo);
    I16 PASCAL _mnet_io_output(U16 RingNo, U16 SlaveIP, U8 PortNo, U8 Val);
    I16 PASCAL _mnet_io_input_all(U16 RingNo, U16 SlaveIP, U8 Value[]);
    I16 PASCAL _mnet_io_input_all_ex(U16 RingNo, U16 SlaveIP, U8 Value[]);
    I16 PASCAL _mnet_io_output_all(U16 RingNo, U16 SlaveIP, U8 Value[]);
    I16 PASCAL _mnet_bit_io_input(U16 RingNo, U16 SlaveIP, U8 PortNo, U8 BitNo, U8 *OnOff);
    I16 PASCAL _mnet_bit_io_output(U16 RingNo, U16 SlaveIP, U8 PortNo, U8 BitNo, U8 OnOff);
    I16 PASCAL _mnet_bit_io_toggle(U16 RingNo, U16 SlaveIP, U8 PortNo, U8 BitNo);
    I16 PASCAL _mnet_io_memory_input(U16 RingNo, U32 *DataInArray);
    I16 PASCAL _mnet_io_memory_input_ex(U16 RingNo, U32 *DataInArray);
    I16 PASCAL _mnet_io_memory_output(U16 RingNo, U32 *DataOutArray);
    //
    // Misc.
    I16 PASCAL _mnet_get_DLL_path(char *lpFilePath, U32 nSize, U32 *nLength);
    I16 PASCAL _mnet_get_DLL_version(char *lpBuf, U32 nSize, U32 *nLength);
    //
#ifdef __cplusplus
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#endif //__MNET_H__
