#include "led_pwm.h"
#include "fsl_port.h"

void LedPwm_Init() {
    tpm_config_t tpmInfo;
    tpm_chnl_pwm_signal_param_t tpmParam[1];/* = {{
            .chnlNumber = LED_PWM_TPM_CHANNEL,
            .level = kTPM_LowTrue,
            .dutyCyclePercent = 00,
    }};*/

    CLOCK_EnableClock(LED_PWM_CLOCK);
    PORT_SetPinMux(LED_PWM_PORT, LED_PWM_PIN, kPORT_MuxAlt2);

    tpmParam[0].chnlNumber = LED_PWM_TPM_CHANNEL;
    tpmParam[0].level = kTPM_LowTrue;
    tpmParam[0].dutyCyclePercent = 100 - INITIAL_DUTY_CYCLE_PERCENT;
    TPM_GetDefaultConfig(&tpmInfo);

    TPM_Init(LED_PWM_TPM_BASEADDR, &tpmInfo);
    TPM_SetupPwm(LED_PWM_TPM_BASEADDR, tpmParam, sizeof(tpmParam),
                 kTPM_EdgeAlignedPwm, TPM_PWM_FREQUENCY, TPM_SOURCE_CLOCK);
    TPM_StartTimer(LED_PWM_TPM_BASEADDR, kTPM_SystemClock);
//    LedPwm_SetBrightness(INITIAL_DUTY_CYCLE_PERCENT);
}

void LedPwm_SetBrightness(uint8_t brightnessPercent)
{
    TPM_UpdatePwmDutycycle(LED_PWM_TPM_BASEADDR, LED_PWM_TPM_CHANNEL,
            kTPM_EdgeAlignedPwm, 100-brightnessPercent);
}
