// PCE_D122Test.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#if defined(__linux__)
#include <unistd.h> // for usleep()
#define Sleep(_ms) usleep((_ms)*1000)
#else
#include <windows.h> // for Sleep()
#endif
#include "PCI_L122_DSF.h"
#include "CMNet.h"

static U16 SwitchCardNo = 0;
static U16 BaudRate = 3; // 20M
////////////////////////////////////////////////////////////////////////////////

int MNetTest(U16 SwitchCardNo)
{
    I16 rc = 0;

    for (U16 ring = 0; ring < 2; ring++)
    {
        rc = _mnet_set_ring_config(ring, BaudRate);
        if (rc < 0)
            printf("_mnet_set_ring_config() error: %d\n", rc);
        assert(rc == 0);

        rc = _mnet_reset_ring(ring);
        if (rc < 0)
            printf("_mnet_reset_ring() error: %d\n", rc);
        assert(rc == 0);
        Sleep(50);

        rc = _mnet_start_ring(ring);
        if (rc < 0)
            printf("_mnet_start_ring() error: %d\n", rc);
        assert(rc == 0);

        U32 devTable[2] = {0};
        rc = _mnet_get_ring_active_table(ring, devTable);
        if (rc < 0)
            printf("_mnet_get_ring_active_table() error: %d\n", rc);
        assert(rc == 0);

        printf("Ring%u DevTable[2]: {0x%lX, 0x%lX}\n", ring, devTable[0], devTable[1]);
        for (U16 ip = 0; ip < 64; ip++)
        {
            if (devTable[ip / 32] & (0x1 << (ip % 32)))
            {
                U8 slvType;
                rc = _mnet_get_slave_type(ring, ip, &slvType);
                if (rc < 0)
                    printf("_mnet_get_slave_type() error: %d\n", rc);
                assert(rc == 0);

                U8 outPorts = 0;
                switch (slvType)
                {
                case G9002_Q32:
                    outPorts = 4;
                    printf("MNet Slave %u: 32-out DIO\n", ip);
                    break;
                case G9002_I16Q16:
                    outPorts = 2;
                    printf("MNet Slave %u: 16-in/16-out DIO\n", ip);
                    break;
                default:
                    printf("MNet Slave %u: 0x%X\n", ip, slvType);
                    break;
                }

                if (outPorts > 0)
                {
                    for (size_t i = 0; i < 800; i++)
                    {
                        U8 portVal = (1 << (i % 8));
                        for (U8 pn = 4 - outPorts; pn < 4; pn++)
                            _mnet_io_output(ring, ip, pn, portVal);
                        Sleep(10);
                    }
                }
            }
        }
    }

    return rc;
}

int main(int argc, char *argv[])
{
    I16 rc;
    U16 existCards = 0;

    if (argc != 2)
        printf("Usage: %s [BAUD RATE]\n", argv[0]);
    else {
        BaudRate = (U16)atoi(argv[1]);
        if (BaudRate > 3) {
            BaudRate = 3;
            printf("Invalid baud rate.\n");
        }
    }
    printf("Test with MNet baud rate: %u\n", BaudRate);
    printf("\n");

    rc = _l122_dsf_open(&existCards);
    if (rc < 0)
        printf("_l122_dsf_open error: %d\n", rc);
    else if (existCards == 0)
        printf("PCE-D122 doesn't exist!!\n");
    else
    {
        printf("ExistCards: %d\n", existCards);
        _l122_dsf_get_switch_card_num(0, &SwitchCardNo);
        printf("SwitchCardNo: 0x%X\n", SwitchCardNo);
        U16 ver;
        _l122_dsf_get_cpld_version(SwitchCardNo, &ver);
        printf("FPGA ver: 0x%X\n", ver);
        U8 cardType;
        _l122_dsf_get_card_type(SwitchCardNo, &cardType);
        if (cardType == CARD_LPE_L122)
            printf("Card Type: LPE-L122\n");
        else
            printf("Card Type: 0x%X\n", cardType);
        MNetTest(SwitchCardNo);
    }
    rc = _l122_dsf_close();

    printf("\n");

    return 0;
}
