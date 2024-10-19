/**
 * \file IfxGtm_Atom_Timer.h
 * \brief GTM TIMER details
 * \ingroup IfxLld_Gtm
 *
 * \version iLLD_1_0_1_17_0
 * \copyright Copyright (c) 2023 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 * \defgroup IfxLld_Gtm_Atom_Timer_Usage How to use the GTM ATOM Timer Driver
 * \ingroup IfxLld_Gtm_Atom_Timer
 *
 *   This driver implements the timer functionalities as defined by \ref library_srvsw_stdif_timer.
 *   The user is free to use either the driver specific APIs below or to used the \ref library_srvsw_stdif_timer "standard interface APIs".
 *
 * \section Specific Specific implementation
 *   Implementation is similar to \ref IfxLld_Gtm_Tom_Timer.
 *
 *  \todo Add documentation
 *
 *   For a detailed configuration of the microcontroller, see \ref IfxGtm_Atom_Timer_init().
 *
 * \section Example Usage example
 *   Initialisation:
 * \code
 *   IfxGtm_Atom_Timer_Config driverConfig;
 *   IfxGtm_Atom_Timer driverData;
 *   IfxStdIf_Timer timer;
 *   IfxGtm_Atom_Timer_initConfig(&driverConfig, &MODULE_GTM);
 *   IfxGtm_Atom_Timer_init (&driverData, &driverConfig);
 *    boolean IfxGtm_Atom_Timer_stdIfTimerInit(&timer, &driverData);
 * \endcode
 *
 *   During run-time, \ref library_srvsw_stdif_timer "the interface functions" should be used:
 * \code
 *   IfxStdIf_Timer_run(timer);
 *   IfxStdIf_Timer_disableUpdate(timer);
 *   IfxStdIf_Timer_setPeriod(timer, period);
 *  IfxStdIf_Timer_applyUpdate(timer);
 * \endcode
 *
 * \defgroup IfxLld_Gtm_Atom_Timer ATOM Timer Interface Driver
 * \ingroup IfxLld_Gtm_Atom
 * \defgroup IfxLld_Gtm_Atom_Timer_Timer_StdIf_Functions Timer StdIf Functions
 * \ingroup IfxLld_Gtm_Atom_Timer
 * \defgroup IfxLld_Gtm_Atom_Timer_Timer_Functions Timer Functions
 * \ingroup IfxLld_Gtm_Atom_Timer
 * \defgroup IfxLld_Gtm_Atom_Timer_Data_Structures Data Structures
 * \ingroup IfxLld_Gtm_Atom_Timer
 */

#ifndef IFXGTM_ATOM_TIMER_H
#define IFXGTM_ATOM_TIMER_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_PinMap/IfxGtm_PinMap.h"
#include "Gtm/Std/IfxGtm_Atom.h"
#include "Gtm/Std/IfxGtm_Cmu.h"
#include "Gtm/Std/IfxGtm_Dtm.h"
#include "StdIf/IfxStdIf_Timer.h"

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Gtm_Atom_Timer_Data_Structures
 * \{ */
/** \brief Structure for the timer base
 */
typedef struct
{
    Ifx_TimerValue          period;               /**< \brief Timer period in ticks (cached value) */
    boolean                 triggerEnabled;       /**< \brief If TRUE, the trigger functionality is Initialised */
    float32                 clockFreq;            /**< \brief Timer input clock frequency (cached value) */
    IfxStdIf_Timer_CountDir countDir;             /**< \brief Timer counting mode */
} IfxGtm_Atom_Timer_Base;

/** \} */

/** \addtogroup IfxLld_Gtm_Atom_Timer_Data_Structures
 * \{ */
/** \brief TOM Timer interface
 */
typedef struct
{
    IfxGtm_Atom_Timer_Base base;                   /**< \brief Timer base structure */
    Ifx_GTM               *gtm;                    /**< \brief GTM module used for the timer functionality */
    Ifx_GTM_ATOM          *atom;                   /**< \brief ATOM used for the timer functionality */
    Ifx_GTM_ATOM_AGC      *agc;                    /**< \brief Pointer to the AGC object */
    IfxGtm_Atom            atomIndex;              /**< \brief Enum for ATOM objects */
    IfxGtm_Atom_Ch         timerChannel;           /**< \brief ATOM channel used for the timer */
    IfxGtm_Atom_Ch         triggerChannel;         /**< \brief ATOM channel used for the trigger, if identical to the timerChannel, the trigger interrupt is having the same interrupt level as  the timer interrupt */
    uint16                 channelsMask;           /**< \brief Mask for channels to be modified together */
    Ifx_TimerValue         offset;                 /**< \brief Timer initial offset in ticks */
    Ifx_GTM_CDTM_DTM      *dtm;                    /**< \brief Pointer to DTM object used by ATOM */
    IfxGtm_Dtm_Ch          dtmChannel;             /**< \brief DTM channel */
    uint32                 agcDisableUpdate;       /**< \brief AGC value for disable update */
    uint32                 agcApplyUpdate;         /**< \brief AGC value for apply update */
} IfxGtm_Atom_Timer;

/** \brief Configuration structure for TOM Timer
 */
typedef struct
{
    IfxStdIf_Timer_Config  base;                 /**< \brief Standard interface timer configuration */
    Ifx_GTM               *gtm;                  /**< \brief GTM used for the timer functionality */
    IfxGtm_Atom            atom;                 /**< \brief ATOM used for the timer functionality */
    IfxGtm_Atom_Ch         timerChannel;         /**< \brief ATOM channel used for the timer */
    IfxGtm_Atom_ToutMap   *triggerOut;           /**< \brief ATOM channel used for the trigger output, can be identical to the timer channe */
    IfxGtm_Cmu_Clk         clock;                /**< \brief Timer input clock */
    IfxGtm_IrqMode         irqModeTimer;         /**< \brief Interrupt mode for the timer */
    IfxGtm_IrqMode         irqModeTrigger;       /**< \brief Interrupt mode for the trigger */
    IfxGtm_Dtm_ClockSource dtmClockSource;       /**< \brief DTM clock source */
    boolean                initPins;             /**< \brief TRUE: Initialize pins in driver
                                                  * FALSE: Don't initialize pins in driver : user handles separately */
} IfxGtm_Atom_Timer_Config;

/** \} */

/** \addtogroup IfxLld_Gtm_Atom_Timer_Timer_StdIf_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the timer event
 * \see IfxStdIf_Timer_AckTimerIrq
 * \param driver ATOM Timer interface Handle
 * \return Timer event
 */
IFX_EXTERN boolean IfxGtm_Atom_Timer_acknowledgeTimerIrq(IfxGtm_Atom_Timer *driver);

/** \brief Returns the trigger event
 * \see IfxStdIf_Timer_AckTriggerIrq
 * \param driver ATOM Timer interface Handle
 * \return Trigger event
 */
IFX_EXTERN boolean IfxGtm_Atom_Timer_acknowledgeTriggerIrq(IfxGtm_Atom_Timer *driver);

/** \brief Add a channel to the channel mask
 * Channels present in the mask are started, stopped, updated at the same time as the timer:
 * IfxGtm_Atom_Timer_applyUpdate, IfxGtm_Atom_Timer_disableUpdate, IfxGtm_Atom_Timer_stop, IfxGtm_Atom_Timer_run
 * \param driver ATOM Timer interface Handle
 * \param channel Channel to ba added to the mask
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_addToChannelMask(IfxGtm_Atom_Timer *driver, IfxGtm_Atom_Ch channel);

/** \brief Enables the transfer of the shadow registers
 * \see IfxStdIf_Timer_ApplyUpdate
 * \param driver ATOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_applyUpdate(IfxGtm_Atom_Timer *driver);

/** \brief Disables the upadte
 * \see IfxStdIf_Timer_DisableUpdate
 * \param driver ATOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_disableUpdate(IfxGtm_Atom_Timer *driver);

/** \brief Returns the frequency
 * \see IfxStdIf_Timer_GetFrequency
 * \param driver ATOM Timer interface Handle
 * \return Frequency
 */
IFX_EXTERN float32 IfxGtm_Atom_Timer_getFrequency(IfxGtm_Atom_Timer *driver);

/** \brief Returns the Input frequncy
 * \see IfxStdIf_Timer_GetInputFrequency
 * \param driver ATOM Timer interface Handle
 * \return Frequency
 */
IFX_EXTERN float32 IfxGtm_Atom_Timer_getInputFrequency(IfxGtm_Atom_Timer *driver);

/** \brief Returns the period of the timer
 * \see IfxStdIf_Timer_GetPeriod
 * \param driver ATOM Timer interface Handle
 * \return Period
 */
IFX_EXTERN Ifx_TimerValue IfxGtm_Atom_Timer_getPeriod(IfxGtm_Atom_Timer *driver);

/** \brief Returns the resolution
 * \see IfxStdIf_Timer_GetResolution
 * \param driver ATOM Timer interface Handle
 * \return Resolution
 */
IFX_EXTERN float32 IfxGtm_Atom_Timer_getResolution(IfxGtm_Atom_Timer *driver);

/** \brief Returns the trigger point
 * \param driver ATOM Timer interface Handle
 * \return Trigger point
 */
IFX_EXTERN Ifx_TimerValue IfxGtm_Atom_Timer_getTrigger(IfxGtm_Atom_Timer *driver);

/** \brief Runs the timer
 * \see IfxStdIf_Timer_Run
 * \param driver ATOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_run(IfxGtm_Atom_Timer *driver);

/** \brief Sets the frequency
 * \see IfxStdIf_Timer_SetFrequency
 * \param driver ATOM Timer interface Handle
 * \param frequency Frequency
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Atom_Timer_setFrequency(IfxGtm_Atom_Timer *driver, float32 frequency);

/** \brief Sets the period for the timer
 * \see IfxStdIf_Timer_SetPeriod
 * \param driver ATOM Timer interface Handle
 * \param period Period value
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Atom_Timer_setPeriod(IfxGtm_Atom_Timer *driver, Ifx_TimerValue period);

/** \brief Sets the single shot mode of the timer
 * \see IfxStdIf_Timer_SetSingleMode
 * \param driver ATOM Timer interface Handle
 * \param enabled If TRUE, sets the single shot mode
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_setSingleMode(IfxGtm_Atom_Timer *driver, boolean enabled);

/** \brief Sets the trigger
 * \see IfxStdIf_Timer_SetTrigger
 * \param driver ATOM Timer interface Handle
 * \param triggerPoint Trigger point value
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_setTrigger(IfxGtm_Atom_Timer *driver, Ifx_TimerValue triggerPoint);

/** \brief Initializes the standard interface timer
 * \param stdif Standard interface object, will be initialized by the function
 * \param driver Interface driver to be used by the standard interface. must be initialised separately
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Atom_Timer_stdIfTimerInit(IfxStdIf_Timer *stdif, IfxGtm_Atom_Timer *driver);

/** \brief Stops the timer
 * \see IfxStdIf_Timer_Stop
 * \param driver ATOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_stop(IfxGtm_Atom_Timer *driver);

/** \brief Updates the input frequency
 * \see IfxStdIf_Timer_UpdateInputFrequency
 * \param driver ATOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_updateInputFrequency(IfxGtm_Atom_Timer *driver);

/** \} */

/** \addtogroup IfxLld_Gtm_Atom_Timer_Timer_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the initial timer offset in ticks
 * \see IfxStdIf_Timer_GetOffset
 * \param driver ATOM Timer interface Handle
 * \return Returns the initial timer offset in ticks
 */
IFX_EXTERN Ifx_TimerValue IfxGtm_Atom_Timer_getOffset(IfxGtm_Atom_Timer *driver);

/** \brief Returns the pointer to timer channel
 * \param driver ATOM Timer interface Handle
 * \return Pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_Timer_getPointer(IfxGtm_Atom_Timer *driver);

/** \brief Returns the pointer to trigger channel
 * \param driver ATOM Timer interface Handle
 * \return Pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Atom_Timer_getTriggerPointer(IfxGtm_Atom_Timer *driver);

/** \brief Initialises the timer object
 * \param driver ATOM Timer interface Handle
 * \param config Configuration structure for ATOM Timer
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Atom_Timer_init(IfxGtm_Atom_Timer *driver, const IfxGtm_Atom_Timer_Config *config);

/** \brief Initializes the configuration structure to default
 * \param config Configuration structure for ATOM Timer
 * \param gtm Pointer to GTM module
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Timer_initConfig(IfxGtm_Atom_Timer_Config *config, Ifx_GTM *gtm);

/** \} */

#endif /* IFXGTM_ATOM_TIMER_H */
