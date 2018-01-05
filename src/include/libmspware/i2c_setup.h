
#ifndef __MSP430WARE_I2C_SETUP_H__
#define __MSP430WARE_I2C_SETUP_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_EUSCI_Bx__

//*****************************************************************************
//
//! \brief Initializes the i2c peripheral on an msp430fr5949
//!
//! 
//! \param None
//!
//! \return None
//
//*****************************************************************************
extern void EUSCI_B_I2C_setup(void);


#endif //HAS_EUSCI_Bx__

#endif // I2C_SETUP_H
