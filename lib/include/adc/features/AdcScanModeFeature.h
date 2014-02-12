/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


namespace stm32plus {

  /**
   * This enum determines when the EOC flag is set during scan mode. END_AFTER_EACH_CHANNEL
   * means that EOC gets raised after each channel in the group is converted. So there will
   * be N EOC's for a group containing N channels. END_AFTER_WHOLE_GROUP means that only a
   * single EOC flag will be raised for each group of configured channels. This mode normally
   * implies that you'll be using DMA to move data out to SRAM after each channel is converted.
   */

  enum class AdcScanModeEndType : uint8_t {
    END_AFTER_EACH_CHANNEL,
    END_AFTER_WHOLE_GROUP
  };


  /**
   * Feature class to enable scan-mode. The scan mode end type is a template parameter so
   * that we can generate zero conditional code for the ADC_EOCOnEachRegularChannelCmd parameter.
   * @tparam TEndType The desired condition for raising the EOC flag
   */

  template<AdcScanModeEndType TEndType>
  struct AdcScanModeFeature : AdcFeatureBase {

    AdcScanModeFeature(Adc& adc)
      : AdcFeatureBase(adc) {

      static_assert(
          TEndType==AdcScanModeEndType::END_AFTER_EACH_CHANNEL ||
          TEndType==AdcScanModeEndType::END_AFTER_WHOLE_GROUP,
          "TEndType is not a member of the AdcScanModeEndType enumeration");

      ADC_EOCOnEachRegularChannelCmd(adc,TEndType==AdcScanModeEndType::END_AFTER_EACH_CHANNEL ? ENABLE : DISABLE);
      ((ADC_InitTypeDef *)adc)->ADC_ScanConvMode=ENABLE;
    }
  };
}
