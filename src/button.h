#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button {
private:
	uint8_t _pin;
	uint32_t _startPressedTime;
	bool _lastState = BTN_RELEASED;
	bool _stableState = BTN_RELEASED;

public:
	Button(uint8_t pin) { _pin = pin; }

	void begin() {
		pinMode(_pin, INPUT_PULLUP);
	}
	
	bool pressed() {
		bool cur = digitalRead(_pin);
		if (cur != _lastState) {
			_startPressedTime = millis();
			_lastState = cur;
		}
		if (millis() - _startPressedTime >= 50) {
			if (_lastState != _stableState) {
				_stableState = _lastState;
				if (_stableState == BTN_PRESSED) return true;
			}
		}
		return false;
	}
};

#endif // _BUTTON_H_
