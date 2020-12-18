#include "DCMotor.h"

namespace Motors {
    DCMotor::DCMotor() {}

    DCMotor::DCMotor(uint8_t grbl_axis_index, uint8_t spi_axis_index) {
        type_id                = DC_MOTOR;
        this->_axis_index      = grbl_axis_index % MAX_AXES;
        this->_dual_axis_index = grbl_axis_index < MAX_AXES ? 0 : 1;  // 0 = primary 1 = ganged
        this->spi_axis_index   = spi_axis_index;

        set_axis_name();
        init();
        config_message();
    }

    void DCMotor::init() {
        this->spi_axis_index = 0;
    }

    void DCMotor::config_message() {
        grbl_msg_sendf(CLIENT_SERIAL,
                       MsgLevel::Info,
                       "%s Axis Unipolar Stepper Ph0:%s Ph1:%s Ph2:%s Ph3:%s Limits(%0.3f,%0.3f)",
                       _axis_name,
                       pinName(_pin_phase0).c_str(),
                       pinName(_pin_phase1).c_str(),
                       pinName(_pin_phase2).c_str(),
                       pinName(_pin_phase3).c_str(),
                       _position_min,
                       _position_max);
    }

    void DCMotor::set_disable(bool disable) {
        if (disable) {
            digitalWrite(_pin_phase0, 0);
            digitalWrite(_pin_phase1, 0);
            digitalWrite(_pin_phase2, 0);
            digitalWrite(_pin_phase3, 0);
        }
        _enabled = !disable;
    }

    void DCMotor::step(uint8_t step_mask, uint8_t dir_mask) {
        if (step_mask & _axis_index) {
            if (dir_mask & _axis_index) {
                _step_counter += 1;
            } 
            else {
                _step_counter -= 1;
            }

        }

        
    }
}
