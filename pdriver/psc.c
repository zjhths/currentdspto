/**
 * \file      psc.c
 *
 * \brief     This file contains the device abstraction layer APIs for the
 *            PSC module. There are APIs here to enable power domain,
 *            transitions for a particular module
 */

/* HW Macros */
#include "hw_types.h"

/* DSP System Defines */
#include "hw_psc_C6748.h"

#include "psc.h"

/**************************************************************************
  API FUNCTION DEFINITIONS
***************************************************************************/

/**
 *
 *  \brief   This function sets the requested module in the required state
 *
 * \param     baseAdd         Memory address of the PSC instance used.
 * \param     moduleId        The module number of the module to be commanded.
 * \param     powerDomain     The power domain of the module to be commanded.
 * \param     flags           This contains the flags that is a logical OR of
 *                            the commands that can be given to a module.
 *
 * \return                    0 in case of successful transition, -1 otherwise.
 *
 */

int PSCModuleControl (unsigned int baseAdd, unsigned int moduleId,
                         unsigned int powerDomain, unsigned int flags)
{
    volatile unsigned int timeout = 0xFFFFFF;
    int    retVal = 0;
    unsigned int    status = 0;

    HWREG(baseAdd +  PSC_MDCTL(moduleId)) = (flags & PSC_MDCTL_NEXT);

    if (powerDomain == 0)
    {
        HWREG(baseAdd + PSC_PTCMD) = PSC_PTCMD_GO0;
    }
    else
    {
        HWREG(baseAdd + PSC_PTCMD) = PSC_PTCMD_GO1;
    }

    if (powerDomain == 0)
    {
        do {
            status = HWREG(baseAdd + PSC_PTSTAT) & PSC_PTSTAT_GOSTAT0;
        } while (status && timeout--);
    }
    else
    {
        do {
            status = HWREG(baseAdd + PSC_PTSTAT) & PSC_PTSTAT_GOSTAT1;
        } while (status && timeout--);
    }

    if (timeout != 0)
    {
        timeout = 0xFFFFFF;
        status = flags & PSC_MDCTL_NEXT;
        do {
            timeout--;
        } while(timeout &&
                (HWREG(baseAdd + PSC_MDSTAT(moduleId)) & PSC_MDSTAT_STATE) != status);
    }

    if (timeout == 0)
    {
        retVal = -1;
    }

    return retVal;
}

