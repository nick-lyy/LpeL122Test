#ifndef __PCI_L122_DSF_H__
#define __PCI_L122_DSF_H__

#include "type_def.h"


#define MAX_SWITCH_CARD_NUM 15

// +ErrorCode Definition
#define ERR_NoError                     0
#define ERR_InvalidSwitchCardNumber    -1
#define ERR_SwitchCardNumberRepeated   -2
#define ERR_OpenCardFailed             -3
#define ERR_CardNotExist               -4
#define ERR_InvalidParameter1          -5
#define ERR_InvalidParameter2          -6
#define ERR_InvalidParameter3          -7
#define ERR_InvalidParameter4          -8
#define ERR_InvalidParameter5          -9
#define ERR_InvalidParameter6         -10
#define ERR_InvalidParameter7         -11
#define ERR_InvalidParameter8         -12
#define ERR_InvalidParameter9         -13
#define ERR_GetSecureIdFailed         -14
#define ERR_GenAesKeyFailed           -15
#define ERR_NotSupported              -17
#define ERR_SetInterruptFailed        -18
#define ERR_WaitInterruptFailed       -19
#define ERR_WaitInterruptTimeout      -20
#define ERR_InvalidBoardID            -21
#define ERR_LinkMNetFailed            -22
#define ERR_RingSlotFull              -23
#define ERR_SetAutoCmpFifoFailed      -24
#define ERR_SetAnalogOutputFailed     -25
#define ERR_DriverOperationFailed     -26
// -ErrorCode Definition

enum EBaudRate
{
    BR_2_5M = 0,
    BR_5M = 1,
    BR_10M = 2,
    BR_20M = 3,
};

enum ECardType
{
    CARD_UNKNOWN = 0,
    CARD_PCI_L122_DSF = 1,
    CARD_LPE_L122 = 3,
    CARD_PCE_L122_DCO = 4,
    CARD_PCE_L123_DCO = 5,
    CARD_APE_L122 = 6,
    CARD_SPE_L122 = 7,
    CARD_SPE_L121 = 8,
    CARD_SPE_C116D = 9,
};


#ifdef __cplusplus
extern "C" {
#endif
    //
    // Initial
    I16 PASCAL _l122_dsf_open(U16 *ExistCards);
    I16 PASCAL _l122_dsf_open_card(U16 CardTypes, U16 *ExistCards);
    I16 PASCAL _l122_dsf_close();
    I16 PASCAL _l122_dsf_check_switch_card_num(U16 SwitchCardNo, U8 *IsExist);
    I16 PASCAL _l122_dsf_get_switch_card_num(U16 CardIndex, U16 *SwitchCardNo);
    I16 PASCAL _l122_dsf_get_start_ring_num(U16 SwitchCardNo, U16 *RingNo);
    I16 PASCAL _l122_dsf_set_ring_config(U16 SwitchCardNo, U16 RingOfCard, U8 BaudRate);
    I16 PASCAL _l122_dsf_get_card_type(U16 SwitchCardNo, U8* CardType);
    I16 PASCAL _l122_dsf_get_cpld_version(U16 SwitchCardNo, U16 *CpldVer);
    //
    // Local Digital I/O
    I16 PASCAL _l122_dsf_read_local_input(U16 SwitchCardNo, U8* Val);
    I16 PASCAL _l122_dsf_read_local_output(U16 SwitchCardNo, U8* Val);
    I16 PASCAL _l122_dsf_write_local_output(U16 SwitchCardNo, U8 Val);
    //
    // AES
    I16 PASCAL _l122_dsf_get_secure_id(U16 SwitchCardNo, U8 SecureID[8]);
    I16 PASCAL _l122_dsf_gen_aes_key(U16 SwitchCardNo, U8 SI_Key[16], U8 SecureID[8], U8 AES_Key[16]);
    I16 PASCAL _l122_dsf_check_aes_key(U16 SwitchCardNo, U8 SI_Key[16], U8 AES_Key[16], U8* Validity);
    //
    // Interrupt
    I16 PASCAL _l122_dsf_int_control(U16 SwitchCardNo, U16 IntType);
    I16 PASCAL _l122_dsf_int_check(U16 SwitchCardNo, U16 *IntType);
    I16 PASCAL _l122_dsf_int_wait(U16 SwitchCardNo, U32 TimeoutInMs);
    //
    // Encoder (PCE-L122-DCO & PCE-L123-DCO & SPE-L121 Only)
    I16 PASCAL _l122_dsf_set_encoder_mode(U16 SwitchCardNo, U16 EncNo, U16 Mode);
    I16 PASCAL _l122_dsf_get_encoder(U16 SwitchCardNo, U16 EncNo, I32 *EncPos);
    I16 PASCAL _l122_dsf_set_encoder(U16 SwitchCardNo, U16 EncNo, I32 EncPos);
    //
    // Auto Compare (PCE-L122-DCO & PCE-L123-DCO & SPE-L121 Only)
    I16 PASCAL _l122_dsf_set_auto_compare_source(U16 SwitchCardNo, U16 CmpNo, U16 SrcEncNo);
    I16 PASCAL _l122_dsf_get_auto_compare_count(U16 SwitchCardNo, U16 CmpNo, U32 *Count);
    I16 PASCAL _l122_dsf_get_auto_compare_status(U16 SwitchCardNo, U16 CmpNo, U16 *OnOff);
    I16 PASCAL _l122_dsf_set_auto_compare_trigger(U16 SwitchCardNo, U16 CmpNo, U16 Level, U16 Width);
    I16 PASCAL _l122_dsf_set_auto_compare_function(U16 SwitchCardNo, U16 CmpNo, U8 Dir, I32 StrPos, I32 Interval, U32 TrgCnt);
    I16 PASCAL _l122_dsf_set_auto_compare_table(U16 SwitchCardNo, U16 CmpNo, U8 Dir, U32 Size, I32 *Table);
    I16 PASCAL _l122_dsf_start_auto_compare(U16 SwitchCardNo, U16 CmpNo, U16 OnOff);
    I16 PASCAL _l122_dsf_force_trigger_output(U16 SwitchCardNo, U16 CmpNo);
    //
    // DO Generator (PCE-L122-DCO & PCE-L123-DCO & SPE-L121 Only)
    I16 PASCAL _l122_dsf_start_local_output(U16 SwitchCardNo, U16 DoNo, U16 OnTime, U16 OffTime, U16 Count);
    I16 PASCAL _l122_dsf_set_local_output_time(U16 SwitchCardNo, U16 DoNo, U16 OnTime, U16 OffTime);
    I16 PASCAL _l122_dsf_stop_local_output(U16 SwitchCardNo, U16 DoNo);
    I16 PASCAL _l122_dsf_get_local_output_count(U16 SwitchCardNo, U16 DoNo, U16 *Count);
    //
    // FIFO Latch (PCE-L122-DCO & PCE-L123-DCO & SPE-L121 Only)
    I16 PASCAL _l122_dsf_start_fifo_latch(U16 SwitchCardNo, U16 LtcNo, U16 SrcEncNo, U16 Mode);
    I16 PASCAL _l122_dsf_stop_fifo_latch(U16 SwitchCardNo, U16 LtcNo);
    I16 PASCAL _l122_dsf_get_fifo_latch_data_length(U16 SwitchCardNo, U16 LtcNo, U16 *Length);
    I16 PASCAL _l122_dsf_get_fifo_latch_data(U16 SwitchCardNo, U16 LtcNo, U16 MaxSize, U16 *Size, I32 *LtcTable);
    I16 PASCAL _l122_dsf_set_fifo_latch_filter(U16 SwitchCardNo, U16 Filter);
    //
    // Analog Output (SPE-L121 Only)
    I16 PASCAL _l122_dsf_set_analog_output(U16 SwitchCardNo, U16 ChannelNo, F64 Volt);
    I16 PASCAL _l122_dsf_set_analog_output_all(U16 SwitchCardNo, F64 Volt[4]);
    I16 PASCAL _l122_dsf_set_analog_output_value(U16 SwitchCardNo, U16 ChannelNo, I16 Val);
    I16 PASCAL _l122_dsf_set_analog_output_value_all(U16 SwitchCardNo, I16 Val[4]);
    //
#ifdef __cplusplus
}
#endif

#endif //__PCI_L122_DSF_H__
