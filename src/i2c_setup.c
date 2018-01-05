
#include "inc/hw_memmap.h"
#include "cs.h"

#ifdef __MSP430_HAS_EUSCI_Bx__
#include "eusci_b_i2c.h"
#include "i2c_setup.h"
#include "driverlib.h"

#include <assert.h>

void EUSCI_B_I2C_setup(void) {
  /*
  * Select Port 1
  * Set Pin 6, 7 to input Secondary Module Function:
  *   (UCB0SIMO/UCB0SDA, UCB0SOMI/UCB0SCL)
  */
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_P1,
    GPIO_PIN6 + GPIO_PIN7,
    GPIO_SECONDARY_MODULE_FUNCTION
  );
	//PRINTF("set periph move\r\n");

	EUSCI_B_I2C_initMasterParam param = {0};
  param.selectClockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK;
  param.i2cClk = CS_getSMCLK();
  param.dataRate = EUSCI_B_I2C_SET_DATA_RATE_400KBPS;
  param.byteCounterThreshold = 0;
  param.autoSTOPGeneration = EUSCI_B_I2C_NO_AUTO_STOP;
  //PRINTF("Done param init\r\n");

  //EUSCI_B_I2C_initMaster(EUSCI_B0_BASE, &param);
  // Dumpting the contents here because clang and gcc must have different
  // calling conventions, or at least different inlining conventions!

  uint16_t preScalarValue;

  //Disable the USCI module and clears the other bits of control register
  HWREG16(EUSCI_B0_BASE + OFS_UCBxCTLW0) = UCSWRST;

  //Configure Automatic STOP condition generation
  HWREG16(EUSCI_B0_BASE + OFS_UCBxCTLW1) &= ~UCASTP_3;
  HWREG16(EUSCI_B0_BASE + OFS_UCBxCTLW1) |= param.autoSTOPGeneration;

  //Byte Count Threshold
  HWREG16(EUSCI_B0_BASE + OFS_UCBxTBCNT) = param.byteCounterThreshold;
  /*
   * Configure as I2C master mode.
   * UCMST = Master mode
   * UCMODE_3 = I2C mode
   * UCSYNC = Synchronous mode
   */
  HWREG16(EUSCI_B0_BASE + OFS_UCBxCTLW0) |= UCMST + UCMODE_3 + UCSYNC;

  //Configure I2C clock source
  HWREG16(EUSCI_B0_BASE +
          OFS_UCBxCTLW0) |= (param.selectClockSource + UCSWRST);

  /*
   * Compute the clock divider that achieves the fastest speed less than or
   * equal to the desired speed.  The numerator is biased to favor a larger
   * clock divider so that the resulting clock is always less than or equal
   * to the desired clock, never greater.
   */
  // For now, this is hardcoded to 8000000 / 40000 precalculated since clang
  // doesn't have a __udivsi function **sigh**
  // TODO make this rely on macros at least!
  //preScalarValue = (uint16_t)(param.i2cClk / param.dataRate);
  preScalarValue = (uint16_t)(200);
  HWREG16(EUSCI_B0_BASE + OFS_UCBxBRW) = preScalarValue;
  // Done i2c initialization

}



#endif

