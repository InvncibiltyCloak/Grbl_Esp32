#pragma once

#include "Motor.h"

namespace Motors {
    class DCMotor : public Motor {
    public:
        DCMotor();
        DCMotor(uint8_t grbl_axis_index, uint8_t spi_axis_index);
        void init();
        void config_message();
        void set_disable(bool disable);
        void step(uint8_t step_mask, uint8_t dir_mask);

    private:
        uint8_t _spi_axis_index;
        uint8_t _axis_index;
        float _p_gain;
        float _i_gain;
        float _d_gain;
        int32_t _step_counter;
    };
}
