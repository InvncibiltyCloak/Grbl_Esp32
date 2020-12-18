/*
    Motor.cpp
    Part of Grbl_ESP32
    2020 -	Marc Jutras
    Grbl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MaslowMotor.h"

namespace Motors {
    MaslowMotor::MaslowMotor() { type_id = MOTOR; }

    void MaslowMotor::init() { _homing_mask = 0; }

    void MaslowMotor::config_message() {}
    void MaslowMotor::debug_message() {}

    void MaslowMotor::read_settings() {
        float max_travel = axis_settings[_axis_index]->max_travel->get();
        float mpos       = axis_settings[_axis_index]->home_mpos->get();

        if (bit_istrue(homing_dir_mask->get(), bit(_axis_index))) {
            _position_min = mpos;
            _position_max = mpos + max_travel;
        } else {
            _position_min = mpos - max_travel;
            _position_max = mpos;
        }
    }

    void MaslowMotor::set_disable(bool disable) {}
    void MaslowMotor::set_direction_pins(uint8_t onMask) {}
    void MaslowMotor::step(uint8_t step_mask, uint8_t dir_mask) {}
    bool MaslowMotor::test() { return true; }  // true = OK
    void MaslowMotor::update() {}
    bool MaslowMotor::can_home() { return _can_home; }

    void MaslowMotor::set_axis_name() { sprintf(_axis_name, "%c%s", report_get_axis_letter(_axis_index), _dual_axis_index ? "2" : " "); }

    void MaslowMotor::set_homing_mode(uint8_t homing_mask, bool isHoming) { _homing_mask = homing_mask; }
}
