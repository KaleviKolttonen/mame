// license:BSD-3-Clause
// copyright-holders:Roberto Fresca
/***************************************************************************

  Note Chance
  Banpresto, 199?

  Screenless system.

  Driver by Roberto Fresca.

****************************************************************************

  Hardware Notes...

  Board etched PT-877.

  CPU:
  1x TOSHIBA TMPZ84C00AP-6 (Z80).

  Sound Device:
  1x OKI6295 or similar...

  ROM:
  1x 27C040 (SND ROM).
  1x 27C256 (PRG ROM).

  RAM:
  1x BR6265A-10LL (8K x 8 CMOS SRAM).

  Backup System:
  1x Fujitsu MB3780A (Battery Backup IC)
  1x Unknown battery.

  Clock:
  1x Xtal: 8.44800 MHz.

  Other:
  1x 8-DIP switches bank.
  1x volume pot.
  1x 60-pins female connector. (CN2: 3 rows of 21, 18, 21)
  1x 10-pins male connector (CN1: for power supply)


  CN1 connector:

  01- DC +12V.
  02- GND
  03- DC +12V.
  04- GND
  05- DC +5V.
  06- GND
  07- 
  08- ACFAIL
  09- DC 12V
  10- GND

  
****************************************************************************

  Specs...

  Cab Size: 470 mm x 450 mm x 1350 mm.
  Weight:   45 Kg.
  Voltage:  AC 90/110 V., 50/60 Hz.
  Power:    30 W.

  
****************************************************************************

  About lamps...

  (nothing yet)

***************************************************************************/

#include "emu.h"
#include "cpu/z80/z80.h"
#include "sound/okim6295.h"
#include "speaker.h"

#define MASTER_CLOCK     8448800
#define CPU_CLOCK        MASTER_CLOCK / 2
#define SND_CLOCK        1056000          // unverified resonator


class notechan_state : public driver_device
{
public:
	notechan_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu") { }

	required_device<cpu_device> m_maincpu;

};


/*********************************************
*            Read/Write Handlers             *
*********************************************/



/*********************************************
*           Memory Map Definition            *
*********************************************/

static ADDRESS_MAP_START( notechan_map, AS_PROGRAM, 8, notechan_state )
	AM_RANGE(0x0000, 0x7fff) AM_ROM
	AM_RANGE(0xa000, 0xbfff) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( notechan_port_map, AS_IO, 8, notechan_state )
	ADDRESS_MAP_GLOBAL_MASK(0xff)
	AM_RANGE(0x00, 0x00) AM_DEVREADWRITE("oki", okim6295_device, read, write)  // wrong... just a placeholder. 00h seems unused.
	AM_RANGE(0xf8, 0xf8) AM_WRITENOP    // watchdog reset?
ADDRESS_MAP_END

/*
  F0:  -W  78
  F8:  RW  (alternate 00 & 02 and ends with C0)
  FA:  -W  00 (from $A4B1 contents transferred to reg A)
  FB:  R-  ???
  FF:  -W  00 (at start, and then often later)

  Need more analysis...

*/

/*********************************************
*          Input Ports Definitions           *
*********************************************/

static INPUT_PORTS_START( notechan )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-1") PORT_CODE(KEYCODE_1)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-2") PORT_CODE(KEYCODE_2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-3") PORT_CODE(KEYCODE_3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-4") PORT_CODE(KEYCODE_4)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-5") PORT_CODE(KEYCODE_5)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-6") PORT_CODE(KEYCODE_6)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-7") PORT_CODE(KEYCODE_7)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("0-8") PORT_CODE(KEYCODE_8)

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-1") PORT_CODE(KEYCODE_Q)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-2") PORT_CODE(KEYCODE_W)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-3") PORT_CODE(KEYCODE_E)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-4") PORT_CODE(KEYCODE_R)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-5") PORT_CODE(KEYCODE_T)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-6") PORT_CODE(KEYCODE_Y)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-7") PORT_CODE(KEYCODE_U)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("1-8") PORT_CODE(KEYCODE_I)

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-1") PORT_CODE(KEYCODE_A)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-2") PORT_CODE(KEYCODE_S)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-3") PORT_CODE(KEYCODE_D)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-4") PORT_CODE(KEYCODE_F)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-5") PORT_CODE(KEYCODE_G)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-6") PORT_CODE(KEYCODE_H)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-7") PORT_CODE(KEYCODE_J)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("2-8") PORT_CODE(KEYCODE_K)

	PORT_START("IN3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-1") PORT_CODE(KEYCODE_Z)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-2") PORT_CODE(KEYCODE_X)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-3") PORT_CODE(KEYCODE_C)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-4") PORT_CODE(KEYCODE_V)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-5") PORT_CODE(KEYCODE_B)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-6") PORT_CODE(KEYCODE_N)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-7") PORT_CODE(KEYCODE_M)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("3-8") PORT_CODE(KEYCODE_L)

	PORT_START("DSW")
	PORT_DIPNAME( 0x01, 0x01, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x02, 0x02, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x02, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x08, 0x08, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x08, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x10, 0x10, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x10, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x20, 0x20, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x20, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x40, 0x40, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x80, DEF_STR( Unknown ) )
	PORT_DIPSETTING(    0x80, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END


/*********************************************
*               Machine Config               *
*********************************************/

static MACHINE_CONFIG_START( notechan )
	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80, CPU_CLOCK)  // unknown...
	MCFG_CPU_PROGRAM_MAP(notechan_map)
	MCFG_CPU_IO_MAP(notechan_port_map)

	/* NO VIDEO */

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("speaker")

	MCFG_OKIM6295_ADD("oki", SND_CLOCK, PIN7_HIGH) /* clock frequency & pin 7 not verified */
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "speaker", 1.0)
MACHINE_CONFIG_END


/*********************************************
*                  Rom Load                  *
*********************************************/

ROM_START( notechan )
	ROM_REGION( 0x40000, "maincpu", 0 )
	ROM_LOAD( "p-650_p1_ver1.10.ic15",  0x0000, 0x8000, CRC(f4878009) SHA1(e8b7f4d84a8995f60d59fe9f4b25e2d1babcf923) )

	ROM_REGION( 0x80000, "oki", 0 ) /* Audio ADPCM */
	ROM_LOAD( "p-650_s1_ver1.00.ic21",  0x0000, 0x80000, CRC(1b8c835b) SHA1(73749c0077605f9ad56e9dd73b60ee04fe54eb73) )
ROM_END


/*********************************************
*                Game Drivers                *
*********************************************/

//    YEAR  NAME      PARENT  MACHINE   INPUT     STATE           INIT  ROT    COMPANY      FULLNAME      FLAGS
GAME( 199?, notechan, 0,      notechan, notechan, notechan_state, 0,    ROT0, "Banpresto", "Note Chance", MACHINE_NOT_WORKING )